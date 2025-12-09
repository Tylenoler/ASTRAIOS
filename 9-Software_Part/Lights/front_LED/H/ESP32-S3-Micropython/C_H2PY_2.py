# new_preprocess.py - 重新编写的头文件提取程序
# -*- coding: utf-8 -*-
import re
import struct
import sys


def extract_frames_from_header(header_file, output_file):
    """从头文件中提取帧数据"""

    print(f"正在处理头文件: {header_file}")

    # 尝试不同的编码
    encodings = ['utf-8', 'gbk', 'latin-1', 'cp1252']
    content = None

    for encoding in encodings:
        try:
            with open(header_file, 'r', encoding=encoding) as f:
                content = f.read()
            print(f"成功使用编码: {encoding}")
            break
        except UnicodeDecodeError:
            continue

    if content is None:
        print("无法使用文本模式读取，尝试二进制模式")
        with open(header_file, 'rb') as f:
            content_bytes = f.read()
            # 尝试用latin-1解码（不会失败）
            content = content_bytes.decode('latin-1')

    # 查找所有帧数据
    frame_pattern = r'const uint32_t ledarray\d+\[\] PROGMEM = \{([^}]+)\}'
    frames = re.findall(frame_pattern, content, re.DOTALL)

    print(f"找到 {len(frames)} 个动画帧")

    if len(frames) == 0:
        print("未找到任何帧数据")
        return False

    # 创建二进制输出文件
    with open(output_file, 'wb') as f:
        # 写入帧数
        f.write(struct.pack('H', len(frames)))

        # 处理每一帧
        for frame_idx, frame_data in enumerate(frames):
            print(f"处理第 {frame_idx} 帧...")

            # 提取所有十六进制颜色值
            hex_values = re.findall(r'0x[0-9A-Fa-f]{6}', frame_data)

            # 检查数据完整性
            if len(hex_values) != 256:
                print(f"警告: 第 {frame_idx} 帧只有 {len(hex_values)} 个值，期望256")
                # 用黑色填充缺失的值
                while len(hex_values) < 256:
                    hex_values.append('0x000000')
                hex_values = hex_values[:256]  # 确保不超过256

            # 处理每个像素
            for hex_val in hex_values:
                try:
                    # 解析32位颜色值 (格式: 0x00GGRRBB)
                    color_32bit = int(hex_val, 16)

                    # 提取颜色分量
                    g = (color_32bit >> 16) & 0xFF  # 绿色
                    r = (color_32bit >> 8) & 0xFF  # 红色
                    b = color_32bit & 0xFF  # 蓝色

                    # 直接存储RGB888值 (3字节)
                    f.write(struct.pack('BBB', r, g, b))

                except ValueError as e:
                    print(f"转换颜色值失败: {hex_val}, 错误: {e}")
                    # 使用黑色作为默认值
                    f.write(struct.pack('BBB', 0, 0, 0))

            print(f"完成第 {frame_idx} 帧")

    print(f"成功提取 {len(frames)} 帧到 {output_file}")
    return True


def create_simple_test_animation(output_file):
    """创建简单的测试动画"""
    print("创建测试动画...")

    with open(output_file, 'wb') as f:
        # 写入帧数 (4帧)
        f.write(struct.pack('H', 4))

        # 定义4种颜色的H图案
        colors = [
            (85, 85, 85),  # 白色
            (85, 0, 0),  # 红色
            (0, 85, 0),  # 绿色
            (0, 0, 85),  # 蓝色
        ]

        for frame_idx, color in enumerate(colors):
            print(f"创建第 {frame_idx} 帧")

            for row in range(16):
                for col in range(16):
                    # 检查是否是H图案的一部分
                    is_h = (
                            (col == 4 or col == 11) or  # 竖线
                            (row == 7 and 4 <= col <= 11)  # 横线
                    )

                    if is_h:
                        r, g, b = color
                    else:
                        r, g, b = (0, 0, 0)

                    # 直接写入RGB值
                    f.write(struct.pack('BBB', r, g, b))

            print(f"完成第 {frame_idx} 帧")

    print(f"创建了测试动画: {output_file}")


if __name__ == "__main__":
    if len(sys.argv) > 1:
        header_file = sys.argv[1]
    else:
        header_file = "H_Logo_32bits_converted.h"

    output_file = "new_animation.bin"

    # 尝试提取头文件
    success = extract_frames_from_header(header_file, output_file)

    if not success:
        print("从头文件提取失败，创建测试动画")
        create_simple_test_animation(output_file)

    print("处理完成!")