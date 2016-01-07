 /*******************************************************/
/* OK LAB Particulate Matter Sensor                    */
/*      - nodemcu-LoLin board                          */
/*      - Shinyei PPD42NS                              */
/*      http://www.sca-shinyei.com/pdf/PPD42NS.pdf     */
/*                                                     */       
/*******************************************************/

/**********************************************/
/* configure your sensors,                    */
/* PINs and WIFI in sensorconfig.h            */
/**********************************************/
#include "sensorconfig.h"

#include <ESP8266WiFi.h>
int value = 0;
#include "apifunctions.h"

/**********************************************/
/* DHT declaration 
/**********************************************/
#ifdef DHT_ACTIVE
// The IDE requires all libraries to be #include’d in the main (.ino) file.
// http://jamesreubenknowles.com/multiple-source-files-with-the-arduino-ide-1618
#include <DHT.h>
#include "dhtpush.h"
#endif

/**********************************************/
/* onewire ds18x20 temperature sensor declaration 
/**********************************************/
// derived from https://github.com/esp8266/Arduino/blob/esp8266/libraries/OneWire/examples/DS18x20_Temperature/DS18x20_Temperature.pde
#ifdef DS_ACTIVE
#include <OneWire.h>
#include "ds18x20push.h"
// on pin ONEWIRE_PIN = GPIO (a 4.7K pullup resistor is necessary)
# endif

/**********************************************/
/* WiFi declarations: see sensorconfig.h      */
/**********************************************/


/**********************************************/
/* Variable Definitions for PPD24NS           */
/**********************************************/
#ifndef PPD42_P1_PIN
#define  PPD42_P1_PIN 12
#endif

#ifndef PPD42_P2_PIN
#define  PPD42_P2_PIN 14
#endif

// P1 for PM10 & P2 for PM25
boolean valP1 = HIGH;
boolean valP2 = HIGH;

unsigned long starttime;
unsigned long durationP1;
unsigned long durationP2;

boolean trigP1 = false;
boolean trigP2 = false;
unsigned long trigOnP1;
unsigned long trigOnP2;

unsigned long lowpulseoccupancyP1 = 0;
unsigned long lowpulseoccupancyP2 = 0;

float ratio = 0;
float concentration = 0;

#ifdef PIN_LED_STATUS
int ledsstate=LOW;
#endif

/**********************************************/
/* The Setup
/**********************************************/

void setup() {

#ifdef PIN_LED_STATUS
pinMode(PIN_LED_STATUS, OUTPUT);
digitalWrite(PIN_LED_STATUS, ledsstate);
#endif

#ifdef PIN_LED_STATUS
ledsstate=HIGH;
digitalWrite(PIN_LED_STATUS, ledsstate);
#endif

  Serial.begin(9600); //Output to Serial at 9600 baud
  delay(10);
  Serial.println("ESP startup, chipid:");
  Serial.println(ESP.getChipId());
  Serial.print("Heap free:");
  Serial.println(ESP.getFreeHeap());
  Serial.print("sampletime [s]:");
  Serial.println(Float2String(sampletime_ms/1000.0));
  int i;
  Serial.println("GPIOx Dx PIN matching");

  for (i = 0; i < 13; i = i + 1) {
        Serial.print(i);
        Serial.print("\t");
        Serial.println(D[i]);
    }

#ifdef PPD_ACTIVE
#ifdef PIN_LED_STATUS
ledsstate=LOW;
digitalWrite(PIN_LED_STATUS, ledsstate);
#endif
  pinMode(PPD42_P1_PIN,INPUT); // Listen at the designated PIN
  pinMode(PPD42_P2_PIN,INPUT); //Listen at the designated PIN
  Serial.println("Sensortype PPD active");
  Serial.print("PPD42_P1_PIN: ");
  Serial.print(PPD42_P1_PIN);
  Serial.print("PPD42_P2_PIN: ");
  Serial.print(PPD42_P2_PIN);
#ifdef PIN_LED_STATUS
ledsstate=HIGH;
digitalWrite(PIN_LED_STATUS, ledsstate);
#endif
#endif
  starttime = millis(); // store the start time
  
#ifdef DHT_ACTIVE
#ifdef PIN_LED_STATUS
ledsstate=LOW;
digitalWrite(PIN_LED_STATUS, ledsstate);
#endif
  Serial.println("Sensortype DHT active");  
  Serial.print("DHTPIN: ");
  Serial.println(DHTPIN);
  Serial.println("init DHT");
  dht.begin(); // Start DHT
  delay(10);
#ifdef PIN_LED_STATUS
ledsstate=HIGH;
digitalWrite(PIN_LED_STATUS, ledsstate);
#endif
#endif


#ifdef DS_ACTIVE
#ifdef PIN_LED_STATUS
ledsstate=LOW;
digitalWrite(PIN_LED_STATUS, ledsstate);
#endif
  Serial.println("Sensortype DS active");  
  Serial.print("ONEWIRE_PIN: ");
  Serial.println(ONEWIRE_PIN);
  Serial.print("init DS");
  Serial.println();
  DSinit();
  delay(10);
  // try to read a temperature
  float t;
  t=DSgetTemperature();
  Serial.print("DSgetTemperature(): t=");
  Serial.println(t);
#endif
  connectWifi(); // Start ConnecWifi
  Serial.print("\n"); 
#ifdef PIN_LED_STATUS
ledsstate=HIGH;
digitalWrite(PIN_LED_STATUS, ledsstate);
#endif
}

/**********************************************/
/* And action
/**********************************************/
void loop() {
  String data;
  // Read pins connected to ppd42ns
#ifdef PPD_ACTIVE
  valP1 = digitalRead(PPD42_P1_PIN);
  valP2 = digitalRead(PPD42_P2_PIN);

  if(valP1 == LOW && trigP1 == false){
    trigP1 = true;
    trigOnP1 = micros();
  }
  
  if (valP1 == HIGH && trigP1 == true){
    durationP1 = micros() - trigOnP1;
    lowpulseoccupancyP1 = lowpulseoccupancyP1 + durationP1;
    trigP1 = false;
  }
  
  if(valP2 == LOW && trigP2 == false){
    trigP2 = true;
    trigOnP2 = micros();
  }
  
  if (valP2 == HIGH && trigP2 == true){
    durationP2 = micros() - trigOnP2;
    lowpulseoccupancyP2 = lowpulseoccupancyP2 + durationP2;
    trigP2 = false;
  }
#endif
  // Checking if it is time to sample
  if ((millis()-starttime) > sampletime_ms)
  {
#ifdef PPD_ACTIVE
    ratio = lowpulseoccupancyP1/(sampletime_ms*10.0);                 // int percentage 0 to 100
    concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // spec sheet curve
    // Begin printing
    Serial.print("LPO P10     : ");
    Serial.println(lowpulseoccupancyP1);
    Serial.print("Ratio PM10  : ");
    Serial.print(ratio);
    Serial.println(" %");
    Serial.print("PM10 Count  : ");
    Serial.println(concentration);

    // json for push to api / P1
    data = "{\"software_version\": \"";
    data += SOFTWARE_VERSION_INITIALS;
    data += "_";
    data += SOFTWARE_VERSION_NUMBER;
    data += "\",";
    data += "\"sensordatavalues\":[{";
    data += "\"value_type\":\"durP1\",\"value\":\"";
    data += long(lowpulseoccupancyP1);
    data += "\"},{";
    data += "\"value_type\":\"ratioP1\",\"value\":\"";
    data += Float2String(ratio);
    data += "\"},{";
    data += "\"value_type\":\"P1\",\"value\":\"";
    data += Float2String(concentration);
    data += "\"},{";

    ratio = lowpulseoccupancyP2/(sampletime_ms*10.0);
    concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62;
    // Begin printing
    Serial.print("LPO PM25    : ");
    Serial.println(lowpulseoccupancyP2);
    Serial.print("Ratio PM25  : ");
    Serial.print(ratio);
    Serial.println(" %");
    Serial.print("PM25 Count  : ");
    Serial.println(concentration);

    // json for push to api / P2
    data += "\"value_type\":\"durP2\",\"value\":\"";
    data += long(lowpulseoccupancyP2);
    data += "\"},{";
    data += "\"value_type\":\"ratioP2\",\"value\":\"";
    data += Float2String(ratio);
    data += "\"},{";
    data += "\"value_type\":\"P2\",\"value\":\"";
    data += Float2String(concentration);
    data += "\"}]}";

    //sending to dustix api
    Serial.println("#### Sending to dusti.xyz: ");
    // -1 -> '-' is default for ppd
    sendData(data,-1);
    
    // Resetting for next sampling
    lowpulseoccupancyP1 = 0;
    lowpulseoccupancyP2 = 0;
#endif
    starttime = millis(); // store the start time


    // FIXME: option to send PIN
#ifdef DHT_ACTIVE
    sensorDHT();  // getting temperature and humidity (optional)
    Serial.println("------------------------------");
#endif
#ifdef DS_ACTIVE
    DSpush();
#endif
  }
}
