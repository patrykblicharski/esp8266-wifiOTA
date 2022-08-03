#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <wifi.h> //Wifi ssid & password

#define DEBUG 1

#ifdef DEBUG
  #define DEBUG_PRINT(x)     Serial.print (x)
  #define DEBUG_PRINTDEC(x)     Serial.print (x, DEC)
  #define DEBUG_PRINTLN(x)  Serial.println (x)
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTDEC(x)
  #define DEBUG_PRINTLN(x) 
#endif




void setup() {
  Serial.begin(115200);
  DEBUG_PRINTLN("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    DEBUG_PRINTLN("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
}

void loop() {
}