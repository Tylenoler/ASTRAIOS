import re
import struct

h_file = "L_32BITS_converted.h"
bin_file = "animation.bin"

frame_size = 16  # 灯珠数

# 读取 H 文件内容
with open(h_file, "r") as f:
    text = f.read()

# 提取所有 0x???????? 数字
raw_values = re.findall(r"0x([0-9A-Fa-f]{6})", text)

print("Found LED values:", len(raw_values))

# 构建 bin 文件
with open(bin_file, "wb") as bf:
    for hex_val in raw_values:
        # 解析 0xRRGGBB
        color = int(hex_val, 16)
        r = (color >> 16) & 0xFF
        g = (color >> 8) & 0xFF
        b = (color >> 0) & 0xFF

        # 写入 GRB 顺序
        bf.write(bytes([g, r, b]))

print("Output:", bin_file)
print("Done.")
