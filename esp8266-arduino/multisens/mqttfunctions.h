// connect/push to an MQTT server
// https://github.com/adafruit/Adafruit_MQTT_Library/blob/master/examples/mqtt_esp8266/mqtt_esp8266.ino
// https://www.youtube.com/watch?v=VjpONmC2tac

#ifdef PUSHTO_MQTT

#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

WiFiClient mqttclient;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
//void MQTT_connect();

void mqttsetup() {
  Serial.println(F("MQTT setup"));
  
  
}

// , const int& mqttport
void push_mqtt(const String& data, const String& feedname){
    // Create an ESP8266 WiFiClient class to connect to the MQTT server.
    if (!mqttclient.connect(MQTT_SERVER, mqttport)) {
        Serial.println("connection failed");
        return;
    }

//Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, AIO_SERVERPORT, MQTT_USERNAME, MQTT_PASSWORD);

// Setup a feed called 'onoff' for subscribing to changes.
const char ONOFF_FEED[] PROGMEM = AIO_USERNAME "/feeds/onoff";
  mqtt.subscribe(&onoffbutton);

}



// endif PUSHTO_MQTT
#endif
