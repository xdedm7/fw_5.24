#include "main.hpp"

/*io口配置*/
//红外发射头 D15
//灯带 D21
//DHT11 D22
//继电器 D33
//LED D2
//步进电机 PUL D25 DIR D26
//语音模块 U2_TX D17 U2_RX D16
//串口屏 U0_TX D1 U0_RX D3
//土壤湿度传感器 D32
//水泵继电器 D18
//增湿器继电器 D19
//指纹模块软串口 rx:13,tx:14


SoftwareSerial softSerial1;
SoftwareSerial yunyin(22,23);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&softSerial1);
uint8_t finger_id;

float MQ2_voltage=0;
//DHT dht(DHTPIN, DHTTYPE);//DHT11
//struct DHT_ DHT_PARA;
IRGreeAC irtrans(infrad_TARS_PIN);
Ticker ticker1;
extern PubSubClient mqttClient;
decode_results results;
NeoGamma<NeoGammaTableMethod> colorGamma; 
extern NeoPixelBrightnessBus<NeoGrbFeature, Neo800KbpsMethod> LED_livingroom_bright;
char password_door[4]={'2','3','1','2'};//????????
char hmi_send_buf[30]="index.t4.txt=\"0000\"";//????????????????

void judge_IRR(void)
{
}
extern char voice[10];

int i=0;
void setup()
{
    delay(500);
    Serial.begin(9600);
    Serial.onReceive(Serial_callback);//??????????
    Serial2.begin(115200);
    Serial2.onReceive(Serial2_callback);
    irtrans.begin();//????????    
    softSerial1.begin(57600,SWSERIAL_8N1,13,14);
    yunyin.begin(115200,SWSERIAL_8N1,22,23);
   // yunyin.onReceive(Voice_serial_callback);
    finger.begin(57600);
    while(1)
    {
        if(finger.verifyPassword()) 
        {
            Serial.println("Found fingerprint sensor!");
            break;
        } 
        else 
        {
            Serial.println("Did not find fingerprint sensor :(");
        }
        delay(50);
    }
  // dht.begin(); // DHT11????? 
    WS2812_init();
    pinMode(LEDpin,OUTPUT);
    pinMode(relayPin, OUTPUT);
    //pinMode(relay_pumpPin,OUTPUT);
    //pinMode(relay_humidifierPin,OUTPUT);
    digitalWrite(relayPin,LOW);
    step_init();
    WiFi_Connect(); //????WIFI
    delay(50);
    connectMQTTServer();//????MQTT??????
   // ticker1.attach(5,ONENET_sendTempAndHumi);//????????????????
}
int MQ2_cnt=0;
int Smoke_flag=0;
int ADC_soil=0;
float soil_=0;
int anto_soil_flag=0;

String  softserial_res="";
void loop()
{
    //wifi配置函数
    if (!WiFi.isConnected())
    {
        WiFi_Connect();
    }
    if (!mqttClient.connected())
    {
        clientReconnect();
    }
    mqttClient.loop();


    //指纹锁的代码
    getFingerprintIDez();
    delay(5);            //don't ned to run this at full speed.


    //语音模块的代码
    while(yunyin.available()) 
    {
         yunyin.readBytes(voice, sizeof(voice));
          Serial1.print(voice);
    }
   
    Voice_Receive_Data(voice);
    for(i=0;voice[i]!='\0';i++)
    {
        voice[i]=0;
    }
    //Serial.println(ADC_IN);
    // digitalWrite(relay_pumpPin,HIGH);
    // digitalWrite(relay_humidifierPin,HIGH);
    // delay(500);
    // digitalWrite(relay_pumpPin,LOW);
    // digitalWrite(relay_humidifierPin,LOW);
    // delay(500);
}



char hdmi[10]={0};
//?????ж????
void Serial_callback() 
{
    while (Serial.available()) 
    {
        Serial.readBytes(hdmi, sizeof(hdmi));
    }
HDMI_Receive_Data(hdmi);
}
char camera[3]={0};
void Serial2_callback() 
{
    while(Serial2.available()) 
    {
        Serial2.readBytes(camera, 3);
     }
       Serial.print(camera);
     Camera_Receive_Data(camera);
}

