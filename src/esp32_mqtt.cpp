
#include "main.hpp"
const char* mqttServer = "183.230.40.39";
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
extern IRGreeAC irtrans;
extern IRrecv irrecv;

char msg_buf[200];                                //������Ϣ������
char dataTemplate[] = "{\"temp_1\":%.2f,\"humi_1\":%.2f,\"humi_flower\":%.2f}"; //��Ϣģ��
char msgJson[75];                                 //Ҫ���͵�json��ʽ������
unsigned short json_len = 0;                      //json����


extern NeoPixelBrightnessBus<NeoGrbFeature, Neo800KbpsMethod> LED_livingroom_bright;

extern char password_door[4];
extern char hmi_send_buf[30];

//���ӷ�����
void connectMQTTServer(void)
{
    // ����MQTT������
    mqttClient.setServer(mqttServer, 6002);
    delay(500);
    while(!mqttClient.connect(mqtt_devid_test, mqtt_pubid_test, mqtt_password))
    {
        Serial.print("Onenet Server Connect Failed. Client State:");
        Serial.println(mqttClient.state());
        delay(500);
    }
    Serial.println("Onenet Connected.");
    Serial.println("Server Address: ");
    Serial.println(mqttServer); 
    // subscribeTopic_test();
    // delay(200);
    mqttClient.setCallback(OneNET_recivecallback);
}

/*
    ���ⷢ����������
*/
void pubMQTTmsg_test(void)
{
    static int value; // �ͻ��˷�����Ϣ������
    // �����������⡣����������ZZQ-Ϊǰ׺����������豸��MAC��ַ��
    // ��ô����Ϊȷ����ͬ�û�����MQTT��Ϣ����ʱ��ESP8266�ͻ������Ƹ�����ͬ��
    String topicString = "ZZQ-" + WiFi.macAddress();
    char publishTopic[topicString.length() + 1];  
    strcpy(publishTopic, topicString.c_str());
     // ����������Ϣ����Ϣ������Hello WorldΪ��ʼ��������ӷ���������
    String messageString = "Hello World ZZQ " + String(value++); 
    char publishMsg[messageString.length() + 1];   
    strcpy(publishMsg, messageString.c_str());
    //����������Ϣ
    if(mqttClient.publish(publishTopic, publishMsg))
    {
       Serial.println("Publish Topic:");
       Serial.println(publishTopic);
       Serial.println("Publish message:");
       Serial.println(publishMsg);    
    } 
    else 
    {
        Serial.println("Message Publish Failed."); 
    }
}
/*
    ����ָ�������������
*/
void subscribeTopic_test(void)
{
    String topicString = "Sub-" + WiFi.macAddress();
    char subTopic[topicString.length() + 1];
    strcpy(subTopic, topicString.c_str());
    if(mqttClient.subscribe(subTopic))
    {
        Serial.println("Subscrib Topic:");
        Serial.println(subTopic);
    } 
    else
    {
        Serial.print("Subscribe Fail...");
    }
}

void receiveCallback_test(char* topic, byte* payload, unsigned int length)
{
    Serial.print("Message Received [");
    Serial.print(topic);
    Serial.print("] ");
    for (int i = 0; i < length; i++) 
    {
        Serial.print((char)payload[i]);
    }
    Serial.println("");
    Serial.print("Message Length(Bytes) ");
    Serial.println(length);
    if ((char)payload[0] == '1') 
    {     // ����յ�����Ϣ�ԡ�1��Ϊ��ʼ
        digitalWrite(2, HIGH);  // �����LED��
        Serial.println("LED ON");
    } 
    else if((char)payload[0] == '0') 
    {                           
    digitalWrite(2, LOW); // ����Ϩ��LED��
    Serial.println("LED OFF");
    }
}


void clientReconnect(void)
{
    while (!mqttClient.connected()) //�������ͻ���
  {
    Serial.println("reconnect MQTT...");
    if (mqttClient.connect(mqtt_devid_test, mqtt_pubid_test, mqtt_password))
    {
      Serial.println("connected");
    }
    else
    {
      Serial.println("failed");
      Serial.println(mqttClient.state());
      Serial.println("try again in 5 sec");
      delay(5000);
    }
  }

}

int window_flag=0;
extern int anto_soil_flag;
/*
    ����ONENET�Ʒ��������ݻص�����
*/
uint8_t AIR_temp_1=16;
uint8_t AIR_fan_1=0;
uint8_t AIR_mode_1=0;
uint8_t LED_breight=40;
uint8_t R_SET=0;
uint8_t G_SET=0;
uint8_t B_SET=0;
uint8_t SEND_CNT=0;
void OneNET_recivecallback(char *topic, byte *payload, unsigned int length)
{
    int i=0;
    Serial.println("message rev:");
    Serial.println(topic);
    for (size_t i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }
    Serial.println();
    /*
        �򿪿յ�
    */
    if(cmp_str(payload,(char *)AIR_ON_1))
    {
        irtrans.on();//���ɿյ��������ĺ�����
        Serial.println(irtrans.toString());//��ʾ���͵Ŀյ������������
        irtrans.send();//���ͺ�������
    }
   
    /*
        ���ڵ�������
    */
    else if(payload[5]=='L'&&payload[16]=='N'&&payload[15]=='I')
    {
        Serial.println(1);
        LED_breight=(payload[25]-'0')*10+(payload[26]-'0');
        Serial.println(LED_breight);
        LED_breight=range(LED_breight,10,90);
        LED_livingroom_bright.SetBrightness(LED_breight);
        LED_livingroom_bright.Show();
    }
    /*
        �رտյ�
    */
    else if(cmp_str(payload,(char *)AIR_OFF_1))
    {
        irtrans.off();
        Serial.println(irtrans.toString());//��ʾ���͵Ŀյ��ػ��������
        irtrans.send();
    }
    /*
        ���ÿյ��¶� 16-30��
    */
    else if(payload[5]=='A'&&payload[9]=='S'&&payload[13]=='T'&&payload[21]=='1')
    {
        if((((payload[18]-'0')*10+(payload[19]-'0'))<=30&&((payload[18]-'0')*10+(payload[19]-'0'))>=16))
        {
            AIR_temp_1=(payload[18]-'0')*10+(payload[19]-'0');
            //Serial.println(AIR_temp_1);
           // sprintf(TXT_,"%c,%c\r\n",payload[18],payload[19]);

            //Serial.println(TXT_);
            AIR_temp_1=range(AIR_temp_1,16,30);
            irtrans.setTemp(AIR_temp_1);
            Serial.println(irtrans.toString());
            irtrans.send();
        }
    }
    /*
        ���÷��� һ���ĵ������Զ� "data=AIR_SET_FUN_(num 0-3)"
    */
    else if(payload[5]=='A'&&payload[9]=='S'&&payload[13]=='F'&&payload[19]=='1')
    {
        if((payload[17]-'0')<=0x03&&((payload[17]-'0')>=0x00))
        {
            AIR_fan_1=(payload[17]-'0');
            irtrans.setFan(AIR_fan_1);
            Serial.println(irtrans.toString());
            irtrans.send();
        }
    }
    /*
        ��ʪģʽ
    */
    else if(cmp_str(payload,(char *)AIR_MODE_DRY_1))
    {
        irtrans.setMode(kGreeDry);
        Serial.println(irtrans.toString());
        irtrans.send();
    }
    /*
        �Զ�ģʽ
    */
    else if(cmp_str(payload,(char *)AIR_MODE_AUTO_1))
    {
        irtrans.setMode(kGreeAuto);
        Serial.println(irtrans.toString());
        irtrans.send();
    } 
    /*
        ����ģʽ
    */
    else if(cmp_str(payload,(char *)AIR_MODE_COOL_1)) 
    {
        irtrans.setMode(kGreeCool);
        Serial.println(irtrans.toString());
        irtrans.send();
    }
    /*
        ����ģʽ
    */
    else if(cmp_str(payload,(char *)AIR_MODE_HOT_1))
    {
        irtrans.setMode(kGreeHeat);
        Serial.println(irtrans.toString());
        irtrans.send();
    }
    /*
        ����ģʽ
    */
    else if(cmp_str(payload,(char *)AIR_MODE_Econo_1))
    {
        irtrans.setMode(kGreeEcono);
        Serial.println(irtrans.toString());
        irtrans.send();
    }
    /*
        ��ȫ��
    */
    else if(cmp_str(payload,(char*)set_LED_ON_ALL))
    {
        for(i=0;i<LED_COUNT;i++)
        {
            LED_livingroom_bright.SetPixelColor(i,RgbColor(255,255,255));
            LED_livingroom_bright.Show();
        }
    }
    /*
        ��ȫ��
    */
    else if(cmp_str(payload,(char*)set_LED_OFF_ALL))
    {
        for(i=0;i<LED_COUNT;i++)
        {
            LED_livingroom_bright.SetPixelColor(i,RgbColor(0,0,0));
            LED_livingroom_bright.Show();
        }
    }
   /*
        ����ĳ��������
   */
   else if(payload[5]=='L'&&payload[11]=='S'&&payload[19]=='N')
   {
        switch(payload[21])
        {
            case '1':
            {
                LED_livingroom_bright.SetPixelColor(0,RgbColor(255,255,255));
                LED_livingroom_bright.Show();
                break;
            }
            case '2':
            {
                LED_livingroom_bright.SetPixelColor(1,RgbColor(255,255,255));
                LED_livingroom_bright.Show();
                break;
            }
            case '3':
            {
                LED_livingroom_bright.SetPixelColor(2,RgbColor(255,255,255));
                LED_livingroom_bright.Show();
                break;
            }
            case '4':
            {
                LED_livingroom_bright.SetPixelColor(4,RgbColor(255,255,255));
                LED_livingroom_bright.Show();
                break;
            }
            case '5':
            {
                LED_livingroom_bright.SetPixelColor(5,RgbColor(255,255,255));
                LED_livingroom_bright.Show();
                break;
            }
            case '6':
            {
                LED_livingroom_bright.SetPixelColor(3,RgbColor(255,255,255));
                LED_livingroom_bright.Show();
                break;
            }
        }
   }
   /*
        ����ĳ��������
   */
   else if(payload[5]=='L'&&payload[11]=='S'&&payload[19]=='F')
   {
        switch(payload[22])
        {
            case '1':
            {
                LED_livingroom_bright.SetPixelColor(0,RgbColor(0,0,0));
                LED_livingroom_bright.Show();
                break;
            }
            case '2':
            {
                LED_livingroom_bright.SetPixelColor(1,RgbColor(0,0,0));
                LED_livingroom_bright.Show();
                break;
            }
            case '3':
            {
                LED_livingroom_bright.SetPixelColor(2,RgbColor(0,0,0));
                LED_livingroom_bright.Show();
                break;
            }
            case '4':
            {
                LED_livingroom_bright.SetPixelColor(4,RgbColor(0,0,0));
                LED_livingroom_bright.Show();
                break;
            }
            case '5':
            {
                LED_livingroom_bright.SetPixelColor(5,RgbColor(0,0,0));
                LED_livingroom_bright.Show();
                break;
            }
            case '6':
            {
                LED_livingroom_bright.SetPixelColor(3,RgbColor(0,0,0));
                LED_livingroom_bright.Show();
                break;
            }
        }
   }
   /*
        ����ĳ�����ݵ�RGB
   */
    else if(payload[5]=='L'&&payload[11]=='S'&&payload[15]=='C')
    {
        R_SET=(payload[21]-'0')*100+(payload[22]-'0')*10+(payload[23]-'0');
        G_SET=(payload[25]-'0')*100+(payload[26]-'0')*10+(payload[27]-'0');
        B_SET=(payload[29]-'0')*100+(payload[30]-'0')*10+(payload[31]-'0');
        /**/
        Serial.println(R_SET);
        Serial.println(G_SET);
        Serial.println(B_SET);
        switch(payload[33])
        {
            case '1':
            {
                LED_livingroom_bright.SetPixelColor(0,RgbColor(R_SET,G_SET,B_SET));
                LED_livingroom_bright.Show();
                break;
            }
            case '2':
            {
                LED_livingroom_bright.SetPixelColor(1,RgbColor(R_SET,G_SET,B_SET));
                LED_livingroom_bright.Show();
                break;
            }
            case '3':
            {
                LED_livingroom_bright.SetPixelColor(2,RgbColor(R_SET,G_SET,B_SET));
                LED_livingroom_bright.Show();
                break;
            }
            case '4':
            {
                LED_livingroom_bright.SetPixelColor(4,RgbColor(R_SET,G_SET,B_SET));
                LED_livingroom_bright.Show();
                break;
            }
            case '5':
            {
                LED_livingroom_bright.SetPixelColor(5,RgbColor(R_SET,G_SET,B_SET));
                LED_livingroom_bright.Show();
                break;
            }
            case '6':
            {
                LED_livingroom_bright.SetPixelColor(3,RgbColor(R_SET,G_SET,B_SET));
                LED_livingroom_bright.Show();
                break;
            }
        }
    }
    /*
        ������
    */
   else if(cmp_str(payload,(char*)LOCK_1_ON))
   {
    
        digitalWrite(relayPin,HIGH);
        delayMicroseconds(1000000);
        Voice_Sends();
   }
    /*
        �ر�����
    */
   else if(cmp_str(payload,(char*)LOCK_1_OFF))
   {
        digitalWrite(relayPin, LOW);
   }
   /*
        ������
   */
   else if(cmp_str(payload,(char*)WINDOW_control_ON))
   {
        delay(50);
        if(window_flag==0)
        {
            stepper_motor_turn(ON_WINDOW);
            window_flag=1;
        }
        
   }
   /*
        �ش���
   */
   else if(cmp_str(payload,(char*)WINDOW_control_OFF))
   {
        delay(50);
        if(window_flag==1)
        {
            stepper_motor_turn(OFF_WINDOW);
            window_flag=0;
        }
   }
   /*
        �򿪳�ˮ��
   */
   else if(cmp_str(payload,(char*)PUMP_ON))
   {
        delay(50);
        digitalWrite(relay_pumpPin,LOW);
   }
   /*
        �رճ�ˮ��
   */
   else if(cmp_str(payload,(char*)PUMP_OFF))
   {
        delay(50);
        digitalWrite(relay_pumpPin,HIGH);
   }
    /*
        ����ʪ
    */
   else if(cmp_str(payload,(char*)humidifier_ON))
   {
        delay(50);
        digitalWrite(relay_humidifierPin,LOW);
   }

   /*
        �ر���ʪ
   */
   else if(cmp_str(payload,(char*)humidifier_OFF))
   {
        delay(50);
        digitalWrite(relay_humidifierPin,HIGH);
   }
   /*
        �޸���������
   */
   else if(payload[5]=='L'&&payload[6]=='O'&&payload[10]=='P'&&payload[11]=='S'&&payload[14]=='R')
   {
        for(i=0;i<4;i++)
        {
            password_door[i]=payload[18+i];
        }
        for(i=0;i<10;i++)
        {
            sprintf(hmi_send_buf,"index.t4.txt=\"%s\"%c%c%c",password_door,0xff,0xff,0xff);  
             HMISends(hmi_send_buf);    
        }
       
        
   }
    /*
        ����Զ�ģʽ��
    */
    else if(cmp_str(payload,(char*)PUMP_AUTO_ON))
    {
        anto_soil_flag=1;
    }
    else if(cmp_str(payload,(char*)PUMP_AUTO_OFF))
    {
        digitalWrite(relay_pumpPin,HIGH);
        anto_soil_flag=0;
    }
}
    /*
        �Ƚ�����ĸ�ַ��� ��ȷ���1 ����ȷ���0
    */
int cmp_str(uint8_t str1[],char str2[])
{
    int i=0;
     for(i=0;str1[i]!='\0'&&str2[i]!='\0';i++)
    {
        if(str1[i]!=str2[i])
        {
            return 0;
        }
    }
    return 1;
}


/*
    ONENET��������ʼ������
*/
void json_struct::ONENET_JSON_init(char* dataTemplate_, short json_len_)
{
    int i=0;
    for(i=0;dataTemplate_[i]!='0';i++)
    {
        dataTemplate[i]=dataTemplate_[i];
    }
    json_len=json_len_;
    Serial.println(dataTemplate);
}

/*
    ESP�������ݵ��Ʒ�����
*/
extern struct DHT_ DHT_PARA;
extern DHT dht;


void ONENET_sendsmoke(int smoke_flag)
{ 
    char* dataTemplate_smoke;
    sprintf(dataTemplate_smoke,"{\"smoke_1\":%d}",smoke_flag);
    Serial.println(dataTemplate_smoke);
    if (mqttClient.connected())
    {
        snprintf(msgJson, 40, dataTemplate_smoke); 
        json_len = strlen(msgJson);                   //msgJson�ĳ���
        msg_buf[0] = char(0x03);                       //Ҫ���͵����ݱ��밴��ONENET��Ҫ����, ����Ҫ��,���ݵ�һλ��3
        msg_buf[1] = char(json_len >> 8);              //���ݵڶ�λ��Ҫ���͵����ݳ��ȵĸ߰�λ
        msg_buf[2] = char(json_len & 0xff);            //���ݵ���λ��Ҫ�������ݵĳ��ȵĵͰ�λ
        memcpy(msg_buf + 3, msgJson, strlen(msgJson)); //��msg_buf�ĵ���λ��ʼ,����Ҫ��������msgJson
        msg_buf[3 + strlen(msgJson)] = 0;              //���һ��0��Ϊ���һλ, ����Ҫ���͵�msg_buf׼������
        Serial.print("public message:");
        Serial.println(msgJson);
        mqttClient.publish("$dp", (uint8_t *)msg_buf, 3 + strlen(msgJson)); //�������ݵ�����$dp
    }
}
extern int Smoke_flag;
extern float soil_;
void ONENET_sendTempAndHumi(void)
{
   
    DHT_PARA.humi_1=dht.readHumidity();
    DHT_PARA.temp_1=dht.readTemperature();
    if (isnan(DHT_PARA.humi_1) || isnan(DHT_PARA.temp_1)) 
    { // ����޷���ȡ������
       // Serial.println("Failed to read from DHT sensor!");
    }
    else
    {
        sprintf(dataTemplate, "{\"temp_1\":%.2f,\"humi_1\":%.2f,\"humi_flower\":%.2f}",DHT_PARA.temp_1,DHT_PARA.humi_1,soil_);
        Serial.println(dataTemplate);
        if (mqttClient.connected())
        {
            snprintf(msgJson, 55, dataTemplate, 22.31, 25.92,0.1); //��ģ����ʪ����������dataTemplateģ����, ���ɵ��ַ�������msgJson
            json_len = strlen(msgJson);                   //msgJson�ĳ���
            msg_buf[0] = char(0x03);                       //Ҫ���͵����ݱ��밴��ONENET��Ҫ����, ����Ҫ��,���ݵ�һλ��3
            msg_buf[1] = char(json_len >> 8);              //���ݵڶ�λ��Ҫ���͵����ݳ��ȵĸ߰�λ
            msg_buf[2] = char(json_len & 0xff);            //���ݵ���λ��Ҫ�������ݵĳ��ȵĵͰ�λ
            memcpy(msg_buf + 3, msgJson, strlen(msgJson)); //��msg_buf�ĵ���λ��ʼ,����Ҫ��������msgJson
            msg_buf[3 + strlen(msgJson)] = 0;              //���һ��0��Ϊ���һλ, ����Ҫ���͵�msg_buf׼������
            Serial.print("public message:");
            Serial.println(msgJson);
            mqttClient.publish("$dp", (uint8_t *)msg_buf, 3 + strlen(msgJson)); //�������ݵ�����$dp
        } 
    }    
}
