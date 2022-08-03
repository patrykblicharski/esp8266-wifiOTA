#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <wifi.h> //Wifi credentials - ssid & password

#define DEBUG 1 //Debug msg to serial(), 1 - Enable 0 - Disable

#ifdef DEBUG
  #define DEBUG_PRINT(x)     Serial.print (x)
  #define DEBUG_PRINTDEC(x)     Serial.print (x, DEC)
  #define DEBUG_PRINTLN(x)  Serial.println(x)
  #define DEBUG_PRINTF(x, y) printf(x, y)
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTDEC(x)
  #define DEBUG_PRINTLN(x) 
  #define DEBUG_PRINTF(x, y)
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

// ============= OTA config

ArduinoOTA.setHostname("uThingName-1");   // Hostname defaults to esp8266-[ChipID]
ArduinoOTA.setPort(8266);                 // Port defaults to 8266
ArduinoOTA.setPassword("admin");          // No authentication by default
//ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3"); // Password can be set with it's md5 value as well, there is hash of MD5(admin)

// ============= OTA events
ArduinoOTA.onStart([]() {                     // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }
    DEBUG_PRINTLN("Start updating " + type);
  });

ArduinoOTA.onEnd([]() {
  DEBUG_PRINTLN("\nEnd");
  });
  
ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
  DEBUG_PRINTF("Progress: %u%%\r", (progress / (total / 100)));
  });
ArduinoOTA.onError([](ota_error_t error) {
  DEBUG_PRINTF("Error[%u]: ", error);
  if (error == OTA_AUTH_ERROR) {
    DEBUG_PRINTLN("Auth Failed");
  } else if (error == OTA_BEGIN_ERROR) {
    DEBUG_PRINTLN("Begin Failed");
  } else if (error == OTA_CONNECT_ERROR) {
    DEBUG_PRINTLN("Connect Failed");
  } else if (error == OTA_RECEIVE_ERROR) {
    DEBUG_PRINTLN("Receive Failed");
  } else if (error == OTA_END_ERROR) {
    DEBUG_PRINTLN("End Failed");
  }
  });
// ============= end OTA events


  ArduinoOTA.begin();     //init instance of OTA
  DEBUG_PRINTLN("Ready");
  DEBUG_PRINT("IP address: ");
  DEBUG_PRINTLN(WiFi.localIP());

} //end of setup()



void loop() {
    ArduinoOTA.handle(); //Handle

}