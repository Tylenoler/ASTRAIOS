'''
Author: Tylenoler harperjeffrey0103@gmail.com
Date: 2025-11-27 20:27:45
LastEditTime: 2025-11-27 20:28:17
FilePath: \undefinedc:\Users\yueborui\OneDrive - Kylian\A_ITEM\Personal_Item\ASTRAIOS\9-Software_Part\Lights\front_LED\H\ESP32-S3-Micropython\Config.py
Description: 

Copyright (c) 2025 by ${git_name_email}, All Rights Reserved. 
'''
# config.py
# 灯效参数配置文件

# 播放帧率（建议 10~60）
FPS = 30

# 亮度 0~255，软件级缩放
BRIGHTNESS = 180

# 播放模式：True = 无限循环，False = 播一次停止
LOOP = True

# 是否反向播放（你有些灯条会反接，这个很实用）
REVERSE = False

# 每次播放结束是否暂停（毫秒）
END_PAUSE = 500
