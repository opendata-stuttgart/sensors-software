/************************************************************/
/* OK LAB Particulate Matter Sensor                         */
/*      - nodemcu-LoLin board                               */
/*      - Shinyei PPD42NS                                   */
/*      http://www.sca-shinyei.com/pdf/PPD42NS.pdf          */
/*                                                          */       
/* Wiring Instruction:                                      */
/*      Pin 2 of dust sensor PM2.5 -> Digital 6 (PWM)       */
/*      Pin 3 of dust sensor       -> +5V                   */
/*      Pin 4 of dust sensor PM1   -> Digital 3 (PMW)       */ 
/*                                                          */
/*      - PPD42NS Pin 1 (grey or green)  => GND             */
/*      - PPD42NS Pin 2 (green or white)) => Pin D5 /GPIO14 */
/*        counts particles PM25                             */
/*      - PPD42NS Pin 3 (black or yellow) => Vin            */
/*      - PPD42NS Pin 4 (white or black) => Pin D6 / GPIO12 */
/*        counts particles PM10                             */
/*      - PPD42NS Pin 5 (red)   => unused                   */
/*                                                          */
/************************************************************/

/**********************************************/
/* DHT declaration 
/**********************************************/
#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

/**********************************************/
/* WiFi declarations
/**********************************************/
#include <ESP8266WiFi.h>

const char* ssid = "Freifunk";
const char* password = "";
// const char* host = "";
const char* host = "api.dusti.xyz";
// const int httpPort = 8000;
const int httpPort = 80;
int value = 0;

/**********************************************/
/* Variable Definitions for PPD24NS
/**********************************************/
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

unsigned long sampletime_ms = 30000;
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
//  dht.begin(); // Start DHT
  delay(10);
  connectWifi(); // Start ConnecWifi 
  Serial.print("\n"); 
}

/**********************************************/
/* And action
/**********************************************/
void loop() {
  String data;

  // Read pins connected to ppd42ns
  valP1 = digitalRead(12);
  valP2 = digitalRead(14);

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
    sendData(data);
    
    // Resetting for next sampling
    lowpulseoccupancyP1 = 0;
    lowpulseoccupancyP2 = 0;
    starttime = millis(); // store the start time

    // FIXME: option to send PIN
    // sensorDHT();  // getting temperature and humidity (optional)
    Serial.println("------------------------------");
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
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
/**********************************************/
/* send data to rest api
/**********************************************/
void sendData(const String& data) {
  //  delay(60000);
  ++value;

  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  // create an URI for the request
  String url = "/v1/push-sensor-data/";
  
  Serial.print("Requesting URL: ");
  Serial.println(url);
  Serial.println(ESP.getChipId());
  Serial.println(data);
  
  // send request to the server
              // "PIN: ": + "-" + "\r\n" +
  client.print(String("POST ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Content-Type: application/json\r\n" +
               "Sensor: esp8266-");
  client.println(ESP.getChipId());
  client.print("Content-Length: ");
  client.println(data.length(), DEC);
  client.println("Connection: close\r\n");

  client.println(data);

  delay(1);
  
  // Read reply from server and print them
  while(client.available()){
    char c = client.read();
    Serial.print(c);
  }
  
  Serial.println();
  Serial.println("closing connection");
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

