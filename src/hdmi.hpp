#ifndef HDMI_H
#define HDMI_H

#include "main.hpp"
extern char open_door;

void HDMI_Receive_Data(char *hdmi);
void HMISends(char buf1[]);
#endif