#include "voice.hpp"

int voice_code=0;
extern uint8_t LED_breight;
extern uint8_t AIR_temp_1;
extern NeoPixelBrightnessBus<NeoGrbFeature, Neo800KbpsMethod> LED_livingroom_bright;
extern IRGreeAC irtrans;
void Voice_Receive_Data(char *voice)//��������ģ�鴫����������
{
    int i;
    if(voice[0]=0x13&&voice[2]==0x5C&&voice[3]==0x4b)
    {
        //Serial.print(voice[1]);
        voice_code=voice[1];
        switch(voice_code)
        {
            case 0x01||0x0e://�򿪵�1
            {
                LED_livingroom_bright.SetPixelColor(0,RgbColor(255,255,255));
                LED_livingroom_bright.Show();
                break;
            }
            case 0x02://�رյ�1
            {
                LED_livingroom_bright.SetPixelColor(0,RgbColor(0,0,0));
                LED_livingroom_bright.Show();
                break;
            }
            case 0x03://�򿪵�2
            {
                LED_livingroom_bright.SetPixelColor(1,RgbColor(255,255,255));
                LED_livingroom_bright.Show();
                break;
            }
            case 0x04://�رյ�2
            {
                LED_livingroom_bright.SetPixelColor(1,RgbColor(0,0,0));
                LED_livingroom_bright.Show();
                break;
            }
            case 0x05://�򿪵�3
            {
                LED_livingroom_bright.SetPixelColor(2,RgbColor(255,255,255));
                LED_livingroom_bright.Show();
                break;
            }
            case 0x06://�رյ�3
            {
                LED_livingroom_bright.SetPixelColor(2,RgbColor(0,0,0));
                LED_livingroom_bright.Show();
                break;
            }
            case 0x07://�򿪵�4
             {   
                LED_livingroom_bright.SetPixelColor(3,RgbColor(255,255,255));
                LED_livingroom_bright.Show();
                break;
            }
            case 0x08://�رյ�4
            {
                LED_livingroom_bright.SetPixelColor(3,RgbColor(0,0,0));
                LED_livingroom_bright.Show();
                break;
            }
            case 0x09://�����е�
            {
                for(i=0;i<LED_COUNT;i++)
                {
                    LED_livingroom_bright.SetPixelColor(i,RgbColor(255,255,255));
                    LED_livingroom_bright.Show();
                }
                break;
            }
            case 0x0a://�ر����е�
            {
                for(i=0;i<LED_COUNT;i++)
                {
                    LED_livingroom_bright.SetPixelColor(i,RgbColor(0,0,0));
                    LED_livingroom_bright.Show();
                }
                break;
            }
            case 0x0b://����
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
            case 0x0d://�صƹش�
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
            case 0x11://������+
            {
                LED_breight+=20;
                LED_breight=range(LED_breight,1,99);
                LED_livingroom_bright.SetBrightness(LED_breight);
                LED_livingroom_bright.Show();
                break;
            }
            case 0x12://������-
            {
                LED_breight-=20;
                LED_breight=range(LED_breight,1,99);
                LED_livingroom_bright.SetBrightness(LED_breight);
                LED_livingroom_bright.Show();
                break;
            }   
            case 0x21://�򿪿յ�
            {
                irtrans.on();//���ɿյ��������ĺ�����
                Serial.println(irtrans.toString());//��ʾ���͵Ŀյ������������
                irtrans.send();//���ͺ�������
                break;
            }
            case 0x22://�رտյ�
            {
                irtrans.off();//���ɿյ��������ĺ�����
                Serial.println(irtrans.toString());//��ʾ���͵Ŀյ������������
                irtrans.send();//���ͺ�������
                break;
            }
            case 0x23://��ʪ
            {   
                irtrans.setMode(kGreeDry);
                Serial.println(irtrans.toString());
                irtrans.send();
                break;
            }
            case 0x24://����
            {
                irtrans.setMode(kGreeCool);
                Serial.println(irtrans.toString());
                irtrans.send();
                break;
            }
            case 0x25://����
            {
                irtrans.setMode(kGreeHeat);
                Serial.println(irtrans.toString());
                irtrans.send();
                break;
            }
            case 0x26://����
            {
                irtrans.setMode(kGreeEcono);
                Serial.println(irtrans.toString());
                irtrans.send();
                break;
            }
            case 0x27://�Զ�
            {
                irtrans.setMode(kGreeAuto);
                Serial.println(irtrans.toString());
                irtrans.send();
                break;
            }
            case 0x28://�յ��¶�++
            {
                AIR_temp_1+=2;
                AIR_temp_1=range(AIR_temp_1,16,30);
                irtrans.setTemp(AIR_temp_1);
                Serial.println(irtrans.toString());
                irtrans.send();
                break;
            }
            case 0x29://�յ��¶�--
            {
                AIR_temp_1-=2;
                AIR_temp_1=range(AIR_temp_1,16,30);
                irtrans.setTemp(AIR_temp_1);
                Serial.println(irtrans.toString());
                irtrans.send();
                break;
            }
            case 0x31://�յ�16
            {
                irtrans.setTemp(16);
                Serial.println(irtrans.toString());
                irtrans.send();
                break;
            }
            case 0x32://�յ�17
            {
                irtrans.setTemp(17);
                Serial.println(irtrans.toString());
                irtrans.send();
                break;
            }
            case 0x33://�յ�18
            {
                irtrans.setTemp(18);
                Serial.println(irtrans.toString());
                irtrans.send();
                break;
            }
            case 0x34://�յ�19
            {
                irtrans.setTemp(19);
                Serial.println(irtrans.toString());
                irtrans.send();
                break;
            }
            case 0x35://�յ�20
            {
                irtrans.setTemp(20);
                Serial.println(irtrans.toString());
                irtrans.send();
                break;
            }
            case 0x36://�յ�21
            {
                irtrans.setTemp(21);
                Serial.println(irtrans.toString());
                irtrans.send();
                break;
            }
            case 0x37://�յ�22
            {
                irtrans.setTemp(22);
                Serial.println(irtrans.toString());
                irtrans.send();
                break;
            }
            case 0x38://�յ�23
            {
                irtrans.setTemp(23);
                Serial.println(irtrans.toString());
                irtrans.send();
                break;
            }
            case 0x39://�յ�24
            {
                irtrans.setTemp(24);
                Serial.println(irtrans.toString());
                irtrans.send();
                break;
            }
            case 0x3a://�յ�25
            {
                irtrans.setTemp(25);
                Serial.println(irtrans.toString());
                irtrans.send();
                break;
            }
            case 0x3b://�յ�26
            {
                irtrans.setTemp(26);
                Serial.println(irtrans.toString());
                irtrans.send();
                break;
            }
            case 0x3c://�յ�27
            {
                irtrans.setTemp(27);
                Serial.println(irtrans.toString());
                irtrans.send();
                break;
            }
            case 0x3d://�յ�28
            {
                irtrans.setTemp(28);
                Serial.println(irtrans.toString());
                irtrans.send();
                break;
            }
            case 0x3e://�յ�29
            {
                irtrans.setTemp(29);
                Serial.println(irtrans.toString());
                irtrans.send();
                break;
            }
            case 0x3f://�յ�30
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