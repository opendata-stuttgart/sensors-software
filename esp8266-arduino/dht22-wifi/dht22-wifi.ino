/************************************************************/
/* DHT22 -> luftdaten.info api                              */
/************************************************************/

// increment on change
#define SOFTWARE_VERSION "MFA-2015-002-DHT22"

*****************************************************************
/* Includes                                                      *
/*****************************************************************/
#if defined(ESP8266)
#include <FS.h>                     // must be first
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ESP8266httpUpdate.h>
#include <WiFiClientSecure.h>
#include <SoftwareSerial.h>
#include <SSD1306.h>
#include <LiquidCrystal_I2C.h>
#include <base64.h>
#endif


bool dht_read = 1;
bool htu21d_read = 0;
bool ppd_read = 0;
bool sds_read = 1;
bool pms24_read = 0;
bool pms32_read = 0;
bool bmp_read = 0;
bool bmp280_read = 0;
bool bme280_read = 0;
bool ds18b20_read = 0;
bool gps_read = 0;
bool send2dusti = 1;
bool send2madavi = 1;
bool send2cfa = 1;
bool send2sensemap = 0;
bool send2custom = 0;
bool send2lora = 1;
bool send2influx = 0;
bool send2csv = 0;
bool auto_update = 0;
bool has_display = 0;
bool has_lcd1602 = 0;
int  debug = 3;

/**********************************************/
/* DHT declaration 
/**********************************************/
#include "DHT.h"
#define DHTPIN 4  // D2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);


//*****************************************************************
/* SDS011 declarations                                           *
/*****************************************************************/
#include <SSD1306.h>
#if defined(ESP8266)
SoftwareSerial serialSDS(SDS_PIN_RX, SDS_PIN_TX, false, 128);
#endif
#if defined(ARDUINO_SAMD_ZERO)
#define serialSDS SERIAL_PORT_HARDWARE
#endif
/**********************************************/
/* WiFi declarations
/**********************************************/
#include <ESP8266WiFi.h>

const char* ssid = "Nairobi Garage";
const char* password = "Livestream";
// const char* host = "192.168.1.12";
const char* host = "api.airquality.codeforafrica.org";
// const int httpPort = 8000;
const int httpPort = 80;
int value = 0;


unsigned long starttime;
unsigned long sampletime_ms = 30000;



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
void sendData(const String& data, int pin=-1) {
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
  Serial.println(data);

  String pinstr=String('-');
  if (pin > 0 ){pinstr=String(pin);}
  // send request to the server
  client.print(String("POST ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Pin: " + pinstr + "\r\n" +
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

/*****************************************************************
/* Debug output                                                  *
/*****************************************************************/
void debug_out(const String& text, const int level, const bool linebreak) {
  if (level <= debug) {
    if (linebreak) {
      Serial.println(text);
    } else {
      Serial.print(text);
    }
  }

}

// DHT22 Sensor
void sensorDHT(){
  String data;
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
   
   // json for push to api: h t
   data = "{\"software_version\": \"";
   data += SOFTWARE_VERSION;
   data += "\",";
   data += "\"sensordatavalues\":[{";
   data += "\"value_type\":\"temperature\",\"value\":\"";
   data += Float2String(t);
   data += "\"},{";
   data += "\"value_type\":\"humidity\",\"value\":\"";
   data += Float2String(h);
   data += "\"}]}";
   sendData(data, DHTPIN);
 
 }
}


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

  debug_out(F("Start reading SDS011"), DEBUG_MED_INFO, 1);
  if (long(act_milli - starttime) < (long(sending_intervall_ms) - long(warmup_time_SDS_ms + reading_time_SDS_ms))) {
    if (is_SDS_running) {
      stop_SDS();
    }
  } else {
    if (! is_SDS_running) {
      start_SDS();
    }

    while (serialSDS.available() > 0) {
      buffer = serialSDS.read();
      debug_out(String(len) + " - " + String(buffer, DEC) + " - " + String(buffer, HEX) + " - " + int(buffer) + " .", DEBUG_MAX_INFO, 1);
//      "aa" = 170, "ab" = 171, "c0" = 192
      value = int(buffer);
      switch (len) {
      case (0): if (value != 170) { len = -1; }; break;
      case (1): if (value != 192) { len = -1; }; break;
      case (2): pm25_serial = value; checksum_is = value; break;
      case (3): pm25_serial += (value << 8); checksum_is += value; break;
      case (4): pm10_serial = value; checksum_is += value; break;
      case (5): pm10_serial += (value << 8); checksum_is += value; break;
      case (6): checksum_is += value; break;
      case (7): checksum_is += value; break;
      case (8):
        debug_out(F("Checksum is: "), DEBUG_MED_INFO, 0); debug_out(String(checksum_is % 256), DEBUG_MED_INFO, 0);
        debug_out(F(" - should: "), DEBUG_MED_INFO, 0); debug_out(String(value), DEBUG_MED_INFO, 1);
        if (value == (checksum_is % 256)) { checksum_ok = 1; } else { len = -1; }; break;
      case (9): if (value != 171) { len = -1; }; break;
      }
      len++;
      if (len == 10 && checksum_ok == 1 && (long(act_milli - starttime) > (long(sending_intervall_ms) - long(reading_time_SDS_ms)))) {
        if ((! isnan(pm10_serial)) && (! isnan(pm25_serial))) {
          sds_pm10_sum += pm10_serial;
          sds_pm25_sum += pm25_serial;
          if (sds_pm10_min > pm10_serial) { sds_pm10_min = pm10_serial; }
          if (sds_pm10_max < pm10_serial) { sds_pm10_max = pm10_serial; }
          if (sds_pm25_min > pm25_serial) { sds_pm25_min = pm25_serial; }
          if (sds_pm25_max < pm25_serial) { sds_pm25_max = pm25_serial; }
          debug_out(F("PM10 (sec.) : "), DEBUG_MED_INFO, 0); debug_out(Float2String(float(pm10_serial) / 10), DEBUG_MED_INFO, 1);
          debug_out(F("PM2.5 (sec.): "), DEBUG_MED_INFO, 0); debug_out(Float2String(float(pm25_serial) / 10), DEBUG_MED_INFO, 1);
          sds_val_count++;
        }
        len = 0; checksum_ok = 0; pm10_serial = 0.0; pm25_serial = 0.0; checksum_is = 0;
      }
      yield();
    }

  }
  if (send_now) {
    last_value_SDS_P1 = "";
    last_value_SDS_P2 = "";
    if (sds_val_count > 2) {
      sds_pm10_sum = sds_pm10_sum - sds_pm10_min - sds_pm10_max;
      sds_pm25_sum = sds_pm25_sum - sds_pm25_min - sds_pm25_max;
      sds_val_count = sds_val_count - 2;
    }
    if (sds_val_count > 0) {
      debug_out("PM10:  " + Float2String(float(sds_pm10_sum) / (sds_val_count * 10.0)), DEBUG_MIN_INFO, 1);
      debug_out("PM2.5: " + Float2String(float(sds_pm25_sum) / (sds_val_count * 10.0)), DEBUG_MIN_INFO, 1);
      debug_out("------", DEBUG_MIN_INFO, 1);
      last_value_SDS_P1 = Float2String(float(sds_pm10_sum) / (sds_val_count * 10.0));
      last_value_SDS_P2 = Float2String(float(sds_pm25_sum) / (sds_val_count * 10.0));
      s += Value2Json("SDS_P1", last_value_SDS_P1);
      s += Value2Json("SDS_P2", last_value_SDS_P2);
      last_value_SDS_P1.remove(last_value_SDS_P1.length() - 1);
      last_value_SDS_P2.remove(last_value_SDS_P2.length() - 1);
    }
    sds_pm10_sum = 0; sds_pm25_sum = 0; sds_val_count = 0;
    sds_pm10_max = 0; sds_pm10_min = 20000; sds_pm25_max = 0; sds_pm25_min = 20000;
    if ((sending_intervall_ms > (warmup_time_SDS_ms + reading_time_SDS_ms)) && (! will_check_for_update)) {
      stop_SDS();
    }
  }

  debug_out(F("End reading SDS011"), DEBUG_MED_INFO, 1);

  return s;
}


/**********************************************/
/* The Setup
/**********************************************/
void setup() {
  Serial.begin(9600); //Output to Serial at 9600 baud
  pinMode(DHTPIN,INPUT);
  delay(10);
  starttime = millis(); // store the start time
  dht.begin(); // Start DHT
  delay(1000);
  connectWifi(); // Start ConnecWifi 
  Serial.print("\n"); 
  Serial.println("ChipId: ");
  Serial.println(ESP.getChipId());
}

/**********************************************/
/* And action
/**********************************************/
void loop() {
  // Checking if it is time to sample
  if ((millis()-starttime) > sampletime_ms)
  {
    starttime = millis(); // store the start time
    sensorDHT();  // getting temperature and humidity
    Serial.println("------------------------------");
  }
}


