#include <Arduino.h>

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
/*      - DHT22 Pin 2 (DATA)    -> Pin D7 (GPIO13)               *
/*      - DHT22 Pin 3 (NULL)    -> unused                        *
/*      - DHT22 Pin 4 (GND)     -> Pin GND                       *
/*                                                               *
/*****************************************************************
/* Extension: OLED Display with SSD1309                          *
/*                                                               *
/* Wiring Instruction                                            *
/* (see labels on display)                                       *
/*      VCC       ->     Pin 3V3                                 *
/*      GND       ->     Pin GND                                 *
/*      SCL       ->     Pin D4 (GPIO2)                          *
/*      SDA       ->     Pin D3 (GPIO0)                          *
/*                                                               *
/*****************************************************************/
// increment on change
#define SOFTWARE_VERSION "NRZ-2016-022"

/*****************************************************************
/* Global definitions (moved to ext_def.h)                       *
/* #define WLANSSID "Freifunk"                                   *
/* #define WLANPWD ""                                            *
/*                                                               *
/* #define DHT_READ 0                                            *
/* #define PPD_READ 1                                            *
/* #define SDS_READ 0                                            *
/*                                                               *
/* #define SEND2DUSTI 1                                          *
/* #define SEND2MADAVI 0                                         *
/* #define SEND2MQTT 0                                           *
/* #define SEND2CSV 0                                            *
/*                                                               *
/* #define DEBUG 1                                               *
/*****************************************************************/

/*****************************************************************
/* Includes                                                      *
/*****************************************************************/
#if defined(ESP8266)
#include <FS.h>                     // must be first
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <ESP8266httpUpdate.h>
#include <WiFiClientSecure.h>
#include <SoftwareSerial.h>
#include <SSD1306.h>
#endif
#if defined(ARDUINO_SAMD_ZERO)
#include <RHReliableDatagram.h>
#include <RH_RF69.h>
#include <SPI.h>
#endif
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <DHT.h>
#include <Adafruit_BMP085.h>

#include "ext_def.h"

/*****************************************************************
/* Variables with defaults                                       *
/*****************************************************************/
char wlanssid[65] = "Freifunk";
char wlanpwd[65] = "";

char version_from_local_config[30] = "";

bool dht_read = 0;
bool ppd_read = 1;
bool sds_read = 0;
bool bmp_read = 0;
bool send2dusti = 1;
bool send2madavi = 0;
bool send2custom = 0;
bool send2mqtt = 0;
bool send2lora = 0;
bool send2csv = 0;
bool auto_update = 1;
bool has_display = 0;
int  debug = 3;

long int sample_count = 0;

const char* host_madavi = "www.madavi.de";
const char* url_madavi = "/sensor/data.php";
const int httpPort_madavi = 443;

const char* host_dusti = "api.luftdaten.info";
const char* url_dusti = "/v1/push-sensor-data/";
const int httpPort_dusti = 443;

char host_custom[100] = "192.168.234.1";
char url_custom[100] = "/data.php";
int httpPort_custom = 80;

const char* host_mqtt = "mqtt.opensensors.io";
const int mqtt_port = 1883;
const char* mqtt_user = "";
const char* mqtt_pwd = "";
const char* mqtt_client_id = "";
const char* mqtt_topic = "";

const char* update_host = "www.madavi.de";
const char* update_url = "/sensor/update/firmware.php";
const int update_port = 80;

#if defined(ESP8266)
WiFiClient mqtt_wifi;
PubSubClient mqtt_client(mqtt_wifi);
#endif

#if defined(ARDUINO_SAMD_ZERO)
RH_RF69 rf69(RFM69_CS, RFM69_INT);
RHReliableDatagram manager(rf69, CLIENT_ADDRESS);
#endif

/*****************************************************************
/* Display definitions                                           *
/*****************************************************************/
#if defined(ESP8266)
SSD1306   display(0x3c, D3, D4);
#endif

/*****************************************************************
/* SDS011 declarations                                           *
/*****************************************************************/
#if defined(ESP8266)
SoftwareSerial serialSDS(SDS_PIN_RX, SDS_PIN_TX, false, 128);
#endif

/*****************************************************************
/* DHT declaration                                               *
/*****************************************************************/
DHT dht(DHT_PIN, DHT_TYPE);

/*****************************************************************
/* BMP declaration                                               *
/*****************************************************************/
Adafruit_BMP085 bmp;

/*****************************************************************
/* Variable Definitions for PPD24NS                              *
/* P1 for PM10 & P2 for PM25                                     *
/*****************************************************************/

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
unsigned long last_micro = 0;
unsigned long min_micro = 1000000000;
unsigned long max_micro = 0;
unsigned long diff_micro = 0;

unsigned long sampletime_ms = 30000;
unsigned long sampletime_SDS_ms = 1000;

unsigned long last_update_attempt;
unsigned long pause_between_update_attempts = 86400000;

int sds_pm10_sum = 0;
int sds_pm25_sum = 0;
int sds_val_count = 0;

bool first_csv_line = 1;

/*****************************************************************
/* Debug output                                                  *
/*****************************************************************/
void debug_out(const String& text, int level, bool linebreak) {
	if (level <= debug) {
		if (linebreak) {
			Serial.println(text);
		} else {
			Serial.print(text);
		}
	}
}

/*****************************************************************
/* display values                                                 *
/*****************************************************************/
void display_debug(const String& text) {
#if defined(ESP8266)
	if (has_display) {
		debug_out("output debug text to display...",DEBUG_MIN_INFO,1);
		debug_out(text,DEBUG_MAX_INFO,1);
		display.resetDisplay();
		display.clear();
		display.displayOn();
		display.setFont(ArialMT_Plain_10);
		display.setTextAlignment(TEXT_ALIGN_LEFT);
		display.drawStringMaxWidth(0,12,120,text);
		display.display();
	}
#endif
}

/*****************************************************************
/* IPAddress to String                                           *
/*****************************************************************/
String IPAddress2String(IPAddress ipaddress) {
	char myIpString[24];	
	sprintf(myIpString, "%d.%d.%d.%d", ipaddress[0], ipaddress[1], ipaddress[2], ipaddress[3]);
	return String(myIpString);
}

/*****************************************************************
/* WifiConfig                                                    *
/*****************************************************************/
void wifiConfig() {
#if defined(ESP8266)
	String boolvar;
	String apname;
	String custom_wlanssid;
	String custom_wlanpwd;
	WiFiManager wifiManager;

	if (debug < 5) wifiManager.setDebugOutput(false);
	WiFiManagerParameter custom_send2dusti("send2dusti", "Senden an luftdaten.info (0/1) ?", "", 10);
	wifiManager.addParameter(&custom_send2dusti);
	WiFiManagerParameter custom_send2madavi("send2madavi", "Senden an madavi.de (0/1) ?", "", 10);
	wifiManager.addParameter(&custom_send2madavi);
	WiFiManagerParameter custom_send2csv("send2csv", "Seriell als CSV (0/1) ?", "", 10);
	wifiManager.addParameter(&custom_send2csv);
	WiFiManagerParameter custom_dht_read("dht_read", "DHT Sensor (0/1) ?", "", 10);
	wifiManager.addParameter(&custom_dht_read);
	WiFiManagerParameter custom_ppd_read("ppd_read", "PPD42NS Sensor (0/1) ?", "", 10);
	wifiManager.addParameter(&custom_ppd_read);
	WiFiManagerParameter custom_sds_read("sds_read", "SDS Sensor (0/1) ?", "", 10);
	wifiManager.addParameter(&custom_sds_read);
	WiFiManagerParameter custom_bmp_read("bmp_read", "BMP Sensor (0/1) ?", "", 10);
	wifiManager.addParameter(&custom_bmp_read);
	WiFiManagerParameter custom_auto_update("auto_update", "Auto-Update (0/1) ?", "", 10);
	wifiManager.addParameter(&custom_auto_update);
	WiFiManagerParameter custom_has_display("has_display", "Display (0/1) ?", "", 10);
	wifiManager.addParameter(&custom_has_display);
	WiFiManagerParameter custom_debug("debug", "Debug output (0-5) ?", "", 10);
	wifiManager.addParameter(&custom_debug);
	WiFiManagerParameter custom_send2custom("send2custom", "Senden an eigene API (0/1)?", "", 10);
	wifiManager.addParameter(&custom_send2custom);
//	WiFiManagerParameter custom_host_custom("host_custom", "Host ?", "", 40);
//	wifiManager.addParameter(&custom_host_custom);
//	WiFiManagerParameter custom_url_custom("url_custom", "Pfad ?", "", 40);
//	wifiManager.addParameter(&custom_url_custom);
//	WiFiManagerParameter custom_httpPort_custom("httpPort_custom", "HTTP Port (80) ?", "", 10);
//	wifiManager.addParameter(&custom_httpPort_custom);
	apname  = "Feinstaubsensor-" + String(ESP.getChipId());
	wifiManager.setTimeout(300);
	wifiManager.setBreakAfterConfig(true);
	wifiManager.startConfigPortal(apname.c_str());
	custom_wlanssid = WiFi.SSID();
	custom_wlanpwd = WiFi.psk();
	strcpy(wlanssid,custom_wlanssid.c_str());
	strcpy(wlanpwd,custom_wlanpwd.c_str());
	if (strcmp(custom_dht_read.getValue(),"") != 0) dht_read = strtol(custom_dht_read.getValue(), NULL, 10);
	if (strcmp(custom_ppd_read.getValue(),"") != 0) ppd_read = strtol(custom_ppd_read.getValue(), NULL, 10);
	if (strcmp(custom_sds_read.getValue(),"") != 0) sds_read = strtol(custom_sds_read.getValue(), NULL, 10);
	if (strcmp(custom_bmp_read.getValue(),"") != 0) bmp_read = strtol(custom_bmp_read.getValue(), NULL, 10);
	if (strcmp(custom_send2dusti.getValue(),"") != 0) send2dusti = strtol(custom_send2dusti.getValue(), NULL, 10);
	if (strcmp(custom_send2madavi.getValue(),"") != 0) send2madavi = strtol(custom_send2madavi.getValue(), NULL, 10);
	if (strcmp(custom_send2csv.getValue(),"") != 0) send2csv = strtol(custom_send2csv.getValue(), NULL, 10);
	if (strcmp(custom_auto_update.getValue(),"") != 0) auto_update = strtol(custom_auto_update.getValue(), NULL, 10);
	if (strcmp(custom_has_display.getValue(),"") != 0) has_display = strtol(custom_has_display.getValue(), NULL, 10);
	if (strcmp(custom_debug.getValue(),"") != 0) debug = strtol(custom_debug.getValue(), NULL, 10);
	if (strcmp(custom_send2custom.getValue(),"") != 0) send2custom = strtol(custom_send2custom.getValue(), NULL, 10);
//	if (strcmp(custom_host_custom.getValue(),"") != 0) strcpy(host_custom,custom_host_custom.getValue());
//	if (strcmp(custom_url_custom.getValue(),"") != 0) strcpy(url_custom,custom_url_custom.getValue());
//	if (strcmp(custom_httpPort_custom.getValue(),"") != 0) httpPort_custom = strtol(custom_httpPort_custom.getValue(), NULL, 10);
	debug_out("------ Result from Webconfig ------",DEBUG_MIN_INFO,1);
	debug_out("WLANSSID: ",DEBUG_MIN_INFO,0);debug_out(wlanssid,DEBUG_MIN_INFO,1);
	debug_out("DHT_read: "+String(custom_dht_read.getValue())+" - "+String(dht_read),DEBUG_MIN_INFO,1);
	debug_out("PPD_read: "+String(custom_ppd_read.getValue())+" - "+String(ppd_read),DEBUG_MIN_INFO,1);
	debug_out("SDS_read: "+String(custom_sds_read.getValue())+" - "+String(sds_read),DEBUG_MIN_INFO,1);
	debug_out("BMP_read: "+String(custom_bmp_read.getValue())+" - "+String(bmp_read),DEBUG_MIN_INFO,1);
	debug_out("Dusti: "+String(custom_send2dusti.getValue())+" - "+String(send2dusti),DEBUG_MIN_INFO,1);
	debug_out("Madavi: "+String(custom_send2madavi.getValue())+" - "+String(send2madavi),DEBUG_MIN_INFO,1);
	debug_out("CSV: "+String(custom_send2csv.getValue())+" - "+String(send2csv),DEBUG_MIN_INFO,1);
	debug_out("Autoupdate: "+String(custom_auto_update.getValue())+" - "+String(auto_update),DEBUG_MIN_INFO,1);
	debug_out("Display: "+String(custom_has_display.getValue())+" - "+String(has_display),DEBUG_MIN_INFO,1);
	debug_out("Debug: "+String(custom_debug.getValue())+" - "+String(debug),DEBUG_MIN_INFO,1);
	debug_out("Custom API: "+String(custom_send2custom.getValue())+" - "+String(send2custom),DEBUG_MIN_INFO,1);
//	debug_out("Custom Host: "+String(custom_host_custom.getValue())+" - "+String(host_custom),DEBUG_MIN_INFO,1);
//	debug_out("Custom URL: "+String(custom_url_custom.getValue())+" - "+String(url_custom),DEBUG_MIN_INFO,1);
//	debug_out("Custom Port: "+String(custom_httpPort_custom.getValue())+" - "+String(httpPort_custom),DEBUG_MIN_INFO,1);
	debug_out("-----------------------------------",DEBUG_MIN_INFO,1);
#endif
}

/*****************************************************************
/* WiFi auto connecting script                                   *
/*****************************************************************/
void connectWifi() {
#if defined(ESP8266)
	int retry_count = 0;
	debug_out(String(WiFi.status()),DEBUG_MIN_INFO,1);
	WiFi.begin(wlanssid, wlanpwd); // Start WiFI
	WiFi.mode(WIFI_STA);
  
	debug_out("Connecting to ",DEBUG_MIN_INFO,0);
	debug_out(wlanssid,DEBUG_MIN_INFO,1);

	while ((WiFi.status() != WL_CONNECTED) && (retry_count < 20)) {
		delay(500);
		debug_out(".",DEBUG_MIN_INFO,0);
		retry_count++;
	}
	debug_out("",DEBUG_MIN_INFO,1);
	if (WiFi.status() != WL_CONNECTED) {
		display_debug("AP ID: Feinstaubsensor-"+String(ESP.getChipId())+" - IP: 192.168.4.1");
		wifiConfig();
		if (WiFi.status() != WL_CONNECTED) {
			retry_count = 0;
			while ((WiFi.status() != WL_CONNECTED) && (retry_count < 20)) {
				delay(500);
				debug_out(".",DEBUG_MIN_INFO,0);
				retry_count++;
			}
			debug_out("",DEBUG_MIN_INFO,1);
		}
	}
    debug_out("WiFi connected\nIP address: "+IPAddress2String(WiFi.localIP()),DEBUG_MIN_INFO,1);
#endif
}

#if defined(ARDUINO_SAMD_ZERO) && defined(SERIAL_PORT_USBVIRTUAL)
#if 0
char *dtostrf (double val, signed char width, unsigned char prec, char *sout) {
	char fmt[20];
	sprintf(fmt, "%%%d.%df", width, prec);
	sprintf(sout, fmt, val);
	return sout;
}
#else
#include <string.h>
#include <stdlib.h>
char *dtostrf(double val, int width, unsigned int prec, char *sout) {
	int decpt, sign, reqd, pad;
	const char *s, *e;
	char *p;
	s = fcvt(val, prec, &decpt, &sign);
	if (prec == 0 && decpt == 0) {
		s = (*s < '5') ? "0" : "1";
		reqd = 1;
	} else {
		reqd = strlen(s);
		if (reqd > decpt) reqd++;
		if (decpt == 0) reqd++;
	}
	if (sign) reqd++;
	p = sout;
	e = p + reqd;
	pad = width - reqd;
	if (pad > 0) {
		e += pad;
		while (pad-- > 0) *p++ = ' ';
	}
	if (sign) *p++ = '-';
	if (decpt <= 0 && prec > 0) {
		*p++ = '0';
		*p++ = '.';
		e++;
		while ( decpt < 0 ) {
			decpt++;
			*p++ = '0';
		}
	}   
	while (p < e) {
		*p++ = *s++;
		if (p == e) break;
		if (--decpt == 0) *p++ = '.';
	}
	if (width < 0) {
		pad = (reqd + width) * -1;
		while (pad-- > 0) *p++ = ' ';
	}
	*p = 0;
	return sout;
}
#endif
#endif

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

String FeatherChipId() {
#if defined(ARDUINO_SAMD_ZERO)
  String s;
  volatile uint32_t val1, val2, val3, val4;
  volatile uint32_t *ptr1 = (volatile uint32_t *)0x0080A00C;
  val1 = *ptr1;
  volatile uint32_t *ptr = (volatile uint32_t *)0x0080A040;
  val2 = *ptr;
  ptr++;
  val3 = *ptr;
  ptr++;
  val4 = *ptr;

  s = String(val1,HEX)+String(val2,HEX)+String(val3,HEX)+String(val4,HEX);

  return s;
#endif
}


/*****************************************************************
/* send data to rest api                                         *
/*****************************************************************/
void sendData(const String& data, const int pin, const char* host, const int httpPort, const char* url) {
#if defined(ESP8266)

	debug_out("connecting to ",DEBUG_MIN_INFO,0);
	debug_out(host,DEBUG_MIN_INFO,1);
  
	WiFiClient client;
	WiFiClientSecure client_s;
	// Use WiFiClient class to create TCP connections
	
	if (httpPort == 80) {
		if (!client.connect(host, httpPort)) {
			debug_out("connection failed",DEBUG_ERROR,1);
			return;
		}

		debug_out("Requesting URL: ",DEBUG_MIN_INFO,0);
		debug_out(url,DEBUG_MIN_INFO,1);
		debug_out(String(ESP.getChipId()),DEBUG_MIN_INFO,1);
		debug_out(data,DEBUG_MIN_INFO,1);
  
		// send request to the server
		client.print(String("POST ") + url + " HTTP/1.1\r\n" +
					"Host: " + host + "\r\n" +
					"Content-Type: application/json\r\n" +
					"PIN: " + String(pin) + "\r\n" +
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
			debug_out(String(c),DEBUG_MIN_INFO,0);
		}
  
		debug_out("\nclosing connection\n------------------------------\n\n",DEBUG_MIN_INFO,1);

	} else {

		if (!client_s.connect(host, httpPort)) {
			debug_out("connection failed",DEBUG_ERROR,1);
			return;
		}

		debug_out("Requesting URL: ",DEBUG_MIN_INFO,0);
		debug_out(url,DEBUG_MIN_INFO,1);
		debug_out(String(ESP.getChipId()),DEBUG_MIN_INFO,1);
		debug_out(data,DEBUG_MIN_INFO,1);
  
		// send request to the server
		client_s.print(String("POST ") + url + " HTTP/1.1\r\n" +
					"Host: " + host + "\r\n" +
					"Content-Type: application/json\r\n" +
					"PIN: " + String(pin) + "\r\n" +
					"Sensor: esp8266-");
		client_s.println(ESP.getChipId());
		client_s.print("Content-Length: ");
		client_s.println(data.length(), DEC);
		client_s.println("Connection: close\r\n");

		client_s.println(data);

		delay(1);
  
		// Read reply from server and print them
		while(client_s.available()){
			char c = client_s.read();
			debug_out(String(c),DEBUG_MIN_INFO,0);
		}
  
		debug_out("\nclosing connection\n------------------------------\n\n",DEBUG_MIN_INFO,1);
	}
#endif
}

void send_lora(const String& data) {
#if defined(ARDUINO_SAMD_ZERO)
	uint8_t buf[RH_RF69_MAX_MESSAGE_LEN];

	debug_out("connecting to LoRa gateway ",DEBUG_MIN_INFO,1);
	
	if (manager.sendtoWait((uint8_t*)(data.c_str()), sizeof(data), SERVER_ADDRESS))
	{
		// Now wait for a reply from the server
		uint8_t len = sizeof(buf);
		uint8_t from;   
		if (manager.recvfromAckTimeout(buf, &len, 2000, &from))
		{
			debug_out("got reply from : 0x",DEBUG_MIN_INFO,0);
			debug_out(String(from, HEX),DEBUG_MIN_INFO,0);
//			debug_out(": ",DEBUG_MIN_INFO,0);
//			debug_out(s,DEBUG_MIN_INFO,1);
		} else {
			debug_out("No reply, is rf69_reliable_datagram_server running?",DEBUG_MIN_INFO,1);
		}
	}  else
		Serial.println("sendtoWait failed");

		debug_out("\nclosing connection\n------------------------------\n\n",DEBUG_MIN_INFO,1);
#endif
}

/*****************************************************************
/* send data to mqtt api                                         *
/*****************************************************************/
void sendmqtt(const String& data, const char* host, const int mqtt_port) {
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
	StaticJsonBuffer<2000> jsonBuffer;
	JsonObject& json2data = jsonBuffer.parseObject(data);
	debug_out("CSV Output",DEBUG_MIN_INFO,1);
	debug_out(data,DEBUG_MIN_INFO,1);
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
		debug_out("Data read failed",DEBUG_ERROR,1);
	}
}

/*****************************************************************
/* read DHT22 sensor values                                      *
/*****************************************************************/
String sensorDHT() {
	String s = "";
	float h = dht.readHumidity(); //Read Humidity
	float t = dht.readTemperature(); //Read Temperature

	// Check if valid number if non NaN (not a number) will be send.
	if (isnan(t) || isnan(h)) {
		debug_out("DHT22 couldn't be read",DEBUG_ERROR,1);
	} else {
		debug_out("Humidity    : "+String(h)+"%",DEBUG_MIN_INFO,1);
		debug_out("Temperature : "+String(t)+" C",DEBUG_MIN_INFO,1);
		s += "{\"value_type\":\"temperature\",\"value\":\"";
		s += Float2String(t);
		s += "\"},";
		s += "{\"value_type\":\"humidity\",\"value\":\"";
		s += Float2String(h);
		s += "\"},";
	}
	debug_out("------------------------------",DEBUG_MIN_INFO,1);    
	return s;
}

/*****************************************************************
/* read BMP180 sensor values                                      *
/*****************************************************************/
String sensorBMP() {
	String s = "";
	int p;
	float t;

	p = bmp.readPressure();
	t = bmp.readTemperature();
	if (isnan(p) || isnan(t)) {
		debug_out("BMP180 couldn't be read",DEBUG_ERROR,1);
	} else {
		debug_out("Pressure    : "+Float2String(float(p)/100)+" hPa",DEBUG_MIN_INFO,1);
		debug_out("Temperature : "+String(t)+" C",DEBUG_MIN_INFO,1);
		s += "{\"value_type\":\"BMP_pressure\",\"value\":\"";
		s += String(p);
		s += "\"},";
		s += "{\"value_type\":\"BMP_temperature\",\"value\":\"";
		s += Float2String(t);
		s += "\"},";
	}
	debug_out("------------------------------",DEBUG_MIN_INFO,1);    
	return s;
}

/*****************************************************************
/* read SDS011 sensor values                                     *
/*****************************************************************/
String sensorSDS() {
#if defined(ESP8266)
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
		debug_out(String(len)+" - "+String(buffer,DEC)+" - "+String(buffer,HEX)+" - "+int(buffer)+" .",DEBUG_MAX_INFO,1);
//		"aa" = 170, "ab" = 171, "c0" = 192
		value = int(buffer);
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
					debug_out("Checksum is: "+String(checksum_is % 256)+" - should: "+String(value),DEBUG_MED_INFO,1);
					if (value == (checksum_is % 256)) { checksum_ok = 1; } else { len = -1; }; break;
			case (9): if (value != 171) { len = -1; }; break;
		}
		len++;
		if (len == 10 && checksum_ok == 1) {
			sds_pm10_sum += pm10_serial;
			sds_pm25_sum += pm25_serial;
			debug_out("PM10 (sec.) : "+Float2String(float(pm10_serial)),DEBUG_MED_INFO,1);
			debug_out("PM2.5 (sec.): "+Float2String(float(pm25_serial)),DEBUG_MED_INFO,1);
			sds_val_count++;
			len = 0; checksum_ok = 0; pm10_serial = 0.0; pm25_serial = 0.0; checksum_is = 0;
		}
		yield();
	}
	if ((act_milli-starttime) > sampletime_ms) {
		debug_out("PM10:  "+Float2String(float(sds_pm10_sum)/(sds_val_count*10.0)),DEBUG_MIN_INFO,1);
		debug_out("PM2.5: "+Float2String(float(sds_pm25_sum)/(sds_val_count*10.0)),DEBUG_MIN_INFO,1);
		debug_out("------------------------------",DEBUG_MIN_INFO,1);
		s += "{\"value_type\":\"SDS_P1\",\"value\":\"";
		s += Float2String(float(sds_pm10_sum)/(sds_val_count*10.0));
		s += "\"},";
		s += "{\"value_type\":\"SDS_P2\",\"value\":\"";
		s += Float2String(float(sds_pm25_sum)/(sds_val_count*10.0));
		s += "\"},";
		if (! ppd_read) {
			s.replace("SDS_","");
		}
		sds_pm10_sum = 0; sds_pm25_sum = 0; sds_val_count = 0;
	}
	return s;
#endif
}

/*****************************************************************
/* read PPD42NS sensor values                                    *
/*****************************************************************/
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
		debug_out("LPO P10     : "+String(lowpulseoccupancyP1),DEBUG_MIN_INFO,1);
		debug_out("Ratio PM10  : "+Float2String(ratio)+" %",DEBUG_MIN_INFO,1);
		debug_out("PM10 Count  : "+Float2String(concentration),DEBUG_MIN_INFO,1);

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
		debug_out("LPO PM25    : "+String(lowpulseoccupancyP2),DEBUG_MIN_INFO,1);
		debug_out("Ratio PM25  : "+Float2String(ratio)+" %",DEBUG_MIN_INFO,1);
		debug_out("PM25 Count  : "+Float2String(concentration),DEBUG_MIN_INFO,1);

		// json for push to api / P2
		s += "{\"value_type\":\"durP2\",\"value\":\"";
		s += long(lowpulseoccupancyP2);
		s += "\"},";
		s += "{\"value_type\":\"ratioP2\",\"value\":\"";
		s += Float2String(ratio);
		s += "\"},";
		s += "{\"value_type\":\"P2\",\"value\":\"";
		s += Float2String(concentration);
		s += "\"},";

		debug_out("------------------------------",DEBUG_MIN_INFO,1);    
	}
	return s;
}

/*****************************************************************
/* copy config from ext_def                                      *
/*****************************************************************/
void copyExtDef() {
#if defined(ESP8266)
	if (WLANSSID != NULL) { strcpy(wlanssid,WLANSSID); }
	if (WLANPWD  != NULL) { strcpy(wlanpwd,WLANPWD); }
	if (DHT_READ != dht_read) { dht_read = DHT_READ; }
	if (PPD_READ != ppd_read) { ppd_read = PPD_READ; }
	if (SDS_READ != sds_read) { sds_read = SDS_READ; }
	if (BMP_READ != bmp_read) { bmp_read = BMP_READ; }
	if (SEND2DUSTI != send2dusti) { send2dusti = SEND2DUSTI; }
	if (SEND2MADAVI != send2madavi) { send2madavi = SEND2MADAVI; }
	if (SEND2MQTT != send2mqtt) { send2mqtt = SEND2MQTT; }
	if (SEND2CSV != send2csv) { send2csv = SEND2CSV; }
	if (AUTO_UPDATE != auto_update) { auto_update = AUTO_UPDATE; }
	if (HAS_DISPLAY != has_display) { has_display = HAS_DISPLAY; }

	if (DEBUG != debug) { debug = DEBUG; }

	if (SEND2CUSTOM != send2custom) { send2custom = SEND2CUSTOM; }
	if (HOST_CUSTOM != NULL) { strcpy(host_custom,HOST_CUSTOM); }
	if (URL_CUSTOM != NULL) { strcpy(url_custom,URL_CUSTOM); }
	if (HTTPPORT_CUSTOM != httpPort_custom) { httpPort_custom = HTTPPORT_CUSTOM; }
#endif
}

/*****************************************************************
/* write config to spiffs                                        *
/*****************************************************************/
void writeConfig() {
#if defined(ESP8266)
	debug_out("saving config...",DEBUG_MIN_INFO,1);
	DynamicJsonBuffer jsonBuffer;
	JsonObject& json = jsonBuffer.createObject();
	json["SOFTWARE_VERSION"] = SOFTWARE_VERSION;
	json["wlanssid"] = wlanssid;
	json["wlanpwd"] = wlanpwd;
	json["dht_read"] = dht_read;
	json["ppd_read"] = ppd_read;
	json["sds_read"] = sds_read;
	json["bmp_read"] = bmp_read;
	json["send2dusti"] = send2dusti;
	json["send2madavi"] = send2madavi;
	json["send2mqtt"] = send2mqtt;
	json["send2csv"] = send2csv;
	json["auto_update"] = auto_update;
	json["has_display"] = has_display;
	json["debug"] = debug;
	json["send2custom"] = send2custom;
	json["host_custom"] = host_custom;
	json["url_custom"] = url_custom;
	json["httpPort_custom"] = httpPort_custom;

	File configFile = SPIFFS.open("/config.json", "w");
	if (!configFile) {
		debug_out("failed to open config file for writing",DEBUG_ERROR,1);
	}

	char buffer[512];
	json.printTo(buffer, sizeof(buffer));
	debug_out(buffer,DEBUG_MIN_INFO,1);
	json.printTo(configFile);
	configFile.close();
	//end save
#endif
}

/*****************************************************************
/* read config from spiffs                                       *
/*****************************************************************/
void readConfig() {
#if defined(ESP8266)
	debug_out("mounting FS...",DEBUG_MIN_INFO,1);

	if (SPIFFS.begin()) {
		debug_out("mounted file system...",DEBUG_MIN_INFO,1);
		if (SPIFFS.exists("/config.json")) {
			//file exists, reading and loading
			debug_out("reading config file...",DEBUG_MIN_INFO,1);
			File configFile = SPIFFS.open("/config.json", "r");
			if (configFile) {
				debug_out("opened config file...",DEBUG_MIN_INFO,1);
				size_t size = configFile.size();
				// Allocate a buffer to store contents of the file.
				std::unique_ptr<char[]> buf(new char[size]);

				configFile.readBytes(buf.get(), size);
				DynamicJsonBuffer jsonBuffer;
				JsonObject& json = jsonBuffer.parseObject(buf.get());
				char buffer[512];
				json.printTo(buffer, sizeof(buffer));
				debug_out(buffer,DEBUG_MAX_INFO,1);
				if (json.success()) {
					debug_out("parsed json...",DEBUG_MIN_INFO,1);
					if (json.containsKey("SOFTWARE_VERSION")) strcpy(version_from_local_config, json["SOFTWARE_VERSION"]);
					if (json.containsKey("wlanssid")) strcpy(wlanssid, json["wlanssid"]);
					if (json.containsKey("wlanssid")) strcpy(wlanpwd, json["wlanpwd"]);
					if (json.containsKey("dht_read")) dht_read = json["dht_read"];
					if (json.containsKey("ppd_read")) ppd_read = json["ppd_read"];
					if (json.containsKey("sds_read")) sds_read = json["sds_read"];
					if (json.containsKey("bmp_read")) bmp_read = json["bmp_read"];
					if (json.containsKey("send2dusti")) send2dusti = json["send2dusti"];
					if (json.containsKey("send2madavi")) send2madavi = json["send2madavi"];
					if (json.containsKey("send2mqtt")) send2mqtt = json["send2mqtt"];
					if (json.containsKey("send2csv")) send2csv = json["send2csv"];
					if (json.containsKey("auto_update")) has_display = json["auto_update"];
					if (json.containsKey("has_display")) has_display = json["has_display"];
					if (json.containsKey("debug")) debug = json["debug"];
					if (json.containsKey("send2custom")) send2custom = json["send2custom"];
					if (json.containsKey("host_custom")) strcpy(host_custom, json["host_custom"]);
					if (json.containsKey("url_custom")) strcpy(url_custom, json["url_custom"]);
					if (json.containsKey("httpPort_custom")) httpPort_custom = json["httpPort_custom"];
				} else {
					debug_out("failed to load json config",DEBUG_ERROR,1);
				}
			}
		} else {
			debug_out("config file not found ...",DEBUG_ERROR,1);
		}
	} else {
		debug_out("failed to mount FS",DEBUG_ERROR,1);
	}
#endif
}

/*****************************************************************
/* AutoUpdate                                                    *
/*****************************************************************/
void autoUpdate() {
#if defined(ESP8266)
	if (auto_update) {
		debug_out("Starting OTA update ...",DEBUG_MIN_INFO,1);
		display_debug("Looking for OTA update");
		last_update_attempt = millis();
		t_httpUpdate_return ret = ESPhttpUpdate.update(update_host, update_port, update_url, SOFTWARE_VERSION);
		switch(ret) {
			case HTTP_UPDATE_FAILED:
					debug_out("[update] Update failed.",DEBUG_ERROR,1);
					display_debug("Update failed.");
					break;
			case HTTP_UPDATE_NO_UPDATES:
					debug_out("[update] Update no Update.",DEBUG_MIN_INFO,1);
					display_debug("No update found.");
					break;
			case HTTP_UPDATE_OK:
					debug_out("[update] Update ok.",DEBUG_MIN_INFO,1); // may not called we reboot the ESP
					break;
		}
	}
#endif
}

/*****************************************************************
/* display values                                                 *
/*****************************************************************/
void display_values(const String& data) {
#if defined(ESP8266)
	char* s;
	String tmp_type;
	String tmp_val;
	String temp;
	String humidity;
	String ppd_p1;
	String ppd_p2;
	String sds_p1;
	String sds_p2;
	int value_count = 0;
	StaticJsonBuffer<2000> jsonBuffer;
	JsonObject& json2data = jsonBuffer.parseObject(data);
	debug_out("output values to display...",DEBUG_MIN_INFO,1);
	debug_out(data,DEBUG_MAX_INFO,1);
	if (json2data.success()) {
		if (ppd_read) value_count += 6;
		if (sds_read) value_count += 2;
		if (dht_read) value_count += 2;
		for (int i=0;i<value_count;i++) {
			tmp_type = jsonBuffer.strdup(json2data["sensordatavalues"][i]["value_type"].asString());
			tmp_val = jsonBuffer.strdup(json2data["sensordatavalues"][i]["value"].asString());
			if (tmp_type == "temperature") temp = tmp_val;
			if (tmp_type == "humidity") humidity = tmp_val;
			if (tmp_type == "P1") ppd_p1 = tmp_val;
			if (tmp_type == "P2") ppd_p2 = tmp_val;
			if (tmp_type == "SDS_P1") sds_p1 = tmp_val;
			if (tmp_type == "SDS_P2") sds_p2 = tmp_val;
		}
	} else {
		debug_out("Data read failed",DEBUG_ERROR,1);
	}
	display.resetDisplay();
	display.clear();
	display.displayOn();
	display.setFont(ArialMT_Plain_10);
	display.setTextAlignment(TEXT_ALIGN_LEFT);
	value_count = 0;
	if (dht_read) display.drawString(0,12*(value_count++),"Temp: "+temp+"   Hum.: "+humidity);
	if (ppd_read) {
		display.drawString(0,12*(value_count++),"PPD P1: "+ppd_p1);
		display.drawString(0,12*(value_count++),"PPD P2: "+ppd_p2);
	}
	if (sds_read) {
		if (ppd_read) {
			display.drawString(0,12*(value_count++),"SDS P1: "+sds_p1);
			display.drawString(0,12*(value_count++),"SDS P2: "+sds_p2);
		} else {
			display.drawString(0,12*(value_count++),"SDS P1: "+ppd_p1);
			display.drawString(0,12*(value_count++),"SDS P2: "+ppd_p2);
		}
	}
	display.display();
#endif
}

/*****************************************************************
/* Init display                                                  *
/*****************************************************************/
void init_display() {
#if defined(ESP8266)
	display.init();
	display.resetDisplay();
#endif
}

/*****************************************************************
/* The Setup                                                     *
/*****************************************************************/
void setup() {
	Serial.begin(9600);             // Output to Serial at 9600 baud
#if defined(ESP8266)
	WiFi.persistent(false);
	Wire.pins(D3,D4);				// must be set before all other I2C cmds 
	Wire.begin(D3,D4);
#endif
#if defined(ARDUINO_SAMD_ZERO)
    Wire.begin();
#endif
	init_display();
	copyExtDef();
	display_debug("Reading config from SPIFFS");
	readConfig();
	display_debug("Connecting to "+String(wlanssid));
	connectWifi();                  // Start ConnectWifi
	display_debug("Writing config to SPIFFS");
	writeConfig();
	autoUpdate();
	pinMode(PPD_PIN_PM1,INPUT_PULLUP); // Listen at the designated PIN
	pinMode(PPD_PIN_PM2,INPUT_PULLUP); // Listen at the designated PIN
	dht.begin();                       // Start DHT
	delay(10);
#if defined(ESP8266)
	debug_out("\nChipId: ",DEBUG_MIN_INFO,1);
	debug_out(String(ESP.getChipId()),DEBUG_MIN_INFO,1);
#endif
#if defined(ARDUINO_SAMD_ZERO)
	if (!manager.init())
		debug_out("Manager init failed",DEBUG_MIN_INFO,1);
	if (!rf69.setFrequency(RF69_FREQ)) {
		debug_out("setFrequency failed",DEBUG_MIN_INFO,1);
		while (1);
	}
	debug_out("Set Freq to: ",DEBUG_MIN_INFO,0);
	debug_out(String(RF69_FREQ),DEBUG_MIN_INFO,1);
	rf69.setTxPower(15);
	debug_out("\nChipId: ",DEBUG_MIN_INFO,0);
	debug_out(FeatherChipId(),DEBUG_MIN_INFO,1);
#endif
	if (ppd_read) debug_out("Lese PPD...",DEBUG_MIN_INFO,1);
	if (sds_read) debug_out("Lese SDS...",DEBUG_MIN_INFO,1);
	if (dht_read) debug_out("Lese DHT...",DEBUG_MIN_INFO,1);
	if (bmp_read) debug_out("Lese BMP...",DEBUG_MIN_INFO,1);
	if (send2dusti) debug_out("Sende an luftdaten.info...",DEBUG_MIN_INFO,1);
	if (send2madavi) debug_out("Sende an madavi.de...",DEBUG_MIN_INFO,1);
	if (send2mqtt) debug_out("Sende an MQTT broker...",DEBUG_MIN_INFO,1);
	if (send2csv) debug_out("Sende als CSV an Serial...",DEBUG_MIN_INFO,1);
	if (send2custom) debug_out("Sende an custom API...",DEBUG_MIN_INFO,1);
	if (auto_update) debug_out("Auto-Update wird ausgeführt...",DEBUG_MIN_INFO,1);
	if (has_display) debug_out("Zeige auf Display...",DEBUG_MIN_INFO,1);
	if (bmp_read) {
		if (!bmp.begin()) {
			Serial.println("Could not find a valid BMP085 sensor, check wiring!");
			bmp_read = 0;
		}
	}
	starttime = millis();           // store the start time
	starttime_SDS = millis();
}

/*****************************************************************
/* And action                                                    *
/*****************************************************************/
void loop() {
	String data = "";
	String data_first_part = "{\"software_version\": \"" + String(SOFTWARE_VERSION) + "\", \"sensordatavalues\":[";
	String data_ppd = "";
	String data_dht = "";
	String data_sds = "";
	String data_bmp = "";
	String data_sample_times = "";

	act_micro = micros();
	act_milli = millis();

	sample_count++;
	
	if (last_micro != 0) {
		diff_micro = act_micro-last_micro;
		if (max_micro < diff_micro) { max_micro = diff_micro;}
		if (min_micro > diff_micro) { min_micro = diff_micro;}
		last_micro = act_micro;
	} else {
		last_micro = act_micro;
	}

	String result_PPD;
	String result_SDS;
	String result_DHT;
	String result_BMP;
	
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

	if (bmp_read && ((act_milli-starttime) > sampletime_ms)) {
		result_BMP = sensorBMP();  // getting temperature and humidity (optional)
	}

	if ((act_milli-starttime) > sampletime_ms) {
		debug_out("Creating data string:",DEBUG_MIN_INFO,1);
		data = data_first_part;
		data_sample_times  = "{\"value_type\":\"samples\",\"value\":\"";
		data_sample_times += long(sample_count);
		data_sample_times += "\"},";
		data_sample_times += "{\"value_type\":\"min_micro\",\"value\":\"";
		data_sample_times += long(min_micro);
		data_sample_times += "\"},";
		data_sample_times += "{\"value_type\":\"max_micro\",\"value\":\"";
		data_sample_times += long(max_micro);
		data_sample_times += "\"},";

		if (ppd_read) {
			data += result_PPD;
			data_ppd  = data_first_part + result_PPD;
			data_ppd += data_sample_times;
			data_ppd.remove(data_ppd.length()-1);
			data_ppd += "]}";
			if (send2dusti) {
				debug_out("#### Sending PPD data to luftdaten.info: ",DEBUG_MIN_INFO,1);
				sendData(data_ppd,PPD_API_PIN,host_dusti,httpPort_dusti,url_dusti);
			}
		}
		if (sds_read) {
			data += result_SDS;
			data_sds  = data_first_part + result_SDS;
			data_sds += data_sample_times;
			data_sds.remove(data_sds.length()-1);
			data_sds.replace("SDS_","");
			data_sds += "]}";
			if (send2dusti) {
				debug_out("#### Sending SDS data to luftdaten.info: ",DEBUG_MIN_INFO,1);
				sendData(data_sds,SDS_API_PIN,host_dusti,httpPort_dusti,url_dusti);
			}
		}
		if (dht_read) {
			data += result_DHT;
			data_dht  = data_first_part + result_DHT;
			data_dht += data_sample_times;
			data_dht.remove(data_dht.length()-1);
			data_dht += "]}";
			if (send2dusti) {
				debug_out("#### Sending DHT data to luftdaten.info: ",DEBUG_MIN_INFO,1);
				sendData(data_dht,DHT_API_PIN,host_dusti,httpPort_dusti,url_dusti);
			}
		}
		if (bmp_read) {
			data += result_BMP;
			data_bmp  = data_first_part + result_BMP;
			data_bmp += data_sample_times;
			data_bmp.remove(data_bmp.length()-1);
			data_bmp.replace("BMP_","");
			data_bmp += "]}";
			if (send2dusti) {
				debug_out("#### Sending BMP data to luftdaten.info: ",DEBUG_MIN_INFO,1);
				sendData(data_bmp,BMP_API_PIN,host_dusti,httpPort_dusti,url_dusti);
			}
		}

		data += data_sample_times;

		if ((result_PPD.length() > 0) || (result_DHT.length() > 0) || (result_SDS.length() > 0)) {
			data.remove(data.length()-1);
		}
		data += "]}";

		//sending to api(s)

		if (has_display) {
			display_values(data);
		}

		if (send2madavi) {
			debug_out("#### Sending to madavi.de: ",DEBUG_MIN_INFO,1);
			sendData(data,0,host_madavi,httpPort_madavi,url_madavi);
		}

		if (send2custom) {
			debug_out("#### Sending to custom api: ",DEBUG_MIN_INFO,1);
			sendData(data,0,host_custom,httpPort_custom,url_custom);
		}

		if (send2mqtt) {
			debug_out("#### Sending to mqtt: ",DEBUG_MIN_INFO,1);
			sendmqtt(data,host_mqtt,mqtt_port);
		}
		
		if (send2lora) {
			debug_out("#### Sending to LoRa gateway: ",DEBUG_MIN_INFO,1);
			send_lora(data);
		}

		if (send2csv) {
			debug_out("#### Sending as csv: ",DEBUG_MIN_INFO,1);
			send_csv(data);
		}

		if ((act_milli-last_update_attempt) > pause_between_update_attempts) {
			autoUpdate();
		}

		// Resetting for next sampling
		lowpulseoccupancyP1 = 0;
		lowpulseoccupancyP2 = 0;
		sample_count = 0;
		last_micro = 0;
		min_micro = 1000000000;
		max_micro = 0;
		starttime = millis(); // store the start time
	}
	
	yield();
}
