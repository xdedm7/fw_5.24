#ifndef ESP_MQTT_H
#define ESP_MQTT_H

#include "PubSubClient.h"
#define mqtt_devid_test "1037659370" //设备ID
#define mqtt_pubid_test "569568"    //产品ID
#define mqtt_password "a20010722"   //鉴权信息



#define LED1_ON "data=LED_LED1_ON"
#define LED1_OFF "data=LED_LED1_OFF"


class json_struct
{
    private:
        char msg_buf[200];//json数据缓存
        char *dataTemplate;//信息模板
        char msgJson[75];//要发送的json格式的数据
        unsigned short json_len =0;
    public:
        void  ONENET_JSON_init(char* dataTemplate_, short json_len_);
};
void connectMQTTServer(void);
void pubMQTTmsg_test(void);
void subscribeTopic_test(void);
void receiveCallback_test(char* topic, byte* payload, unsigned int length);
/*
    重连客服端
*/
void clientReconnect(void);


/*
    1:topic 主题, 2: payload: 传递过来的信息 3: length: 长度
*/
void OneNET_recivecallback(char *topic, byte *payload, unsigned int length);
void ONENET_sendTempAndHumi(void);
void ONENET_sendsmoke(int smoke_flag);


int cmp_str(uint8_t str1[],char str2[]);

#endif