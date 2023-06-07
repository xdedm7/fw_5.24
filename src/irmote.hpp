#ifndef IRMOTE_H_
#define IRMOTE_H_

#include "ir_Gree.h"
#include "IRrecv.h"
#define infrad_TARS_PIN 15  //红外发射头
#define infrad_RECV_PIN 14  //红外接收头

#define AIR_ON_1 "data=AIR_SWITCH_ON_1"//空调_开
#define AIR_OFF_1 "data=AIR_SWITCH_OFF_1"//空调_关

#define AIR_SET_TEMP_1  "data=AIR_SET_TEMP_00_1"//空调设置温度
#define AIR_SET_FUN_1  "data=AIR_SET_FUN_0_1"//空调设置风速

#define AIR_MODE_AUTO_1 "data=AIR_MODE_AUTO_1"//自动模式
#define AIR_MODE_COOL_1 "data=AIR_MODE_COOL_1"//制冷模式
#define AIR_MODE_HOT_1 "data=AIR_MODE_HOT_1"//制热模式
#define AIR_MODE_DRY_1 "data=AIR_MODE_DRY_1"//除湿模式
#define AIR_MODE_Econo_1 "data=AIR_MODE_Econo_1"//节能模式
#endif