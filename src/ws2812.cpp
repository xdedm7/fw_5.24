#include  "ws2812.hpp"


NeoPixelBrightnessBus<NeoGrbFeature, Neo800KbpsMethod> LED_livingroom_bright(LED_COUNT, LED_Pin);
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> LED_livingroom(LED_COUNT, LED_Pin);//µ∆÷È1
void WS2812_init(void)
{
    //≥ı ºªØµ∆≈›
    LED_livingroom.Begin();
    LED_livingroom_bright.Begin();
}
