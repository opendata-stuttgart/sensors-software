/*******************************************************/
/* OK LAB Particulate Matter Sensor                    */
/*      - nodemcu-LoLin board                          */
/*      - Shinyei PPD42NS                              */
/*      http://www.sca-shinyei.com/pdf/PPD42NS.pdf     */
/*                                                     */       
/* Wiring Instruction:                                 */
/*      Pin 2 of dust sensor PM2.5 -> Digital 6 (PWM)  */
/*      Pin 3 of dust sensor       -> +5V              */
/*      Pin 4 of dust sensor PM1   -> Digital 3 (PMW)  */ 
/*                                                     */
/*      - PPD42NS Pin 1 (grey)  => GND                 */
/*      - PPD42NS Pin 2 (green) => Pin D5 /GPIO14      */
/*        counts particles PM25                        */
/*      - PPD42NS Pin 3 (black) => Vin                 */
/*      - PPD42NS Pin 4 (white) => Pin D6 / GPIO12     */
/*        counts particles PM10                        */
/*      - PPD42NS Pin 5 (red)   => unused              */
/*                                                     */
/*      ATTENTION this is another wiring, from lua version */
/*      -- esp8266-12                                  */
/*         pin_P1=6  -- gpio12   black                 */
/*         pin_P2=5  -- gpio14   white                 */
/*         green => GND                                */
/*         yellow => Vin (5V)                          */
/* see datasheet http://sca-shinyei.com/pdf/PPD42NS.pdf */
/* CN : S5B-EH(JST) (PINs on sensor board)             */
/* 1 : COMMON(GND)                                     */
/* 2 : OUTPUT(P2)                                      */
/* 3 : INPUT(5VDC 90mA)                                */
/* 4 : OUTPUT(P1)                                      */
/* 5 : INPUT(T1)   FOR THRESHOLD FOR [P2]              */
/*                                                     */
/*******************************************************/
// nodemcu pins Dx - GPIOx
// 0 [*]   GPIO16
// 1       GPIO5
// 2       GPIO4
// 3       GPIO0
// 4       GPIO2
// 5       GPIO14 (SPI CLK)
// 6       GPIO12 (SPI MISO)
// 7       GPIO13 (SPI MOSI)
// 8       GPIO15 (SPI CS)
// 9       GPIO3 (UART RX)
// 10      GPIO1 (UART TX)
// 11      GPIO9
// 12      GPIO10

/**********************************************/
/* read sensorconfig.h configure your sensors,*/
/* PINs and WIFI there                        */
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

/**********************************************/
/* The Setup
/**********************************************/
void setup() {
  Serial.begin(9600); //Output to Serial at 9600 baud
  delay(10);
  pinMode(12,INPUT); // Listen at the designated PIN
  pinMode(14,INPUT); //Listen at the designated PIN
  starttime = millis(); // store the start time

#ifdef DHT_ACTIVE
  Serial.print("init DHT");
  Serial.println();
  dht.begin(); // Start DHT
  delay(10);
#endif

#ifdef DS_ACTIVE
  Serial.print("init DS");
  Serial.println();
  DSinit();
  delay(10);
#endif
  // connectWifi(); // Start ConnecWifi 
  Serial.print("\n"); 
}

/**********************************************/
/* And action
/**********************************************/
void loop() {
  String data;
  // Read pins connected to ppd42ns
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

  // Checking if it is time to sample
  if ((millis()-starttime) > sampletime_ms)
  {
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
    data = "{\"sensordatavalues\":[{";
    data += "\"value_type\":\"durP1\",\"value\":\"";
    data += Float2String(lowpulseoccupancyP1);
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
    data += Float2String(lowpulseoccupancyP1);
    data += "\"},{";
    data += "\"value_type\":\"ratioP2\",\"value\":\"";
    data += Float2String(ratio);
    data += "\"},{";
    data += "\"value_type\":\"P2\",\"value\":\"";
    data += Float2String(concentration);
    data += "\"}]}";

    //sending to dustix api
    Serial.println("#### Sending to dusti.xyz: ");
    sendData(data);
    
    // Resetting for next sampling
    lowpulseoccupancyP1 = 0;
    lowpulseoccupancyP2 = 0;
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
