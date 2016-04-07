/************************************************************/
/*                                                          */       
/*  dht22 in shackspace with mqtt                           */
/*                                                          */

// https://home-assistant.io/blog/2015/10/11/measure-temperature-with-esp8266-and-report-to-mqtt/

/************************************************************/

// increment on change
#define SOFTWARE_VERSION "MFA-2016-001"

/**********************************************/
/* DHT declaration 
/**********************************************/
#include "DHT.h"
#define DHTPIN 2 // pin D4 auf nodemcu
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

/**********************************************/
/* WiFi declarations
/**********************************************/
#include <ESP8266WiFi.h>

const char* ssid = "Freifunk";
const char* password = "";

/**********************************************/
/* MQTTdeclarations
/**********************************************/

#include <PubSubClient.h>

#define mqtt_server "hass.shack"

WiFiClient espClient;
PubSubClient mqttClient(espClient);
long lastMsg = 0;
char msg[50];

unsigned long sampletime_ms = 1000; // 1 second

/**********************************************/
/* The Setup
/**********************************************/
void setup() {
  Serial.begin(9600); //Output to Serial at 9600 baud
  dht.begin(); // Start DHT
  delay(10);
  connectWifi(); // Start ConnecWifi 
  Serial.print("\n"); 
  Serial.println("ChipId: ");
  Serial.println(String(ESP.getChipId()));
  mqttClient.setServer(mqtt_server, 1883);

}

/**********************************************/
/* And action
/**********************************************/
void loop() {

  if (!mqttClient.connected()) {
    reconnect();
  }
  mqttClient.loop();

  long now = millis();
  if (now - lastMsg > sampletime_ms) {
    lastMsg = now;
    sensorDHT();  // getting temperature and humidity
   }
}

// DHT22 Sensor
void sensorDHT(){
 float h = dht.readHumidity(); //Read Humidity
 float t = dht.readTemperature(); //Read Temperature

 // Check if valid number if non NaN (not a number) will be send.
 if (isnan(t) || isnan(h)) {
   Serial.println("DHT22 couldn’t be read");
 } else {
   Serial.print("Humidity    : ");
   Serial.print(h);
   Serial.println(" %");
   Serial.print("Temperature : ");
   Serial.print(t);
   Serial.println(" C");

   if(!mqttClient.publish((String("home-assistant/") + String(ESP.getChipId()) + String("/humidity")).c_str(),
                       String(dht.readHumidity()).c_str())) {
    Serial.println("Publish failed");
   }
   if(!mqttClient.publish((String("home-assistant/") + String(ESP.getChipId()) + String("/temperature")).c_str(),
                       String(dht.readTemperature()).c_str())) {
    Serial.println("Publish failed");
   }

 }
}

/**********************************************/
/* WiFi connecting script
/**********************************************/
void connectWifi() {
  WiFi.begin(ssid, password); // Start WiFI
  
  Serial.print("Connecting ");
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

String Float2String(float value)
{
  // Convert a float to String with two decimals.
  char temp[15];
  String s;

  dtostrf(value,13, 2, temp);
  s = String(temp);
  s.trim();
  return s;
}

/**********************************************/
/*
/**********************************************/

void reconnect() {
  // Loop until we're reconnected
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (mqttClient.connect(String(ESP.getChipId()).c_str())) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

