/*****************************************************************/
/* OK LAB Particulate Matter Sensor                              */
/*      - nodemcu-LoLin board                                    */
/*      - Shinyei PPD42NS                                        */
/*      http://www.sca-shinyei.com/pdf/PPD42NS.pdf               */
/*                                                               */
/* Wiring Instruction:                                           */
/*      Pin 2 of dust sensor PM2.5 -> Digital 6 (PWM)            */
/*      Pin 3 of dust sensor       -> +5V                        */
/*      Pin 4 of dust sensor PM1   -> Digital 3 (PMW)            */ 
/*                                                               */
/*      - PPD42NS Pin 1 (grey or green)  => GND                  */
/*      - PPD42NS Pin 2 (green or white)) => Pin D5 /GPIO14      */
/*        counts particles PM25                                  */
/*      - PPD42NS Pin 3 (black or yellow) => Vin                 */
/*      - PPD42NS Pin 4 (white or black) => Pin D6 / GPIO12      */
/*        counts particles PM10                                  */
/*      - PPD42NS Pin 5 (red)   => unused                        */
/*                                                               */
/*****************************************************************/
/*                                                               */
/* Alternative                                                   */
/*      - nodemcu-LoLin board                                    */
/*      - Nova SDS0111                                           */
/*  ﻿http://inovafitness.com/en/Laser-PM2-5-Sensor-SDS011-35.html */
/*                                                               */
/* Wiring Instruction:                                           */
/*      - SDS011 Pin 1  (TX)   -> Pin D1 / GPIO5                 */
/*      - SDS011 Pin 2  (RX)   -> Pin D2 / GPIO4                 */
/*      - SDS011 Pin 3  (GND)  -> GND                            */
/*      - SDS011 Pin 4  (2.5m) -> unused                         */
/*      - SDS011 Pin 5  (5V)   -> Vin                            */
/*      - SDS011 Pin 6  (1m)   -> unused                         */
/*                                                               */
/*****************************************************************/
/* Extension: DHT22 (AM2303)                                     */
/*  ﻿http://www.aosong.com/en/products/details.asp?id=117         */
/*                                                               */
/* DHT22 Wiring Instruction                                      */
/* (left to right, front is perforated side):                    */
/*      - DHT22 Pin 1 (VDD)     -> Pin 3V3 (3.3V)                */
/*      - DHT22 Pin 2 (DATA)    -> Pin D4 (GPIO4)                */
/*      - DHT22 Pin 3 (NULL)    -> unused                        */
/*      - DHT22 Pin 4 (GND)     -> Pin GND                       */
/*                                                               */
/*****************************************************************/
// increment on change
#define SOFTWARE_VERSION "NRZ-2016-003"

#include "FS.h"

// #define WLANSSID "Freifunk"
// #define WLANPWD ""

// #define DHT_READ 0
// #define PPD_READ 1
// #define SDS_READ 0

/**********************************************/
/* WiFi declarations                          */
/**********************************************/
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

char wlanssid[64] = "Freifunk";
char wlanpwd[64] = "";

bool ppd_read = 1;
bool sds_read = 0;
bool dht_read = 0;

#include "ext_def.h"

const char* host_madavi = "www.madavi.de";
const char* url_madavi = "/sensor/data.php";

const char* host_dusti = "api.dusti.xyz";
const char* url_dusti = "/v1/push-sensor-data/";

const int   httpPort = 80;

int value = 0;

/**********************************************/
/* SDS011 declarations                        */
/**********************************************/

#include <SoftwareSerial.h>
#define SDSPINRX 5
#define SDSPINTX 4

SoftwareSerial serialSDS(SDSPINRX, SDSPINTX, 128);

/**********************************************/
/* DHT declaration 
/**********************************************/
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

/**********************************************/
/* Variable Definitions for PPD24NS
/**********************************************/
#define PPDPINP1 12
#define PPDPINP2 14

// P1 for PM10 & P2 for PM25
boolean valP1 = HIGH;
boolean valP2 = HIGH;
unsigned long durationP1;
unsigned long durationP2;

boolean trigP1 = false;
boolean trigP2 = false;
unsigned long trigOnP1;
unsigned long trigOnP2;

unsigned long lowpulseoccupancyP1 = 0;
unsigned long lowpulseoccupancyP2 = 0;

unsigned long starttime;
unsigned long starttime_SDS;
unsigned long act_micro;
unsigned long act_milli;

unsigned long sampletime_ms = 30000;
unsigned long sampletime_SDS_ms = 1000;

int sds_pm10_sum = 0;
int sds_pm25_sum = 0;
int sds_val_count = 0;

/**********************************************/
/* WiFi connecting script                     */
/**********************************************/
void connectWifi() {
  WiFi.begin(wlanssid, wlanpwd); // Start WiFI
  
  Serial.print("Connecting to ");
  Serial.print(wlanssid);
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
/* convert float to string with a             */
/* precision of two decimal places            */
/**********************************************/
String Float2String(float value) {
  // Convert a float to String with two decimals.
  char temp[15];
  String s;

  dtostrf(value,13, 2, temp);
  s = String(temp);
  s.trim();
  return s;
}

/**********************************************/
/* send data to rest api                      */
/**********************************************/
void sendData(const String& data, const char* host, const int httpPort, const char* url) {

  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  Serial.print("Requesting URL: ");
  Serial.println(url);
  Serial.println(ESP.getChipId());
  Serial.println(data);
  
  // send request to the server
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
  Serial.println("------------------------------");    
  Serial.println();
  Serial.println();
}

// DHT22 Sensor
String sensorDHT() {
  String s = "";
  float h = dht.readHumidity(); //Read Humidity
  float t = dht.readTemperature(); //Read Temperature

  // Check if valid number if non NaN (not a number) will be send.
  if (isnan(t) || isnan(h)) {
    Serial.println("DHT22 couldn't be read");
  } else {
    Serial.println("Humidity    : "+String(h)+"%");
    Serial.println("Temperature : "+String(t)+" C");
	s += "{\"value_type\":\"temp\",\"value\":\"";
    s += Float2String(t);
    s += "\"},";
    s += "{\"value_type\":\"humidity\",\"value\":\"";
    s += Float2String(h);
    s += "\"},";
  }
  Serial.println("------------------------------");    
  return s;
}

// SDS011 Sensor
String sensorSDS() {
  String s = "";
  String value_hex;
  char buffer;
  int value;
  int len = 0;
  int pm10_serial = 0;
  int pm25_serial = 0;
  int checksum_is;
  int checksum_ok = 0;
  int position = 0;
  while (serialSDS.available() > 0) {
    buffer = serialSDS.read();
//  Serial.println(String(len)+" - "+String(buffer,DEC)+" - "+String(buffer,HEX)+" - "+int(buffer)+" .");
    value = int(buffer);
    value_hex = String(value,HEX);
    switch (len) {
      case (0): if (! value_hex.equals("aa")) { len = -1; }; break;
      case (1): if (! value_hex.equals("c0")) { len = -1; }; break;
      case (2): pm25_serial = value; checksum_is  = value; break;
      case (3): pm25_serial += 256 * value; checksum_is += value; break;
      case (4): pm10_serial = value; checksum_is += value; break;
      case (5): pm10_serial += 256 * value; checksum_is += value; break;
      case (6): checksum_is += value; break;
      case (7): checksum_is += value; break;
      case (8):
//      Serial.println("Checksum is: "+String(checksum_is % 256)+" - should: "+String(value));
        if (value == (checksum_is % 256)) { checksum_ok = 1; } else { len = -1; }; break;
      case (9): if (! value_hex.equals("ab")) { len = -1; }; break;
    }
    len++;
    if (len == 10 && checksum_ok == 1) {
      sds_pm10_sum += pm10_serial;
      sds_pm25_sum += pm25_serial;
      sds_val_count++;
      len = 0; checksum_ok = 0; pm10_serial = 0.0; pm25_serial = 0.0; checksum_is = 0;
    }
    yield();
  }
  if ((act_milli-starttime) > sampletime_ms) {
    Serial.println("PM10:  "+Float2String(float(sds_pm10_sum)/(sds_val_count*10.0)));
    Serial.println("PM2.5: "+Float2String(float(sds_pm25_sum)/(sds_val_count*10.0)));
    Serial.println("------------------------------");    
    s += "{\"value_type\":\"SDS_P1\",\"value\":\"";
    s += Float2String(float(sds_pm10_sum)/(sds_val_count*10.0));
    s += "\"},";
    s += "{\"value_type\":\"SDS_P2\",\"value\":\"";
    s += Float2String(float(sds_pm25_sum)/(sds_val_count*10.0));
    s += "\"},";
    sds_pm10_sum = 0; sds_pm25_sum = 0; sds_val_count = 0;
  }
  return s;
}

// PPD42NS Sensor 
String sensorPPD() {
  float ratio = 0;
  float concentration = 0;
  String s = "";
  
  // Read pins connected to ppd42ns
  valP1 = digitalRead(PPDPINP1);
  valP2 = digitalRead(PPDPINP2);

  if(valP1 == LOW && trigP1 == false){
    trigP1 = true;
    trigOnP1 = act_micro;
  }
  
  if (valP1 == HIGH && trigP1 == true){
    durationP1 = act_micro - trigOnP1;
    lowpulseoccupancyP1 = lowpulseoccupancyP1 + durationP1;
    trigP1 = false;
  }
  
  if(valP2 == LOW && trigP2 == false){
    trigP2 = true;
    trigOnP2 = act_micro;
  }
  
  if (valP2 == HIGH && trigP2 == true){
    durationP2 = act_micro - trigOnP2;
    lowpulseoccupancyP2 = lowpulseoccupancyP2 + durationP2;
    trigP2 = false;
  }

  // Checking if it is time to sample
  if ((act_milli-starttime) > sampletime_ms) {
    ratio = lowpulseoccupancyP1/(sampletime_ms*10.0);                 // int percentage 0 to 100
    concentration = (1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62); // spec sheet curve
    // Begin printing
    Serial.print("LPO P10     : ");
	Serial.println(lowpulseoccupancyP1);
    Serial.print("Ratio PM10  : ");
	Serial.print(Float2String(ratio));
	Serial.println(" %");
    Serial.print("PM10 Count  : ");
	Serial.println(Float2String(concentration));

    // json for push to api / P1
    s += "{\"value_type\":\"durP1\",\"value\":\"";
    s += long(lowpulseoccupancyP1);
    s += "\"},";
    s += "{\"value_type\":\"ratioP1\",\"value\":\"";
    s += Float2String(ratio);
    s += "\"},";
    s += "{\"value_type\":\"P1\",\"value\":\"";
    s += Float2String(concentration);
    s += "\"},";

    ratio = lowpulseoccupancyP2/(sampletime_ms*10.0);
    concentration = (1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62);
    // Begin printing
    Serial.print("LPO PM25    : ");
	Serial.println(lowpulseoccupancyP2);
    Serial.print("Ratio PM25  : ");
	Serial.print(Float2String(ratio));
	Serial.println(" %");
    Serial.print("PM25 Count  : ");
	Serial.println(Float2String(concentration));

    // json for push to api / P2
    s += "{\"value_type\":\"durP2\",\"value\":\"";
    s += long(lowpulseoccupancyP1);
    s += "\"},";
    s += "{\"value_type\":\"ratioP2\",\"value\":\"";
    s += Float2String(ratio);
    s += "\"},";
    s += "{\"value_type\":\"P2\",\"value\":\"";
    s += Float2String(concentration);
    s += "\"},";

    Serial.println("------------------------------");    
  }
  return s;
}

/**********************************************/
/* copy config from ext_def                   */
/**********************************************/
void copyExtDef() {
	if (WLANSSID != NULL) { strcpy(wlanssid,WLANSSID); }
	if (WLANPWD  != NULL) { strcpy(wlanpwd,WLANPWD); }
	if (DHT_READ != dht_read) { dht_read = DHT_READ; }
	if (PPD_READ != ppd_read) { ppd_read = PPD_READ; }
	if (SDS_READ != sds_read) { sds_read = SDS_READ; }
}

/**********************************************/
/* write config to spiffs                     */
/**********************************************/
void writeConfig() {
    Serial.println("saving config");
    DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();
    json["wlanssid"] = wlanssid;
    json["wlanpwd"] = wlanpwd;
    json["dht_read"] = dht_read;
    json["ppd_read"] = ppd_read;
    json["sds_read"] = sds_read;

    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile) {
      Serial.println("failed to open config file for writing");
    }

    json.printTo(Serial);
    json.printTo(configFile);
    configFile.close();
    //end save
}

/**********************************************/
/* read config from spiffs                    */
/**********************************************/
void readConfig() {
  Serial.println("mounting FS...");

  if (SPIFFS.begin()) {
    Serial.println("mounted file system");
    if (SPIFFS.exists("/config.json")) {
      //file exists, reading and loading
      Serial.println("reading config file");
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile) {
        Serial.println("opened config file");
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        json.printTo(Serial);
        if (json.success()) {
          Serial.println("\nparsed json");
          strcpy(wlanssid, json["wlanssid"]);
          strcpy(wlanpwd, json["wlanpwd"]);
          dht_read = json["dht_read"];
          ppd_read = json["ppd_read"];
          sds_read = json["sds_read"];
          Serial.print(" - "); Serial.println(wlanssid);
          Serial.print(" - "); Serial.println(wlanpwd);
          Serial.print(" - "); Serial.println(dht_read);
          Serial.print(" - "); Serial.println(ppd_read);
          Serial.print(" - "); Serial.println(sds_read);
        } else {
          Serial.println("failed to load json config");
		  writeConfig();
        }
      }
    } else {
          Serial.println("config file not found ...");
		  writeConfig();		
	}
  } else {
    Serial.println("failed to mount FS");
  }
}

/**********************************************/
/* AutoUpdate                                 */
/**********************************************/
void autoUpdate() {
}

/**********************************************/
/* WifiConfig                                 */
/**********************************************/
void wifiConfig() {
}

/**********************************************/
/* The Setup                                  */
/**********************************************/
void setup() {
  Serial.begin(9600); //Output to Serial at 9600 baud
  copyExtDef();
  readConfig();
  pinMode(PPDPINP1,INPUT_PULLUP); // Listen at the designated PIN
  pinMode(PPDPINP2,INPUT_PULLUP); //Listen at the designated PIN
  dht.begin(); // Start DHT
  delay(10);
  connectWifi(); // Start ConnecWifi 
  Serial.print("\n"); 
  Serial.println("ChipId: ");
  Serial.println(ESP.getChipId());
  if(ppd_read) { Serial.println("Lese PPD...");}
  if(sds_read) { Serial.println("Lese SDS...");}
  if(dht_read) { Serial.println("Lese DHT...");}
  starttime = millis(); // store the start time
  starttime_SDS = millis();
}

/**********************************************/
/* And action                                 */
/**********************************************/
void loop() {
  String data = "";

  act_micro = micros();
  act_milli = millis();

  String result_PPD;
  String result_SDS;
  String result_DHT;
  
  if (PPD_READ) {
	result_PPD = sensorPPD();
  }
  
  if (SDS_READ && (((act_milli-starttime_SDS) > sampletime_SDS_ms) || ((act_milli-starttime) > sampletime_ms))) {
	  result_SDS = sensorSDS();
	  starttime_SDS = act_milli;
  }
  
  if (DHT_READ && ((act_milli-starttime) > sampletime_ms)) {
    result_DHT = sensorDHT();  // getting temperature and humidity (optional)
  }

  if ((act_milli-starttime) > sampletime_ms) {
    Serial.println("Creating data string:");
    data = "{\"software_version\": \"";
    data += SOFTWARE_VERSION;
    data += "\",";
    data += "\"sensordatavalues\":[";
    if (PPD_READ) {data += result_PPD;}
    if (SDS_READ) {data += result_SDS;}
    if (DHT_READ) {data += result_DHT;}
    if ((result_PPD.length() > 0) || (result_DHT.length() > 0) || (result_SDS.length() > 0)) {
		data.remove(data.length()-1);
	}
    data += "]}";

    //sending to api
    Serial.println("#### Sending to madavi.de: ");
    sendData(data,host_madavi,httpPort,url_madavi);
    //Serial.println("#### Sending to dusti.xyz: ");
    //sendData(data,host_dusti,httpPort,url_dusti);
    
    // Resetting for next sampling
    lowpulseoccupancyP1 = 0;
    lowpulseoccupancyP2 = 0;
    starttime = millis(); // store the start time
  }
  yield();
}
