#include <Arduino.h>

/*****************************************************************
/* OK LAB Particulate Matter Sensor                              *
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
/*                                                               *
/* Alternative                                                   *
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
/* Extensions connected via I2C:                                 *
/* BMP180, BME280, OLED Display with SSD1309                     *
/*                                                               *
/* Wiring Instruction                                            *
/* (see labels on display or sensor board)                       *
/*      VCC       ->     Pin 3V3                                 *
/*      GND       ->     Pin GND                                 *
/*      SCL       ->     Pin D4 (GPIO2)                          *
/*      SDA       ->     Pin D3 (GPIO0)                          *
/*                                                               *
/*****************************************************************/
// increment on change
#define SOFTWARE_VERSION "NRZ-2016-052"

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
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ESP8266httpUpdate.h>
#include <WiFiClientSecure.h>
#include <SoftwareSerial.h>
#include <SSD1306.h>
#include <base64.h>
#endif
#if defined(ARDUINO_SAMD_ZERO)
#include <RHReliableDatagram.h>
#include <RH_RF69.h>
#include <SPI.h>
#endif
#include <ArduinoJson.h>
#include <Wire.h>
#include <DHT.h>
#include <Adafruit_BMP085.h>
#include <Adafruit_BME280.h>
#include <TinyGPS++.h>
#include <Ticker.h>

#include "ext_def.h"
#include "html-content.h"

/*****************************************************************
/* Variables with defaults                                       *
/*****************************************************************/
char wlanssid[65] = "Freifunk";
char wlanpwd[65] = "";

char www_username[65] = "admin";
char www_password[65] = "feinstaub";
bool www_basicauth_enabled = 0;

char version_from_local_config[30] = "";

bool dht_read = 1;
bool ppd_read = 0;
bool sds_read = 1;
bool bmp_read = 0;
bool bme280_read = 0;
bool gps_read = 0;
bool send2dusti = 1;
bool send2madavi = 1;
bool send2custom = 0;
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

char host_influxdb[100] = "api.luftdaten.info";
char url_influxdb[100] = "/write?db=luftdaten";
int httpPort_influxdb = 8086;
char user_influxdb[100] = "luftdaten";
char pwd_influxdb[100] = "info";
String basic_auth_influxdb = "";

char host_custom[100] = "192.168.234.1";
char url_custom[100] = "/data.php";
int httpPort_custom = 80;
char user_custom[100] = "";
char pwd_custom[100] = "";
String basic_auth_custom = "";

const char* update_host = "www.madavi.de";
const char* update_url = "/sensor/update/firmware.php";
const int update_port = 80;

#if defined(ESP8266)
ESP8266WebServer server(80);
int TimeZone=1;
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
SoftwareSerial serialGPS(GPS_PIN_RX, GPS_PIN_TX, false, 128);
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
/* BME280 declaration                                            *
/*****************************************************************/
Adafruit_BME280 bme280;

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

bool send_now = false;
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
// const unsigned long reading_time_SDS_ms = 60000;
bool is_SDS_running = true;

const unsigned long display_update_interval = 5000;
unsigned long display_last_update;
float sds_display_values_10[5];
float sds_display_values_25[5];
unsigned int sds_display_value_pos = 0;

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

String last_result_PPD = "";
String last_result_SDS = "";
String last_result_DHT = "";
String last_result_BMP = "";
String last_result_BME280 = "";
String last_result_GPS = "";
String last_value_PPD_P1 = "";
String last_value_PPD_P2 = "";
String last_value_SDS_P1 = "";
String last_value_SDS_P2 = "";
String last_value_DHT_T = "";
String last_value_DHT_H = "";
String last_value_BMP_T = "";
String last_value_BMP_P = ""; 
String last_value_BME280_T = "";
String last_value_BME280_H = ""; 
String last_value_BME280_P = "";
String last_data_string = "";

String last_gps_lat;
String last_gps_lng;
String last_gps_alt;
String last_gps_date;
String last_gps_time;

String esp_chipid;

String server_name;

long last_page_load = millis();

bool config_needs_write = false;

bool first_csv_line = 1;

String data_first_part = "{\"software_version\": \"" + String(SOFTWARE_VERSION) + "\"FEATHERCHIPID, \"sensordatavalues\":[";

#define LEAP_YEAR(Y)     ( ((1970+Y)>0) && !((1970+Y)%4) && ( ((1970+Y)%100) || !((1970+Y)%400) ) )
static uint8_t monthDays[]={31,28,31,30,31,30,31,31,30,31,30,31}; // API starts months from 1, this array starts from 0

static unsigned long last_loop;

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
		debug_out(F("output debug text to display..."),DEBUG_MIN_INFO,1);
		debug_out(text,DEBUG_MAX_INFO,1);
		display.resetDisplay();
		display.clear();
		display.displayOn();
		display.setFont(Monospaced_plain_9);
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
String Value2Json(const String& type, const String& value) {
	String s = F("{\"value_type\":\"{t}\",\"value\":\"{v}\"},");
	s.replace("{t}",type);s.replace("{v}",value);
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
/* start SDS011 sensor                                           *
/*****************************************************************/
void start_SDS() {
	const uint8_t start_SDS_cmd[] = {0xAA, 0xB4, 0x06, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x06, 0xAB};
	serialSDS.write(start_SDS_cmd,sizeof(start_SDS_cmd)); is_SDS_running = true;
}

/*****************************************************************
/* stop SDS011 sensor                                            *
/*****************************************************************/
void stop_SDS() {
	const uint8_t stop_SDS_cmd[] = {0xAA, 0xB4, 0x06, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x05, 0xAB};
	serialSDS.write(stop_SDS_cmd,sizeof(stop_SDS_cmd)); is_SDS_running = false;
}

/*****************************************************************
/* read SDS011 sensor values                                     *
/*****************************************************************/
String SDS_version_date() {
	const uint8_t version_SDS_cmd[] = {0xAA, 0xB4, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x05, 0xAB};
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

	debug_out(F("Start reading SDS011 version date"),DEBUG_MED_INFO,1);

	start_SDS();

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
			debug_out(F("SDS version date : "),DEBUG_MIN_INFO,0);
			debug_out(version_date,DEBUG_MIN_INFO,1);
			debug_out(F("SDS device ID:     "),DEBUG_MIN_INFO,0);
			debug_out(device_id,DEBUG_MIN_INFO,1);
			len = 0; checksum_ok = 0; version_date = ""; device_id = ""; checksum_is = 0;
		}
		yield();
	}

	debug_out(F("End reading SDS011 version date"),DEBUG_MED_INFO,1);

	return s;
}

/*****************************************************************
/* copy config from ext_def                                      *
/*****************************************************************/
void copyExtDef() {
	if (WLANSSID != NULL) { strcpy(wlanssid,WLANSSID); }
	if (WLANPWD  != NULL) { strcpy(wlanpwd,WLANPWD); }
	if (WWW_USERNAME != NULL) { strcpy(www_username,WWW_USERNAME); }
	if (WWW_PASSWORD  != NULL) { strcpy(www_password,WWW_PASSWORD); }
	if (WWW_BASICAUTH_ENABLED != www_basicauth_enabled) { www_basicauth_enabled = WWW_BASICAUTH_ENABLED; }
	if (DHT_READ != dht_read) { dht_read = DHT_READ; }
	if (PPD_READ != ppd_read) { ppd_read = PPD_READ; }
	if (SDS_READ != sds_read) { sds_read = SDS_READ; }
	if (BMP_READ != bmp_read) { bmp_read = BMP_READ; }
	if (BME280_READ != bme280_read) { bme280_read = BME280_READ; }
	if (GPS_READ != gps_read) { gps_read = GPS_READ; }
	if (SEND2DUSTI != send2dusti) { send2dusti = SEND2DUSTI; }
	if (SEND2MADAVI != send2madavi) { send2madavi = SEND2MADAVI; }
	if (SEND2LORA != send2lora) { send2lora = SEND2LORA; }
	if (SEND2CSV != send2csv) { send2csv = SEND2CSV; }
	if (AUTO_UPDATE != auto_update) { auto_update = AUTO_UPDATE; }
	if (HAS_DISPLAY != has_display) { has_display = HAS_DISPLAY; }

	if (DEBUG != debug) { debug = DEBUG; }

	if (SEND2CUSTOM != send2custom) { send2custom = SEND2CUSTOM; }
	if (HOST_CUSTOM != NULL) { strcpy(host_custom,HOST_CUSTOM); }
	if (URL_CUSTOM != NULL) { strcpy(url_custom,URL_CUSTOM); }
	if (HTTPPORT_CUSTOM != httpPort_custom) { httpPort_custom = HTTPPORT_CUSTOM; }
	if (USER_CUSTOM != NULL) { strcpy(user_custom,USER_CUSTOM); }
	if (PWD_CUSTOM != NULL) { strcpy(pwd_custom,PWD_CUSTOM); }

	if (SEND2INFLUXDB != send2influxdb) { send2influxdb = SEND2INFLUXDB; }
	if (HOST_INFLUXDB != NULL) { strcpy(host_influxdb,HOST_INFLUXDB); }
	if (URL_INFLUXDB != NULL) { strcpy(url_influxdb,URL_INFLUXDB); }
	if (HTTPPORT_INFLUXDB != httpPort_influxdb) { httpPort_influxdb = HTTPPORT_INFLUXDB; }
	if (USER_INFLUXDB != NULL) {strcpy(user_influxdb,USER_INFLUXDB); }
	if (PWD_INFLUXDB != NULL) {strcpy(pwd_influxdb,PWD_INFLUXDB); }
}

/*****************************************************************
/* read config from spiffs                                       *
/*****************************************************************/
void readConfig() {
#if defined(ESP8266)
	String json_string = "";
	debug_out(F("mounting FS..."),DEBUG_MIN_INFO,1);

	if (SPIFFS.begin()) {
		debug_out(F("mounted file system..."),DEBUG_MIN_INFO,1);
		if (SPIFFS.exists("/config.json")) {
			//file exists, reading and loading
			debug_out(F("reading config file..."),DEBUG_MIN_INFO,1);
			File configFile = SPIFFS.open("/config.json", "r");
			if (configFile) {
				debug_out(F("opened config file..."),DEBUG_MIN_INFO,1);
				size_t size = configFile.size();
				// Allocate a buffer to store contents of the file.
				std::unique_ptr<char[]> buf(new char[size]);

				configFile.readBytes(buf.get(), size);
				StaticJsonBuffer<2000> jsonBuffer;
				JsonObject& json = jsonBuffer.parseObject(buf.get());
				json.printTo(json_string);
				debug_out(F("File content: "),DEBUG_MAX_INFO,0);
				debug_out(String(buf.get()),DEBUG_MAX_INFO,1);
				debug_out(F("JSON Buffer content: "),DEBUG_MAX_INFO,0);
				debug_out(json_string,DEBUG_MAX_INFO,1);
				if (json.success()) {
					debug_out(F("parsed json..."),DEBUG_MIN_INFO,1);
					if (json.containsKey("SOFTWARE_VERSION")) strcpy(version_from_local_config, json["SOFTWARE_VERSION"]);
					if (json.containsKey("wlanssid")) strcpy(wlanssid, json["wlanssid"]);
					if (json.containsKey("wlanpwd")) strcpy(wlanpwd, json["wlanpwd"]);
					if (json.containsKey("www_username")) strcpy(www_username, json["www_username"]);
					if (json.containsKey("www_password")) strcpy(www_password, json["www_password"]);
					if (json.containsKey("www_basicauth_enabled")) www_basicauth_enabled = json["www_basicauth_enabled"];
					if (json.containsKey("dht_read")) dht_read = json["dht_read"];
					if (json.containsKey("ppd_read")) ppd_read = json["ppd_read"];
					if (json.containsKey("sds_read")) sds_read = json["sds_read"];
					if (json.containsKey("bmp_read")) bmp_read = json["bmp_read"];
					if (json.containsKey("bme280_read")) bme280_read = json["bme280_read"];
					if (json.containsKey("gps_read")) gps_read = json["gps_read"];
					if (json.containsKey("send2dusti")) send2dusti = json["send2dusti"];
					if (json.containsKey("send2madavi")) send2madavi = json["send2madavi"];
					if (json.containsKey("send2lora")) send2lora = json["send2lora"];
					if (json.containsKey("send2csv")) send2csv = json["send2csv"];
					if (json.containsKey("auto_update")) auto_update = json["auto_update"];
					if (json.containsKey("has_display")) has_display = json["has_display"];
					if (json.containsKey("debug")) debug = json["debug"];
					if (json.containsKey("send2custom")) send2custom = json["send2custom"];
					if (json.containsKey("host_custom")) strcpy(host_custom, json["host_custom"]);
					if (json.containsKey("url_custom")) strcpy(url_custom, json["url_custom"]);
					if (json.containsKey("httpPort_custom")) httpPort_custom = json["httpPort_custom"];
					if (json.containsKey("user_custom")) strcpy(user_custom, json["user_custom"]);
					if (json.containsKey("pwd_custom")) strcpy(pwd_custom, json["pwd_custom"]);
					if (json.containsKey("send2influxdb")) send2influxdb = json["send2influxdb"];
					if (json.containsKey("host_influxdb")) strcpy(host_influxdb, json["host_influxdb"]);
					if (json.containsKey("url_influxdb")) strcpy(url_influxdb, json["url_influxdb"]);
					if (json.containsKey("httpPort_influxdb")) httpPort_influxdb = json["httpPort_influxdb"];
					if (json.containsKey("user_influxdb")) strcpy(user_influxdb, json["user_influxdb"]);
					if (json.containsKey("pwd_influxdb")) strcpy(pwd_influxdb, json["pwd_influxdb"]);
				} else {
					debug_out(F("failed to load json config"),DEBUG_ERROR,1);
				}
			}
		} else {
			debug_out(F("config file not found ..."),DEBUG_ERROR,1);
		}
	} else {
		debug_out(F("failed to mount FS"),DEBUG_ERROR,1);
	}
#endif
}

/*****************************************************************
/* write config to spiffs                                        *
/*****************************************************************/
void writeConfig() {
#if defined(ESP8266)
	String json_string = "";
	debug_out(F("saving config..."),DEBUG_MIN_INFO,1);
	StaticJsonBuffer<2000> jsonBuffer;
	JsonObject& json = jsonBuffer.createObject();
	json["SOFTWARE_VERSION"] = SOFTWARE_VERSION;
	json["wlanssid"] = wlanssid;
	json["wlanpwd"] = wlanpwd;
	json["www_username"] = www_username;
	json["www_password"] = www_password;
	json["www_basicauth_enabled"] = www_basicauth_enabled;
	json["dht_read"] = dht_read;
	json["ppd_read"] = ppd_read;
	json["sds_read"] = sds_read;
	json["bmp_read"] = bmp_read;
	json["bme280_read"] = bme280_read;
	json["gps_read"] = gps_read;
	json["send2dusti"] = send2dusti;
	json["send2madavi"] = send2madavi;
	json["send2lora"] = send2lora;
	json["send2csv"] = send2csv;
	json["auto_update"] = auto_update;
	json["has_display"] = has_display;
	json["debug"] = debug;
	json["send2custom"] = send2custom;
	json["host_custom"] = host_custom;
	json["url_custom"] = url_custom;
	json["httpPort_custom"] = httpPort_custom;
	json["user_custom"] = user_custom;
	json["pwd_custom"] = pwd_custom;

	json["send2influxdb"] = send2influxdb;
	json["host_influxdb"] = host_influxdb;
	json["url_influxdb"] = url_influxdb;
	json["httpPort_influxdb"] = httpPort_influxdb;
	json["user_influxdb"] = user_influxdb;
	json["pwd_influxdb"] = pwd_influxdb;

	File configFile = SPIFFS.open("/config.json", "w");
	if (!configFile) {
		debug_out(F("failed to open config file for writing"),DEBUG_ERROR,1);
	}

	json.printTo(json_string);
	debug_out(F("Config length: "),DEBUG_MAX_INFO,0);
	debug_out(String(json.measureLength()),DEBUG_MAX_INFO,1);
	debug_out(F("Config written: "),DEBUG_MIN_INFO,0);
	debug_out(json_string,DEBUG_MIN_INFO,1);
	json.printTo(configFile);
	configFile.close();
	config_needs_write = false;
	//end save
#endif
}

/*****************************************************************
/* Base64 encode user:password                                   *
/*****************************************************************/
void create_basic_auth_strings() {
	basic_auth_custom = base64::encode(String(user_custom)+":"+String(pwd_custom));
	basic_auth_influxdb = base64::encode(String(user_influxdb)+":"+String(pwd_influxdb));
}

/*****************************************************************
/* html helper functions                                         *
/*****************************************************************/
String form_input(const String& name, const String& info, const String& value, const int length) {
	String s = F("<tr><td>{i} </td><td style='width:90%;'><input type='text' name='{n}' id='{n}' placeholder='{i}' value='{v}' maxlength='{l}'/></td></tr>");
	s.replace("{i}",info);s.replace("{n}",name);s.replace("{v}",value);s.replace("{l}",String(length));
	return s;
}

String form_password(const String& name, const String& info, const String& value, const int length) {
	String s = F("<tr><td>{i} </td><td style='width:90%;'><input type='password' name='{n}' id='{n}' placeholder='{i}' value='{v}' maxlength='{l}'/></td></tr>");
	s.replace("{i}",info);s.replace("{n}",name);s.replace("{v}",value);s.replace("{l}",String(length));
	return s;
}

String form_checkbox(const String& name, const String& info, const bool checked) {
	String s = F("<label for='{n}'><input type='checkbox' name='{n}' value='1' id='{n}' {c}/> {i}</label><br/>");
	if (checked) {s.replace("{c}",F(" checked='checked'"));} else {s.replace("{c}","");};
	s.replace("{i}",info);s.replace("{n}",name);
	return s;
}

String table_row_from_value(const String& name, const String& value) {
	String s = F("<tr><td>{n}</td><td style='width:80%;'>{v}</td></tr>");
	s.replace("{n}",name);s.replace("{v}",value);
	return s;
}

String wlan_ssid_to_table_row(const String& ssid, const String& encryption, const long rssi) {
	long rssi_temp = rssi;
	if (rssi_temp > -50) {rssi_temp = -50; }
	if (rssi_temp < -100) {rssi_temp = -100; }
	int quality = (rssi_temp+100)*2;
	String s = F("<tr><td><a href='#wlanpwd' onclick='setSSID(this)' style='background:none;color:blue;padding:5px;display:inline;'>{n}</a>&nbsp;{e}</a></td><td style='width:80%;vertical-align:middle;'>{v}%</td></tr>");
	s.replace("{n}",ssid);s.replace("{e}",encryption);s.replace("{v}",String(quality));
	return s;
}

/*****************************************************************
/* Webserver request auth: prompt for BasicAuth                              
 *  
 * -Provide BasicAuth for all page contexts except /values and images
/*****************************************************************/
void webserver_request_auth() {
	debug_out(F("validate request auth..."),DEBUG_MIN_INFO,1);
	if (www_basicauth_enabled) {
		if (!server.authenticate(www_username, www_password))
			return server.requestAuthentication();  
	}
}

/*****************************************************************
/* Webserver root: show all options                              *
/*****************************************************************/
void webserver_root() {
	webserver_request_auth();
 
	String page_content = "";
	last_page_load = millis();
	debug_out(F("output root page..."),DEBUG_MIN_INFO,1);
	page_content = FPSTR(WEB_PAGE_HEADER);
	page_content.replace("{t}",F("Übersicht"));
	page_content.replace("{id}",esp_chipid);
	page_content.replace("{fw}",SOFTWARE_VERSION);
	page_content += FPSTR(WEB_ROOT_PAGE_CONTENT);
	page_content += FPSTR(WEB_PAGE_FOOTER);
	server.send(200,FPSTR(TXT_CONTENT_TYPE_TEXT_HTML),page_content);
}

/*****************************************************************
/* Webserver root: show all options                              *
/*****************************************************************/
void webserver_config() {
	webserver_request_auth();
	
	String page_content = "";
	last_page_load = millis();

	debug_out(F("output config page ..."),DEBUG_MIN_INFO,1);
	page_content += FPSTR(WEB_PAGE_HEADER);
	page_content.replace("{t}",F("Konfiguration"));
	page_content.replace("{id}",esp_chipid);
	page_content.replace("{fw}",SOFTWARE_VERSION);
	page_content += FPSTR(WEB_CONFIG_SCRIPT);
	if ((!server.hasArg("submit")) || (server.arg("submit") != "Save")) {
		page_content += F("<form method='POST' action='/config' style='width: 100%;'>");
		page_content += F("<b>WLAN Daten</b><br/>");
		if (WiFi.status() != WL_CONNECTED) {  // scan for wlan ssids
			WiFi.disconnect();
			debug_out(F("scan for wifi networks..."),DEBUG_MIN_INFO,1);
			int n = WiFi.scanNetworks();
			debug_out(F("wifi networks found: "),DEBUG_MIN_INFO,0);
			debug_out(String(n),DEBUG_MIN_INFO,1);
			if (n == 0) {
				page_content += F("<br/>Keine Netzwerke gefunden<br/>");
			} else {
				page_content += F("<br/>Netzwerke gefunden: ");
				page_content += String(n);
				page_content += F("<br/>");
				int indices[n];
				for (int i = 0; i < n; i++) { indices[i] = i; }
				for (int i = 0; i < n; i++) {
					for (int j = i + 1; j < n; j++) {
						if (WiFi.RSSI(indices[j]) > WiFi.RSSI(indices[i])) {
							std::swap(indices[i], indices[j]);
						}
					}
				}
				String cssid;
				for (int i = 0; i < n; i++) {
					if (indices[i] == -1) continue;
						cssid = WiFi.SSID(indices[i]);
						for (int j = i + 1; j < n; j++) {
							if (cssid == WiFi.SSID(indices[j])) {
							indices[j] = -1; // set dup aps to index -1
						}
					}
				}
				page_content += F("<br/><table>");
				for (int i = 0; i < n; ++i) {
					if (indices[i] == -1) continue;
					// Print SSID and RSSI for each network found
					page_content += wlan_ssid_to_table_row(WiFi.SSID(indices[i]),((WiFi.encryptionType(indices[i]) == ENC_TYPE_NONE)?" ":"*"),WiFi.RSSI(indices[i]));
				}
				page_content += F("</table><br/><br/>");
			}
		}
		page_content += F("<table>");
		page_content += form_input(F("wlanssid"),F("WLAN"),wlanssid,64);
		page_content += form_password(F("wlanpwd"),F("Passwort"),wlanpwd,64);
		page_content += F("</table><br/><input type='submit' name='submit' value='Speichern'/><br/><br/><b>BasicAuth</b><br/>");
		page_content += F("<table>");
		page_content += form_input(F("www_username"),F("User"),www_username,64);
		page_content += form_password(F("www_password"),F("Passwort"),www_password,64);
		page_content += form_checkbox(F("www_basicauth_enabled"),F("BasicAuth aktivieren"),www_basicauth_enabled);
		page_content += F("</table><br/><input type='submit' name='submit' value='Speichern'/><br/><br/><b>APIs</b><br/>");
		page_content += form_checkbox(F("send2dusti"),F("API Luftdaten.info"),send2dusti);
		page_content += form_checkbox(F("send2madavi"),F("API Madavi.de"),send2madavi);
		page_content += F("<br/><b>Sensoren</b><br/>");
		page_content += form_checkbox(F("sds_read"),F("SDS011 (Feinstaub)"),sds_read);
		page_content += form_checkbox(F("dht_read"),F("DHT22 (Temp.,Luftfeuchte)"),dht_read);
		page_content += form_checkbox(F("ppd_read"),F("PPD42NS"),ppd_read);
		page_content += form_checkbox(F("bmp_read"),F("BMP180"),bmp_read);
		page_content += form_checkbox(F("bme280_read"),F("BME280"),bme280_read);
		page_content += form_checkbox(F("gps_read"),F("GPS (NEO 6M)"),gps_read);
		page_content += F("<br/><b>Weitere Einstellungen</b><br/>");
		page_content += form_checkbox(F("auto_update"),F("Auto Update"),auto_update);
		page_content += form_checkbox(F("has_display"),F("Display"),has_display);
		page_content += F("<table>");
		page_content += form_input(F("debug"),F("Debug&nbsp;Level"),String(debug),5);
		page_content += F("</table><br/><b>Weitere APIs</b><br/><br/>");
		page_content += form_checkbox(F("send2custom"),F("An eigene API senden"),send2custom);
		page_content += F("<table>");
		page_content += form_input(F("host_custom"),F("Server: "),host_custom,50);
		page_content += form_input(F("url_custom"),F("Pfad: "),url_custom,50);
		page_content += form_input(F("httpPort_custom"),F("Port: "),String(httpPort_custom),30);
		page_content += form_input(F("user_custom"),F("Benutzer: "),user_custom,50);
		page_content += form_input(F("pwd_custom"),F("Passwort: "),pwd_custom,50);
		page_content += F("</table><br/>");
		page_content += form_checkbox(F("send2influxdb"),F("Senden an InfluxDB"),send2influxdb);
		page_content += F("<table>");
		page_content += form_input(F("host_influxdb"),F("Server: "),host_influxdb,50);
		page_content += form_input(F("url_influxdb"),F("Pfad: "),url_influxdb,50);
		page_content += form_input(F("httpPort_influxdb"),F("Port: "),String(httpPort_influxdb),30);
		page_content += form_input(F("user_influxdb"),F("Benutzer: "),user_influxdb,50);
		page_content += form_input(F("pwd_influxdb"),F("Passwort: "),pwd_influxdb,50);
		page_content += F("</table><br/>");
		page_content += F("<br/><input type='submit' name='submit' value='Speichern'/></form>");
	} else {
		if (server.hasArg("wlanssid") && server.arg("wlanssid") != "") {
			server.arg("wlanssid").toCharArray(wlanssid,65);
			if (server.hasArg("wlanpwd") && server.arg("wlanpwd") != "") {
				server.arg("wlanpwd").toCharArray(wlanpwd,65);
			}
		}
		if (server.hasArg("www_username") && server.arg("www_username") != "") { server.arg("www_username").toCharArray(www_username,65); }
		if (server.hasArg("www_password") && server.arg("www_password") != "") { server.arg("www_password").toCharArray(www_password,65); }
		if (server.hasArg("www_basicauth_enabled") && server.arg("www_basicauth_enabled") == "1") { www_basicauth_enabled = 1; } else { www_basicauth_enabled = 0; }
		if (server.hasArg("send2dusti") && server.arg("send2dusti") == "1") { send2dusti = 1; } else { send2dusti = 0; }
		if (server.hasArg("send2madavi") && server.arg("send2madavi") == "1") { send2madavi = 1; } else { send2madavi = 0; }
		if (server.hasArg("dht_read") && server.arg("dht_read") == "1") { dht_read = 1; } else { dht_read = 0; }
		if (server.hasArg("sds_read") && server.arg("sds_read") == "1") { sds_read = 1; } else { sds_read = 0; }
		if (server.hasArg("ppd_read") && server.arg("ppd_read") == "1") { ppd_read = 1; } else { ppd_read = 0; }
		if (server.hasArg("bmp_read") && server.arg("bmp_read") == "1") { bmp_read = 1; } else { bmp_read = 0; }
		if (server.hasArg("bme280_read") && server.arg("bme280_read") == "1") { bme280_read = 1; } else { bme280_read = 0; }
		if (server.hasArg("gps_read") && server.arg("gps_read") == "1") { gps_read = 1; } else { gps_read = 0; }
		if (server.hasArg("auto_update") && server.arg("auto_update") == "1") { auto_update = 1; } else { auto_update = 0; }
		if (server.hasArg("has_display") && server.arg("has_display") == "1") { has_display = 1; } else { has_display = 0; }
		if (server.hasArg("debug")) { debug = server.arg("debug").toInt(); } else { debug = 0; }

		if (server.hasArg("send2custom") && server.arg("send2custom") == "1") { send2custom = 1; } else { send2custom = 0; }
		if (server.hasArg("host_custom") && server.arg("host_custom") != "") { server.arg("host_custom").toCharArray(host_custom,100); }
		if (server.hasArg("url_custom") && server.arg("url_custom") != "") { server.arg("url_custom").toCharArray(url_custom,100); }
		if (server.hasArg("httpPort_custom") && server.arg("httpPort_custom").toInt() != 0) { httpPort_custom = server.arg("httpPort_custom").toInt();}
		if (server.hasArg("user_custom") && server.arg("user_custom") != "") { server.arg("user_custom").toCharArray(user_custom,100); }
		if (server.hasArg("pwd_custom") && server.arg("pwd_custom") != "") { server.arg("pwd_custom").toCharArray(pwd_custom,100); }

		if (server.hasArg("send2influxdb") && server.arg("send2influxdb") == "1") { send2influxdb = 1; } else { send2influxdb = 0; }
		if (server.hasArg("host_influxdb") && server.arg("host_influxdb") != "") { server.arg("host_influxdb").toCharArray(host_influxdb,100); }
		if (server.hasArg("url_influxdb") && server.arg("url_influxdb") != "") { server.arg("url_influxdb").toCharArray(url_influxdb,100); }
		if (server.hasArg("httpPort_influxdb") && server.arg("httpPort_influxdb").toInt() != 0) { httpPort_influxdb = server.arg("httpPort_influxdb").toInt();}
		if (server.hasArg("user_influxdb") && server.arg("user_influxdb") != "") { server.arg("user_influxdb").toCharArray(user_influxdb,100); }
		if (server.hasArg("pwd_influxdb") && server.arg("pwd_influxdb") != "") { server.arg("pwd_influxdb").toCharArray(pwd_influxdb,100); }

		config_needs_write = true;

		page_content += F("<br/>Senden an Luftdaten.info: "); page_content += String(send2dusti);
		page_content += F("<br/>Senden an Madavi: "); page_content += String(send2madavi);
		page_content += F("<br/>Lese DHT "); page_content += String(dht_read);
		page_content += F("<br/>Lese SDS "); page_content += String(sds_read);
		page_content += F("<br/>Lese PPD "); page_content += String(ppd_read);
		page_content += F("<br/>Lese BMP180 "); page_content += String(bmp_read);
		page_content += F("<br/>Lese BME280 "); page_content += String(bme280_read);
		page_content += F("<br/>Lese GPS "); page_content += String(gps_read);
		page_content += F("<br/>Auto Update "); page_content += String(auto_update);
		page_content += F("<br/>Display "); page_content += String(has_display);
		page_content += F("<br/>Debug Level "); page_content += String(debug);
		page_content += F("<br/><br/>Eigene API "); page_content += String(send2custom);
		page_content += F("<br/>Server "); page_content += host_custom;
		page_content += F("<br/>Pfad "); page_content += url_custom;
		page_content += F("<br/>Port "); page_content += String(httpPort_custom);
		page_content += F("<br/>Benutzer "); page_content += user_custom;
		page_content += F("<br/>Passwort "); page_content += pwd_custom;
		page_content += F("<br/><br/>InfluxDB "); page_content += String(send2influxdb);
		page_content += F("<br/>Server "); page_content += host_influxdb;
		page_content += F("<br/>Pfad "); page_content += url_influxdb;
		page_content += F("<br/>Port "); page_content += String(httpPort_influxdb);
		page_content += F("<br/>Benutzer "); page_content += user_influxdb;
		page_content += F("<br/>Passwort "); page_content += pwd_influxdb;
		page_content += F("<br/><br/><a href='/reset?confirm=yes'>Gerät neu starten?</a>");

	}
	page_content += FPSTR(WEB_PAGE_FOOTER);
	server.send(200,FPSTR(TXT_CONTENT_TYPE_TEXT_HTML),page_content);
}

/*****************************************************************
/* Webserver root: show latest values                            *
/*****************************************************************/
void webserver_values() {
#if defined(ESP8266)
	String page_content = "";
	last_page_load = millis();
	long signal_strength = WiFi.RSSI();
	long signal_temp = signal_strength;
	if (signal_temp > -50) {signal_temp = -50; }
	if (signal_temp < -100) {signal_temp = -100; }
	int signal_quality = (signal_temp+100)*2;
	int value_count = 0;
	debug_out(F("output values to web page..."),DEBUG_MIN_INFO,1);
	page_content += FPSTR(WEB_PAGE_HEADER);
	page_content.replace("{t}",F("Aktuelle Werte"));
	page_content.replace("{id}",esp_chipid);
	page_content.replace("{fw}",SOFTWARE_VERSION);
	page_content += F("<table>");
	if (ppd_read) {
		page_content += table_row_from_value(F("PPD42NS&nbsp;PM1:"),last_value_PPD_P1+F("&nbsp;Partikel/Liter"));
		page_content += table_row_from_value(F("PPD42NS&nbsp;PM2.5:"),last_value_PPD_P2+F("&nbsp;Partikel/Liter"));
	}
	if (sds_read) {
		page_content += table_row_from_value(F("SDS011&nbsp;PM2.5:"),last_value_SDS_P2+F("&nbsp;µg/m³"));
		page_content += table_row_from_value(F("SDS011&nbsp;PM10:"),last_value_SDS_P1+F("&nbsp;µg/m³"));
	}
	if (dht_read) {
		page_content += table_row_from_value(F("DHT22&nbsp;Temperatur:"),last_value_DHT_T+"&nbsp;°C");
		page_content += table_row_from_value(F("DHT22&nbsp;rel.&nbsp;Luftfeuchte:"),last_value_DHT_H+"&nbsp;%");
	}
	if (bmp_read) {
		page_content += table_row_from_value(F("BMP180&nbsp;Temperatur:"),last_value_BMP_T+"&nbsp;°C");
		page_content += table_row_from_value(F("BMP180&nbsp;Luftdruck:"),last_value_BMP_P+"&nbsp;Pascal");
	}
	if (bme280_read) {
		page_content += table_row_from_value(F("BME280&nbsp;Temperatur:"),last_value_BME280_T+"&nbsp;°C");
		page_content += table_row_from_value(F("BME280&nbsp;rel.&nbsp;Luftfeuchte:"),last_value_BME280_H+"&nbsp;%");
		page_content += table_row_from_value(F("BME280&nbsp;Luftdruck:"),last_value_BME280_P+"&nbsp;Pascal");
	}
	page_content += table_row_from_value(" "," ");
	page_content += table_row_from_value(F("WiFi&nbsp;Signal"),String(signal_strength)+"&nbsp;dBm");
	page_content += table_row_from_value(F("Signal&nbsp;Qualität"),String(signal_quality)+"%");
	page_content += F("</table>");
	page_content += FPSTR(WEB_PAGE_FOOTER);
	server.send(200,FPSTR(TXT_CONTENT_TYPE_TEXT_HTML),page_content);
#endif
}

/*****************************************************************
/* Webserver set debug level                                     *
/*****************************************************************/
void webserver_debug_level() {
	webserver_request_auth();
  
	String page_content = "";
	last_page_load = millis();
	debug_out(F("output change debug level page..."),DEBUG_MIN_INFO,1);
	page_content += FPSTR(WEB_PAGE_HEADER);
	page_content.replace("{t}","Debug level");
	page_content.replace("{id}",esp_chipid);
	page_content.replace("{fw}",SOFTWARE_VERSION);
	if (server.hasArg("level")) {
		switch (server.arg("level").toInt()) {
			case (0): debug=0; page_content += F("<h3>Setze Debug auf none.</h3>");break;
			case (1): debug=1; page_content += F("<h3>Setze Debug auf error.</h3>");break;
			case (2): debug=2; page_content += F("<h3>Setze Debug auf warning.</h3>");break;
			case (3): debug=3; page_content += F("<h3>Setze Debug auf min. info.</h3>");break;
			case (4): debug=4; page_content += F("<h3>Setze Debug auf med. info.</h3>");break;
			case (5): debug=5; page_content += F("<h3>Setze Debug auf max. info.</h3>");break;
		}
	}
	page_content += FPSTR(WEB_PAGE_FOOTER);
	server.send(200, FPSTR(TXT_CONTENT_TYPE_TEXT_HTML), page_content);
}

/*****************************************************************
/* Webserver remove config                                       *
/*****************************************************************/
void webserver_removeConfig() {
	webserver_request_auth();
 
	String page_content = "";
	last_page_load = millis();
	debug_out(F("output remove config page..."),DEBUG_MIN_INFO,1);
	page_content += FPSTR(WEB_PAGE_HEADER);
	page_content.replace("{t}","Config.json löschen");
	page_content.replace("{id}",esp_chipid);
	page_content.replace("{fw}",SOFTWARE_VERSION);
	if (server.hasArg("confirm") && server.arg("confirm") == "yes") {
#if defined(ESP8266)
		if (SPIFFS.exists("/config.json")) {	//file exists
			debug_out(F("removing config.json..."),DEBUG_MIN_INFO,1);
			if (SPIFFS.remove("/config.json")) {
				page_content += F("<h3>Config.json gelöscht.</h3>");
			} else {
				page_content += F("<h3>Config.json konnte nicht gelöscht werden.</h3>");
			}
		} else {
			page_content += F("<h3>Config.json nicht gefunden.</h3>");
		}
#endif
	} else {
		page_content += FPSTR(WEB_REMOVE_CONFIG_CONTENT);
	}
	page_content += FPSTR(WEB_PAGE_FOOTER);
	server.send(200, FPSTR(TXT_CONTENT_TYPE_TEXT_HTML), page_content);
}

/*****************************************************************
/* Webserver reset NodeMCU                                       *
/*****************************************************************/
void webserver_reset() {
	webserver_request_auth();
 
	String page_content = "";
	last_page_load = millis();
	debug_out(F("output reset NodeMCU page..."),DEBUG_MIN_INFO,1);
	page_content += FPSTR(WEB_PAGE_HEADER);
	page_content.replace("{t}","Sensor neu starten");
	page_content.replace("{id}",esp_chipid);
	page_content.replace("{fw}",SOFTWARE_VERSION);
	if (server.hasArg("confirm") && server.arg("confirm") == "yes") {
#if defined(ESP8266)
		ESP.restart();
#endif
	} else {
		page_content += FPSTR(WEB_RESET_CONTENT);
	}
	page_content += FPSTR(WEB_PAGE_FOOTER);
	server.send(200, FPSTR(TXT_CONTENT_TYPE_TEXT_HTML), page_content);
}

/*****************************************************************
/* Webserver Logo Luftdaten.info                                 *
/*****************************************************************/
void webserver_luftdaten_logo() {
	debug_out(F("output luftdaten.info logo..."),DEBUG_MIN_INFO,1);
	server.send(200, FPSTR(TXT_CONTENT_TYPE_IMAGE_SVG),FPSTR(LUFTDATEN_INFO_LOGO_SVG));
}

/*****************************************************************
/* Webserver Logo Code For Germany                               *
/*****************************************************************/
void webserver_cfg_logo() {
	debug_out(F("output codefor.de logo..."),DEBUG_MIN_INFO,1);
	server.send(200, FPSTR(TXT_CONTENT_TYPE_IMAGE_SVG),FPSTR(CFG_LOGO_SVG));
}

/*****************************************************************
/* Webserver page not found                                      *
/*****************************************************************/
void webserver_not_found() {
	last_page_load = millis();
	debug_out(F("output not found page..."),DEBUG_MIN_INFO,1);
	 server.send(404, FPSTR(TXT_CONTENT_TYPE_TEXT_PLAIN), F("Not found."));
}

/*****************************************************************
/* Webserver setup                                               *
/*****************************************************************/
void setup_webserver() {
	server_name  = F("Feinstaubsensor-");
	server_name += esp_chipid;

	server.on("/", webserver_root);
	server.on("/config",webserver_config);
	server.on("/values",webserver_values);
	server.on("/generate_204",webserver_root);
	server.on("/fwlink",webserver_root);
	server.on("/debug", webserver_debug_level);
	server.on("/removeConfig", webserver_removeConfig);
	server.on("/reset", webserver_reset);
	server.on("/luftdaten_logo.svg", webserver_luftdaten_logo);
	server.on("/cfg_logo.svg", webserver_cfg_logo);
	server.onNotFound(webserver_not_found);

	debug_out(F("Starte Webserver... "),DEBUG_MIN_INFO,0);
	debug_out(IPAddress2String(WiFi.localIP()),DEBUG_MIN_INFO,1);
	server.begin();
}

/*****************************************************************
/* WifiConfig                                                    *
/* Custom API, MQTT, InfuxDB have to be configured in ext_def.h  *
/* no more fields possible for new options                       *
/*****************************************************************/
void wifiConfig() {
#if defined(ESP8266)
	const char *softAP_password = "";
	const byte DNS_PORT = 53;
	int retry_count = 0;
	DNSServer dnsServer;
	IPAddress apIP(192, 168, 4, 1);
	IPAddress netMsk(255, 255, 255, 0);

	debug_out(F("Starting WiFiManager"),DEBUG_MIN_INFO,1);
	debug_out(F("AP ID: Feinstaubsensor-"),DEBUG_MIN_INFO,0);
	debug_out(String(ESP.getChipId()),DEBUG_MIN_INFO,1);

	WiFi.softAPConfig(apIP, apIP, netMsk);
	WiFi.softAP(server_name.c_str(), "");

	dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
	dnsServer.start(DNS_PORT, "*", apIP);

	// 10 minutes timeout for wifi config
	last_page_load = millis();
	while (((millis() - last_page_load) < 600000) && (! config_needs_write)) {
		dnsServer.processNextRequest();
		server.handleClient();
		yield();
	}

	// half second to answer last requests
	last_page_load = millis();
	while (((millis() - last_page_load) < 500)) {
		dnsServer.processNextRequest();
		server.handleClient();
		yield();
	}

	WiFi.softAPdisconnect(true);
	WiFi.mode(WIFI_STA);
	WiFi.disconnect();

	delay(100);

	debug_out(F("Connecting to "),DEBUG_MIN_INFO,0);
	debug_out(wlanssid,DEBUG_MIN_INFO,1);

	WiFi.begin(wlanssid, wlanpwd);
	
	while ((WiFi.status() != WL_CONNECTED) && (retry_count < 20)) {
		delay(500);
		debug_out(".",DEBUG_MIN_INFO,0);
		retry_count++;
	}
	debug_out("",DEBUG_MIN_INFO,1);


	debug_out(F("------ Result from Webconfig ------"),DEBUG_MIN_INFO,1);
	debug_out(F("WLANSSID: "),DEBUG_MIN_INFO,0);debug_out(wlanssid,DEBUG_MIN_INFO,1);
	debug_out(F("DHT_read: "),DEBUG_MIN_INFO,0);debug_out(String(dht_read),DEBUG_MIN_INFO,1);
	debug_out(F("PPD_read: "),DEBUG_MIN_INFO,0);debug_out(String(ppd_read),DEBUG_MIN_INFO,1);
	debug_out(F("SDS_read: "),DEBUG_MIN_INFO,0);debug_out(String(sds_read),DEBUG_MIN_INFO,1);
	debug_out(F("BMP_read: "),DEBUG_MIN_INFO,0);debug_out(String(bmp_read),DEBUG_MIN_INFO,1);
	debug_out(F("Dusti: "),DEBUG_MIN_INFO,0);debug_out(String(send2dusti),DEBUG_MIN_INFO,1);
	debug_out(F("Madavi: "),DEBUG_MIN_INFO,0);debug_out(String(send2madavi),DEBUG_MIN_INFO,1);
	debug_out(F("CSV: "),DEBUG_MIN_INFO,0);debug_out(String(send2csv),DEBUG_MIN_INFO,1);
	debug_out(F("Autoupdate: "),DEBUG_MIN_INFO,0);debug_out(String(auto_update),DEBUG_MIN_INFO,1);
	debug_out(F("Display: "),DEBUG_MIN_INFO,0);debug_out(String(has_display),DEBUG_MIN_INFO,1);
	debug_out(F("Debug: "),DEBUG_MIN_INFO,0);debug_out(String(debug),DEBUG_MIN_INFO,1);
	debug_out(F("------"),DEBUG_MIN_INFO,1);
#endif
}

/*****************************************************************
/* WiFi auto connecting script                                   *
/*****************************************************************/
void connectWifi() {
#if defined(ESP8266)
	int retry_count = 0;
	debug_out(String(WiFi.status()),DEBUG_MIN_INFO,1);
	WiFi.mode(WIFI_STA);
	WiFi.begin(wlanssid, wlanpwd); // Start WiFI

	debug_out(F("Connecting to "),DEBUG_MIN_INFO,0);
	debug_out(wlanssid,DEBUG_MIN_INFO,1);

	while ((WiFi.status() != WL_CONNECTED) && (retry_count < 20)) {
		delay(500);
		debug_out(".",DEBUG_MIN_INFO,0);
		retry_count++;
	}
	debug_out("",DEBUG_MIN_INFO,1);
	if (WiFi.status() != WL_CONNECTED) {
		display_debug("AP ID: Feinstaubsensor-"+esp_chipid+" - IP: 192.168.4.1");
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
	WiFi.softAPdisconnect(true);
	debug_out(F("WiFi connected\nIP address: "),DEBUG_MIN_INFO,0);
	debug_out(IPAddress2String(WiFi.localIP()),DEBUG_MIN_INFO,1);
#endif
}

/*****************************************************************
/* send data to rest api                                         *
/*****************************************************************/
void sendData(const String& data, const int pin, const char* host, const int httpPort, const char* url, const char* basic_auth_string, const String& contentType) {
#if defined(ESP8266)

	debug_out(F("Start connecting to "),DEBUG_MIN_INFO,0);
	debug_out(host,DEBUG_MIN_INFO,1);
	
	String request_head = F("POST "); request_head += String(url); request_head += F(" HTTP/1.1\r\n");
	request_head += F("Host: "); request_head += String(host) + "\r\n";
	request_head += F("Content-Type: "); request_head += contentType + "\r\n";
	if (basic_auth_string != "") { request_head += F("Authorization: Basic "); request_head += String(basic_auth_string) + "\r\n";}
	request_head += F("PIN: "); request_head += String(pin) + "\r\n";
	request_head += F("Sensor: esp8266-"); request_head += esp_chipid + "\r\n";
	request_head += F("Content-Length: "); request_head += String(data.length(),DEC) + "\r\n";
	request_head += F("Connection: close\r\n\r\n");

	// Use WiFiClient class to create TCP connections

	if (httpPort == 443) {

		WiFiClientSecure client_s;
		
		client_s.setNoDelay(true);

		if (!client_s.connect(host, httpPort)) {
			debug_out(F("connection failed"),DEBUG_ERROR,1);
			return;
		}

		debug_out(F("Requesting URL: "),DEBUG_MIN_INFO,0);
		debug_out(url,DEBUG_MIN_INFO,1);
		debug_out(esp_chipid,DEBUG_MIN_INFO,1);
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

		debug_out(F("\nclosing connection\n------\n\n"),DEBUG_MIN_INFO,1);

	} else {

		WiFiClient client;
		
		client.setNoDelay(true);

		if (!client.connect(host, httpPort)) {
			debug_out(F("connection failed"),DEBUG_ERROR,1);
			return;
		}

		debug_out(F("Requesting URL: "),DEBUG_MIN_INFO,0);
		debug_out(url,DEBUG_MIN_INFO,1);
		debug_out(esp_chipid,DEBUG_MIN_INFO,1);
		debug_out(data,DEBUG_MIN_INFO,1);

		client.print(request_head);

		client.println(data);

		delay(10);

		// Read reply from server and print them
		while(client.available()){
			char c = client.read();
			debug_out(String(c),DEBUG_MAX_INFO,0);
		}

		debug_out(F("\nclosing connection\n------\n\n"),DEBUG_MIN_INFO,1);

	}

	debug_out(F("End connecting to "),DEBUG_MIN_INFO,0);
	debug_out(host,DEBUG_MIN_INFO,1);

	yield();
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

	debug_out(F("Start connecting to LoRa gateway"),DEBUG_MIN_INFO,1);

	debug_out(F("data.length(): "),DEBUG_MAX_INFO,0);
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

	debug_out(F("\nclosing connection\n------\n\n"),DEBUG_MIN_INFO,1);

	debug_out(F("End connecting to LoRa gateway"),DEBUG_MIN_INFO,1);

#endif
}

/*****************************************************************
/* send data to mqtt api                                         *
/*****************************************************************/
// rejected (see issue #33)

/*****************************************************************
/* send data to influxdb                                         *
/*****************************************************************/
String create_influxdb_string(const String& data) {
	String tmp_str;
	String data_4_influxdb;
	debug_out(F("Parse JSON for influx DB"), DEBUG_MIN_INFO, 1);
	debug_out(data, DEBUG_MIN_INFO, 1);
	StaticJsonBuffer<2000> jsonBuffer;
	JsonObject& json2data = jsonBuffer.parseObject(data);
	if (json2data.success()) {
		data_4_influxdb = "";
		data_4_influxdb += F("feinstaub,node=esp8266-");
		data_4_influxdb += esp_chipid+" ";
		for (int i = 0; i < json2data["sensordatavalues"].size()-1; i++) {
			tmp_str = jsonBuffer.strdup(json2data["sensordatavalues"][i]["value_type"].as<char*>());
			data_4_influxdb += tmp_str + "=";
			tmp_str = jsonBuffer.strdup(json2data["sensordatavalues"][i]["value"].as<char*>());
			data_4_influxdb += tmp_str;
			if (i < (json2data["sensordatavalues"].size()-2)) data_4_influxdb += ",";
		}
		data_4_influxdb += "\n";
	} else {
		debug_out(F("Data read failed"), DEBUG_ERROR, 1);
	}
	return data_4_influxdb;
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
	StaticJsonBuffer<1000> jsonBuffer;
	JsonObject& json2data = jsonBuffer.parseObject(data);
	debug_out(F("CSV Output"),DEBUG_MIN_INFO,1);
	debug_out(data,DEBUG_MIN_INFO,1);
	if (json2data.success()) {
		headline = F("Timestamp_ms;");
		valueline = String(act_milli)+";";
		for (int i=0;i<json2data["sensordatavalues"].size();i++) {
			tmp_str = jsonBuffer.strdup(json2data["sensordatavalues"][i]["value_type"].as<char*>());
			headline += tmp_str+";";
			tmp_str = jsonBuffer.strdup(json2data["sensordatavalues"][i]["value"].as<char*>());
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
		debug_out(F("Data read failed"),DEBUG_ERROR,1);
	}
}

/*****************************************************************
/* read DHT22 sensor values                                      *
/*****************************************************************/
String sensorDHT() {
	String s = "";
	int i = 0;
	float h;
	float t;

	debug_out(F("Start reading DHT11/22"),DEBUG_MED_INFO,1);

	// Check if valid number if non NaN (not a number) will be send.

	while ((i++ < 5) && (s == "")) {
//		dht.begin();
		h = dht.readHumidity(); //Read Humidity
		t = dht.readTemperature(); //Read Temperature
		if (isnan(t) || isnan(h)) {
			delay(100);
			h = dht.readHumidity(true); //Read Humidity
			t = dht.readTemperature(false,true); //Read Temperature
		}
		if (isnan(t) || isnan(h)) {
			debug_out(F("DHT22 couldn't be read"),DEBUG_ERROR,1);
		} else {
			debug_out(F("Humidity    : "),DEBUG_MIN_INFO,0);
			debug_out(String(h)+"%",DEBUG_MIN_INFO,1);
			debug_out(F("Temperature : "),DEBUG_MIN_INFO,0);
			debug_out(String(t)+" C",DEBUG_MIN_INFO,1);
			last_value_DHT_T = Float2String(t);
			last_value_DHT_H = Float2String(h);
			s += Value2Json(F("temperature"),last_value_DHT_T);
			s += Value2Json(F("humidity"),last_value_DHT_H);
		}
	}
	debug_out(F("------"),DEBUG_MIN_INFO,1);

	debug_out(F("End reading DHT11/22"),DEBUG_MED_INFO,1);

	return s;
}

/*****************************************************************
/* read BMP180 sensor values                                     *
/*****************************************************************/
String sensorBMP() {
	String s = "";
	int p;
	float t;

	debug_out(F("Start reading BMP180"),DEBUG_MED_INFO,1);

	p = bmp.readPressure();
	t = bmp.readTemperature();
	if (isnan(p) || isnan(t)) {
		debug_out(F("BMP180 couldn't be read"),DEBUG_ERROR,1);
	} else {
		debug_out(F("Pressure    : "),DEBUG_MIN_INFO,0);
		debug_out(Float2String(float(p)/100)+" hPa",DEBUG_MIN_INFO,1);
		debug_out(F("Temperature : "),DEBUG_MIN_INFO,0);
		debug_out(String(t)+" C",DEBUG_MIN_INFO,1);
		last_value_BMP_T = Float2String(t);
		last_value_BMP_P = String(p);
		s += Value2Json(F("BMP_pressure"),last_value_BMP_P);
		s += Value2Json(F("BMP_temperature"),last_value_BMP_T);
	}
	debug_out(F("------"),DEBUG_MIN_INFO,1);

	debug_out(F("End reading BMP180"),DEBUG_MED_INFO,1);

	return s;
}

/*****************************************************************
/* read BME280 sensor values                                     *
/*****************************************************************/
String sensorBME280() {
	String s = "";
	float t;
	float h;
	float p;

	debug_out(F("Start reading BME280"),DEBUG_MED_INFO,1);

	t = bme280.readTemperature();
	h = bme280.readHumidity();
	p = bme280.readPressure();
	if (isnan(t) || isnan(h) || isnan(p)) {
		debug_out(F("BME280 couldn't be read"),DEBUG_ERROR,1);
	} else {
		debug_out(F("Temperature : "),DEBUG_MIN_INFO,0);
		debug_out(Float2String(t)+" C",DEBUG_MIN_INFO,1);
		debug_out(F("humidity : "),DEBUG_MIN_INFO,0);
		debug_out(Float2String(h)+" %",DEBUG_MIN_INFO,1);
		debug_out(F("Pressure    : "),DEBUG_MIN_INFO,0);
		debug_out(Float2String(float(p)/100)+" hPa",DEBUG_MIN_INFO,1);
		last_value_BME280_T = Float2String(t);
		last_value_BME280_H = Float2String(h);
		last_value_BME280_P = Float2String(p);
		s += Value2Json(F("BME280_temperature"),last_value_BME280_T);
		s += Value2Json(F("BME280_humidity"),last_value_BME280_H);
		s += Value2Json(F("BME280_pressure"),last_value_BME280_P);
	}
	debug_out(F("------"),DEBUG_MIN_INFO,1);

	debug_out(F("End reading BME280"),DEBUG_MED_INFO,1);

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

	debug_out(F("Start reading SDS011"),DEBUG_MED_INFO,1);

	if (long(act_milli-starttime) < (long(sending_intervall_ms) - long(warmup_time_SDS_ms + reading_time_SDS_ms))) {
		if (is_SDS_running) {
			stop_SDS();
		}
	} else {
		if (! is_SDS_running) {
			start_SDS();
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
			if (len == 10 && checksum_ok == 1 && (long(act_milli-starttime) > (long(sending_intervall_ms) - long(reading_time_SDS_ms)))) {
				if ((! isnan(pm10_serial)) && (! isnan(pm25_serial))) {
					sds_pm10_sum += pm10_serial;
					sds_pm25_sum += pm25_serial;
					sds_display_values_10[sds_display_value_pos] = pm10_serial;
					sds_display_values_25[sds_display_value_pos] = pm25_serial;
					sds_display_value_pos = (sds_display_value_pos+1) % 5;
					debug_out("PM10 (sec.) : "+Float2String(float(pm10_serial)/10),DEBUG_MED_INFO,1);
					debug_out("PM2.5 (sec.): "+Float2String(float(pm25_serial)/10),DEBUG_MED_INFO,1);
					sds_val_count++;
				}
				len = 0; checksum_ok = 0; pm10_serial = 0.0; pm25_serial = 0.0; checksum_is = 0;
			}
			yield();
		}

	}
	if (send_now && (sds_val_count > 0)) {
		debug_out("PM10:  "+Float2String(float(sds_pm10_sum)/(sds_val_count*10.0)),DEBUG_MIN_INFO,1);
		debug_out("PM2.5: "+Float2String(float(sds_pm25_sum)/(sds_val_count*10.0)),DEBUG_MIN_INFO,1);
		debug_out("------",DEBUG_MIN_INFO,1);
		last_value_SDS_P1 = Float2String(float(sds_pm10_sum)/(sds_val_count*10.0));
		last_value_SDS_P2 = Float2String(float(sds_pm25_sum)/(sds_val_count*10.0));
		s += Value2Json("SDS_P1",last_value_SDS_P1);
		s += Value2Json("SDS_P2",last_value_SDS_P2);
		sds_pm10_sum = 0; sds_pm25_sum = 0; sds_val_count = 0;
		if ((sending_intervall_ms > (warmup_time_SDS_ms + reading_time_SDS_ms)) && (! will_check_for_update)) {
			stop_SDS();
		}
	}

	debug_out(F("End reading SDS011"),DEBUG_MED_INFO,1);

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

	debug_out(F("Start reading PPD42NS"),DEBUG_MED_INFO,1);

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
	if (send_now) {
		ratio = lowpulseoccupancyP1/(sampletime_ms*10.0);					// int percentage 0 to 100
		concentration = (1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62);	// spec sheet curve
		// Begin printing
		debug_out(F("LPO P10    : "),DEBUG_MIN_INFO,0);
		debug_out(String(lowpulseoccupancyP1),DEBUG_MIN_INFO,1);
		debug_out(F("Ratio PM10 : "),DEBUG_MIN_INFO,0);
		debug_out(Float2String(ratio)+" %",DEBUG_MIN_INFO,1);
		debug_out(F("PM10 Count : "),DEBUG_MIN_INFO,0);
		debug_out(Float2String(concentration),DEBUG_MIN_INFO,1);

		// json for push to api / P1
		last_value_PPD_P1 = Float2String(concentration);
		s += Value2Json("durP1",String(long(lowpulseoccupancyP1)));
		s += Value2Json("ratioP1",Float2String(ratio));
		s += Value2Json("P1",last_value_PPD_P1);

		ratio = lowpulseoccupancyP2/(sampletime_ms*10.0);
		concentration = (1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62);
		// Begin printing
		debug_out(F("LPO PM25   : "),DEBUG_MIN_INFO,0);
		debug_out(String(lowpulseoccupancyP2),DEBUG_MIN_INFO,1);
		debug_out(F("Ratio PM25 : "),DEBUG_MIN_INFO,0);
		debug_out(Float2String(ratio)+" %",DEBUG_MIN_INFO,1);
		debug_out(F("PM25 Count : "),DEBUG_MIN_INFO,0);
		debug_out(Float2String(concentration),DEBUG_MIN_INFO,1);

		// json for push to api / P2
		last_value_PPD_P2 = Float2String(concentration);
		s += Value2Json("durP2",String(long(lowpulseoccupancyP2)));
		s += Value2Json("ratioP2",Float2String(ratio));
		s += Value2Json("P2",last_value_PPD_P2);

		debug_out(F("------"),DEBUG_MIN_INFO,1);
	}

	debug_out(F("End reading PPD42NS"),DEBUG_MED_INFO,1);

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

	debug_out(F("Start reading GPS"),DEBUG_MED_INFO,1);

	while (serialGPS.available() > 0) {
		if (gps.encode(serialGPS.read())) {
			if (gps.location.isValid()) {
				last_gps_lat = String(gps.location.lat(),6);
				last_gps_lng = String(gps.location.lng(),6);
			} else {
				debug_out(F("Lat/Lng INVALID"),DEBUG_MAX_INFO,1);
			}
			if (gps.altitude.isValid()) {
				last_gps_alt = String(gps.altitude.meters(),2);
			} else {
				debug_out(F("Altitude INVALID"),DEBUG_MAX_INFO,1);
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
				debug_out(F("Date INVALID"),DEBUG_MAX_INFO,1);
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
				debug_out(F("Time: INVALID"),DEBUG_MAX_INFO,1);
			}
		}
	}

	if (send_now) {
		debug_out("Lat/Lng: "+last_gps_lat+","+last_gps_lng,DEBUG_MIN_INFO,1);
		debug_out("Altitude: "+last_gps_alt,DEBUG_MIN_INFO,1);
		debug_out("Date: "+last_gps_date,DEBUG_MIN_INFO,1);
		debug_out("Time "+last_gps_time,DEBUG_MIN_INFO,1);
		debug_out("------",DEBUG_MIN_INFO,1);
		s += Value2Json(F("GPS_lat"),last_gps_lat);
		s += Value2Json(F("GPS_lon"),last_gps_lng);
		s += Value2Json(F("GPS_height"),last_gps_alt);
		s += Value2Json(F("GPS_date"),last_gps_date);
		s += Value2Json(F("GPS_time"),last_gps_time);
		last_gps_lat = "";
		last_gps_lng = "";
		last_gps_alt = "";
		last_gps_date = "";
		last_gps_time = "";
	}

	if ( gps.charsProcessed() < 10) {
		debug_out(F("No GPS data received: check wiring"),DEBUG_ERROR,1);
	}

	debug_out(F("End reading GPS"),DEBUG_MED_INFO,1);

#endif
	return s;
}

/*****************************************************************
/* AutoUpdate                                                    *
/*****************************************************************/
void autoUpdate() {
#if defined(ESP8266)
	String SDS_version = "";
	if (auto_update) {
		debug_out(F("Starting OTA update ..."),DEBUG_MIN_INFO,1);
		debug_out(F("NodeMCU firmware : "),DEBUG_MIN_INFO,0);
		debug_out(String(SOFTWARE_VERSION),DEBUG_MIN_INFO,1);
		if (sds_read) { SDS_version = SDS_version_date();}
		display_debug(F("Looking for OTA update"));
		last_update_attempt = millis();
		t_httpUpdate_return ret = ESPhttpUpdate.update(update_host, update_port, update_url, String(SOFTWARE_VERSION)+String(" ")+esp_chipid+String(" ")+SDS_version);
		switch(ret) {
			case HTTP_UPDATE_FAILED:
					debug_out(F("[update] Update failed."),DEBUG_ERROR,1);
					display_debug(F("Update failed."));
					break;
			case HTTP_UPDATE_NO_UPDATES:
					debug_out(F("[update] No Update."),DEBUG_MIN_INFO,1);
					display_debug(F("No update found."));
					break;
			case HTTP_UPDATE_OK:
					debug_out(F("[update] Update ok."),DEBUG_MIN_INFO,1); // may not called we reboot the ESP
					break;
		}
	}
	will_check_for_update = false;
#endif
}

/*****************************************************************
/* display values                                                *
/*****************************************************************/
void display_values(const String& value_DHT_T, const String& value_DHT_H, const String& value_BMP_T, const String& value_BMP_P, const String& value_PPD_P1, const String& value_PPD_P2, const String& value_SDS_P1, const String& value_SDS_P2) {
#if defined(ESP8266)
	int value_count = 0;
	debug_out(F("output values to display..."),DEBUG_MIN_INFO,1);
	display.resetDisplay();
	display.clear();
	display.displayOn();
	display.setFont(Monospaced_plain_9);
	display.setTextAlignment(TEXT_ALIGN_LEFT);
	value_count = 0;
	if (dht_read) {
		display.drawString(0,10*(value_count++),"Temp:"+value_DHT_T+"  Hum.:"+value_DHT_H);
	}
	if (bmp_read) {
		display.drawString(0,10*(value_count++),"Temp:"+value_BMP_T+" Druck:"+value_BMP_P);
	}
	if (ppd_read) {
		display.drawString(0,10*(value_count++),"PPD P1: "+value_PPD_P1);
		display.drawString(0,10*(value_count++),"PPD P2: "+value_PPD_P2);
	}
	if (sds_read) {
		display.drawString(0,10*(value_count++),"SDS P1: "+value_SDS_P1);
		display.drawString(0,10*(value_count++),"SDS P2: "+value_SDS_P2);
	}
	if (gps_read) {
		if(gps.location.isValid()) {
			display.drawString(0,10*(value_count++),"lat: "+String(gps.location.lat(),6));
			display.drawString(0,10*(value_count++),"long: "+String(gps.location.lng(),6));
		}
		display.drawString(0,10*(value_count++),"satelites: "+String(gps.satellites.value()));
	}
	display.display();
	yield();
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
/* Init BME280                                                   *
/*****************************************************************/
bool initBME280(char addr) {
	debug_out("Trying BME280 sensor on ",DEBUG_MIN_INFO,0);
	debug_out(String(addr,HEX),DEBUG_MIN_INFO,0);

	if (bme280.begin(addr)) {
		debug_out(F(" ... found"), DEBUG_MIN_INFO, 1);
		return true;
	} else {
		debug_out(F(" ... not found"), DEBUG_MIN_INFO, 1);
		return false;
	}
}


/*****************************************************************
/* The Setup                                                     *
/*****************************************************************/
void setup() {
	Serial.begin(9600);					// Output to Serial at 9600 baud
#if defined(ESP8266)
	Wire.begin(D3,D4);
	esp_chipid = String(ESP.getChipId());
#endif
#if defined(ARDUINO_SAMD_ZERO)
	Wire.begin();
#endif
	init_display();
	copyExtDef();
	display_debug(F("Reading config from SPIFFS"));
	readConfig();
	setup_webserver();
	display_debug("Connecting to "+String(wlanssid));
	connectWifi();						// Start ConnectWifi
	display_debug(F("Writing config to SPIFFS"));
	writeConfig();
	autoUpdate();

	create_basic_auth_strings();

	serialSDS.begin(9600);
	serialGPS.begin(9600);

	pinMode(PPD_PIN_PM1,INPUT_PULLUP);	// Listen at the designated PIN
	pinMode(PPD_PIN_PM2,INPUT_PULLUP);	// Listen at the designated PIN
	dht.begin();						// Start DHT
	delay(10);
#if defined(ESP8266)
	debug_out("\nChipId: " + esp_chipid,DEBUG_MIN_INFO,1);
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

	if (ppd_read) debug_out(F("Lese PPD..."),DEBUG_MIN_INFO,1);
	if (sds_read) debug_out(F("Lese SDS..."),DEBUG_MIN_INFO,1);
	if (dht_read) debug_out(F("Lese DHT..."),DEBUG_MIN_INFO,1);
	if (bmp_read) debug_out(F("Lese BMP..."),DEBUG_MIN_INFO,1);
	if (bme280_read) debug_out(F("Lese BME280..."),DEBUG_MIN_INFO,1);
	if (gps_read) debug_out(F("Lese GPS..."),DEBUG_MIN_INFO,1);
	if (send2dusti) debug_out(F("Sende an luftdaten.info..."),DEBUG_MIN_INFO,1);
	if (send2madavi) debug_out(F("Sende an madavi.de..."),DEBUG_MIN_INFO,1);
	if (send2lora) debug_out(F("Sende an LoRa gateway..."),DEBUG_MIN_INFO,1);
	if (send2csv) debug_out(F("Sende als CSV an Serial..."),DEBUG_MIN_INFO,1);
	if (send2custom) debug_out(F("Sende an custom API..."),DEBUG_MIN_INFO,1);
	if (send2influxdb) debug_out(F("Sende an custom influx DB..."),DEBUG_MIN_INFO,1);
	if (auto_update) debug_out(F("Auto-Update wird ausgeführt..."),DEBUG_MIN_INFO,1);
	if (has_display) debug_out(F("Zeige auf Display..."),DEBUG_MIN_INFO,1);
	if (bmp_read) {
		if (!bmp.begin()) {
			debug_out(F("No valid BMP085 sensor, check wiring!"),DEBUG_MIN_INFO,1);
			bmp_read = 0;
		}
	}
	if (bme280_read && !initBME280(0x76) && !initBME280(0x77)) {
		debug_out(F("Check BME280 wiring"),DEBUG_MIN_INFO,1);
		bme280_read = 0;
	}
	if (sds_read) {
		debug_out(F("Stoppe SDS011..."),DEBUG_MIN_INFO,1);
		stop_SDS();
	}
#if defined(ARDUINO_SAMD_ZERO)
	data_first_part.replace("FEATHERCHIPID", ", \"chipid\": \"" + FeatherChipId() + "\"");
#else
	data_first_part.replace("FEATHERCHIPID", "");
#endif

	if (MDNS.begin(server_name.c_str())) {
		MDNS.addService("http", "tcp", 80);
	}

	starttime = millis();					// store the start time
	starttime_SDS = millis();
}

/*****************************************************************
/* And action                                                    *
/*****************************************************************/
void loop() {
	String data = "";
	String tmp_str;
	String data_4_dusti = "";
	String data_4_influxdb = "";
	String data_sample_times = "";

	String result_PPD = "";
	String result_SDS = "";
	String result_DHT = "";
	String result_BMP = "";
	String result_BME280 = "";
	String result_GPS = "";
	String signal_strength = "";
	
	unsigned long sum_send_time = 0;
	unsigned long start_send;

	send_failed = false;

	act_micro = micros();
	act_milli = millis();
	send_now = (act_milli-starttime) > sending_intervall_ms;

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
		debug_out(F("Call sensorPPD"),DEBUG_MAX_INFO,1);
		result_PPD = sensorPPD();
	}

	if (sds_read && (send_now || (act_milli-starttime_SDS) > sampletime_SDS_ms)) {
		debug_out(F("Call sensorSDS"),DEBUG_MAX_INFO,1);
		result_SDS = sensorSDS();
		starttime_SDS = act_milli;
	}

	if (dht_read && send_now) {
		debug_out(F("Call sensorDHT"),DEBUG_MAX_INFO,1);
		result_DHT = sensorDHT();			// getting temperature and humidity (optional)
	}

	if (bmp_read && send_now) {
		debug_out(F("Call sensorBMP"),DEBUG_MAX_INFO,1);
		result_BMP = sensorBMP();			// getting temperature and humidity (optional)
	}

	if (bme280_read && send_now) {
		debug_out(F("Call sensorBME280"),DEBUG_MAX_INFO,1);
		result_BME280 = sensorBME280();			// getting temperature and humidity (optional)
	}

	if (gps_read && (send_now || (act_milli-starttime_GPS > sampletime_GPS_ms))) {
		debug_out(F("Call sensorGPS"),DEBUG_MAX_INFO,1);
		result_GPS = sensorGPS();			// getting GPS coordinates
		starttime_GPS = act_milli;
	}

	if (has_display) {
		if ((act_milli-display_last_update) > display_update_interval) {
			if (sds_read) {
				last_value_SDS_P1 = Float2String(float(sds_display_values_10[0]+sds_display_values_10[1]+sds_display_values_10[2]+sds_display_values_10[3]+sds_display_values_10[4])/50.0);
				last_value_SDS_P2 = Float2String(float(sds_display_values_25[0]+sds_display_values_25[1]+sds_display_values_25[2]+sds_display_values_25[3]+sds_display_values_25[4])/50.0);
			}
			display_values(last_value_DHT_T,last_value_DHT_H,last_value_BMP_T,last_value_BMP_P,last_value_PPD_P1,last_value_PPD_P2,last_value_SDS_P1,last_value_SDS_P2);
			display_last_update = act_milli;
		}
	}

	if (send_now) {
		debug_out(F("Creating data string:"),DEBUG_MIN_INFO,1);
		data = data_first_part;
		data_sample_times  = Value2Json("samples",String(long(sample_count)));
		data_sample_times += Value2Json("min_micro",String(long(min_micro)));
		data_sample_times += Value2Json("max_micro",String(long(max_micro)));

		signal_strength = String(WiFi.RSSI())+" dBm";
		debug_out(F("WLAN signal strength: "),DEBUG_MIN_INFO,0);
		debug_out(signal_strength,DEBUG_MIN_INFO,1);
		debug_out(F("------"),DEBUG_MIN_INFO,1);

		if (ppd_read) {
			last_result_PPD = result_PPD;
			data += result_PPD;
			data_4_dusti  = data_first_part + result_PPD;
			data_4_dusti.remove(data_4_dusti.length()-1);
			data_4_dusti += "]}";
			if (send2dusti) {
				debug_out(F("## Sending to luftdaten.info (PPD): "),DEBUG_MIN_INFO,1);
				start_send = micros();
				if (result_PPD != "") {
					sendData(data_4_dusti,PPD_API_PIN,host_dusti,httpPort_dusti,url_dusti,"",FPSTR(TXT_CONTENT_TYPE_JSON));
				} else {
					debug_out(F("No data sent..."),DEBUG_MIN_INFO,1);
				}
				sum_send_time += micros() - start_send;
			}
		}
		if (sds_read) {
			data += result_SDS;
			data_4_dusti  = data_first_part + result_SDS;
			data_4_dusti.remove(data_4_dusti.length()-1);
			data_4_dusti.replace("SDS_","");
			data_4_dusti += "]}";
			if (send2dusti) {
				debug_out(F("## Sending to luftdaten.info (SDS): "),DEBUG_MIN_INFO,1);
				start_send = micros();
				if (result_SDS != "") {
					sendData(data_4_dusti,SDS_API_PIN,host_dusti,httpPort_dusti,url_dusti,"",FPSTR(TXT_CONTENT_TYPE_JSON));
				} else {
					debug_out(F("No data sent..."),DEBUG_MIN_INFO,1);
				}
				sum_send_time += micros() - start_send;
			}
		}
		if (dht_read) {
			last_result_DHT = result_DHT;
			data += result_DHT;
			data_4_dusti  = data_first_part + result_DHT;
			data_4_dusti.remove(data_4_dusti.length()-1);
			data_4_dusti += "]}";
			if (send2dusti) {
				debug_out(F("## Sending to luftdaten.info (DHT): "),DEBUG_MIN_INFO,1);
				start_send = micros();
				if (result_DHT != "") {
					sendData(data_4_dusti,DHT_API_PIN,host_dusti,httpPort_dusti,url_dusti,"",FPSTR(TXT_CONTENT_TYPE_JSON));
				} else {
					debug_out(F("No data sent..."),DEBUG_MIN_INFO,1);
				}
				sum_send_time += micros() - start_send;
			}
		}
		if (bmp_read) {
			last_result_BMP = result_BMP;
			data += result_BMP;
			data_4_dusti  = data_first_part + result_BMP;
			data_4_dusti.remove(data_4_dusti.length()-1);
			data_4_dusti.replace("BMP_","");
			data_4_dusti += "]}";
			if (send2dusti) {
				debug_out(F("## Sending to luftdaten.info (BMP): "),DEBUG_MIN_INFO,1);
				start_send = micros();
				if (result_BMP != "") {
					sendData(data_4_dusti,BMP_API_PIN,host_dusti,httpPort_dusti,url_dusti,"",FPSTR(TXT_CONTENT_TYPE_JSON));
				} else {
					debug_out(F("No data sent..."),DEBUG_MIN_INFO,1);
				}
				sum_send_time += micros() - start_send;
			}
		}
		if (bme280_read) {
			last_result_BME280 = result_BME280;
			data += result_BME280;
			data_4_dusti  = data_first_part + result_BME280;
			data_4_dusti.remove(data_4_dusti.length()-1);
			data_4_dusti.replace("BME280_","");
			data_4_dusti += "]}";
			if (send2dusti) {
				debug_out(F("## Sending to luftdaten.info (BME280): "),DEBUG_MIN_INFO,1);
				start_send = micros();
				if (result_BME280 != "") {
					sendData(data_4_dusti,BME280_API_PIN,host_dusti,httpPort_dusti,url_dusti,"",FPSTR(TXT_CONTENT_TYPE_JSON));
				} else {
					debug_out(F("No data sent..."),DEBUG_MIN_INFO,1);
				}
				sum_send_time += micros() - start_send;
			}
		}

		if (gps_read) {
			data += result_GPS;
			data_4_dusti  = data_first_part + result_GPS;
			data_4_dusti.remove(data_4_dusti.length()-1);
			data_4_dusti.replace("GPS_","");
			data_4_dusti += "]}";
			if (send2dusti) {
				debug_out(F("## Sending to luftdaten.info (GPS): "),DEBUG_MIN_INFO,1);
				start_send = micros();
				if (result_GPS != "") {
					sendData(data_4_dusti,GPS_API_PIN,host_dusti,httpPort_dusti,url_dusti,"",FPSTR(TXT_CONTENT_TYPE_JSON));
				} else {
					debug_out(F("No data sent..."),DEBUG_MIN_INFO,1);
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
			display_values(last_value_DHT_T,last_value_DHT_H,last_value_BMP_T,last_value_BMP_P,last_value_PPD_P1,last_value_PPD_P2,last_value_SDS_P1,last_value_SDS_P2);
		}

		if (send2madavi) {
			debug_out(F("## Sending to madavi.de: "),DEBUG_MIN_INFO,1);
			start_send = micros();
			sendData(data,0,host_madavi,httpPort_madavi,url_madavi,"",FPSTR(TXT_CONTENT_TYPE_JSON));
			sum_send_time += micros() - start_send;
		}

		if (send2custom) {
			debug_out(F("## Sending to custom api: "),DEBUG_MIN_INFO,1);
			start_send = micros();
			sendData(data,0,host_custom,httpPort_custom,url_custom,basic_auth_custom.c_str(),FPSTR(TXT_CONTENT_TYPE_JSON));
			sum_send_time += micros() - start_send;
		}

		if (send2influxdb) {
			debug_out(F("## Sending to custom influx db: "),DEBUG_MIN_INFO,1);
			start_send = micros();
			data_4_influxdb = create_influxdb_string(data);
			sendData(data_4_influxdb,0,host_influxdb,httpPort_influxdb,url_influxdb,basic_auth_influxdb.c_str(),FPSTR(TXT_CONTENT_TYPE_INFLUXDB));
			sum_send_time += micros() - start_send;
		}

		if (send2lora) {
			debug_out(F("## Sending to LoRa gateway: "),DEBUG_MIN_INFO,1);
			send_lora(data);
		}

		if (send2csv) {
			debug_out(F("## Sending as csv: "),DEBUG_MIN_INFO,1);
			send_csv(data);
		}

		if ((act_milli-last_update_attempt) > (28 * pause_between_update_attempts)) {
			ESP.restart();
		}

		if ((act_milli-last_update_attempt) > pause_between_update_attempts) {
			autoUpdate();
		}

		if (! send_failed) sending_time = (4 * sending_time + sum_send_time) / 5;
		debug_out(F("Time for sending data: "),DEBUG_MIN_INFO,0);
		debug_out(String(sending_time),DEBUG_MIN_INFO,1);
		// Resetting for next sampling
		last_data_string = data;
		lowpulseoccupancyP1 = 0;
		lowpulseoccupancyP2 = 0;
		sample_count = 0;
		last_micro = 0;
		min_micro = 1000000000;
		max_micro = 0;
		starttime = millis(); // store the start time
		if (WiFi.status() != WL_CONNECTED) {  // reconnect if connection lost
			int retry_count = 0;
			debug_out(F("Connection lost, reconnecting "),DEBUG_MIN_INFO,0);
			WiFi.reconnect();
			while ((WiFi.status() != WL_CONNECTED) && (retry_count < 20)) {
				delay(500);
				debug_out(".",DEBUG_MIN_INFO,0);
				retry_count++;
			}
			debug_out("",DEBUG_MIN_INFO,1);
		}
	}
	if (config_needs_write) { writeConfig(); create_basic_auth_strings(); }
	server.handleClient();
	yield();
}
