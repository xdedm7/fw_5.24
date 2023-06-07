#ifndef _WS2812_H_
#define _WS2812_H_
#include "NeoPixelBus.h"
#include "NeoPixelBrightnessBus.h"
void WS2812_init(void);
#define LED_NUM 6



#define set_LED_RGB "data=LIGHT_SET_COLOR_000_000_000_0"//���õ��ݵ�RGBɫ�� R-G-B-id
#define set_LED_ON "data=LIGHT_SWITCH_ON_0"//����ĳ�������� id
#define set_LED_OFF "data=LIGHT_SWITCH_OFF_0"//����ĳ�������� id
#define set_LED_bright "data=LIGHT_SET_INTENSITY_00_0"//���õ��ݵ����� bright_id

#define set_LED_ON_ALL "data=LIGHT_SWITCH_ALL_ON"//���з���LEDȫ��
#define set_LED_OFF_ALL "data=LIGHT_SWITCH_ALL_OFF"//���з���LEDȫ��


// RgbColor red(colorSaturation, 0, 0);
// RgbColor green(0, colorSaturation, 0);
// RgbColor blue(0, 0, colorSaturation);
// RgbColor white(colorSaturation);
// RgbColor black(0);
// RgbColor num1(0.8 * colorSaturation  , 0, 0.2 * colorSaturation);
// RgbColor num2(0.5 * colorSaturation, 0, 0.5 * colorSaturation);
// RgbColor num3(0.25 * colorSaturation, 0, 0.75 * colorSaturation);
#define LED_COUNT 6//��������
#define LED_Pin  21
#define LED2_Pin  5
#define LED3_Pin  12
#define LED4_Pin  13


#endif