/************************************************************/
/* OK LAB Particulate Matter Sensor                         */
/*      - nodemcu-LoLin board                               */
/*      - Shinyei PPD42NS                                   */
/*      http://www.sca-shinyei.com/pdf/PPD42NS.pdf          */
/*                                                          */       
/*                                                          */
/*                                                          */
/************************************************************/

// increment on change
#define SOFTWARE_VERSION "MFA-2016-001"

/**********************************************/
/* DHT declaration 
/**********************************************/
#include "DHT.h"
#define DHTPIN 4 // pin 2 auf nodemcu
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

/**********************************************/
/* WiFi declarations
/**********************************************/
#include <ESP8266WiFi.h>

const char* ssid = "Freifunk";
const char* password = "";

/**********************************************/
/* The Setup
/**********************************************/
void setup() {
  Serial.begin(9600); //Output to Serial at 9600 baud
  dht.begin(); // Start DHT
  delay(10);
//  connectWifi(); // Start ConnecWifi 
  Serial.print("\n"); 
  Serial.println("ChipId: ");
  Serial.println(ESP.getChipId());
}

/**********************************************/
/* And action
/**********************************************/
void loop() {
  sensorDHT();  // getting temperature and humidity
  delay(1000);
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

