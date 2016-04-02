/*****************************************************************
/* OK LAB Particulate Matter Sensor                              *
/*      - nodemcu-LoLin board                                    *
/*      - Shinyei PPD42NS                                        *
/*      http://www.sca-shinyei.com/pdf/PPD42NS.pdf               *
/*                                                               *
/* Wiring Instruction:                                           *
/*      Pin 2 of dust sensor PM2.5 -> Digital 6 (PWM)            *
/*      Pin 3 of dust sensor       -> +5V                        *
/*      Pin 4 of dust sensor PM1   -> Digital 3 (PMW)            * 
/*                                                               *
/*      - PPD42NS Pin 1 (grey or green)  => GND                  *
/*      - PPD42NS Pin 2 (green or white)) => Pin D5 /GPIO14      *
/*        counts particles PM25                                  *
/*      - PPD42NS Pin 3 (black or yellow) => Vin                 *
/*      - PPD42NS Pin 4 (white or black) => Pin D6 / GPIO12      *
/*        counts particles PM10                                  *
/*      - PPD42NS Pin 5 (red)   => unused                        *
/*                                                               *
/*****************************************************************
/*                                                               *
/* Alternative                                                   *
/*      - nodemcu-LoLin board                                    *
/*      - Nova SDS0111                                           *
/*  ﻿http://inovafitness.com/en/Laser-PM2-5-Sensor-SDS011-35.html *
/*                                                               *
/* Wiring Instruction:                                           *
/*      - SDS011 Pin 1  (TX)   -> Pin D1 / GPIO5                 *
/*      - SDS011 Pin 2  (RX)   -> Pin D2 / GPIO4                 *
/*      - SDS011 Pin 3  (GND)  -> GND                            *
/*      - SDS011 Pin 4  (2.5m) -> unused                         *
/*      - SDS011 Pin 5  (5V)   -> Vin                            *
/*      - SDS011 Pin 6  (1m)   -> unused                         *
/*                                                               *
/*****************************************************************
/* Extension: DHT22 (AM2303)                                     *
/*  ﻿http://www.aosong.com/en/products/details.asp?id=117         *
/*                                                               *
/* DHT22 Wiring Instruction                                      *
/* (left to right, front is perforated side):                    *
/*      - DHT22 Pin 1 (VDD)     -> Pin 3V3 (3.3V)                *
/*      - DHT22 Pin 2 (DATA)    -> Pin D4 (GPIO2)                *
/*      - DHT22 Pin 3 (NULL)    -> unused                        *
/*      - DHT22 Pin 4 (GND)     -> Pin GND                       *
/*                                                               *
/*****************************************************************/
// increment on change
#define SOFTWARE_VERSION "NRZ-2016-008"

/*****************************************************************
/* Global definitions (moved to ext_def.h)                       *
/* #define WLANSSID "Freifunk"                                   *
/* #define WLANPWD ""                                            *
/*                                                               *
/* #define DHT_READ 0                                            *
/* #define PPD_READ 1                                            *
/* #define SDS_READ 0                                            *
/*                                                               *
/* #define SEND2DUSTI 0                                          *
/* #define SEND2MADAVI 1                                         *
/* #define SEND2MQTT 0                                           *
/* #define SEND2CSV 0                                            *
/*                                                               *
/* #define DEBUG 1                                               *
/*****************************************************************/

/*****************************************************************
/* Includes                                                      *
/*****************************************************************/
#include <FS.h>                     // must be first
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

#include "DHT.h"

#include "ext_def.h"

/*****************************************************************
/* Variables with defaults                                       *
/*****************************************************************/
char wlanssid[65] = "Freifunk";
char wlanpwd[65] = "";

bool dht_read = 0;
bool dht_pin  = 2;
int  dht_type = DHT22;
bool ppd_read = 1;
int  ppd_pin_pm1 = 12;
int  ppd_pin_pm2 = 14;
bool sds_read = 0;
int  sds_pin_rx = 4;
int  sds_pin_tx = 5;
bool send2dusti = 1;
bool send2madavi = 0;
bool send2mqtt = 0;
bool send2csv = 0;
bool debug = 1;

const char* host_madavi = "www.madavi.de";
const char* url_madavi = "/sensor/data.php";
const int httpPort_madavi = 80;

const char* host_dusti = "api.luftdaten.info";
const char* url_dusti = "/v1/push-sensor-data/";
const int httpPort_dusti = 80;

const char* host_mqtt = "mqtt.opensensors.io";
const char* mqtt_user = "";
const char* mqtt_pw = "";
const char* mqtt_client_id = "";
const char* mqtt_topic = "";

/*****************************************************************
/* SDS011 declarations                                           *
/*****************************************************************/
SoftwareSerial serialSDS(sds_pin_rx, sds_pin_tx, 128);

/*****************************************************************
/* DHT declaration                                               *
/*****************************************************************/
DHT dht(dht_pin, dht_type);

/*****************************************************************
/* Variable Definitions for PPD24NS                              *
/*****************************************************************/

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

bool first_csv_line = 1;

String debug_before_write = "";

/*****************************************************************
/* Debug output                                                  *
/*****************************************************************/
void debug_out(const String& text, int level) {
	if (level <= debug) {
		Serial.print(text);
	}
}

/*****************************************************************
/* WifiConfig                                                    *
/*****************************************************************/
void wifiConfig() {
  String boolvar;
  String apname;
  String custom_wlanssid;
  String custom_wlanpwd;
  WiFiManager wifiManager;

  if (! debug) wifiManager.setDebugOutput(false);
  boolvar = (send2dusti) ? '1' : '0';
  WiFiManagerParameter custom_send2dusti("send2dusti", "Senden an luftdaten.info (0/1) ?", "", 10);
  wifiManager.addParameter(&custom_send2dusti);
  boolvar = (send2madavi) ? '1' : '0';
  WiFiManagerParameter custom_send2madavi("send2madavi", "Senden an madavi.de (0/1) ?", "", 10);
  wifiManager.addParameter(&custom_send2madavi);
  boolvar = (send2csv) ? '1' : '0';
  WiFiManagerParameter custom_send2csv("send2csv", "Seriell als CSV (0/1) ?", "", 10);
  wifiManager.addParameter(&custom_send2csv);
  boolvar = (dht_read) ? '1' : '0';
  WiFiManagerParameter custom_dht_read("dht_read", "DHT Sensor (0/1) ?", "", 10);
  wifiManager.addParameter(&custom_dht_read);
  WiFiManagerParameter custom_dht_pin("dht_pin", "DHT PIN (GPIO) ?", "", 10);
  wifiManager.addParameter(&custom_dht_pin);
  WiFiManagerParameter custom_dht_type("dht_type", "DHT Type (11,21,22)?", "", 10);
  wifiManager.addParameter(&custom_dht_type);
  boolvar = (ppd_read) ? '1' : '0';
  WiFiManagerParameter custom_ppd_read("ppd_read", "PPD42NS Sensor (0/1) ?", "", 10);
  wifiManager.addParameter(&custom_ppd_read);
  WiFiManagerParameter custom_ppd_pin_pm1("ppd_pin_pm1", "PPD42NS PIN PM1 (GPIO) ?", "", 10);
  wifiManager.addParameter(&custom_ppd_pin_pm1);
  WiFiManagerParameter custom_ppd_pin_pm2("ppd_pin_pm2", "PPD42NS PIN PM2 (GPIO) ?", "", 10);
  wifiManager.addParameter(&custom_ppd_pin_pm2);
  boolvar = (sds_read) ? '1' : '0';
  WiFiManagerParameter custom_sds_read("sds_read", "SDS Sensor (0/1) ?", "", 10);
  wifiManager.addParameter(&custom_sds_read);
  WiFiManagerParameter custom_sds_pin_rx("sds_pin_rx", "SDS PIN RX (GPIO) ?", "", 10);
  wifiManager.addParameter(&custom_sds_pin_rx);
  WiFiManagerParameter custom_sds_pin_tx("sds_pin_tx", "SDS PIN TX (GPIO) ?", "", 10);
  wifiManager.addParameter(&custom_sds_pin_tx);
  boolvar = (debug) ? '1' : '0';
  WiFiManagerParameter custom_debug("debug", "Debug output (0/1) ?", "", 10);
  wifiManager.addParameter(&custom_debug);
  apname  = "Feinstaubsensor-";
  apname += ESP.getChipId();
  wifiManager.setTimeout(300);
  wifiManager.setBreakAfterConfig(true);
  wifiManager.startConfigPortal(apname.c_str());
  custom_wlanssid = WiFi.SSID();
  custom_wlanpwd = WiFi.psk();
  strcpy(wlanssid,custom_wlanssid.c_str());
  strcpy(wlanpwd,custom_wlanpwd.c_str());
  if (strcmp(custom_dht_read.getValue(),"") != 0) dht_read = strtol(custom_dht_read.getValue(), NULL, 10);
  if (strcmp(custom_dht_pin.getValue(),"")  != 0) dht_pin  = strtol(custom_dht_pin.getValue(), NULL, 10);
  if (strcmp(custom_dht_type.getValue(),"") != 0) dht_type = strtol(custom_dht_type.getValue(), NULL, 10);
  if (strcmp(custom_ppd_read.getValue(),"") != 0) ppd_read = strtol(custom_ppd_read.getValue(), NULL, 10);
  if (strcmp(custom_ppd_pin_pm1.getValue(),"") != 0) ppd_pin_pm1 = strtol(custom_ppd_pin_pm1.getValue(), NULL, 10);
  if (strcmp(custom_ppd_pin_pm2.getValue(),"") != 0) ppd_pin_pm2 = strtol(custom_ppd_pin_pm2.getValue(), NULL, 10);
  if (strcmp(custom_sds_read.getValue(),"") != 0) sds_read = strtol(custom_sds_read.getValue(), NULL, 10);
  if (strcmp(custom_sds_pin_rx.getValue(),"") != 0) sds_pin_rx = strtol(custom_sds_pin_rx.getValue(), NULL, 10);
  if (strcmp(custom_sds_pin_tx.getValue(),"") != 0) sds_pin_tx = strtol(custom_sds_pin_tx.getValue(), NULL, 10);
  if (strcmp(custom_send2dusti.getValue(),"") != 0) send2dusti = strtol(custom_send2dusti.getValue(), NULL, 10);
  if (strcmp(custom_send2madavi.getValue(),"") != 0) send2madavi = strtol(custom_send2madavi.getValue(), NULL, 10);
  if (strcmp(custom_send2csv.getValue(),"") != 0) send2csv = strtol(custom_send2csv.getValue(), NULL, 10);
  if (strcmp(custom_debug.getValue(),"") != 0) debug = strtol(custom_debug.getValue(), NULL, 10);
  if (debug) {
	Serial.println("------ Result from Webconfig ------");
    Serial.print("WLANSSID: ");Serial.println(wlanssid);
    Serial.print("DHT_read: ");Serial.print(custom_dht_read.getValue());Serial.print(" - ");Serial.println(dht_read);
    Serial.print("PPD_read: ");Serial.print(custom_ppd_read.getValue());Serial.print(" - ");Serial.println(ppd_read);
    Serial.print("SDS_read: ");Serial.print(custom_sds_read.getValue());Serial.print(" - ");Serial.println(sds_read);
    Serial.print("Dusti   : ");Serial.print(custom_send2dusti.getValue());Serial.print(" - ");Serial.println(send2dusti);
    Serial.print("Madavi  : ");Serial.print(custom_send2madavi.getValue());Serial.print(" - ");Serial.println(send2madavi);
    Serial.print("CSV     : ");Serial.print(custom_send2csv.getValue());Serial.print(" - ");Serial.println(send2csv);
    Serial.print("Debug   : ");Serial.print(custom_debug.getValue());Serial.print(" - ");Serial.println(debug);
	Serial.println("-----------------------------------");
  }
}

/*****************************************************************
/* WiFi auto connecting script                                   *
/*****************************************************************/
void connectWifi() {
  int retry_count = 0;
  Serial.println(WiFi.status());
  WiFi.begin(wlanssid, wlanpwd); // Start WiFI
  WiFi.mode(WIFI_STA);
  
//  if (debug) {
//    Serial.print("Connecting to ");
//    Serial.print(wlanssid);
//  }

  debug_out("Connecting to ",DEBUG_INFO);
  debug_out(wlanssid,DEBUG_INFO);

  while ((WiFi.status() != WL_CONNECTED) && (retry_count < 20))
  {
    delay(500);
    if (debug) Serial.print(".");
    retry_count++;
  }
  if (WiFi.status() != WL_CONNECTED) {
    wifiConfig();
    if (WiFi.status() != WL_CONNECTED) {
      retry_count = 0;
      while ((WiFi.status() != WL_CONNECTED) && (retry_count < 20))
      {
        delay(500);
        if (debug) Serial.print(".");
        retry_count++;
      }
    }
  }
  if (debug) {
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
}

/*****************************************************************
/* convert float to string with a                                *
/* precision of two decimal places                               *
/*****************************************************************/
String Float2String(float value) {
  // Convert a float to String with two decimals.
  char temp[15];
  String s;

  dtostrf(value,13, 2, temp);
  s = String(temp);
  s.trim();
  return s;
}

/*****************************************************************
/* send data to rest api                                         *
/*****************************************************************/
void sendData(const String& data, const char* host, const int httpPort, const char* url) {

  if (debug) {
    Serial.print("connecting to ");
    Serial.println(host);
  }
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  if (debug) {
    Serial.print("Requesting URL: ");
    Serial.println(url);
    Serial.println(ESP.getChipId());
    Serial.println(data);
  }
  
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
    if (debug) Serial.print(c);
  }
  
  if (debug) {
    Serial.println();
    Serial.println("closing connection");
    Serial.println("------------------------------");    
    Serial.println();
    Serial.println();
  }
}

/*****************************************************************
/* send data as csv to serial out                                *
/*****************************************************************/
void send_csv(const String& data) {
  char* s;
  String tmp_str;
  String headline;
  String valueline;
  int value_count = 0;
  StaticJsonBuffer<500> jsonBuffer;
  JsonObject& json2data = jsonBuffer.parseObject(data);
  if (debug) {
    Serial.println("CSV Output");
    Serial.println(data);
  }
  if (json2data.success()) {
    headline = "Timestamp_ms;";
    valueline = String(act_milli)+";";
    if (ppd_read) value_count += 6;
    if (sds_read) value_count += 2;
    if (dht_read) value_count += 2;
    for (int i=0;i<value_count;i++) {
      tmp_str = jsonBuffer.strdup(json2data["sensordatavalues"][i]["value_type"].asString());
      headline += tmp_str+";";
      tmp_str = jsonBuffer.strdup(json2data["sensordatavalues"][i]["value"].asString());
      valueline += tmp_str+";";
    }
    if (first_csv_line) {
      if (headline.length() > 0) headline.remove(headline.length()-1);
      Serial.println(headline);
      first_csv_line = 0;
    }
    if (valueline.length() > 0) valueline.remove(valueline.length()-1);
    Serial.println(valueline);
  } else {
    Serial.println("Data read failed");
  }
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
    if (debug) {
      Serial.println("Humidity    : "+String(h)+"%");
      Serial.println("Temperature : "+String(t)+" C");
    }
    s += "{\"value_type\":\"temp\",\"value\":\"";
    s += Float2String(t);
    s += "\"},";
    s += "{\"value_type\":\"humidity\",\"value\":\"";
    s += Float2String(h);
    s += "\"},";
  }
  if (debug) Serial.println("------------------------------");    
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
//  "aa" = 170, "ab" = 171, "c0" = 192
    value = int(buffer);
//  value_hex = String(value,HEX);
    switch (len) {
      case (0): if (value != 170) { len = -1; }; break;
      case (1): if (value != 192) { len = -1; }; break;
      case (2): pm25_serial = value; checksum_is  = value; break;
      case (3): pm25_serial += (value << 8); checksum_is += value; break;
      case (4): pm10_serial = value; checksum_is += value; break;
      case (5): pm10_serial += (value << 8); checksum_is += value; break;
      case (6): checksum_is += value; break;
      case (7): checksum_is += value; break;
      case (8):
//      Serial.println("Checksum is: "+String(checksum_is % 256)+" - should: "+String(value));
        if (value == (checksum_is % 256)) { checksum_ok = 1; } else { len = -1; }; break;
      case (9): if (value != 171) { len = -1; }; break;
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
    if (debug) {
      Serial.println("PM10:  "+Float2String(float(sds_pm10_sum)/(sds_val_count*10.0)));
      Serial.println("PM2.5: "+Float2String(float(sds_pm25_sum)/(sds_val_count*10.0)));
      Serial.println("------------------------------");
    }
    s += "{\"value_type\":\"P1\",\"value\":\"";
    s += Float2String(float(sds_pm10_sum)/(sds_val_count*10.0));
    s += "\"},";
    s += "{\"value_type\":\"P2\",\"value\":\"";
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
  valP1 = digitalRead(PPD_PIN_PM1);
  valP2 = digitalRead(PPD_PIN_PM2);

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
    ratio = lowpulseoccupancyP1/(sampletime_ms*10.0);                   // int percentage 0 to 100
    concentration = (1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62); // spec sheet curve
    // Begin printing
    if (debug) {
      Serial.print("LPO P10     : ");
      Serial.println(lowpulseoccupancyP1);
      Serial.print("Ratio PM10  : ");
      Serial.print(Float2String(ratio));
      Serial.println(" %");
      Serial.print("PM10 Count  : ");
      Serial.println(Float2String(concentration));
    }

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
    if (debug) {
      Serial.print("LPO PM25    : ");
      Serial.println(lowpulseoccupancyP2);
      Serial.print("Ratio PM25  : ");
      Serial.print(Float2String(ratio));
      Serial.println(" %");
      Serial.print("PM25 Count  : ");
      Serial.println(Float2String(concentration));
    }

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

    if (debug) Serial.println("------------------------------");    
  }
  return s;
}

/*****************************************************************
/* copy config from ext_def                                      *
/*****************************************************************/
void copyExtDef() {
  if (WLANSSID != NULL) { strcpy(wlanssid,WLANSSID); }
  if (WLANPWD  != NULL) { strcpy(wlanpwd,WLANPWD); }
  if (DHT_READ != dht_read) { dht_read = DHT_READ; }
  if (DHT_PIN  != dht_pin ) { dht_pin  = DHT_PIN;  }
  if (DHT_TYPE != dht_type) { dht_type = DHT_TYPE; }
  if (PPD_READ != ppd_read) { ppd_read = PPD_READ; }
  if (PPD_PIN_PM1 != ppd_pin_pm1) { ppd_pin_pm1 = PPD_PIN_PM1; }
  if (PPD_PIN_PM2 != ppd_pin_pm2) { ppd_pin_pm2 = PPD_PIN_PM2; }
  if (SDS_READ != sds_read) { sds_read = SDS_READ; }
  if (SDS_PIN_RX != sds_pin_rx) { sds_pin_rx = SDS_PIN_RX; }
  if (SDS_PIN_TX != sds_pin_tx) { sds_pin_tx = SDS_PIN_TX; }
  if (SEND2DUSTI != send2dusti) { send2dusti = SEND2DUSTI; }
  if (SEND2MADAVI != send2madavi) { send2madavi = SEND2MADAVI; }
  if (SEND2MQTT != send2mqtt) { send2mqtt = SEND2MQTT; }
  if (SEND2CSV != send2csv) { send2csv = SEND2CSV; }
  
  if (DEBUG != debug) { debug = DEBUG; }
}

/*****************************************************************
/* write config to spiffs                                        *
/*****************************************************************/
void writeConfig() {
    if (debug) Serial.println("saving config");
    DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();
    json["wlanssid"] = wlanssid;
    json["wlanpwd"] = wlanpwd;
    json["dht_read"] = dht_read;
    json["dht_pin"] = dht_pin;
    json["dht_type"] = dht_type;
    json["ppd_read"] = ppd_read;
    json["ppd_pin_pm1"] = ppd_pin_pm1;
    json["ppd_pin_pm2"] = ppd_pin_pm2;
    json["sds_read"] = sds_read;
    json["sds_pin_rx"] = sds_pin_rx;
    json["sds_pin_tx"] = sds_pin_tx;
    json["send2dusti"] = send2dusti;
    json["send2madavi"] = send2madavi;
    json["send2mqtt"] = send2mqtt;
    json["debug"] = debug;

    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile) {
      Serial.println("failed to open config file for writing");
    }

    if (debug) json.printTo(Serial);
    json.printTo(configFile);
    configFile.close();
    //end save
}

/*****************************************************************
/* read config from spiffs                                       *
/*****************************************************************/
void readConfig() {
  if (debug) Serial.println("mounting FS...");

  if (SPIFFS.begin()) {
    if (debug) Serial.println("mounted file system");
    if (SPIFFS.exists("/config.json")) {
      //file exists, reading and loading
      if (debug) Serial.println("reading config file");
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile) {
        if (debug) Serial.println("opened config file");
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        if (debug) json.printTo(Serial);
        if (json.success()) {
          if (debug) Serial.println("\nparsed json");
          if (json.containsKey("wlanssid")) strcpy(wlanssid, json["wlanssid"]);
          if (json.containsKey("wlanssid")) strcpy(wlanpwd, json["wlanpwd"]);
          if (json.containsKey("dht_read")) dht_read = json["dht_read"];
          if (json.containsKey("dht_pin") ) dht_pin  = json["dht_pin"];
          if (json.containsKey("dht_type")) dht_type = json["dht_type"];
          if (json.containsKey("ppd_read")) ppd_read = json["ppd_read"];
          if (json.containsKey("ppd_pin_pm1")) ppd_pin_pm1 = json["ppd_pin_pm1"];
          if (json.containsKey("ppd_pin_pm2")) ppd_pin_pm2 = json["ppd_pin_pm2"];
          if (json.containsKey("sds_read")) sds_read = json["sds_read"];
          if (json.containsKey("sds_pin_rx")) sds_pin_rx = json["sds_pin_rx"];
          if (json.containsKey("sds_pin_tx")) sds_pin_tx = json["sds_pin_tx"];
          if (json.containsKey("send2dusti")) send2dusti = json["send2dusti"];
          if (json.containsKey("send2madavi")) send2madavi = json["send2madavi"];
          if (json.containsKey("send2mqtt")) send2mqtt = json["send2mqtt"];
          if (json.containsKey("debug")) debug = json["debug"];
        } else {
          if (debug) Serial.println("failed to load json config");
        }
      }
    } else {
          if (debug) Serial.println("config file not found ...");
    }
  } else {
    Serial.println("failed to mount FS");
  }
}

/*****************************************************************
/* AutoUpdate                                                    *
/*****************************************************************/
void autoUpdate() {
}

/*****************************************************************
/* The Setup                                                     *
/*****************************************************************/
void setup() {
  WiFi.persistent(false);
  Serial.begin(9600);             // Output to Serial at 9600 baud
  copyExtDef();
  readConfig();
  connectWifi();                  // Start ConnectWifi
  writeConfig();
  pinMode(ppd_pin_pm1,INPUT_PULLUP); // Listen at the designated PIN
  pinMode(ppd_pin_pm2,INPUT_PULLUP); // Listen at the designated PIN
  dht.begin();                    // Start DHT
  delay(10);
  if (debug){
    Serial.print("\n"); 
    Serial.println("ChipId: ");
    Serial.println(ESP.getChipId());
    if (ppd_read) Serial.println("Lese PPD...");
    if (sds_read) Serial.println("Lese SDS...");
    if (dht_read) Serial.println("Lese DHT...");
    if (send2dusti) Serial.println("Sende an luftdaten.info...");
    if (send2madavi) Serial.println("Sende an madavi.de...");
	if (send2mqtt) Serial.println("Sende an MQTT broker...");
  }
  starttime = millis();           // store the start time
  starttime_SDS = millis();
}

/*****************************************************************
/* And action                                                    *
/*****************************************************************/
void loop() {
  String data = "";

  act_micro = micros();
  act_milli = millis();

  String result_PPD;
  String result_SDS;
  String result_DHT;
  
  if (ppd_read) {
    result_PPD = sensorPPD();
  }
  
  if (sds_read && (((act_milli-starttime_SDS) > sampletime_SDS_ms) || ((act_milli-starttime) > sampletime_ms))) {
    result_SDS = sensorSDS();
    starttime_SDS = act_milli;
  }
  
  if (dht_read && ((act_milli-starttime) > sampletime_ms)) {
    result_DHT = sensorDHT();  // getting temperature and humidity (optional)
  }

  if ((act_milli-starttime) > sampletime_ms) {
    if (debug) Serial.println("Creating data string:");
    data = "{\"software_version\": \"";
    data += SOFTWARE_VERSION;
    data += "\",";
    data += "\"sensordatavalues\":[";
    if (ppd_read) {data += result_PPD;}
    if (sds_read) {data += result_SDS;}
    if (dht_read) {data += result_DHT;}
    if ((result_PPD.length() > 0) || (result_DHT.length() > 0) || (result_SDS.length() > 0)) {
      data.remove(data.length()-1);
    }
    data += "]}";

    //sending to api
    
    if (send2madavi) {
      if (debug) Serial.println("#### Sending to madavi.de: ");
      sendData(data,host_madavi,httpPort_madavi,url_madavi);
    }
    if (send2dusti) {
      if (debug) Serial.println("#### Sending to luftdaten.info: ");
      sendData(data,host_dusti,httpPort_dusti,url_dusti);
    }
    if (send2csv) {
      if (debug) Serial.println("#### Sending as csv: ");
      send_csv(data);
    }
    
    // Resetting for next sampling
    lowpulseoccupancyP1 = 0;
    lowpulseoccupancyP2 = 0;
    starttime = millis(); // store the start time
  }
  yield();
}
