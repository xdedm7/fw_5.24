#include "wifi_esp32.hpp"
const char* WIFI_SSID="xdedm7";
const char* WIFI_PASSPAUSE="a20010722";
char *txt_print=NULL;
void WiFi_Connect(void)
{
    WiFi.mode(WIFI_STA);
    WiFi.setTxPower(WIFI_POWER_5dBm);
    WiFi.begin(WIFI_SSID, WIFI_PASSPAUSE,6);
    Serial.print("Connecting.. ");
	while (WiFi.status() != WL_CONNECTED)
	{ //这里是阻塞程序，直到连接成功
		delay(800);
		Serial.print(".");
	}
    Serial.print("wifi_connected ");
    delay(500);
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}