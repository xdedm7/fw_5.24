#include  "ws2812.hpp"


NeoPixelBrightnessBus<NeoGrbFeature, Neo800KbpsMethod> LED_livingroom_bright(LED_COUNT, LED_Pin);
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> LED_livingroom(LED_COUNT, LED_Pin);//����1
void WS2812_init(void)
{
    //��ʼ������
    LED_livingroom.Begin();
    LED_livingroom_bright.Begin();
}
