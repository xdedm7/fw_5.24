#include "voice.hpp"

int voice_code=0;
extern uint8_t LED_breight;
extern uint8_t AIR_temp_1;
extern NeoPixelBrightnessBus<NeoGrbFeature, Neo800KbpsMethod> LED_livingroom_bright;
extern IRGreeAC irtrans;
void Voice_Receive_Data(char *voice)//接收语音模块传过来的数据
{
    int i;
    if(voice[0]=0x13&&voice[2]==0x5C&&voice[3]==0x4b)
    {
        //Serial.print(voice[1]);
        voice_code=voice[1];
        switch(voice_code)
        {
            case 0x01||0x0e://打开灯1
            {
                LED_livingroom_bright.SetPixelColor(0,RgbColor(255,255,255));
                LED_livingroom_bright.Show();
                break;
            }
            case 0x02://关闭灯1
            {
                LED_livingroom_bright.SetPixelColor(0,RgbColor(0,0,0));
                LED_livingroom_bright.Show();
                break;
            }
            case 0x03://打开灯2
            {
                LED_livingroom_bright.SetPixelColor(1,RgbColor(255,255,255));
                LED_livingroom_bright.Show();
                break;
            }
            case 0x04://关闭灯2
            {
                LED_livingroom_bright.SetPixelColor(1,RgbColor(0,0,0));
                LED_livingroom_bright.Show();
                break;
            }
            case 0x05://打开灯3
            {
                LED_livingroom_bright.SetPixelColor(2,RgbColor(255,255,255));
                LED_livingroom_bright.Show();
                break;
            }
            case 0x06://关闭灯3
            {
                LED_livingroom_bright.SetPixelColor(2,RgbColor(0,0,0));
                LED_livingroom_bright.Show();
                break;
            }
            case 0x07://打开灯4
             {   
                LED_livingroom_bright.SetPixelColor(3,RgbColor(255,255,255));
                LED_livingroom_bright.Show();
                break;
            }
            case 0x08://关闭灯4
            {
                LED_livingroom_bright.SetPixelColor(3,RgbColor(0,0,0));
                LED_livingroom_bright.Show();
                break;
            }
            case 0x09://打开所有灯
            {
                for(i=0;i<LED_COUNT;i++)
                {
                    LED_livingroom_bright.SetPixelColor(i,RgbColor(255,255,255));
                    LED_livingroom_bright.Show();
                }
                break;
            }
            case 0x0a://关闭所有灯
            {
                for(i=0;i<LED_COUNT;i++)
                {
                    LED_livingroom_bright.SetPixelColor(i,RgbColor(0,0,0));
                    LED_livingroom_bright.Show();
                }
                break;
            }
            case 0x0b://开窗
            {
                delay(1000);
                stepper_motor_turn(ON_WINDOW);
                break;
            }
            case 0x0c:
            {
                delay(1000);
                stepper_motor_turn(OFF_WINDOW);
                break;
            }
            case 0x0d://关灯关窗
            {
                delay(1000);
                stepper_motor_turn(OFF_WINDOW);
                delay(1000);
                for(i=0;i<LED_COUNT;i++)
                {
                    LED_livingroom_bright.SetPixelColor(i,RgbColor(0,0,0));
                    LED_livingroom_bright.Show();
                }
                break;
            }
            case 0x11://灯亮度+
            {
                LED_breight+=20;
                LED_breight=range(LED_breight,1,99);
                LED_livingroom_bright.SetBrightness(LED_breight);
                LED_livingroom_bright.Show();
                break;
            }
            case 0x12://灯亮度-
            {
                LED_breight-=20;
                LED_breight=range(LED_breight,1,99);
                LED_livingroom_bright.SetBrightness(LED_breight);
                LED_livingroom_bright.Show();
                break;
            }   
            case 0x21://打开空调
            {
                irtrans.on();//生成空调“开”的红外码
                Serial.println(irtrans.toString());//显示发送的空调开机红外编码
                irtrans.send();//发送红外命令
                break;
            }
            case 0x22://关闭空调
            {
                irtrans.off();//生成空调“开”的红外码
                Serial.println(irtrans.toString());//显示发送的空调开机红外编码
                irtrans.send();//发送红外命令
                break;
            }
            case 0x23://除湿
            {   
                irtrans.setMode(kGreeDry);
                Serial.println(irtrans.toString());
                irtrans.send();
                break;
            }
            case 0x24://制冷
            {
                irtrans.setMode(kGreeCool);
                Serial.println(irtrans.toString());
                irtrans.send();
                break;
            }
            case 0x25://制热
            {
                irtrans.setMode(kGreeHeat);
                Serial.println(irtrans.toString());
                irtrans.send();
                break;
            }
            case 0x26://节能
            {
                irtrans.setMode(kGreeEcono);
                Serial.println(irtrans.toString());
                irtrans.send();
                break;
            }
            case 0x27://自动
            {
                irtrans.setMode(kGreeAuto);
                Serial.println(irtrans.toString());
                irtrans.send();
                break;
            }
            case 0x28://空调温度++
            {
                AIR_temp_1+=2;
                AIR_temp_1=range(AIR_temp_1,16,30);
                irtrans.setTemp(AIR_temp_1);
                Serial.println(irtrans.toString());
                irtrans.send();
                break;
            }
            case 0x29://空调温度--
            {
                AIR_temp_1-=2;
                AIR_temp_1=range(AIR_temp_1,16,30);
                irtrans.setTemp(AIR_temp_1);
                Serial.println(irtrans.toString());
                irtrans.send();
                break;
            }
            case 0x31://空调16
            {
                irtrans.setTemp(16);
                Serial.println(irtrans.toString());
                irtrans.send();
                break;
            }
            case 0x32://空调17
            {
                irtrans.setTemp(17);
                Serial.println(irtrans.toString());
                irtrans.send();
                break;
            }
            case 0x33://空调18
            {
                irtrans.setTemp(18);
                Serial.println(irtrans.toString());
                irtrans.send();
                break;
            }
            case 0x34://空调19
            {
                irtrans.setTemp(19);
                Serial.println(irtrans.toString());
                irtrans.send();
                break;
            }
            case 0x35://空调20
            {
                irtrans.setTemp(20);
                Serial.println(irtrans.toString());
                irtrans.send();
                break;
            }
            case 0x36://空调21
            {
                irtrans.setTemp(21);
                Serial.println(irtrans.toString());
                irtrans.send();
                break;
            }
            case 0x37://空调22
            {
                irtrans.setTemp(22);
                Serial.println(irtrans.toString());
                irtrans.send();
                break;
            }
            case 0x38://空调23
            {
                irtrans.setTemp(23);
                Serial.println(irtrans.toString());
                irtrans.send();
                break;
            }
            case 0x39://空调24
            {
                irtrans.setTemp(24);
                Serial.println(irtrans.toString());
                irtrans.send();
                break;
            }
            case 0x3a://空调25
            {
                irtrans.setTemp(25);
                Serial.println(irtrans.toString());
                irtrans.send();
                break;
            }
            case 0x3b://空调26
            {
                irtrans.setTemp(26);
                Serial.println(irtrans.toString());
                irtrans.send();
                break;
            }
            case 0x3c://空调27
            {
                irtrans.setTemp(27);
                Serial.println(irtrans.toString());
                irtrans.send();
                break;
            }
            case 0x3d://空调28
            {
                irtrans.setTemp(28);
                Serial.println(irtrans.toString());
                irtrans.send();
                break;
            }
            case 0x3e://空调29
            {
                irtrans.setTemp(29);
                Serial.println(irtrans.toString());
                irtrans.send();
                break;
            }
            case 0x3f://空调30
            {
                irtrans.setTemp(30);
                Serial.println(irtrans.toString());
                irtrans.send();
                break;
            }
        }
    }
    for(i=0;voice[i]!='\0';i++)
    {
        voice[i]=0;

    }
}
extern SoftwareSerial yunyin;
void Voice_Sends(void)
{
    char v1=0x12;
    char v2=0x01;
    char v3=0x4C;
    char v4=0x5B;
    Serial2.printf("%c%c%c%c",v1,v2,v3,v4);
}
char voice[10]={0};
void Voice_serial_callback() 
{
    while(yunyin.available()) 
    {
         yunyin.readBytes(voice, sizeof(voice));
         //Voice_Receive_Data(voice);
    }
    Serial1.print(voice);
    Voice_Receive_Data(voice);
}