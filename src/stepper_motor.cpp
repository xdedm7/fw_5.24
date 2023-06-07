#include "stepper_motor.hpp"

void step_init(void)
{
    pinMode(DIR, OUTPUT);
    pinMode(PUL, OUTPUT);
}

void stepper_motor_turn(int state)
{
    if(state)
    {
        digitalWrite(DIR, LOW);//设置步进电机转动方向
    }
    else digitalWrite(DIR, HIGH);//设置步进电机转动方向
    for(int i=0;i<12100;i++)
    {
        digitalWrite(PUL, HIGH);
        delayMicroseconds(320);

        digitalWrite(PUL, LOW);
        delayMicroseconds(320);    
    }
}

