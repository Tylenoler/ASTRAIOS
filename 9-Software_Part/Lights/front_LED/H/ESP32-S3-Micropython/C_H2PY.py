# -*- coding: utf-8 -*-
# preprocess.py - 在电脑上运行这个脚本来预处理头文件
import re
import struct
import sys


def detect_encoding(file_path):
    """检测文件编码"""
    encodings = ['utf-8', 'gbk', 'gb2312', 'latin-1', 'cp1252']

    for encoding in encodings:
        try:
            with open(file_path, 'r', encoding=encoding) as f:
                f.read()
            return encoding
        except UnicodeDecodeError:
            continue

    return None


def convert_header_to_binary(header_file, output_file):
    """将头文件转换为紧凑的二进制格式"""

    # 检测文件编码
    encoding = detect_encoding(header_file)
    if encoding is None:
        print("无法确定文件编码，尝试使用UTF-8")
        encoding = 'utf-8'

    print(f"使用编码: {encoding}")

    try:
        with open(header_file, 'r', encoding=encoding) as f:
            content = f.read()
    except Exception as e:
        print(f"读取文件失败: {e}")
        # 尝试二进制方式读取
        with open(header_file, 'rb') as f:
            content_bytes = f.read()
            # 尝试解码为文本
            try:
                content = content_bytes.decode('utf-8')
            except:
                try:
                    content = content_bytes.decode('gbk')
                except:
                    print("无法解码文件内容，尝试直接处理二进制")
                    content = content_bytes.decode('latin-1')  # 最后的手段

    # 找到所有帧
    pattern = r'const uint32_t ledarray\d+\[\] PROGMEM = \{([^}]+)\}'
    matches = re.findall(pattern, content, re.DOTALL)

    print(f"找到 {len(matches)} 帧")

    if len(matches) == 0:
        print("未找到任何帧数据，检查文件格式")
        return

    with open(output_file, 'wb') as f:
        # 写入帧数
        f.write(struct.pack('H', len(matches)))

        for i, match in enumerate(matches):
            hex_values = re.findall(r'0x[0-9A-Fa-f]+', match)

            if len(hex_values) != 256:
                print(f"帧 {i} 数据不完整，期望256个值，找到{len(hex_values)}个")
                # 用黑色填充缺失的像素
                while len(hex_values) < 256:
                    hex_values.append('0x00000000')
                hex_values = hex_values[:256]  # 确保不超过256

            # 将32位GRB转换为16位RGB565（更紧凑）
            for hex_val in hex_values:
                try:
                    color_32bit = int(hex_val, 16)
                    g = (color_32bit >> 16) & 0xFF
                    r = (color_32bit >> 8) & 0xFF
                    b = color_32bit & 0xFF

                    # 转换为RGB565
                    r5 = (r * 31) // 255
                    g6 = (g * 63) // 255
                    b5 = (b * 31) // 255
                    rgb565 = (r5 << 11) | (g6 << 5) | b5

                    f.write(struct.pack('H', rgb565))
                except ValueError as e:
                    print(f"转换颜色值失败: {hex_val}, 错误: {e}")
                    # 使用黑色作为默认值
                    f.write(struct.pack('H', 0))

            print(f"处理完第 {i} 帧")


def create_simple_h_animation(output_file):
    """创建一个简单的H图案动画，用于测试"""
    print("创建简单的H图案动画...")

    with open(output_file, 'wb') as f:
        # 写入帧数 (4帧)
        f.write(struct.pack('H', 4))

        # 定义4种颜色的H图案
        colors = [
            (100, 100, 100),  # 白色
            (100, 0, 0),  # 红色
            (0, 100, 0),  # 绿色
            (0, 0, 100),  # 蓝色
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

                    # 转换为RGB565
                    r5 = (r * 31) // 255
                    g6 = (g * 63) // 255
                    b5 = (b * 31) // 255
                    rgb565 = (r5 << 11) | (g6 << 5) | b5

                    f.write(struct.pack('H', rgb565))

            print(f"完成第 {frame_idx} 帧")


if __name__ == "__main__":
    if len(sys.argv) > 1:
        header_file = sys.argv[1]
    else:
        header_file = "H_Logo_32bits.h"

    output_file = "animation.bin"

    try:
        convert_header_to_binary(header_file, output_file)
        print(f"转换完成！将 {output_file} 上传到ESP32")
    except Exception as e:
        print(f"转换失败: {e}")
        print("创建简单的H图案动画作为替代...")
        create_simple_h_animation(output_file)
        print(f"创建了简单的动画文件: {output_file}")