#ifndef DHT11_H
#define DHT11_H
#include "DHT.h"
#include "DHT_U.h"
#define DHTPIN 22 // DHT11传感器连接到Arduino的数字引脚2
#define DHTTYPE DHT11 // 使用DHT11传感器类型

struct DHT_
{
    float temp_1;
    float humi_1;
};

#endif