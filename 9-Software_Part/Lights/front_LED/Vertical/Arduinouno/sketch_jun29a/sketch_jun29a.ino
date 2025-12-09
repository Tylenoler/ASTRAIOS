#include <FastLED.h>

// ===== 可配置参数 =====
#define LED_PIN     6     // LED数据引脚
#define NUM_LEDS    16    // LED数量（根据你的灯带修改）
#define LED_TYPE    WS2812B // LED型号
#define COLOR_ORDER GRB   // 颜色顺序
#define BRIGHTNESS  255   // 初始亮度(0-255)
#define SPEEDTIME   50
#define LightFactor1 128
#define LightFactor2 250

CRGB leds[NUM_LEDS];      // LED数组

// ===== 帧动画系统 =====
// 定义帧结构（存储在PROGMEM中以节省内存）
struct AnimationFrame {
  const uint32_t* data;   // 帧数据指针
  uint16_t length;        // 帧数据长度
  uint16_t delayMs;       // 帧显示时间(毫秒)
  uint8_t brightnessFactor; // 帧亮度因子(0.0-1.0)
};

// === 帧数据定义 - 保持你原始的名称 ===
const uint32_t ledarray0[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
};

const uint32_t ledarray1[] PROGMEM = {
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
};

const uint32_t ledarray2[] PROGMEM = {
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
};

const uint32_t ledarray3[] PROGMEM = {
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
};

const uint32_t ledarray4[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
};

const uint32_t ledarray5[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
};

const uint32_t ledarray6[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
};

const uint32_t ledarray7[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
};

const uint32_t ledarray8[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
};

const uint32_t ledarray9[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
};

const uint32_t ledarray10[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
};

const uint32_t ledarray11[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
};

const uint32_t ledarray12[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
};

const uint32_t ledarray13[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
};

const uint32_t ledarray14[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
};

const uint32_t ledarray15[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
};

const uint32_t ledarray16[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
};

const uint32_t ledarray17[] PROGMEM = {
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
};

const uint32_t ledarray18[] PROGMEM = {
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
};

const uint32_t ledarray19[] PROGMEM = {
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
};

const uint32_t ledarray20[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
};

const uint32_t ledarray21[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
};

const uint32_t ledarray22[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
};

const uint32_t ledarray23[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
};

const uint32_t ledarray24[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
};

const uint32_t ledarray25[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
};

const uint32_t ledarray26[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
};

const uint32_t ledarray27[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
};

const uint32_t ledarray28[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
};

const uint32_t ledarray29[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0xFFFFFF, 
};

const uint32_t ledarray30[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0xFFFFFF, 
};

const uint32_t ledarray31[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray32[] PROGMEM = {
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray33[] PROGMEM = {
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray34[] PROGMEM = {
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray35[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray36[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray37[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray38[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray39[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray40[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray41[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray42[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray43[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray44[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray45[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray46[] PROGMEM = {
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray47[] PROGMEM = {
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray48[] PROGMEM = {
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray49[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray50[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray51[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray52[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray53[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray54[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray55[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray56[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray57[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray58[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray59[] PROGMEM = {
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray60[] PROGMEM = {
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray61[] PROGMEM = {
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray62[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray63[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray64[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray65[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray66[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray67[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray68[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray69[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray70[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray71[] PROGMEM = {
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray72[] PROGMEM = {
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray73[] PROGMEM = {
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray74[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray75[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray76[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray77[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray78[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray79[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray80[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray81[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray82[] PROGMEM = {
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray83[] PROGMEM = {
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray84[] PROGMEM = {
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray85[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray86[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray87[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray88[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray89[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray90[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray91[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray92[] PROGMEM = {
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray93[] PROGMEM = {
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray94[] PROGMEM = {
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray95[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray96[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray97[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray98[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray99[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray100[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray101[] PROGMEM = {
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray102[] PROGMEM = {
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray103[] PROGMEM = {
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray104[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray105[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray106[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray107[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray108[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray109[] PROGMEM = {
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray110[] PROGMEM = {
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray111[] PROGMEM = {
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray112[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray113[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray114[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray115[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray116[] PROGMEM = {
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray117[] PROGMEM = {
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray118[] PROGMEM = {
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray119[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray120[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray121[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray122[] PROGMEM = {
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray123[] PROGMEM = {
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray124[] PROGMEM = {
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray125[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray126[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray127[] PROGMEM = {
0xFFFFFF, 
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray128[] PROGMEM = {
0x000000, 
0xFFFFFF, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray129[] PROGMEM = {
0x000000, 
0x000000, 
0xFFFFFF, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray130[] PROGMEM = {
0x000000, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray131[] PROGMEM = {
0xFFFFFF, 
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray132[] PROGMEM = {
0x000000, 
0xFFFFFF, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray133[] PROGMEM = {
0x000000, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray134[] PROGMEM = {
0xFFFFFF, 
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray135[] PROGMEM = {
0x000000, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray136[] PROGMEM = {
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};

const uint32_t ledarray137[] PROGMEM = {
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
0xFFFFFF, 
};


// 帧序列（在这里添加所有帧）
AnimationFrame frames[] = {
  { ledarray0, sizeof(ledarray0)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },  // 第0帧，显示500ms
  { ledarray1, sizeof(ledarray1)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },  // 第1帧
  { ledarray2, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray3, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray4, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray5, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray6, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray7, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray8, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray9, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray10, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray11, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray12, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray13, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray14, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray15, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray16, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray17, sizeof(ledarray0)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },  // 第0帧，显示500ms
  { ledarray18, sizeof(ledarray1)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },  // 第1帧
  { ledarray19, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray20, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray21, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray22, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray23, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray24, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray25, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray26, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray27, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray28, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray29, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray30, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray31, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray32, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray33, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },  
  { ledarray34, sizeof(ledarray0)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },  // 第0帧，显示500ms
  { ledarray35, sizeof(ledarray1)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },  // 第1帧
  { ledarray36, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray37, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray38, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray39, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray40, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray41, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray42, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray43, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray44, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray45, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray46, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray47, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray48, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray49, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray50, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray51, sizeof(ledarray0)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },  // 第0帧，显示500ms
  { ledarray52, sizeof(ledarray1)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },  // 第1帧
  { ledarray53, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray54, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray55, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray56, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray57, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray58, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray59, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray60, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray61, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray62, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray63, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray64, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray65, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray66, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray67, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray68, sizeof(ledarray0)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },  // 第0帧，显示500ms
  { ledarray69, sizeof(ledarray1)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },  // 第1帧
  { ledarray70, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray71, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray72, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray73, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray74, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray75, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray76, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray77, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray78, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray79, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray80, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray81, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray82, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray83, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray84, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray85, sizeof(ledarray0)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },  // 第0帧，显示500ms
  { ledarray86, sizeof(ledarray1)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },  // 第1帧
  { ledarray87, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray88, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray89, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray90, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray91, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray92, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray93, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray94, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray95, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray96, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray97, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray98, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray99, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray100, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray101, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray102, sizeof(ledarray0)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },  // 第0帧，显示500ms
  { ledarray103, sizeof(ledarray1)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },  // 第1帧
  { ledarray104, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray105, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray106, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray107, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray108, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray109, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray110, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray111, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray112, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray113, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray114, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray115, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray116, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray117, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray118, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray119, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray120, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME , LightFactor1},
  { ledarray121, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray122, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray123, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray124, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray125, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray126, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray127, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray128, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },
  { ledarray129, sizeof(ledarray0)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },  // 第0帧，显示500ms
  { ledarray130, sizeof(ledarray1)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },  // 第1帧
  { ledarray131, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray132, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray133, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray134, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray135, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray136, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor1 },   // 第2帧
  { ledarray137, sizeof(ledarray2)/sizeof(uint32_t), SPEEDTIME, LightFactor2 },
  // 添加更多帧...
};

const uint8_t FRAME_COUNT = sizeof(frames)/sizeof(AnimationFrame); // 总帧数

// 动画模式
enum AnimationMode {
  FRAME_ANIMATION,        // 帧动画模式
  SOLID_COLOR             // 其他模式...
};

AnimationMode currentMode = FRAME_ANIMATION; // 默认模式
CRGB solidColor = CRGB::Blue;        // 单色模式的默认颜色

// 帧动画变量
uint8_t currentFrame = 0;            // 当前帧索引
unsigned long lastFrameTime = 0;     // 上次帧切换时间
bool playOnce = true;     // 是否只播放一次
bool isPlaying = true;    // 当前是否正在播放

// ===== 辅助函数 =====
void setAll(CRGB color) {
  fill_solid(leds, NUM_LEDS, color);
}

// 从PROGMEM加载帧数据到LED
void loadFrame(uint8_t frameIndex) {
  if (frameIndex >= FRAME_COUNT) return;
  
  AnimationFrame frame = frames[frameIndex];
  
  // 确保帧数据长度不超过LED数量
  uint16_t ledCount = min(frame.length, (uint16_t)NUM_LEDS);
  
  for (uint16_t i = 0; i < ledCount; i++) {
    // 从PROGMEM读取32位颜色值
    uint32_t colorData = pgm_read_dword(&(frame.data[i]));
    
    // 提取RGB分量
    uint8_t r = (colorData >> 16) & 0xFF;
    uint8_t g = (colorData >> 8)  & 0xFF;
    uint8_t b = colorData        & 0xFF;
    
    // 应用帧的亮度因子 - 关键修复！
    r = (uint16_t)r * frame.brightnessFactor / 255;
    g = (uint16_t)g * frame.brightnessFactor / 255;
    b = (uint16_t)b * frame.brightnessFactor / 255;
    
    leds[i] = CRGB(r, g, b);
  }
  
  // 如果帧数据少于LED数量，剩余LED设为黑色
  for (uint16_t i = ledCount; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
}

// 帧动画函数
void frameAnimation() {
  // 如果不在播放状态，直接返回
  if (!isPlaying) return;
  
  // 检查是否到了切换帧的时间
  if (millis() - lastFrameTime >= frames[currentFrame].delayMs) {
    // 如果是最后一帧且设置为只播放一次
    if (playOnce && currentFrame == FRAME_COUNT - 1) {
      isPlaying = false; // 停止播放
      Serial.println("动画播放完成，停止在最后一帧");
      return;
    }
    
    // 切换到下一帧
    currentFrame = (currentFrame + 1) % FRAME_COUNT;
    loadFrame(currentFrame);
    lastFrameTime = millis();
    FastLED.show();
  }
}

// ===== 主程序 =====
void setup() {
  Serial.begin(115200);
  Serial.println("FastLED 帧动画系统启动");
  
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  
  // 初始化并显示第一帧
  loadFrame(0);
  FastLED.show();
  lastFrameTime = millis();

}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();
    handleCommand(command);
  }
  
  switch(currentMode) {
    case FRAME_ANIMATION:
      frameAnimation();
      break;
    case SOLID_COLOR:
      setAll(solidColor);
      FastLED.show();
      break;
  }
}

//处理串口命令
void handleCommand(char cmd) {
  switch(cmd) {
    case '0':
      currentMode = SOLID_COLOR;
      Serial.println("模式: 单色");
      break;
      
    case '6': // 帧动画模式
      currentMode = FRAME_ANIMATION;
      Serial.println("模式: 帧动画");
      currentFrame = 0;
      isPlaying = true;
      loadFrame(currentFrame);
      FastLED.show();
      lastFrameTime = millis();
      break;
      
    case 'r': // 重置并重新播放
      currentFrame = 0;
      isPlaying = true;
      loadFrame(currentFrame);
      FastLED.show();
      lastFrameTime = millis();
      Serial.println("重置并重新播放动画");
      break;
      
    case 'p': // 暂停/继续
      isPlaying = !isPlaying;
      Serial.print("播放状态: ");
      Serial.println(isPlaying ? "继续" : "暂停");
      break;
      
    case 'o': // 切换播放模式
      playOnce = !playOnce;
      Serial.print("播放模式: ");
      Serial.println(playOnce ? "单次播放" : "循环播放");
      break;
      
    case 'f': // 跳转帧
      while(!Serial.available());
      int frame = Serial.parseInt();
      if (frame >= 0 && frame < FRAME_COUNT) {
        currentFrame = frame;
        isPlaying = true; // 跳转时自动继续播放
        loadFrame(currentFrame);
        FastLED.show();
        lastFrameTime = millis();
        Serial.print("跳转到帧: ");
        Serial.println(frame);
      }
      break;
      
    case 'b': // 设置亮度
      while(!Serial.available());
      int brightness = Serial.parseInt();
      FastLED.setBrightness(constrain(brightness, 0, 255));
      Serial.print("亮度设置为: ");
      Serial.println(brightness);
      FastLED.show();
      break;
      
    default:
      Serial.println("未知命令");
      break;
  }
}