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
/* DHT declaration 
/**********************************************/
#include <DHT.h>
// change the following in sensorconfig.h
#define DHTPIN 4 // = GPIO PIN, not D
#define DHTTYPE DHT22

/**********************************************/
/* onewire ds18x20 temperature sensor declaration 
/**********************************************/
// derived from https://github.com/esp8266/Arduino/blob/esp8266/libraries/OneWire/examples/DS18x20_Temperature/DS18x20_Temperature.pde
#include <OneWire.h>
#define ONEWIRE_PIN 15 // 15=D8
// on pin ONEWIRE_PIN = GPIO (a 4.7K pullup resistor is necessary)
byte dsaddr[8];

/**********************************************/
/* WiFi declarations now in sensorconfig.h
/**********************************************/
#include <ESP8266WiFi.h>
int value = 0;

/**********************************************/
/* Variable Definitions for PPD24NS           */
/**********************************************/
#define  PPD42_P1_PIN 12
#define  PPD42_P2_PIN 14

/**********************************************/
/* read sensorconfig.h configure your PINs and WIFI there */
/**********************************************/

#include "sensorconfig.h"


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

unsigned long sampletime_ms = 15000;
unsigned long lowpulseoccupancyP1 = 0;
unsigned long lowpulseoccupancyP2 = 0;

float ratio = 0;
float concentration = 0;

DHT dht(DHTPIN, DHTTYPE);
OneWire  ds(ONEWIRE_PIN);


/**********************************************/
/* The Setup
/**********************************************/
void setup() {
  Serial.begin(9600); //Output to Serial at 9600 baud
  delay(10);
  pinMode(12,INPUT); // Listen at the designated PIN
  pinMode(14,INPUT); //Listen at the designated PIN
  starttime = millis(); // store the start time
  Serial.print("init DHT");
  Serial.println();
  dht.begin(); // Start DHT
  delay(10);
  
  Serial.print("init DS");
  Serial.println();
  DSinit();
  delay(10);
  // connectWifi(); // Start ConnecWifi 
  Serial.print("\n"); 
}

/**********************************************/
/* And action
/**********************************************/
void loop() {
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
    Serial.print(lowpulseoccupancyP1);
    Serial.print("\n");
    Serial.print("Ratio PM10  : ");
    Serial.print(ratio);
    Serial.print(" %");
    Serial.print("\n");
    Serial.print("PM10 Count  : ");
    Serial.print(concentration);
    Serial.println("\n");

    ratio = lowpulseoccupancyP2/(sampletime_ms*10.0);
    concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62;
    // Begin printing
    Serial.print("LPO PM25    : ");
    Serial.print(lowpulseoccupancyP2);
    Serial.print("\n");
    Serial.print("Ratio PM25  : ");
    Serial.print(ratio);
    Serial.print(" %");
    Serial.print("\n");
    Serial.print("PM25 Count  : ");
    Serial.print(concentration);
    Serial.println("\n");
    
    // Resetting for next sampling
    lowpulseoccupancyP1 = 0;
    lowpulseoccupancyP2 = 0;
    starttime = millis(); // store the start time

    //connectiong to dusty api
    // Serial.println("#### Sending to Dusty: ");
    // connect2API();
    // Serial.print("\n");

    sensorDHT();  // getting temperature and humidity (optional)
    // Serial.print("------------------------------");
    // Serial.print("\n");
    sensorDS();
  }
}

/**********************************************/
/* DHT22 Sensor
/**********************************************/
void sensorDHT(){
  float h = dht.readHumidity(); //Read Humidity
  float t = dht.readTemperature(); //Read Temperature

  // Check if valid number if non NaN (not a number) will be send.
  if (isnan(t) || isnan(h)) {
    Serial.println("DHT22 could not be read");
  } else {
    Serial.print("Humidity    : ");
    Serial.print(h);
    Serial.print(" %\n");
    Serial.print("Temperature : ");
    Serial.print(t);
    Serial.println(" C");
    
    //Serial.println("#### Sending to Dusty: ");
    //connect2API();
    //Serial.print("\n");
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
  Serial.print("IP dsaddress: ");
  Serial.print(WiFi.localIP());
  Serial.print('\n');
}
/**********************************************/
/* Connect 2 API Script
/**********************************************/
void connect2API() {
  delay(60000);
  ++value;

  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 8000;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  // create an URI for the request
  String url = "/v1/push-sensor-data/";
  
  Serial.print("Requesting URL: ");
  Serial.println(url);
  Serial.println(ESP.getChipId());
  
  // send request to the server
  client.print(String("POST ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Content-Type: application/json\r\n" +
               "Sensor: esp8266-");
  client.println(ESP.getChipId());
  client.println("Connection: close\r\n");
  delay(1);
  
  // Read reply from server and print them
  while(client.available()){
    char c = client.read();
    Serial.print(c);
  }
  
  Serial.println();
  Serial.println("closing connection");
}

void DSinit(){
  byte i;
  byte type_s;
    ds.reset_search();
    if (!ds.search(dsaddr)) {
    Serial.println("No more addresses. No DS device found");
    Serial.println();
    ds.reset_search();
    delay(250);
    return;
  }
  
  Serial.print("ROM =");
  for( i = 0; i < 8; i++) {
    Serial.write(' ');
    Serial.print(dsaddr[i], HEX);
  }

  if (OneWire::crc8(dsaddr, 7) != dsaddr[7]) {
      Serial.println("CRC is not valid!");
      return;
  }
  Serial.println();
 
  // the first ROM byte indicates which chip
  switch (dsaddr[0]) {
    case 0x10:
      Serial.println("  Chip = DS18S20");  // or old DS1820
      type_s = 1;
      break;
    case 0x28:
      Serial.println("  Chip = DS18B20");
      type_s = 0;
      break;
    case 0x22:
      Serial.println("  Chip = DS1822");
      type_s = 0;
      break;
    default:
      Serial.println("Device is not a DS18x20 family device.");
      return;
  ds.reset();
  }
}

void sensorDS(){
  byte i;
  byte present = 0;
  byte type_s;
  byte data[12];
//  byte addr[8]; // replaced by dsaddr - a global var
  float celsius = -999;
  float fahrenheit = -999;

  ds.reset();
  ds.select(dsaddr);
  ds.write(0x44, 1);        // start conversion, with parasite power on at the end
  
  delay(1000);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.
  
  present = ds.reset();
  ds.select(dsaddr);    
  ds.write(0xBE);         // Read Scratchpad
  Serial.print("  Data = ");
  Serial.print(present, HEX);
  Serial.print(" ");
  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  Serial.print(" CRC=");
  Serial.print(OneWire::crc8(data, 8), HEX);
  Serial.println();

  // Convert the data to actual temperature
  // because the result is a 16 bit signed integer, it should
  // be stored to an "int16_t" type, which is always 16 bits
  // even when compiled on a 32 bit processor.
  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      // "count remain" gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    // at lower res, the low bits are undefined, so let's zero them
    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
    //// default is 12 bit resolution, 750 ms conversion time
  }
  celsius = (float)raw / 16.0;
  fahrenheit = celsius * 1.8 + 32.0;
  Serial.print("  Temperature = ");
  Serial.print(celsius);
  Serial.print(" Celsius, ");
  Serial.print(fahrenheit);
  Serial.println(" Fahrenheit");
  // TODO: call API

}

