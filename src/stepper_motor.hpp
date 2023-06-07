#ifndef STEPPER_MOTOR_H
#define STEPPER_MOTOR_H

#include "main.hpp"

#define WINDOW_control_ON "data=OTHER_SWITCH_ON_1"
#define WINDOW_control_OFF "data=OTHER_SWITCH_OFF_1"
#define DIR 26 //方向信号
#define PUL 25 //脉冲信号
#define ON_WINDOW 1
#define OFF_WINDOW 0
void step_init(void);
void stepper_motor_turn(int state);
#endif