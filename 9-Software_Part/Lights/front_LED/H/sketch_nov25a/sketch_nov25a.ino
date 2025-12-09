#include <FastLED.h>

// LED矩阵配置
#define LED_PIN     6
#define NUM_LEDS    256  // 16x16矩阵
#define BRIGHTNESS  255
#define LED_TYPE   WS2812B
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];

// 32位格式的单帧数据 (0x00RRGGBB 格式)
const uint32_t ledarray81[] PROGMEM = {
  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
  0x00000000, 0x00555555, 0x00555555, 0x00555555, 0x00555555, 0x00555555, 0x00000000, 0x00000000, 0x00000000, 0x00555555, 0x00555555, 0x00555555, 0x00555555, 0x00555555, 0x00555555, 0x00000000, 
  0x00000000, 0x00555555, 0x00000000, 0x00000000, 0x00000000, 0x00555555, 0x00000000, 0x00000000, 0x00000000, 0x00555555, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00555555, 0x00000000, 
  0x00000000, 0x00555555, 0x00000000, 0x00000000, 0x00000000, 0x00555555, 0x00000000, 0x00000000, 0x00000000, 0x00555555, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00555555, 0x00000000, 
  0x00000000, 0x00555555, 0x00000000, 0x00000000, 0x00000000, 0x00555555, 0x00000000, 0x00000000, 0x00000000, 0x00555555, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00555555, 0x00000000, 
  0x00000000, 0x00555555, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00555555, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00555555, 0x00000000, 
  0x00000000, 0x00555555, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00555555, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00555555, 0x00000000, 
  0x00000000, 0x00555555, 0x00000000, 0x00000000, 0x00000000, 0x00555555, 0x00555555, 0x00555555, 0x00555555, 0x00555555, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00555555, 0x00000000, 
  0x00000000, 0x00555555, 0x00000000, 0x00000000, 0x00000000, 0x00555555, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00555555, 0x00000000, 
  0x00000000, 0x00555555, 0x00000000, 0x00000000, 0x00000000, 0x00555555, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00555555, 0x00000000, 
  0x00000000, 0x00555555, 0x00000000, 0x00000000, 0x00000000, 0x00555555, 0x00000000, 0x00000000, 0x00000000, 0x00555555, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00555555, 0x00000000, 
  0x00000000, 0x00555555, 0x00000000, 0x00000000, 0x00000000, 0x00555555, 0x00000000, 0x00000000, 0x00000000, 0x00555555, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00555555, 0x00000000, 
  0x00000000, 0x00555555, 0x00000000, 0x00000000, 0x00000000, 0x00555555, 0x00000000, 0x00000000, 0x00000000, 0x00555555, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00555555, 0x00000000, 
  0x00000000, 0x00555555, 0x00000000, 0x00000000, 0x00000000, 0x00555555, 0x00000000, 0x00000000, 0x00000000, 0x00555555, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00555555, 0x00000000, 
  0x00000000, 0x00555555, 0x00555555, 0x00555555, 0x00555555, 0x00555555, 0x00000000, 0x00000000, 0x00000000, 0x00555555, 0x00555555, 0x00555555, 0x00555555, 0x00555555, 0x00555555, 0x00000000, 
  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
};

void setup() {
  Serial.begin(115200);
  Serial.println("32-bit Frame Display - Simple Layout");
  
  // 初始化FastLED
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  
  // 可选：先测试LED连接
  // testLEDConnection();
  
  // 显示32位格式的单帧
  display32BitFrame();
  
  Serial.println("32-bit frame displayed successfully");
}

void loop() {
  // 空循环，只显示一帧
  delay(1000);
}

void display32BitFrame() {
  // 清除所有LED
  FastLED.clear();
  
  // 逐行处理数据 - 简单行优先顺序
  for (int row = 0; row < 16; row++) {
    for (int col = 0; col < 16; col++) {
      // 计算在数据数组中的位置
      int dataIndex = (row * 16) + col;
      
      // 从PROGMEM读取32位颜色值 (格式: 0x00RRGGBB)
      uint32_t colorData = pgm_read_dword(&(ledarray81[dataIndex]));
      
      // 提取RGB分量
      uint8_t r = (colorData >> 16) & 0xFF;  // 红色分量
      uint8_t g = (colorData >> 8) & 0xFF;   // 绿色分量
      uint8_t b = colorData & 0xFF;          // 蓝色分量
      
      // 计算LED索引 - 简单行优先顺序
      int ledIndex = getLEDIndexSimple(row, col);
      
      // 设置LED颜色
      leds[ledIndex] = CRGB(r, g, b);
    }
  }
  
  FastLED.show();
  
  // 调试输出
  Serial.println("Frame displayed with simple layout");
  Serial.print("Color 0x00555555 = R:");
  Serial.print((0x00555555 >> 16) & 0xFF);
  Serial.print(" G:");
  Serial.print((0x00555555 >> 8) & 0xFF);
  Serial.print(" B:");
  Serial.println(0x00555555 & 0xFF);
}

// 简单行优先顺序布局
int getLEDIndexSimple(int row, int col) {
  // 直接从左到右，从上到下
  return (row * 16) + col;
}

// 测试LED连接和方向
void testLEDConnection() {
  Serial.println("Testing LED connection with simple layout...");
  
  // 清除所有LED
  FastLED.clear();
  FastLED.show();
  delay(500);
  
  // 测试1: 显示网格边框
  for (int row = 0; row < 16; row++) {
    for (int col = 0; col < 16; col++) {
      int index = getLEDIndexSimple(row, col);
      if (row == 0 || row == 15 || col == 0 || col == 15) {
        leds[index] = CRGB::Blue; // 边框为蓝色
      }
    }
  }
  FastLED.show();
  Serial.println("Blue border displayed - check if corners are correct");
  delay(2000);
  
  // 测试2: 显示对角线
  FastLED.clear();
  for (int i = 0; i < 16; i++) {
    int index1 = getLEDIndexSimple(i, i); // 主对角线
    int index2 = getLEDIndexSimple(i, 15-i); // 副对角线
    leds[index1] = CRGB::Red;
    leds[index2] = CRGB::Green;
  }
  FastLED.show();
  Serial.println("Red and Green diagonals displayed");
  delay(2000);
  
  // 清除
  FastLED.clear();
  FastLED.show();
  delay(500);
}