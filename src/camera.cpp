#include "hdmi.hpp"

static char state = 0;
char is_correct_face=0;


void Camera_Receive_Data(char camera[])//接收串口屏传过来的数�?
{
	int i;
    if(camera[0]=0x2b&&camera[2]==0x5b)
    {
        // Serial.print(hdmi[1]);
        is_correct_face=camera[1];
       // Serial.print(is_correct_face);
        if(is_correct_face==0x01)
        {
            digitalWrite(relayPin,HIGH);
            delay(3000);
            digitalWrite(relayPin,LOW);
            is_correct_face=0;
        }
        else{
             digitalWrite(relayPin,LOW);
        }
        is_correct_face=0;
    }
    for(i=0;i<3;i++)
    {
        camera[i]=0;
    }
}
