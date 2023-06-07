#include "hdmi.hpp"

static char state = 0;
char open_door=0;

void HMISends(char buf1[])
{
    Serial.print(buf1);
}

void HDMI_Receive_Data(char *hdmi)//接收串口屏传过来的数据
{
	int i;
    if(hdmi[0]=0x11&&hdmi[2]==0x0b)
    {
        // Serial.print(hdmi[1]);
        open_door=hdmi[1];
        if(open_door==0x01)
        {
            digitalWrite(relayPin,HIGH);
            delayMicroseconds(3000000);
            digitalWrite(relayPin,LOW);
        }
    }
    for(i=0;hdmi[i]!='\0';i++)
    {
        hdmi[i]=0;
    }
}
