#ifndef MAIN_H_
#define MAIN_H_
#include <Arduino.h>
#include "wifi_esp32.hpp"
#include "esp32_mqtt.hpp"
#include "Ticker.h"
#include "irmote.hpp"
#include "ws2812.hpp"
#include "dht11.hpp"
#include "hdmi.hpp"
#include "stepper_motor.hpp"
#include "voice.hpp"
#include "SoftwareSerial.h"
#include "Adafruit_Fingerprint.h"
#include "finger.hpp"
#include "camera.hpp"
#define relayPin   33      //继电器引脚_门锁
#define LEDpin 2//ESP32led
#define smokePin 32//烟雾传感器引脚


#define shiduPin 32
#define relay_pumpPin 18
#define relay_humidifierPin 19



#define LOCK_1_ON  "data=LOCK_SWITCH_ON_1" //开锁
#define LOCK_1_OFF "data=LOCK_SWITCH_OFF_1"//关锁

#define LOCK_2_ON  "data=LOCK_SWITCH_ON_2" //开锁
#define LOCK_2_OFF "data=LOCK_SWITCH_OFF_2"//关锁

#define LOCK_3_ON  "data=LOCK_SWITCH_ON_3" //开锁
#define LOCK_3_OFF "data=LOCK_SWITCH_OFF_3"//关锁

#define LOCK_PSW_repalce "data=LOCK_PSW_RPL_0000_1"//修改门锁密码

#define PUMP_ON "data=PUMP_SWITCH_ON"//灌溉开
#define PUMP_OFF "data=PUMP_SWITCH_OFF"//灌溉关

#define PUMP_AUTO_ON "data=PUMP_AUTO_ON"//灌溉自动模式开
#define PUMP_AUTO_OFF "data=PUMP_AUTO_OFF"//灌溉自动模式关

#define humidifier_ON "data=HUMI_SWITCH_ON" //加湿
#define humidifier_OFF "data=HUMI_SWITCH_OFF"//关闭

void Serial_callback();
void Serial2_callback();
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
#define range(x,a,b)  (min(max(x,a),b))

#endif