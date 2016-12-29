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
/*      - SDS011 Pin 5  (5V)   -> VU                             *
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
#define SOFTWARE_VERSION "NRZ-2016-039"

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
/* #define SEND2LORA 0                                           *
/* #define SEND2CSV 0                                            *
/*                                                               *
/* #define DEBUG 3                                               *
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
#include <TinyGPS++.h>

#include "ext_def.h"

/*****************************************************************
/* Variables with defaults                                       *
/*****************************************************************/
char wlanssid[65] = "Freifunk";
char wlanpwd[65] = "";

char version_from_local_config[30] = "";

bool dht_read = 1;
bool ppd_read = 0;
bool sds_read = 1;
bool bmp_read = 0;
bool gps_read = 0;
bool send2dusti = 1;
bool send2madavi = 1;
bool send2custom = 0;
bool send2mqtt = 0;
bool send2lora = 1;
bool send2influxdb = 0;
bool send2csv = 0;
bool auto_update = 0;
bool has_display = 0;
int  debug = 3;

long int sample_count = 0;

const char* host_madavi = "api-rrd.madavi.de";
const char* url_madavi = "/data.php";
const int httpPort_madavi = 443;

const char* host_dusti = "api.luftdaten.info";
const char* url_dusti = "/v1/push-sensor-data/";
const int httpPort_dusti = 443;

const char* host_api_madavi = "api.madavi.de";
const char* url_api_madavi = "/v1/push-sensor-data/";
const int httpPort_api_madavi = 443;

char host_influxdb[100] = "192.168.234.1";
char url_influxdb[100] = "/write?db=mydb";
int httpPort_influxdb = 8086;

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
WiFiClient client;
WiFiClientSecure client_s;
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
#if defined(ARDUINO_SAMD_ZERO)
#define serialSDS SERIAL_PORT_HARDWARE
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
/* GPS declaration                                               *
/*****************************************************************/
#if defined(ARDUINO_SAMD_ZERO) || defined(ESP8266)
TinyGPSPlus gps;
#endif

/*****************************************************************
/* Variable Definitions for PPD24NS                              *
/* P1 for PM10 & P2 for PM25                                     *
/*****************************************************************/

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
unsigned long starttime_GPS;
unsigned long act_micro;
unsigned long act_milli;
unsigned long last_micro = 0;
unsigned long min_micro = 1000000000;
unsigned long max_micro = 0;
unsigned long diff_micro = 0;

const unsigned long sampletime_ms = 30000;

const unsigned long sampletime_SDS_ms = 1000;
const unsigned long warmup_time_SDS_ms = 10000;
const unsigned long reading_time_SDS_ms = 5000;
bool is_SDS_running = true;

const unsigned long sampletime_GPS_ms = 50;

const unsigned long sending_intervall_ms = 55000;
unsigned long sending_time = 0;
bool send_failed = false;

unsigned long last_update_attempt;
const unsigned long pause_between_update_attempts = 86400000;
bool will_check_for_update = false;

int sds_pm10_sum = 0;
int sds_pm25_sum = 0;
int sds_val_count = 0;

String last_gps_lat;
String last_gps_lng;
String last_gps_alt;
String last_gps_date;
String last_gps_time;

bool first_csv_line = 1;

const byte stop_SDS_cmd[] = {0xAA, 0xB4, 0x06, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x05, 0xAB};
const byte start_SDS_cmd[] = {0xAA, 0xB4, 0x06, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x06, 0xAB};
const byte version_SDS_cmd[] = {0xAA, 0xB4, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x05, 0xAB};

String data_first_part = "{\"software_version\": \"" + String(SOFTWARE_VERSION) + "\"FEATHERCHIPID, \"sensordatavalues\":[";

const String txt_connection_failed = "connection failed";
const String txt_start_connecting_to = "Start connecting to ";
const String txt_end_connecting_to = "End connecting to ";
const String txt_start_reading = "Start reading ";
const String txt_end_reading = "End reading ";
const String txt_sending_to = "## Sending to ";
const String txt_no_data_sent = "No data sent ...";
const String txt_sending_to_luftdaten = "## Sending to luftdaten.info ";

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

/*****************************************************************
/* display values                                                *
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
String IPAddress2String(const IPAddress& ipaddress) {
	char myIpString[24];
	sprintf(myIpString, "%d.%d.%d.%d", ipaddress[0], ipaddress[1], ipaddress[2], ipaddress[3]);
	return String(myIpString);
}

/*****************************************************************
/* dtostrf for Arduino feather                                   *
/*****************************************************************/
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
String Float2String(const float value) {
	// Convert a float to String with two decimals.
	char temp[15];
	String s;

	dtostrf(value,13, 2, temp);
	s = String(temp);
	s.trim();
	return s;
}

/*****************************************************************
/* convert value to json string                                  *
/*****************************************************************/
String Value2Json(const String type, const String value) {
	String s = "{\"value_type\":\""+type+"\",\"value\":\""+value+"\"},";
	return s;
}

/*****************************************************************
/* ChipId Arduino Feather                                        *
/*****************************************************************/
String FeatherChipId() {
	String s;
#if defined(ARDUINO_SAMD_ZERO)
	debug_out("Reading Arduino Feather ChipID",DEBUG_MED_INFO,1);

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

#endif
	return s;
}

/*****************************************************************
/* read SDS011 sensor values                                     *
/*****************************************************************/
String SDS_version_date() {
	String s = "";
	String value_hex;
	char buffer;
	int value;
	int len = 0;
	String version_date = "";
	String device_id = "";
	int checksum_is;
	int checksum_ok = 0;
	int position = 0;

	debug_out(txt_start_reading+"SDS011 version date",DEBUG_MED_INFO,1);

	serialSDS.write(start_SDS_cmd,sizeof(start_SDS_cmd)); is_SDS_running = true;

	delay(100);

	serialSDS.write(version_SDS_cmd,sizeof(version_SDS_cmd));
	
	delay(100);

	while (serialSDS.available() > 0) {
		buffer = serialSDS.read();
		debug_out(String(len)+" - "+String(buffer,DEC)+" - "+String(buffer,HEX)+" - "+int(buffer)+" .",DEBUG_MED_INFO,1);
//		"aa" = 170, "ab" = 171, "c0" = 192
		value = int(buffer);
		switch (len) {
			case (0): if (value != 170) { len = -1; }; break;
			case (1): if (value != 197) { len = -1; }; break;
			case (2): if (value != 7) { len = -1; }; break;
			case (3): version_date  = String(value); checksum_is = 7 + value; break;
			case (4): version_date += "-"+String(value); checksum_is += value; break;
			case (5): version_date += "-"+String(value); checksum_is += value; break;
			case (6): if (value < 0x10) {device_id  = "0"+String(value,HEX);} else {device_id  = String(value,HEX);}; checksum_is += value; break;
			case (7): if (value < 0x10) {device_id += "0";}; device_id += String(value,HEX); checksum_is += value; break;
			case (8):
					debug_out("Checksum is: "+String(checksum_is % 256)+" - should: "+String(value),DEBUG_MED_INFO,1);
					if (value == (checksum_is % 256)) { checksum_ok = 1; } else { len = -1; }; break;
			case (9): if (value != 171) { len = -1; }; break;
		}
		len++;
		if (len == 10 && checksum_ok == 1) {
			s = version_date+"("+device_id+")";
			debug_out("SDS version date : "+version_date,DEBUG_MIN_INFO,1);
			debug_out("SDS device ID:     "+device_id,DEBUG_MIN_INFO,1);
			len = 0; checksum_ok = 0; version_date = ""; device_id = ""; checksum_is = 0;
		}
		yield();
	}

	debug_out(txt_end_reading+"SDS011 version date",DEBUG_MED_INFO,1);

	return s;
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

	debug_out("Starting WiFiManager",DEBUG_MIN_INFO,1);
	debug_out("AP ID: Feinstaubsensor-"+String(ESP.getChipId()),DEBUG_MIN_INFO,1);

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
	WiFiManagerParameter custom_send2influxdb("send2influxdb", "Senden an eigene InfluxDB (0/1)?", "", 10);
	wifiManager.addParameter(&custom_send2influxdb);
//	WiFiManagerParameter custom_host_influxdb("host_influxdb, "Host ?", "", 40);
//	wifiManager.addParameter(&custom_host_influxdb);
//	WiFiManagerParameter custom_url_influxdb("url_influxdb", "Pfad ?", "", 40);
//	wifiManager.addParameter(&custom_url_influxdb);
//	WiFiManagerParameter custom_httpPort_influxdb("httpPort_influxdb, "HTTP Port (8086) ?", "", 10);
//	wifiManager.addParameter(&custom_httpPort_influxdb);
	apname = "Feinstaubsensor-" + String(ESP.getChipId());
	wifiManager.setTimeout(300);
	wifiManager.setBreakAfterConfig(true);
	wifiManager.startConfigPortal(apname.c_str());
	if (WiFi.SSID().length() != 0) {
		custom_wlanssid = WiFi.SSID();
		custom_wlanpwd = WiFi.psk();
		strcpy(wlanssid,custom_wlanssid.c_str());
		strcpy(wlanpwd,custom_wlanpwd.c_str());
	}
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
	if (strcmp(custom_send2influxdb.getValue(),"") != 0) send2influxdb = strtol(custom_send2influxdb.getValue(), NULL, 10);
//	if (strcmp(custom_host_influxdb.getValue(),"") != 0) strcpy(host_influxdb,custom_host_influxdb.getValue());
//	if (strcmp(custom_url_influxdb.getValue(),"") != 0) strcpy(url_influxdb,custom_url_influxdb.getValue());
//	if (strcmp(custom_httpPort_influxdb.getValue(),"") != 0) httpPort_influxdb = strtol(custom_httpPort_influxdb.getValue(), NULL, 10);
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
	debug_out("InfluxDB: "+String(custom_send2influxdb.getValue())+" - "+String(send2influxdb),DEBUG_MIN_INFO,1);
//	debug_out("InfluxDB Host: "+String(custom_host_influxdb.getValue())+" - "+String(host_influxdb),DEBUG_MIN_INFO,1);
//	debug_out("InfluxDB URL: "+String(custom_url_influxdb.getValue())+" - "+String(url_influxdb),DEBUG_MIN_INFO,1);
//	debug_out("InfluxDB Port: "+String(custom_httpPort_influxdb.getValue())+" - "+String(httpPort_influxdb),DEBUG_MIN_INFO,1);
	debug_out("------",DEBUG_MIN_INFO,1);
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

/*****************************************************************
/* send data to rest api                                         *
/*****************************************************************/
void sendData(const String& data, const int pin, const char* host, const int httpPort, const char* url) {
#if defined(ESP8266)

	debug_out(txt_start_connecting_to,DEBUG_MIN_INFO,0);
	debug_out(host,DEBUG_MIN_INFO,1);

	String request_head = "POST " + String(url) + " HTTP/1.1\r\n" +
					"Host: " + String(host) + "\r\n" +
					"Content-Type: application/json\r\n" +
					"PIN: " + String(pin) + "\r\n" +
					"Sensor: esp8266-" + String(ESP.getChipId()) + "\r\n" +
					"Content-Length: " + String(data.length(),DEC) + "\r\n" +
					"Connection: close\r\n\r\n";

	// Use WiFiClient class to create TCP connections

	if (httpPort == 80) {
		if (!client.connect(host, httpPort)) {
			debug_out(txt_connection_failed,DEBUG_ERROR,1);
			return;
		}

		debug_out("Requesting URL: ",DEBUG_MIN_INFO,0);
		debug_out(url,DEBUG_MIN_INFO,1);
		debug_out(String(ESP.getChipId()),DEBUG_MIN_INFO,1);
		debug_out(data,DEBUG_MIN_INFO,1);

		client.print(request_head);

		client.println(data);

		delay(10);

		// Read reply from server and print them
		while(client.available()){
			char c = client.read();
			debug_out(String(c),DEBUG_MAX_INFO,0);
		}

		debug_out("\nclosing connection\n------\n\n",DEBUG_MIN_INFO,1);

	} else {

		if (!client_s.connect(host, httpPort)) {
			debug_out(txt_connection_failed,DEBUG_ERROR,1);
			return;
		}

		debug_out("Requesting URL: ",DEBUG_MIN_INFO,0);
		debug_out(url,DEBUG_MIN_INFO,1);
		debug_out(String(ESP.getChipId()),DEBUG_MIN_INFO,1);
		debug_out(data,DEBUG_MIN_INFO,1);

		// send request to the server

		client_s.print(request_head);

		client_s.println(data);

		delay(10);

		// Read reply from server and print them
		while(client_s.available()){
			char c = client_s.read();
			debug_out(String(c),DEBUG_MAX_INFO,0);
		}

		debug_out("\nclosing connection\n------\n\n",DEBUG_MIN_INFO,1);

	}

	debug_out(txt_end_connecting_to,DEBUG_MIN_INFO,0);
	debug_out(host,DEBUG_MIN_INFO,1);

#endif
}

/*****************************************************************
/* send data to LoRa gateway                                     *
/*****************************************************************/
void send_lora(const String& data) {
#if defined(ARDUINO_SAMD_ZERO)
	uint8_t buf[RH_RF69_MAX_MESSAGE_LEN];
	uint8_t message_end[] = "LORA_MESSAGE_END";
	uint8_t message_start[] = "LORA_MESSAGE_START";
	int counter;
	String part2send;
	const String txt_no_reply = "No reply, server running?";
	const String txt_got_reply_from = "got reply from : 0x";
	const String txt_sentToWait_failed = "sendtoWait failed";

	debug_out(txt_start_connecting_to+"LoRa gateway",DEBUG_MIN_INFO,1);

	debug_out("data.length(): ",DEBUG_MAX_INFO,0);
	debug_out(String(data.length()),DEBUG_MAX_INFO,1);

	if (manager.sendtoWait(message_start, sizeof(message_start), SERVER_ADDRESS)) {
		// Now wait for a reply from the server
		uint8_t len = sizeof(buf);
		uint8_t from;
		if (manager.recvfromAckTimeout(buf, &len, 2000, &from)) {
			debug_out(txt_got_reply_from,DEBUG_MAX_INFO,0);
			debug_out(String(from, HEX),DEBUG_MAX_INFO,1);
		} else {
			debug_out(txt_no_reply,DEBUG_MIN_INFO,1);
		}
	} else
		debug_out(txt_sentToWait_failed,DEBUG_MIN_INFO,1);

	while ((counter * (RH_RF69_MAX_MESSAGE_LEN-1)) < data.length()+1) {

		part2send = data.substring(counter * (RH_RF69_MAX_MESSAGE_LEN-1), (counter * (RH_RF69_MAX_MESSAGE_LEN - 1) + (RH_RF69_MAX_MESSAGE_LEN - 1) <= (data.length()+1) ? counter * (RH_RF69_MAX_MESSAGE_LEN - 1) + (RH_RF69_MAX_MESSAGE_LEN - 1) : (data.length()+1) ) ) + "\0";

		debug_out("Data part: ",DEBUG_MAX_INFO,0);
		debug_out(part2send,DEBUG_MAX_INFO,1);
		debug_out("part2send.length(): ",DEBUG_MAX_INFO,0);
		debug_out(String(part2send.length()),DEBUG_MAX_INFO,1);

		if (manager.sendtoWait((uint8_t*)(part2send.c_str()), part2send.length(), SERVER_ADDRESS))
		{
			// Now wait for a reply from the server
			uint8_t len = sizeof(buf);
			uint8_t from;
			if (manager.recvfromAckTimeout(buf, &len, 2000, &from))
			{
				debug_out(txt_got_reply_from,DEBUG_MAX_INFO,0);
				debug_out(String(from, HEX),DEBUG_MAX_INFO,1);
			} else {
				debug_out(txt_no_reply,DEBUG_MIN_INFO,1);
			}
		} else
			debug_out(txt_sentToWait_failed,DEBUG_MIN_INFO,1);

		counter++;
	}

	if (manager.sendtoWait(message_end, sizeof(message_end), SERVER_ADDRESS)) {
		// Now wait for a reply from the server
		uint8_t len = sizeof(buf);
		uint8_t from;
		if (manager.recvfromAckTimeout(buf, &len, 2000, &from)) {
			debug_out(txt_got_reply_from,DEBUG_MAX_INFO,0);
			debug_out(String(from, HEX),DEBUG_MAX_INFO,1);
		} else {
			debug_out(txt_no_reply,DEBUG_MIN_INFO,1);
		}
	} else
		debug_out(txt_sentToWait_failed,DEBUG_MIN_INFO,1);

	debug_out("\nclosing connection\n------\n\n",DEBUG_MIN_INFO,1);

	debug_out(txt_end_connecting_to+"LoRa gateway",DEBUG_MIN_INFO,1);

#endif
}

/*****************************************************************
/* send data to mqtt api                                         *
/*****************************************************************/
void sendmqtt(const String& data, const char* host, const int mqtt_port) {
}

/*****************************************************************
  /* send data to influxdb                                         *
  /*****************************************************************/
void send_influxDB(const String& data, const int pin, const char* host, const int httpPort, const char* url) {
#if defined(ESP8266)

  debug_out(txt_start_connecting_to, DEBUG_MIN_INFO, 0);
  debug_out(host, DEBUG_MIN_INFO, 1);

  // Use WiFiClient class to create TCP connections
  if (!client.connect(host, httpPort)) {
    debug_out(txt_connection_failed, DEBUG_ERROR, 1);
    return;
  }

  String tmp_str;
  String valueline;
  int value_count = 0;
  StaticJsonBuffer<2000> jsonBuffer;
  JsonObject& json2data = jsonBuffer.parseObject(data);
  debug_out("Parse JSON for influx DB", DEBUG_MIN_INFO, 1);
  debug_out(data, DEBUG_MIN_INFO, 1);
  if (json2data.success()) {
    valueline = "";
    for (int i = 0; i < json2data["sensordatavalues"].size()-1; i++) {
      valueline += "feinstaub,node=esp8266-"+String(ESP.getChipId())+" ";
      tmp_str = jsonBuffer.strdup(json2data["sensordatavalues"][i]["value_type"].asString());
      valueline += tmp_str + "=";
      tmp_str = jsonBuffer.strdup(json2data["sensordatavalues"][i]["value"].asString());
      valueline += tmp_str + "\n";
    }
  } else {
    debug_out("Data read failed", DEBUG_ERROR, 1);
  }

  debug_out("Requesting URL: ", DEBUG_MIN_INFO, 0);
  debug_out(url, DEBUG_MIN_INFO, 1);
  debug_out(String(ESP.getChipId()), DEBUG_MIN_INFO, 1);
  debug_out(valueline, DEBUG_MIN_INFO, 1);

  String request_head = "POST " + String(url) + " HTTP/1.1\r\n" +
                        "Host: " + String(host) + "\r\n" +
                        "Accept: */*\r\n" +
                        "Content-Length: " + String(valueline.length(), DEC) + "\r\n" +
                        "Content-Type: application/x-www-form-urlencoded\r\n" +
                        "PIN: " + String(pin) + "\r\n" +
                        "Sensor: esp8266-" + String(ESP.getChipId()) + "\r\n\r\n";

  // send request to the server

  client.print(request_head);

  client.println(valueline);

  delay(10);

  // Read reply from server and print them
  while (client.available()) {
    char c = client.read();
    debug_out(String(c), DEBUG_MIN_INFO, 0);
  }

  debug_out("\nclosing connection\n------\n\n", DEBUG_MIN_INFO, 1);
  debug_out(txt_end_connecting_to, DEBUG_MIN_INFO, 0);
  debug_out(host, DEBUG_MIN_INFO, 1);

#endif
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
		for (int i=0;i<json2data["sensordatavalues"].size();i++) {
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

	debug_out(txt_start_reading+"DHT11/22",DEBUG_MED_INFO,1);

	// Check if valid number if non NaN (not a number) will be send.
	if (isnan(t) || isnan(h)) {
		debug_out("DHT22 couldn't be read",DEBUG_ERROR,1);
	} else {
		debug_out("Humidity    : "+String(h)+"%",DEBUG_MIN_INFO,1);
		debug_out("Temperature : "+String(t)+" C",DEBUG_MIN_INFO,1);
		s += Value2Json("temperature",Float2String(t));
		s += Value2Json("humidity",Float2String(h));
	}
	debug_out("------",DEBUG_MIN_INFO,1);

	debug_out(txt_end_reading+"DHT11/22",DEBUG_MED_INFO,1);

	return s;
}

/*****************************************************************
/* read BMP180 sensor values                                     *
/*****************************************************************/
String sensorBMP() {
	String s = "";
	int p;
	float t;

	debug_out(txt_start_reading+"BMP180",DEBUG_MED_INFO,1);

	p = bmp.readPressure();
	t = bmp.readTemperature();
	if (isnan(p) || isnan(t)) {
		debug_out("BMP180 couldn't be read",DEBUG_ERROR,1);
	} else {
		debug_out("Pressure    : "+Float2String(float(p)/100)+" hPa",DEBUG_MIN_INFO,1);
		debug_out("Temperature : "+String(t)+" C",DEBUG_MIN_INFO,1);
		s += Value2Json("BMP_pressure",String(p));
		s += Value2Json("BMP_temperature",Float2String(t));
	}
	debug_out("------",DEBUG_MIN_INFO,1);

	debug_out(txt_end_reading+"BMP180",DEBUG_MED_INFO,1);

	return s;
}

/*****************************************************************
/* read SDS011 sensor values                                     *
/*****************************************************************/
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

	debug_out(txt_start_reading+"SDS011",DEBUG_MED_INFO,1);

	if ((act_milli-starttime) < (sending_intervall_ms - (warmup_time_SDS_ms + reading_time_SDS_ms))) {
		if (is_SDS_running) {
			serialSDS.write(stop_SDS_cmd,sizeof(stop_SDS_cmd));	is_SDS_running = false;
		}
	} else {
		if (! is_SDS_running) {
			serialSDS.write(start_SDS_cmd,sizeof(start_SDS_cmd)); is_SDS_running = true;
		}

		while (serialSDS.available() > 0) {
			buffer = serialSDS.read();
			debug_out(String(len)+" - "+String(buffer,DEC)+" - "+String(buffer,HEX)+" - "+int(buffer)+" .",DEBUG_MAX_INFO,1);
//			"aa" = 170, "ab" = 171, "c0" = 192
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
						debug_out("Checksum is: "+String(checksum_is % 256)+" - should: "+String(value),DEBUG_MED_INFO,1);
						if (value == (checksum_is % 256)) { checksum_ok = 1; } else { len = -1; }; break;
				case (9): if (value != 171) { len = -1; }; break;
			}
			len++;
			if (len == 10 && checksum_ok == 1 && ((act_milli-starttime) > (sending_intervall_ms - reading_time_SDS_ms))) {
				if ((! isnan(pm10_serial)) && (! isnan(pm25_serial))) {
					sds_pm10_sum += pm10_serial;
					sds_pm25_sum += pm25_serial;
					debug_out("PM10 (sec.) : "+Float2String(float(pm10_serial)/10),DEBUG_MED_INFO,1);
					debug_out("PM2.5 (sec.): "+Float2String(float(pm25_serial)/10),DEBUG_MED_INFO,1);
					sds_val_count++;
				}
				len = 0; checksum_ok = 0; pm10_serial = 0.0; pm25_serial = 0.0; checksum_is = 0;
			}
			yield();
		}

	}
	if (((act_milli-starttime) > sending_intervall_ms) && (sds_val_count > 0)) {
		debug_out("PM10:  "+Float2String(float(sds_pm10_sum)/(sds_val_count*10.0)),DEBUG_MIN_INFO,1);
		debug_out("PM2.5: "+Float2String(float(sds_pm25_sum)/(sds_val_count*10.0)),DEBUG_MIN_INFO,1);
		debug_out("------",DEBUG_MIN_INFO,1);
		s += Value2Json("SDS_P1",Float2String(float(sds_pm10_sum)/(sds_val_count*10.0)));
		s += Value2Json("SDS_P2",Float2String(float(sds_pm25_sum)/(sds_val_count*10.0)));
		sds_pm10_sum = 0; sds_pm25_sum = 0; sds_val_count = 0;
		if ((sending_intervall_ms > (warmup_time_SDS_ms + reading_time_SDS_ms)) && (! will_check_for_update)) {
			serialSDS.write(stop_SDS_cmd,sizeof(stop_SDS_cmd));	is_SDS_running = false;
		}
	}

	debug_out(txt_end_reading+"SDS011",DEBUG_MED_INFO,1);

	return s;
}

/*****************************************************************
/* read PPD42NS sensor values                                    *
/*****************************************************************/
String sensorPPD() {
	boolean valP1 = HIGH;
	boolean valP2 = HIGH;
	float ratio = 0;
	float concentration = 0;
	String s = "";

	debug_out(txt_start_reading+"PPD42NS",DEBUG_MED_INFO,1);

	if ((act_milli-starttime) <= sampletime_ms) {

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

	}
	// Checking if it is time to sample
	if ((act_milli-starttime) > sending_intervall_ms) {
		ratio = lowpulseoccupancyP1/(sampletime_ms*10.0);					// int percentage 0 to 100
		concentration = (1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62);	// spec sheet curve
		// Begin printing
		debug_out("LPO P10    : "+String(lowpulseoccupancyP1),DEBUG_MIN_INFO,1);
		debug_out("Ratio PM10 : "+Float2String(ratio)+" %",DEBUG_MIN_INFO,1);
		debug_out("PM10 Count : "+Float2String(concentration),DEBUG_MIN_INFO,1);

		// json for push to api / P1
		s += Value2Json("durP1",String(long(lowpulseoccupancyP1)));
		s += Value2Json("ratioP1",Float2String(ratio));
		s += Value2Json("P1",Float2String(concentration));

		ratio = lowpulseoccupancyP2/(sampletime_ms*10.0);
		concentration = (1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62);
		// Begin printing
		debug_out("LPO PM25   : "+String(lowpulseoccupancyP2),DEBUG_MIN_INFO,1);
		debug_out("Ratio PM25 : "+Float2String(ratio)+" %",DEBUG_MIN_INFO,1);
		debug_out("PM25 Count : "+Float2String(concentration),DEBUG_MIN_INFO,1);

		// json for push to api / P2
		s += Value2Json("durP2",String(long(lowpulseoccupancyP2)));
		s += Value2Json("ratioP2",Float2String(ratio));
		s += Value2Json("P2",Float2String(concentration));

		debug_out("------",DEBUG_MIN_INFO,1);
	}

	debug_out(txt_end_reading+"PPD42NS",DEBUG_MED_INFO,1);

	return s;
}

/*****************************************************************
/* read GPS sensor values                                        *
/*****************************************************************/
String sensorGPS() {
	String s = "";
#if defined(ARDUINO_SAMD_ZERO) || defined(ESP8266)
	String gps_lat = "";
	String gps_lng = "";
	String gps_alt = "";
	String gps_date = "";
	String gps_time = "";

	debug_out(txt_start_reading+"GPS",DEBUG_MED_INFO,1);

	while (serialSDS.available() > 0) {
		if (gps.encode(serialSDS.read())) {
			if (gps.location.isValid()) {
				last_gps_lat = String(gps.location.lat(),6);
				last_gps_lng = String(gps.location.lng(),6);
			} else {
				debug_out("Lat/Lng INVALID",DEBUG_MAX_INFO,1);
			}
			if (gps.altitude.isValid()) {
				last_gps_alt = String(gps.altitude.meters(),2);
			} else {
				debug_out("Altitude INVALID",DEBUG_MAX_INFO,1);
			}
			if (gps.date.isValid()) {
				gps_date = "";
				if (gps.date.month() < 10) gps_date += "0";
				gps_date += String(gps.date.month());
				gps_date += "/";
				if (gps.date.day() < 10) gps_date += "0";
				gps_date += String(gps.date.day());
				gps_date += "/";
				gps_date += String(gps.date.year());
				last_gps_date = gps_date;
			} else {
				debug_out("Date INVALID",DEBUG_MAX_INFO,1);
			}
			if (gps.time.isValid()) {
				gps_time = "";
				if (gps.time.hour() < 10) gps_time += "0";
				gps_time += String(gps.time.hour());
				gps_time += ":";
				if (gps.time.minute() < 10) gps_time += "0";
				gps_time += String(gps.time.minute());
				gps_time += ":";
				if (gps.time.second() < 10) gps_time += "0";
				gps_time += String(gps.time.second());
				gps_time += ".";
				if (gps.time.centisecond() < 10) gps_time += "0";
				gps_time += String(gps.time.centisecond());
				last_gps_time = gps_time;
			} else {
				debug_out("Time: INVALID",DEBUG_MAX_INFO,1);
			}
		}
	}

	if ((act_milli-starttime) > sending_intervall_ms) {
		debug_out("Lat/Lng: "+last_gps_lat+","+last_gps_lng,DEBUG_MIN_INFO,1);
		debug_out("Altitude: "+last_gps_alt,DEBUG_MIN_INFO,1);
		debug_out("Date: "+last_gps_date,DEBUG_MIN_INFO,1);
		debug_out("Time "+last_gps_time,DEBUG_MIN_INFO,1);
		debug_out("------",DEBUG_MIN_INFO,1);
		s += Value2Json("GPS_lat",last_gps_lat);
		s += Value2Json("GPS_lon",last_gps_lng);
		s += Value2Json("GPS_height",last_gps_alt);
		s += Value2Json("GPS_date",last_gps_date);
		s += Value2Json("GPS_time",last_gps_time);
		last_gps_lat = "";
		last_gps_lng = "";
		last_gps_alt = "";
		last_gps_date = "";
		last_gps_time = "";
	}
	debug_out(txt_end_reading+"GPS",DEBUG_MED_INFO,1);

#endif
	return s;
}

/*****************************************************************
/* copy config from ext_def                                      *
/*****************************************************************/
void copyExtDef() {
	if (WLANSSID != NULL) { strcpy(wlanssid,WLANSSID); }
	if (WLANPWD  != NULL) { strcpy(wlanpwd,WLANPWD); }
	if (DHT_READ != dht_read) { dht_read = DHT_READ; }
	if (PPD_READ != ppd_read) { ppd_read = PPD_READ; }
	if (SDS_READ != sds_read) { sds_read = SDS_READ; }
	if (BMP_READ != bmp_read) { bmp_read = BMP_READ; }
	if (GPS_READ != gps_read) { gps_read = GPS_READ; }
	if (SEND2DUSTI != send2dusti) { send2dusti = SEND2DUSTI; }
	if (SEND2MADAVI != send2madavi) { send2madavi = SEND2MADAVI; }
	if (SEND2MQTT != send2mqtt) { send2mqtt = SEND2MQTT; }
	if (SEND2LORA != send2lora) { send2lora = SEND2LORA; }
	if (SEND2CSV != send2csv) { send2csv = SEND2CSV; }
	if (AUTO_UPDATE != auto_update) { auto_update = AUTO_UPDATE; }
	if (HAS_DISPLAY != has_display) { has_display = HAS_DISPLAY; }

	if (DEBUG != debug) { debug = DEBUG; }

	if (SEND2CUSTOM != send2custom) { send2custom = SEND2CUSTOM; }
	if (HOST_CUSTOM != NULL) { strcpy(host_custom,HOST_CUSTOM); }
	if (URL_CUSTOM != NULL) { strcpy(url_custom,URL_CUSTOM); }
	if (HTTPPORT_CUSTOM != httpPort_custom) { httpPort_custom = HTTPPORT_CUSTOM; }

	if (SEND2INFLUXDB != send2influxdb) { send2influxdb = SEND2INFLUXDB; }
	if (HOST_INFLUXDB != NULL) { strcpy(host_influxdb,HOST_INFLUXDB); }
	if (URL_INFLUXDB != NULL) { strcpy(url_influxdb,URL_INFLUXDB); }
	if (HTTPPORT_INFLUXDB != httpPort_influxdb) { httpPort_influxdb = HTTPPORT_INFLUXDB; }
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
	json["gps_read"] = gps_read;
	json["send2dusti"] = send2dusti;
	json["send2madavi"] = send2madavi;
	json["send2mqtt"] = send2mqtt;
	json["send2lora"] = send2lora;
	json["send2csv"] = send2csv;
	json["auto_update"] = auto_update;
	json["has_display"] = has_display;
	json["debug"] = debug;
	json["send2custom"] = send2custom;
	json["host_custom"] = host_custom;
	json["url_custom"] = url_custom;
	json["httpPort_custom"] = httpPort_custom;
	json["send2influxdb"] = send2influxdb;
	json["host_influxdb"] = host_influxdb;
	json["url_influxdb"] = url_influxdb;
	json["httpPort_influxdb"] = httpPort_influxdb;

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
					if (json.containsKey("wlanpwd")) strcpy(wlanpwd, json["wlanpwd"]);
					if (json.containsKey("dht_read")) dht_read = json["dht_read"];
					if (json.containsKey("ppd_read")) ppd_read = json["ppd_read"];
					if (json.containsKey("sds_read")) sds_read = json["sds_read"];
					if (json.containsKey("bmp_read")) bmp_read = json["bmp_read"];
					if (json.containsKey("gps_read")) gps_read = json["gps_read"];
					if (json.containsKey("send2dusti")) send2dusti = json["send2dusti"];
					if (json.containsKey("send2madavi")) send2madavi = json["send2madavi"];
					if (json.containsKey("send2mqtt")) send2mqtt = json["send2mqtt"];
					if (json.containsKey("send2lora")) send2lora = json["send2lora"];
					if (json.containsKey("send2csv")) send2csv = json["send2csv"];
					if (json.containsKey("auto_update")) auto_update = json["auto_update"];
					if (json.containsKey("has_display")) has_display = json["has_display"];
					if (json.containsKey("debug")) debug = json["debug"];
					if (json.containsKey("send2custom")) send2custom = json["send2custom"];
					if (json.containsKey("host_custom")) strcpy(host_custom, json["host_custom"]);
					if (json.containsKey("url_custom")) strcpy(url_custom, json["url_custom"]);
					if (json.containsKey("httpPort_custom")) httpPort_custom = json["httpPort_custom"];
					if (json.containsKey("send2influxdb")) send2influxdb = json["send2influxdb"];
					if (json.containsKey("host_influxdb")) strcpy(host_influxdb, json["host_influxdb"]);
					if (json.containsKey("url_influxdb")) strcpy(url_influxdb, json["url_influxdb"]);
					if (json.containsKey("httpPort_influxdb")) httpPort_influxdb = json["httpPort_influxdb"];
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
	String SDS_version = "";
	if (auto_update) {
		debug_out("Starting OTA update ...",DEBUG_MIN_INFO,1);
		debug_out("NodeMCU firmware : "+String(SOFTWARE_VERSION),DEBUG_MIN_INFO,1);
		if (sds_read) { SDS_version = SDS_version_date();}
		display_debug("Looking for OTA update");
		last_update_attempt = millis();
		t_httpUpdate_return ret = ESPhttpUpdate.update(update_host, update_port, update_url, String(SOFTWARE_VERSION)+String(" ")+String(ESP.getChipId())+String(" ")+SDS_version);
		switch(ret) {
			case HTTP_UPDATE_FAILED:
					debug_out("[update] Update failed.",DEBUG_ERROR,1);
					display_debug("Update failed.");
					break;
			case HTTP_UPDATE_NO_UPDATES:
					debug_out("[update] No Update.",DEBUG_MIN_INFO,1);
					display_debug("No update found.");
					break;
			case HTTP_UPDATE_OK:
					debug_out("[update] Update ok.",DEBUG_MIN_INFO,1); // may not called we reboot the ESP
					break;
		}
	}
	will_check_for_update = false;
#endif
}

/*****************************************************************
/* display values                                                *
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
	String bmp_pressure;
	String bmp_temp;
	int value_count = 0;
	StaticJsonBuffer<2000> jsonBuffer;
	JsonObject& json2data = jsonBuffer.parseObject(data);
	debug_out("output values to display...",DEBUG_MIN_INFO,1);
	debug_out(data,DEBUG_MAX_INFO,1);
	if (json2data.success()) {
		if (ppd_read) value_count += 6;
		if (sds_read) value_count += 2;
		if (dht_read) value_count += 2;
		if (bmp_read) value_count += 2;
		for (int i=0;i<value_count;i++) {
			tmp_type = jsonBuffer.strdup(json2data["sensordatavalues"][i]["value_type"].asString());
			tmp_val = jsonBuffer.strdup(json2data["sensordatavalues"][i]["value"].asString());
			if (tmp_type == "temperature") temp = tmp_val;
			if (tmp_type == "humidity") humidity = tmp_val;
			if (tmp_type == "P1") ppd_p1 = tmp_val;
			if (tmp_type == "P2") ppd_p2 = tmp_val;
			if (tmp_type == "SDS_P1") sds_p1 = tmp_val;
			if (tmp_type == "SDS_P2") sds_p2 = tmp_val;
			if (tmp_type == "BMP_pressure") bmp_pressure = tmp_val;
			if (tmp_type == "BMP_temperature") bmp_temp = tmp_val;
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
	if (dht_read) {
		display.drawString(0,10*(value_count++),"Temp: "+temp+"   Hum.: "+humidity);
	}
	if (bmp_read) {
		display.drawString(0,10*(value_count++),"Temp: "+bmp_temp+"  Druck: "+bmp_pressure);
	}
	if (ppd_read) {
		display.drawString(0,10*(value_count++),"PPD P1: "+ppd_p1);
		display.drawString(0,10*(value_count++),"PPD P2: "+ppd_p2);
	}
	if (sds_read) {
		display.drawString(0,10*(value_count++),"SDS P1: "+sds_p1);
		display.drawString(0,10*(value_count++),"SDS P2: "+sds_p2);
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
	Serial.begin(9600);					// Output to Serial at 9600 baud
#if defined(ESP8266)
	Wire.pins(D3,D4);					// must be set before all other I2C cmds 
	Wire.begin(D3,D4);
#endif
#if defined(ARDUINO_SAMD_ZERO)
	Wire.begin();
	serialSDS.begin(9600);
#endif
	init_display();
	copyExtDef();
	display_debug("Reading config from SPIFFS");
	readConfig();
	display_debug("Connecting to "+String(wlanssid));
	connectWifi();						// Start ConnectWifi
	display_debug("Writing config to SPIFFS");
	writeConfig();
	autoUpdate();
	pinMode(PPD_PIN_PM1,INPUT_PULLUP);	// Listen at the designated PIN
	pinMode(PPD_PIN_PM2,INPUT_PULLUP);	// Listen at the designated PIN
	dht.begin();						// Start DHT
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
	rf69.setTxPower(20);
	debug_out("\nChipId: ",DEBUG_MIN_INFO,0);
	debug_out(FeatherChipId(),DEBUG_MIN_INFO,1);
#endif
	if (ppd_read) debug_out("Lese PPD...",DEBUG_MIN_INFO,1);
	if (sds_read) debug_out("Lese SDS...",DEBUG_MIN_INFO,1);
	if (dht_read) debug_out("Lese DHT...",DEBUG_MIN_INFO,1);
	if (bmp_read) debug_out("Lese BMP...",DEBUG_MIN_INFO,1);
	if (gps_read) debug_out("Lese GPS...",DEBUG_MIN_INFO,1);
	if (send2dusti) debug_out("Sende an luftdaten.info...",DEBUG_MIN_INFO,1);
	if (send2madavi) debug_out("Sende an madavi.de...",DEBUG_MIN_INFO,1);
	if (send2mqtt) debug_out("Sende an MQTT broker...",DEBUG_MIN_INFO,1);
	if (send2lora) debug_out("Sende an LoRa gateway...",DEBUG_MIN_INFO,1);
	if (send2csv) debug_out("Sende als CSV an Serial...",DEBUG_MIN_INFO,1);
	if (send2custom) debug_out("Sende an custom API...",DEBUG_MIN_INFO,1);
	if (send2influxdb) debug_out("Sende an custom influx DB...",DEBUG_MIN_INFO,1);
	if (auto_update) debug_out("Auto-Update wird ausgeführt...",DEBUG_MIN_INFO,1);
	if (has_display) debug_out("Zeige auf Display...",DEBUG_MIN_INFO,1);
	if (bmp_read) {
		if (!bmp.begin()) {
			debug_out("No valid BMP085 sensor, check wiring!",DEBUG_MIN_INFO,1);
			bmp_read = 0;
		}
	}
	
#if defined(ARDUINO_SAMD_ZERO)
	data_first_part.replace("FEATHERCHIPID", ", \"chipid\": \"" + FeatherChipId() + "\"");
#else
	data_first_part.replace("FEATHERCHIPID", "");
#endif

	starttime = millis();					// store the start time
	starttime_SDS = millis();
}

/*****************************************************************
/* And action                                                    *
/*****************************************************************/
void loop() {
	String data = "";

	String data_4_dusti = "";
	String data_sample_times = "";

	String result_PPD = "";
	String result_SDS = "";
	String result_DHT = "";
	String result_BMP = "";
	String result_GPS = "";
	String signal_strength = "";
	
	unsigned long sum_send_time = 0;
	unsigned long start_send;

	send_failed = false;

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

	if (ppd_read) {
		debug_out("Call sensorPPD",DEBUG_MAX_INFO,1);
		result_PPD = sensorPPD();
	}

	if (sds_read && (((act_milli-starttime_SDS) > sampletime_SDS_ms) || ((act_milli-starttime) > sending_intervall_ms))) {
		debug_out("Call sensorSDS",DEBUG_MAX_INFO,1);
		result_SDS = sensorSDS();
		starttime_SDS = act_milli;
	}

	if (dht_read && ((act_milli-starttime) > sending_intervall_ms)) {
		debug_out("Call sensorDHT",DEBUG_MAX_INFO,1);
		result_DHT = sensorDHT();			// getting temperature and humidity (optional)
	}

	if (bmp_read && ((act_milli-starttime) > sending_intervall_ms)) {
		debug_out("Call sensorBMP",DEBUG_MAX_INFO,1);
		result_BMP = sensorBMP();			// getting temperature and humidity (optional)
	}

	if (gps_read && (((act_milli-starttime_GPS) > sampletime_GPS_ms) || ((act_milli-starttime) > sending_intervall_ms))) {
		debug_out("Call sensorGPS",DEBUG_MAX_INFO,1);
		result_GPS = sensorGPS();			// getting GPS coordinates
		starttime_GPS = act_milli;
	}

	if ((act_milli-starttime) > sending_intervall_ms) {
		debug_out("Creating data string:",DEBUG_MIN_INFO,1);
		data = data_first_part;
		data_sample_times  = Value2Json("samples",String(long(sample_count)));
		data_sample_times += Value2Json("min_micro",String(long(min_micro)));
		data_sample_times += Value2Json("max_micro",String(long(max_micro)));

		signal_strength = String(WiFi.RSSI())+" dBm";
		debug_out("WLAN signal strength: "+signal_strength,DEBUG_MIN_INFO,1);
		debug_out("------",DEBUG_MIN_INFO,1);

		if (ppd_read) {
			data += result_PPD;
			data_4_dusti  = data_first_part + result_PPD;
			data_4_dusti += data_sample_times;
			data_4_dusti.remove(data_4_dusti.length()-1);
			data_4_dusti += "]}";
			if (send2dusti) {
				debug_out(txt_sending_to_luftdaten+"(PPD): ",DEBUG_MIN_INFO,1);
				start_send = micros();
				if (result_PPD != "") {
					sendData(data_4_dusti,PPD_API_PIN,host_dusti,httpPort_dusti,url_dusti);
//					sendData(data_4_dusti,PPD_API_PIN,host_api_madavi,httpPort_api_madavi,url_api_madavi);
				} else {
					debug_out(txt_no_data_sent,DEBUG_MIN_INFO,1);
				}
				sum_send_time += micros() - start_send;
			}
		}
		if (sds_read) {
			data += result_SDS;
			data_4_dusti  = data_first_part + result_SDS;
			data_4_dusti += data_sample_times;
			data_4_dusti.remove(data_4_dusti.length()-1);
			data_4_dusti.replace("SDS_","");
			data_4_dusti += "]}";
			if (send2dusti) {
				debug_out(txt_sending_to_luftdaten+"(SDS): ",DEBUG_MIN_INFO,1);
				start_send = micros();
				if (result_SDS != "") {
					sendData(data_4_dusti,SDS_API_PIN,host_dusti,httpPort_dusti,url_dusti);
//					sendData(data_4_dusti,SDS_API_PIN,host_api_madavi,httpPort_api_madavi,url_api_madavi);
				} else {
					debug_out(txt_no_data_sent,DEBUG_MIN_INFO,1);
				}
				sum_send_time += micros() - start_send;
			}
		}
		if (dht_read) {
			data += result_DHT;
			data_4_dusti  = data_first_part + result_DHT;
			data_4_dusti += data_sample_times;
			data_4_dusti.remove(data_4_dusti.length()-1);
			data_4_dusti += "]}";
			if (send2dusti) {
				debug_out(txt_sending_to_luftdaten+"(DHT): ",DEBUG_MIN_INFO,1);
				start_send = micros();
				if (result_DHT != "") {
					sendData(data_4_dusti,DHT_API_PIN,host_dusti,httpPort_dusti,url_dusti);
//					sendData(data_4_dusti,DHT_API_PIN,host_api_madavi,httpPort_api_madavi,url_api_madavi);
				} else {
					debug_out(txt_no_data_sent,DEBUG_MIN_INFO,1);
				}
				sum_send_time += micros() - start_send;
			}
		}
		if (bmp_read) {
			data += result_BMP;
			data_4_dusti  = data_first_part + result_BMP;
			data_4_dusti += data_sample_times;
			data_4_dusti.remove(data_4_dusti.length()-1);
			data_4_dusti.replace("BMP_","");
			data_4_dusti += "]}";
			if (send2dusti) {
				debug_out(txt_sending_to_luftdaten+"(BMP): ",DEBUG_MIN_INFO,1);
				start_send = micros();
				if (result_BMP != "") {
					sendData(data_4_dusti,BMP_API_PIN,host_dusti,httpPort_dusti,url_dusti);
//					sendData(data_4_dusti,BMP_API_PIN,host_api_madavi,httpPort_api_madavi,url_api_madavi);
				} else {
					debug_out(txt_no_data_sent,DEBUG_MIN_INFO,1);
				}
				sum_send_time += micros() - start_send;
			}
		}
		if (gps_read) {
			data += result_GPS;
			data_4_dusti  = data_first_part + result_GPS;
			data_4_dusti += data_sample_times;
			data_4_dusti.remove(data_4_dusti.length()-1);
			data_4_dusti.replace("GPS_","");
			data_4_dusti += "]}";
			if (send2dusti) {
				debug_out(txt_sending_to_luftdaten+"(GPS): ",DEBUG_MIN_INFO,1);
				start_send = micros();
				if (result_GPS != "") {
					sendData(data_4_dusti,GPS_API_PIN,host_dusti,httpPort_dusti,url_dusti);
//					sendData(data_4_dusti,GPS_API_PIN,host_api_madavi,httpPort_api_madavi,url_api_madavi);
				} else {
					debug_out(txt_no_data_sent,DEBUG_MIN_INFO,1);
				}
				sum_send_time += micros() - start_send;
			}
		}

		data_sample_times += Value2Json("signal",signal_strength);
		data += data_sample_times;

		if ((result_PPD.length() > 0) || (result_DHT.length() > 0) || (result_SDS.length() > 0)) {
			data.remove(data.length()-1);
		}
		data += "]}";

		//sending to api(s)

		if ((act_milli-last_update_attempt) > pause_between_update_attempts) {
			will_check_for_update = true;
		}

		if (has_display) {
			display_values(data);
		}

		if (send2madavi) {
			debug_out(txt_sending_to+"madavi.de: ",DEBUG_MIN_INFO,1);
			start_send = micros();
			sendData(data,0,host_madavi,httpPort_madavi,url_madavi);
			sum_send_time += micros() - start_send;
		}

		if (send2custom) {
			debug_out(txt_sending_to+"custom api: ",DEBUG_MIN_INFO,1);
			start_send = micros();
			sendData(data,0,host_custom,httpPort_custom,url_custom);
			sum_send_time += micros() - start_send;
		}

		if (send2influxdb) {
			debug_out(txt_sending_to+"custom influx db: ",DEBUG_MIN_INFO,1);
			start_send = micros();
			send_influxDB(data,0,host_influxdb,httpPort_influxdb,url_influxdb);
			sum_send_time += micros() - start_send;
		}

		if (send2mqtt) {
			debug_out(txt_sending_to+"mqtt: ",DEBUG_MIN_INFO,1);
			start_send = micros();
			sendmqtt(data,host_mqtt,mqtt_port);
			sum_send_time += micros() - start_send;
		}

		if (send2lora) {
			debug_out(txt_sending_to+"LoRa gateway: ",DEBUG_MIN_INFO,1);
			send_lora(data);
		}

		if (send2csv) {
			debug_out("## Sending as csv: ",DEBUG_MIN_INFO,1);
			send_csv(data);
		}

		if ((act_milli-last_update_attempt) > pause_between_update_attempts) {
			autoUpdate();
		}

		if (! send_failed) sending_time = (4 * sending_time + sum_send_time) / 5;
		debug_out("Time for sending data: "+String(sending_time),DEBUG_MIN_INFO,1);
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

