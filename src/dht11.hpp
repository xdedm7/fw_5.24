#ifndef DHT11_H
#define DHT11_H
#include "DHT.h"
#include "DHT_U.h"
#define DHTPIN 22 // DHT11���������ӵ�Arduino����������2
#define DHTTYPE DHT11 // ʹ��DHT11����������

struct DHT_
{
    float temp_1;
    float humi_1;
};

#endif