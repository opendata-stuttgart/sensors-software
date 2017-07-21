#include <Arduino.h>
#define INTL_DE
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
#define SOFTWARE_VERSION "NRZ-2017-092_custom"

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
#include <LiquidCrystal_I2C.h>
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
#include <OneWire.h>
#include <DallasTemperature.h>
#include <TinyGPS++.h>
#include <Ticker.h>

#if defined(INTL_BG)
#include "intl_bg.h"
#elif defined(INTL_EN)
#include "intl_en.h"
#elif defined(INTL_ES)
#include "intl_es.h"
#elif defined(INTL_FR)
#include "intl_fr.h"
#elif defined(INTL_IT)
#include "intl_it.h"
#elif defined(INTL_NL)
#include "intl_nl.h"
#else
#include "intl_de.h"
#endif
#include "ext_def.h"
#include "html-content.h"

/*****************************************************************
/* Variables with defaults                                       *
/*****************************************************************/
char wlanssid[65] = "Freifunk-disabled";
char wlanpwd[65] = "";
char current_lang[3] = "de";
char www_username[65] = "admin";
char www_password[65] = "feinstaub";
bool www_basicauth_enabled = 0;

char version_from_local_config[30] = "";

bool dht_read = 1;
bool ppd_read = 0;
bool sds_read = 1;
bool bmp_read = 0;
bool bme280_read = 0;
bool ds18b20_read = 0;
bool gps_read = 0;
bool send2dusti = 1;
bool send2madavi = 1;
bool send2sensemap = 0;
bool send2custom = 0;
bool send2lora = 1;
bool send2influx = 0;
bool send2csv = 0;
bool auto_update = 0;
bool has_display = 0;
bool has_lcd1602 = 0;
int  debug = 3;

long int sample_count = 0;

const char* host_madavi = "api-rrd.madavi.de";
const char* url_madavi = "/data.php";
int httpPort_madavi = 443;

const char* host_dusti = "api.luftdaten.info";
const char* url_dusti = "/v1/push-sensor-data/";
int httpPort_dusti = 443;

// IMPORTANT: NO MORE CHANGES TO VARIABLE NAMES NEEDED FOR EXTERNAL APIS

const char* host_sensemap = "ingress.opensensemap.org";
String url_sensemap = "/boxes/BOXID/data?luftdaten=1";
const int httpPort_sensemap = 443;
char senseboxid[30] = "";

char host_influx[100] = "api.luftdaten.info";
char url_influx[100] = "/write?db=luftdaten";
int port_influx = 8086;
char user_influx[100] = "luftdaten";
char pwd_influx[100] = "info";
String basic_auth_influx = "";

char host_custom[100] = "192.168.234.1";
char url_custom[100] = "/data.php";
int port_custom = 80;
char user_custom[100] = "";
char pwd_custom[100] = "";
String basic_auth_custom = "";

const char* update_host = "www.madavi.de";
const char* update_url = "/sensor/update/firmware.php";
const int update_port = 80;

#if defined(ESP8266)
ESP8266WebServer server(80);
int TimeZone = 1;
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
LiquidCrystal_I2C lcd(0x3F, 16, 2);
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
/* DS18B20 declaration                                            *
/*****************************************************************/
OneWire oneWire(DS18B20_PIN);
DallasTemperature ds18b20(&oneWire);

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
const unsigned long warmup_time_SDS_ms = 15000;
const unsigned long reading_time_SDS_ms = 5000;
// const unsigned long reading_time_SDS_ms = 60000;
bool is_SDS_running = true;

const unsigned long display_update_interval = 5000;
unsigned long display_last_update;

const unsigned long sampletime_GPS_ms = 50;

unsigned long sending_intervall_ms = 145000;
unsigned long sending_time = 0;
bool send_failed = false;

unsigned long time_for_wifi_config = 600000;

unsigned long last_update_attempt;
const unsigned long pause_between_update_attempts = 86400000;
bool will_check_for_update = false;

int sds_pm10_sum = 0;
int sds_pm25_sum = 0;
int sds_val_count = 0;
int sds_pm10_max = 0;
int sds_pm10_min = 20000;
int sds_pm25_max = 0;
int sds_pm25_min = 20000;

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
String last_value_DS18B20_T = "";
String last_data_string = "";

String last_gps_lat;
String last_gps_lng;
String last_gps_alt;
String last_gps_date;
String last_gps_time;

String esp_chipid;

String server_name;

long last_page_load = millis();

bool wificonfig_loop = false;
bool restart_needed = false;

bool config_needs_write = false;

bool first_csv_line = 1;

bool first_cycle = 1;

String data_first_part = "{\"software_version\": \"" + String(SOFTWARE_VERSION) + "\"FEATHERCHIPID, \"sensordatavalues\":[";

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
		debug_out(F("output debug text to display..."), DEBUG_MIN_INFO, 1);
		debug_out(text, DEBUG_MAX_INFO, 1);
		display.resetDisplay();
		display.clear();
		display.displayOn();
		display.setFont(Monospaced_plain_9);
		display.setTextAlignment(TEXT_ALIGN_LEFT);
		display.drawStringMaxWidth(0, 12, 120, text);
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
		if (reqd > decpt) { reqd++; }
		if (decpt == 0) { reqd++; }
	}
	if (sign) { reqd++; }
	p = sout;
	e = p + reqd;
	pad = width - reqd;
	if (pad > 0) {
		e += pad;
		while (pad-- > 0) { *p++ = ' '; }
	}
	if (sign) { *p++ = '-'; }
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
		if (p == e) { break; }
		if (--decpt == 0) { *p++ = '.'; }
	}
	if (width < 0) {
		pad = (reqd + width) * -1;
		while (pad-- > 0) { *p++ = ' '; }
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

	dtostrf(value, 13, 2, temp);
	s = String(temp);
	s.trim();
	return s;
}

/*****************************************************************
/* convert value to json string                                  *
/*****************************************************************/
String Value2Json(const String& type, const String& value) {
	String s = F("{\"value_type\":\"{t}\",\"value\":\"{v}\"},");
	s.replace("{t}", type); s.replace("{v}", value);
	return s;
}

/*****************************************************************
/* ChipId Arduino Feather                                        *
/*****************************************************************/
String FeatherChipId() {
	String s;
#if defined(ARDUINO_SAMD_ZERO)
	debug_out("Reading Arduino Feather ChipID", DEBUG_MED_INFO, 1);

	volatile uint32_t val1, val2, val3, val4;
	volatile uint32_t *ptr1 = (volatile uint32_t *)0x0080A00C;
	val1 = *ptr1;
	volatile uint32_t *ptr = (volatile uint32_t *)0x0080A040;
	val2 = *ptr;
	ptr++;
	val3 = *ptr;
	ptr++;
	val4 = *ptr;

	s = String(val1, HEX) + String(val2, HEX) + String(val3, HEX) + String(val4, HEX);

#endif
	return s;
}

/*****************************************************************
/* start SDS011 sensor                                           *
/*****************************************************************/
void start_SDS() {
	const uint8_t start_SDS_cmd[] = {0xAA, 0xB4, 0x06, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x06, 0xAB};
	serialSDS.write(start_SDS_cmd, sizeof(start_SDS_cmd)); is_SDS_running = true;
}

/*****************************************************************
/* stop SDS011 sensor                                            *
/*****************************************************************/
void stop_SDS() {
	const uint8_t stop_SDS_cmd[] = {0xAA, 0xB4, 0x06, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x05, 0xAB};
	serialSDS.write(stop_SDS_cmd, sizeof(stop_SDS_cmd)); is_SDS_running = false;
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

	debug_out(F("Start reading SDS011 version date"), DEBUG_MED_INFO, 1);

	start_SDS();

	delay(100);

	serialSDS.write(version_SDS_cmd, sizeof(version_SDS_cmd));

	delay(500);

	while (serialSDS.available() > 0) {
		buffer = serialSDS.read();
		debug_out(String(len) + " - " + String(buffer, DEC) + " - " + String(buffer, HEX) + " - " + int(buffer) + " .", DEBUG_MED_INFO, 1);
//		"aa" = 170, "ab" = 171, "c0" = 192
		value = int(buffer);
		switch (len) {
		case (0): if (value != 170) { len = -1; }; break;
		case (1): if (value != 197) { len = -1; }; break;
		case (2): if (value != 7) { len = -1; }; break;
		case (3): version_date  = String(value); checksum_is = 7 + value; break;
		case (4): version_date += "-" + String(value); checksum_is += value; break;
		case (5): version_date += "-" + String(value); checksum_is += value; break;
		case (6): if (value < 0x10) {device_id  = "0" + String(value, HEX);} else {device_id  = String(value, HEX);}; checksum_is += value; break;
		case (7): if (value < 0x10) {device_id += "0";}; device_id += String(value, HEX); checksum_is += value; break;
		case (8):
			debug_out(F("Checksum is: "), DEBUG_MED_INFO, 0);
			debug_out(String(checksum_is % 256), DEBUG_MED_INFO, 0);
			debug_out(F(" - should: "), DEBUG_MED_INFO, 0);
			debug_out(String(value), DEBUG_MED_INFO, 1);
			if (value == (checksum_is % 256)) { checksum_ok = 1; } else { len = -1; }; break;
		case (9): if (value != 171) { len = -1; }; break;
		}
		len++;
		if (len == 10 && checksum_ok == 1) {
			s = version_date + "(" + device_id + ")";
			debug_out(F("SDS version date : "), DEBUG_MIN_INFO, 0);
			debug_out(version_date, DEBUG_MIN_INFO, 1);
			debug_out(F("SDS device ID:     "), DEBUG_MIN_INFO, 0);
			debug_out(device_id, DEBUG_MIN_INFO, 1);
			len = 0; checksum_ok = 0; version_date = ""; device_id = ""; checksum_is = 0;
		}
		yield();
	}

	debug_out(F("End reading SDS011 version date"), DEBUG_MED_INFO, 1);

	return s;
}

/*****************************************************************
/* copy config from ext_def                                      *
/*****************************************************************/
void copyExtDef() {

#define strcpyDef(var, def) if (def != NULL) { strcpy(var, def); }
#define setDef(var, def)    if (def != var) { var = def; }

	strcpyDef(current_lang, CURRENT_LANG);
	strcpyDef(wlanssid, WLANSSID);
	strcpyDef(wlanpwd, WLANPWD);
	strcpyDef(www_username, WWW_USERNAME);
	strcpyDef(www_password, WWW_PASSWORD);
	setDef(www_basicauth_enabled, WWW_BASICAUTH_ENABLED);
	setDef(dht_read, DHT_READ);
	setDef(ppd_read, PPD_READ);
	setDef(sds_read, SDS_READ);
	setDef(bmp_read, BMP_READ);
	setDef(bme280_read, BME280_READ);
  setDef(ds18b20_read, DS18B20_READ);
	setDef(gps_read, GPS_READ);
	setDef(send2dusti, SEND2DUSTI);
	setDef(send2madavi, SEND2MADAVI);
	setDef(send2sensemap, SEND2SENSEMAP)
	setDef(send2lora, SEND2LORA);
	setDef(send2csv, SEND2CSV);
	setDef(auto_update, AUTO_UPDATE);
	setDef(has_display, HAS_DISPLAY);
	setDef(has_lcd1602, HAS_LCD1602);

	setDef(debug, DEBUG);

	strcpyDef(senseboxid, SENSEBOXID);

	setDef(send2custom, SEND2CUSTOM);
	strcpyDef(host_custom, HOST_CUSTOM);
	strcpyDef(url_custom, URL_CUSTOM);
	setDef(port_custom, PORT_CUSTOM);
	strcpyDef(user_custom, USER_CUSTOM);
	strcpyDef(pwd_custom, PWD_CUSTOM);

	setDef(send2influx, SEND2INFLUX);
	strcpyDef(host_influx, HOST_INFLUX);
	strcpyDef(url_influx, URL_INFLUX);
	setDef(port_influx, PORT_INFLUX);
	strcpyDef(user_influx, USER_INFLUX);
	strcpyDef(pwd_influx, PWD_INFLUX);

#undef strcpyDef
#undef setDef
}

/*****************************************************************
/* read config from spiffs                                       *
/*****************************************************************/
void readConfig() {
#if defined(ESP8266)
	String json_string = "";
	debug_out(F("mounting FS..."), DEBUG_MIN_INFO, 1);

	if (SPIFFS.begin()) {
		debug_out(F("mounted file system..."), DEBUG_MIN_INFO, 1);
		if (SPIFFS.exists("/config.json")) {
			//file exists, reading and loading
			debug_out(F("reading config file..."), DEBUG_MIN_INFO, 1);
			File configFile = SPIFFS.open("/config.json", "r");
			if (configFile) {
				debug_out(F("opened config file..."), DEBUG_MIN_INFO, 1);
				size_t size = configFile.size();
				// Allocate a buffer to store contents of the file.
				std::unique_ptr<char[]> buf(new char[size]);

				configFile.readBytes(buf.get(), size);
				StaticJsonBuffer<2000> jsonBuffer;
				JsonObject& json = jsonBuffer.parseObject(buf.get());
				json.printTo(json_string);
				debug_out(F("File content: "), DEBUG_MAX_INFO, 0);
				debug_out(String(buf.get()), DEBUG_MAX_INFO, 1);
				debug_out(F("JSON Buffer content: "), DEBUG_MAX_INFO, 0);
				debug_out(json_string, DEBUG_MAX_INFO, 1);
				if (json.success()) {
					debug_out(F("parsed json..."), DEBUG_MIN_INFO, 1);
					if (json.containsKey("SOFTWARE_VERSION")) { strcpy(version_from_local_config, json["SOFTWARE_VERSION"]); }

#define setFromJSON(key)    if (json.containsKey(#key)) key = json[#key];
#define strcpyFromJSON(key) if (json.containsKey(#key)) strcpy(key, json[#key]);
					strcpyFromJSON(current_lang);
					strcpyFromJSON(wlanssid);
					strcpyFromJSON(wlanpwd);
					strcpyFromJSON(www_username);
					strcpyFromJSON(www_password);
					setFromJSON(www_basicauth_enabled);
					setFromJSON(dht_read);
					setFromJSON(ppd_read);
					setFromJSON(sds_read);
					setFromJSON(bmp_read);
					setFromJSON(bme280_read);
          setFromJSON(ds18b20_read);
					setFromJSON(gps_read);
					setFromJSON(send2dusti);
					setFromJSON(send2madavi);
					setFromJSON(send2sensemap);
					setFromJSON(send2lora);
					setFromJSON(send2csv);
					setFromJSON(auto_update);
					setFromJSON(has_display);
					setFromJSON(has_lcd1602);
					setFromJSON(debug);
					setFromJSON(sending_intervall_ms);
					setFromJSON(time_for_wifi_config);
					strcpyFromJSON(senseboxid);
					setFromJSON(send2custom);
					strcpyFromJSON(host_custom);
					strcpyFromJSON(url_custom);
					setFromJSON(port_custom);
					strcpyFromJSON(user_custom);
					strcpyFromJSON(pwd_custom);
					setFromJSON(send2influx);
					strcpyFromJSON(host_influx);
					strcpyFromJSON(url_influx);
					setFromJSON(port_influx);
					strcpyFromJSON(user_influx);
					strcpyFromJSON(pwd_influx);
#undef setFromJSON
#undef strcpyFromJSON
				} else {
					debug_out(F("failed to load json config"), DEBUG_ERROR, 1);
				}
			}
		} else {
			debug_out(F("config file not found ..."), DEBUG_ERROR, 1);
		}
	} else {
		debug_out(F("failed to mount FS"), DEBUG_ERROR, 1);
	}
#endif
}

/*****************************************************************
/* write config to spiffs                                        *
/*****************************************************************/
void writeConfig() {
#if defined(ESP8266)
	String json_string = "";
	debug_out(F("saving config..."), DEBUG_MIN_INFO, 1);

	json_string = "{";
#define copyToJSON_Bool(varname) json_string +="\""+String(#varname)+"\":"+(varname ? "true":"false")+",";
#define copyToJSON_Int(varname) json_string +="\""+String(#varname)+"\":"+String(varname)+",";
#define copyToJSON_String(varname) json_string +="\""+String(#varname)+"\":\""+String(varname)+"\",";
	copyToJSON_String(current_lang);
	copyToJSON_String(SOFTWARE_VERSION);
	copyToJSON_String(wlanssid);
	copyToJSON_String(wlanpwd);
	copyToJSON_String(www_username);
	copyToJSON_String(www_password);
	copyToJSON_Bool(www_basicauth_enabled);
	copyToJSON_Bool(dht_read);
	copyToJSON_Bool(ppd_read);
	copyToJSON_Bool(sds_read);
	copyToJSON_Bool(bmp_read);
	copyToJSON_Bool(bme280_read);
  copyToJSON_Bool(ds18b20_read);
	copyToJSON_Bool(gps_read);
	copyToJSON_Bool(send2dusti);
	copyToJSON_Bool(send2madavi);
	copyToJSON_Bool(send2sensemap);
	copyToJSON_Bool(send2lora);
	copyToJSON_Bool(send2csv);
	copyToJSON_Bool(auto_update);
	copyToJSON_Bool(has_display);
	copyToJSON_Bool(has_lcd1602);
	copyToJSON_String(debug);
	copyToJSON_String(sending_intervall_ms);
	copyToJSON_String(time_for_wifi_config);
	copyToJSON_String(senseboxid);
	copyToJSON_Bool(send2custom);
	copyToJSON_String(host_custom);
	copyToJSON_String(url_custom);
	copyToJSON_Int(port_custom);
	copyToJSON_String(user_custom);
	copyToJSON_String(pwd_custom);

	copyToJSON_Bool(send2influx);
	copyToJSON_String(host_influx);
	copyToJSON_String(url_influx);
	copyToJSON_Int(port_influx);
	copyToJSON_String(user_influx);
	copyToJSON_String(pwd_influx);
#undef copyToJSON_Bool
#undef copyToJSON_Int
#undef copyToJSON_String

	json_string.remove(json_string.length() - 1);
	json_string += "}";

	debug_out(json_string, DEBUG_MIN_INFO, 1);
	File configFile = SPIFFS.open("/config.json", "w");
	if (!configFile) {
		debug_out(F("failed to open config file for writing"), DEBUG_ERROR, 1);
	}

	configFile.print(json_string);
	debug_out(F("Config written: "), DEBUG_MIN_INFO, 0);
	debug_out(json_string, DEBUG_MIN_INFO, 1);
	configFile.close();
	config_needs_write = false;
	//end save
#endif
}

/*****************************************************************
/* Base64 encode user:password                                   *
/*****************************************************************/
void create_basic_auth_strings() {
	basic_auth_custom = "";
	if (strcmp(user_custom, "") != 0 || strcmp(pwd_custom, "") != 0) {
		basic_auth_custom = base64::encode(String(user_custom) + ":" + String(pwd_custom));
	}
	basic_auth_influx = "";
	if (strcmp(user_influx, "") != 0 || strcmp(pwd_influx, "") != 0) {
		basic_auth_influx = base64::encode(String(user_influx) + ":" + String(pwd_influx));
	}
}

/*****************************************************************
/* html helper functions                                         *
/*****************************************************************/

String make_header(const String& title) {
	String s = "";
	s += FPSTR(WEB_PAGE_HEADER);
	s.replace("{tt}", FPSTR(INTL_FEINSTAUBSENSOR));
	s.replace("{h}", FPSTR(INTL_UBERSICHT));
	if(title != " ") {
		s.replace("{n}", F("&raquo;"));
	} else {
		s.replace("{n}", "");
	}
	s.replace("{t}", title);
	s.replace("{id}", esp_chipid);
	s.replace("{mac}", WiFi.macAddress());
	s.replace("{fwt}", FPSTR(INTL_FIRMWARE));
	s.replace("{fw}", SOFTWARE_VERSION);
	return s;
}

String make_footer() {
	String s = "";
	s += FPSTR(WEB_PAGE_FOOTER);
	s.replace("{t}", FPSTR(INTL_ZURUCK_ZUR_STARTSEITE));
	return s;
}

String form_input(const String& name, const String& info, const String& value, const int length) {
	String s = F("<tr><td>{i} </td><td style='width:90%;'><input type='text' name='{n}' id='{n}' placeholder='{i}' value='{v}' maxlength='{l}'/></td></tr>");
	s.replace("{i}", info); s.replace("{n}", name); s.replace("{v}", value); s.replace("{l}", String(length));
	return s;
}

String form_password(const String& name, const String& info, const String& value, const int length) {
	String s = F("<tr><td>{i} </td><td style='width:90%;'><input type='password' name='{n}' id='{n}' placeholder='{i}' value='{v}' maxlength='{l}'/></td></tr>");
	s.replace("{i}", info); s.replace("{n}", name); s.replace("{v}", value); s.replace("{l}", String(length));
	return s;
}

String form_checkbox(const String& name, const String& info, const bool checked) {
	String s = F("<label for='{n}'><input type='checkbox' name='{n}' value='1' id='{n}' {c}/><input type='hidden' name='{n}' value='0' /> {i}</label><br/>");
	if (checked) {s.replace("{c}", F(" checked='checked'"));} else {s.replace("{c}", "");};
	s.replace("{i}", info); s.replace("{n}", name);
	return s;
}

String form_submit(const String& value) {
	String s = F("<tr><td>&nbsp;</td><td><input type='submit' name='submit' value='{v}' /></td></tr>");
	s.replace("{v}", value);
	return s;
}

String form_select_lang() {
	String s_select = F("selected='selected'");
	String s = F("<tr><td>{t}</td><td><select name='current_lang'><option value='DE' {s_DE}>Deutsch (DE)</option><option value='BG' {s_BG}>Bulgarian (BG)</option><option value='EN' {s_EN}>English (EN)</option><option value='ES' {s_ES}>Español (ES)</option><option value='FR' {s_FR}>Français (FR)</option><option value='IT' {s_IT}>Italiano (IT)</option><option value='NL' {s_NL}>Nederlands (NL)</option></select></td></tr>");

	s.replace("{t}", FPSTR(INTL_SPRACHE));
	if(String(current_lang) == "DE") {
		s.replace(F("{s_DE}"), s_select);
	} else if(String(current_lang) == "BG") {
		s.replace(F("{s_BG}"), s_select);
	} else if(String(current_lang) == "EN") {
		s.replace(F("{s_EN}"), s_select);
	} else if(String(current_lang) == "ES") {
		s.replace(F("{s_ES}"), s_select);
	} else if(String(current_lang) == "FR") {
		s.replace(F("{s_FR}"), s_select);
	} else if(String(current_lang) == "IT") {
		s.replace(F("{s_IT}"), s_select);
	} else if(String(current_lang) == "NL") {
		s.replace(F("{s_NL}"), s_select);
	}
	s.replace(F("{s_DE}"), "");
	s.replace(F("{s_BG}"), "");
	s.replace(F("{s_EN}"), "");
	s.replace(F("{s_ES}"), "");
	s.replace(F("{s_FR}"), "");
	s.replace(F("{s_NL}"), "");
	return s;
}

String tmpl(const String& patt, const String& value) {
	String s = F("{patt}");
	s.replace("{patt}", value); s.replace("{v}", value);
	return s;
}

String tmpl(const String& patt, const String& value1, const String& value2) {
	String s = F("{patt}");
	s.replace("{patt}", patt); s.replace("{v1}", value1); s.replace("{v2}", value2);
	return s;
}

String tmpl(const String& patt, const String& value1, const String& value2, const String& value3) {
	String s = F("{patt}");
	s.replace("{patt}", patt); s.replace("{v1}", value1); s.replace("{v2}", value2); s.replace("{v3}", value3);
	return s;
}

String line_from_value(const String& name, const String& value) {
	String s = F("<br>{n}: {v}");
	s.replace("{n}", name);
	s.replace("{v}", value);
	return s;
}

String table_row_from_value(const String& sensor, const String& param, const String& value, const String& unit) {
	String s = F("<tr><td>{s}</td><td>{p}</td><td class='r'>{v}&nbsp;{u}</td></tr>");
	s.replace("{s}", sensor); s.replace("{p}", param); s.replace("{v}", value); s.replace("{u}", unit);
	return s;
}

String wlan_ssid_to_table_row(const String& ssid, const String& encryption, const long rssi) {
	long rssi_temp = rssi;
	if (rssi_temp > -50) {rssi_temp = -50; }
	if (rssi_temp < -100) {rssi_temp = -100; }
	int quality = (rssi_temp + 100) * 2;
	String s = F("<tr><td><a href='#wlanpwd' onclick='setSSID(this)' style='background:none;color:blue;padding:5px;display:inline;'>{n}</a>&nbsp;{e}</a></td><td style='width:80%;vertical-align:middle;'>{v}%</td></tr>");
	s.replace("{n}", ssid); s.replace("{e}", encryption); s.replace("{v}", String(quality));
	return s;
}

String warning_first_cycle() {
	String s = FPSTR(INTL_ERSTER_MESSZYKLUS);
	s.replace("{v}", String(round((sending_intervall_ms - (act_milli - starttime)) / 1000.0)));
	return s;
}

/*****************************************************************
/* Webserver request auth: prompt for BasicAuth
 *
 * -Provide BasicAuth for all page contexts except /values and images
/*****************************************************************/
void webserver_request_auth() {
	debug_out(F("validate request auth..."), DEBUG_MIN_INFO, 1);
	if (www_basicauth_enabled) {
		if (!server.authenticate(www_username, www_password))
		{ return server.requestAuthentication(); }
	}
}

/*****************************************************************
/* Webserver root: show all options                              *
/*****************************************************************/
void webserver_root() {
	if (WiFi.status() != WL_CONNECTED) {
		server.sendHeader(F("Location"), F("http://192.168.4.1/config"));
		server.send(302, FPSTR(TXT_CONTENT_TYPE_TEXT_HTML), "");
	} else {
		webserver_request_auth();

		String page_content = "";
		last_page_load = millis();
		debug_out(F("output root page..."), DEBUG_MIN_INFO, 1);
		page_content = make_header(" ");
		page_content += FPSTR(WEB_ROOT_PAGE_CONTENT);
		page_content.replace("{t}", FPSTR(INTL_AKTUELLE_WERTE));
		page_content.replace(F("{karte}"), FPSTR(INTL_KARTE_DER_AKTIVEN_SENSOREN));
		page_content.replace(F("{conf}"), FPSTR(INTL_KONFIGURATION));
		page_content.replace(F("{conf_delete}"), FPSTR(INTL_KONFIGURATION_LOSCHEN));
		page_content.replace(F("{restart}"), FPSTR(INTL_SENSOR_NEU_STARTEN));
		page_content += make_footer();
		server.send(200, FPSTR(TXT_CONTENT_TYPE_TEXT_HTML), page_content);
	}
}

/*****************************************************************
/* Webserver root: show all options                              *
/*****************************************************************/
void webserver_config() {
	webserver_request_auth();

	String page_content = "";
	last_page_load = millis();

	debug_out(F("output config page ..."), DEBUG_MIN_INFO, 1);
	page_content += make_header(FPSTR(INTL_KONFIGURATION));
	page_content += FPSTR(WEB_CONFIG_SCRIPT);
	if (server.method() == HTTP_GET) {
		page_content += F("<form method='POST' action='/config' style='width: 100%;'><b>");
		page_content += FPSTR(INTL_WLAN_DATEN);
		page_content += F("</b><br/>");
		debug_out(F("output config page 1"), DEBUG_MIN_INFO, 1);
		if (WiFi.status() != WL_CONNECTED) {  // scan for wlan ssids
			page_content += F("<div id='wifilist'>");
			page_content += FPSTR(INTL_WLAN_LISTE);
			page_content += F("</div><br/>");
		}
		page_content += F("<table>");
		page_content += form_input(F("wlanssid"), F("WLAN"), wlanssid, 64);
		page_content += form_password(F("wlanpwd"), FPSTR(INTL_PASSWORT), wlanpwd, 64);
		page_content += form_submit(FPSTR(INTL_SPEICHERN));
		page_content += F("</table><br/><hr/><b>");

		page_content += FPSTR(INTL_AB_HIER_NUR_ANDERN);
		page_content += F("</b><br/><br/><b>");
		page_content += FPSTR(INTL_BASICAUTH);
		page_content += F("</b><br/>");
		page_content += F("<table>");
		page_content += form_input(F("www_username"), FPSTR(INTL_BENUTZER), www_username, 64);
		page_content += form_password(F("www_password"), FPSTR(INTL_PASSWORT), www_password, 64);
		page_content += form_checkbox(F("www_basicauth_enabled"), FPSTR(INTL_BASICAUTH), www_basicauth_enabled);
		page_content += form_submit(FPSTR(INTL_SPEICHERN));

		page_content += F("</table><br/><b>APIs</b><br/>");
		page_content += form_checkbox(F("send2dusti"), F("API Luftdaten.info"), send2dusti);
		page_content += form_checkbox(F("send2madavi"), F("API Madavi.de"), send2madavi);
		page_content += F("<br/><b>");
		page_content += FPSTR(INTL_SENSOREN);
		page_content += F("</b><br/>");
		page_content += form_checkbox(F("sds_read"), FPSTR(INTL_SDS011), sds_read);
		page_content += form_checkbox(F("dht_read"), FPSTR(INTL_DHT22), dht_read);
		page_content += form_checkbox(F("ppd_read"), FPSTR(INTL_PPD42NS), ppd_read);
		page_content += form_checkbox(F("bmp_read"), FPSTR(INTL_BMP180), bmp_read);
		page_content += form_checkbox(F("bme280_read"), FPSTR(INTL_BME280), bme280_read);
    page_content += form_checkbox(F("ds18b20_read"), FPSTR(INTL_DS18B20), ds18b20_read);
		page_content += form_checkbox(F("gps_read"), F("GPS (NEO 6M)"), gps_read);
		page_content += F("<br/><b>"); page_content += FPSTR(INTL_WEITERE_EINSTELLUNGEN); page_content += F("</b><br/>");
		page_content += form_checkbox(F("auto_update"), FPSTR(INTL_AUTO_UPDATE), auto_update);
		page_content += form_checkbox(F("has_display"), FPSTR(INTL_DISPLAY), has_display);
		page_content += form_checkbox(F("has_lcd1602"), FPSTR(INTL_LCD1602), has_lcd1602);
		page_content += F("<table>");
		page_content += form_select_lang();
		page_content += form_input(F("debug"), FPSTR(INTL_DEBUG_LEVEL), String(debug), 5);
		page_content += form_input(F("sending_intervall_ms"), FPSTR(INTL_MESSINTERVALL), String(sending_intervall_ms / 1000), 5);
		page_content += form_input(F("time_for_wifi_config"), FPSTR(INTL_DAUER_ROUTERMODUS), String(time_for_wifi_config / 1000), 5);
		page_content += F("</table><br/><b>"); page_content += FPSTR(INTL_WEITERE_APIS); page_content += F("</b><br/><br/>");
		page_content += form_checkbox(F("send2sensemap"), tmpl(FPSTR(INTL_SENDEN_AN), F("OpenSenseMap")), send2sensemap);
		page_content += F("<table>");
		page_content += form_input(F("senseboxid"), F("senseBox-ID: "), senseboxid, 50);
		page_content += F("</table><br/>");
		page_content += form_checkbox(F("send2custom"), FPSTR(INTL_AN_EIGENE_API_SENDEN), send2custom);
		page_content += F("<table>");
		page_content += form_input(F("host_custom"), FPSTR(INTL_SERVER), host_custom, 50);
		page_content += form_input(F("url_custom"), FPSTR(INTL_PFAD), url_custom, 50);
		page_content += form_input(F("port_custom"), FPSTR(INTL_PORT), String(port_custom), 30);
		page_content += form_input(F("user_custom"), FPSTR(INTL_BENUTZER), user_custom, 50);
		page_content += form_input(F("pwd_custom"), FPSTR(INTL_PASSWORT), pwd_custom, 50);
		page_content += F("</table><br/>");
		page_content += form_checkbox(F("send2influx"), tmpl(FPSTR(INTL_SENDEN_AN), F("InfluxDB")), send2influx);
		page_content += F("<table>");
		page_content += form_input(F("host_influx"), FPSTR(INTL_SERVER), host_influx, 50);
		page_content += form_input(F("url_influx"), FPSTR(INTL_PFAD), url_influx, 50);
		page_content += form_input(F("port_influx"), FPSTR(INTL_PORT), String(port_influx), 30);
		page_content += form_input(F("user_influx"), FPSTR(INTL_BENUTZER), user_influx, 50);
		page_content += form_input(F("pwd_influx"), FPSTR(INTL_PASSWORT), pwd_influx, 50);
		page_content += form_submit(FPSTR(INTL_SPEICHERN));
		page_content += F("</table><br/>");
		page_content += F("<br/></form>");
		if (WiFi.status() != WL_CONNECTED) {  // scan for wlan ssids
			page_content += F("<script>load_wifi_list();</script>");
		}
	} else {

#define readCharParam(param) if (server.hasArg(#param)){ server.arg(#param).toCharArray(param, sizeof(param)); }
#define readBoolParam(param) if (server.hasArg(#param)){ param = server.arg(#param) == "1"; }
#define readIntParam(param)  if (server.hasArg(#param)){ int val = server.arg(#param).toInt(); if (val != 0){ param = val; }}
#define readTimeParam(param)  if (server.hasArg(#param)){ int val = server.arg(#param).toInt(); if (val != 0){ param = val*1000; }}

		if (server.hasArg(F("wlanssid")) && server.arg(F("wlanssid")) != "") {
			readCharParam(wlanssid);
			readCharParam(wlanpwd);
		}
		readCharParam(current_lang);
		readCharParam(www_username);
		readCharParam(www_password);
		readBoolParam(www_basicauth_enabled);
		readBoolParam(send2dusti);
		readBoolParam(send2madavi);
		readBoolParam(send2sensemap);
		readBoolParam(dht_read);
		readBoolParam(sds_read);
		readBoolParam(ppd_read);
		readBoolParam(bmp_read);
		readBoolParam(bme280_read);
    readBoolParam(ds18b20_read);
		readBoolParam(gps_read);
		readBoolParam(auto_update);
		readBoolParam(has_display);
		readBoolParam(has_lcd1602);
		readIntParam(debug);
		readTimeParam(sending_intervall_ms);
		readTimeParam(time_for_wifi_config);

		readCharParam(senseboxid);

		readBoolParam(send2custom);
		readCharParam(host_custom);
		readCharParam(url_custom);
		readIntParam(port_custom);
		readCharParam(user_custom);
		readCharParam(pwd_custom);

		readBoolParam(send2influx);
		readCharParam(host_influx);
		readCharParam(url_influx);
		readIntParam(port_influx);
		readCharParam(user_influx);
		readCharParam(pwd_influx);

#undef readCharParam
#undef readBoolParam
#undef readIntParam

		config_needs_write = true;

		page_content += line_from_value(tmpl(FPSTR(INTL_SENDEN_AN), F("Luftdaten.info")), String(send2dusti));
		page_content += line_from_value(tmpl(FPSTR(INTL_SENDEN_AN), F("Madavi")), String(send2madavi));
		page_content += line_from_value(tmpl(FPSTR(INTL_LESE), "DHT"), String(dht_read));
		page_content += line_from_value(tmpl(FPSTR(INTL_LESE), "SDS"), String(sds_read));
		page_content += line_from_value(tmpl(FPSTR(INTL_LESE), "PPD"), String(ppd_read));
		page_content += line_from_value(tmpl(FPSTR(INTL_LESE), "BMP180"), String(bmp_read));
		page_content += line_from_value(tmpl(FPSTR(INTL_LESE), "BME280"), String(bme280_read));
    page_content += line_from_value(tmpl(FPSTR(INTL_LESE), "DS18B20"), String(ds18b20_read));
		page_content += line_from_value(tmpl(FPSTR(INTL_LESE), "GPS"), String(gps_read));
		page_content += line_from_value(FPSTR(INTL_AUTO_UPDATE), String(auto_update));
		page_content += line_from_value(FPSTR(INTL_DISPLAY), String(has_display));
		page_content += line_from_value(FPSTR(INTL_LCD1602), String(has_lcd1602));
		page_content += line_from_value(FPSTR(INTL_DEBUG_LEVEL), String(debug));
		page_content += line_from_value(FPSTR(INTL_MESSINTERVALL), String(sending_intervall_ms));
		page_content += line_from_value(tmpl(FPSTR(INTL_SENDEN_AN), "opensensemap"), String(send2sensemap));
		page_content += F("<br/>senseBox-ID "); page_content += senseboxid;
		page_content += F("<br/><br/>Eigene API: "); page_content += String(send2custom);
		page_content += line_from_value(FPSTR(INTL_SERVER), host_custom);
		page_content += line_from_value(FPSTR(INTL_PFAD), url_custom);
		page_content += line_from_value(FPSTR(INTL_PORT), String(port_custom));
		page_content += line_from_value(FPSTR(INTL_BENUTZER), user_custom);
		page_content += line_from_value(FPSTR(INTL_PASSWORT), pwd_custom);
		page_content += F("<br/><br/>InfluxDB: "); page_content += String(send2influx);
		page_content += line_from_value(FPSTR(INTL_SERVER), host_influx);
		page_content += line_from_value(FPSTR(INTL_PFAD), url_influx);
		page_content += line_from_value(FPSTR(INTL_PORT), String(port_influx));
		page_content += line_from_value(FPSTR(INTL_BENUTZER), user_influx);
		page_content += line_from_value(FPSTR(INTL_PASSWORT), pwd_influx);
		if (wificonfig_loop) {
			page_content += F("<br/><br/>"); page_content += FPSTR(INTL_GERAT_WIRD_NEU_GESTARTET);
		} else {
			page_content += F("<br/><br/><a href='/reset?confirm=yes'>"); page_content += FPSTR(INTL_GERAT_NEU_STARTEN); page_content += F("?</a>");
		}
	}
	page_content += make_footer();
	server.send(200, FPSTR(TXT_CONTENT_TYPE_TEXT_HTML), page_content);
}

/*****************************************************************
/* Webserver root: show latest values                            *
/*****************************************************************/
void webserver_wifi() {
	WiFi.disconnect();
	debug_out(F("scan for wifi networks..."), DEBUG_MIN_INFO, 1);
	int n = WiFi.scanNetworks();
	debug_out(F("wifi networks found: "), DEBUG_MIN_INFO, 0);
	debug_out(String(n), DEBUG_MIN_INFO, 1);
	String page_content = "";
	if (n == 0) {
		page_content += F("<br/>");
		page_content += FPSTR(INTL_KEINE_NETZWERKE);
		page_content += F("<br/>");
	} else {
		page_content += FPSTR(INTL_NETZWERKE_GEFUNDEN);
		page_content += String(n);
		page_content += F("<br/>");
		int indices[n];
		debug_out(F("output config page 2"), DEBUG_MIN_INFO, 1);
		for (int i = 0; i < n; i++) { indices[i] = i; }
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				if (WiFi.RSSI(indices[j]) > WiFi.RSSI(indices[i])) {
					std::swap(indices[i], indices[j]);
				}
			}
		}
		String cssid;
		debug_out(F("output config page 3"), DEBUG_MIN_INFO, 1);
		for (int i = 0; i < n; i++) {
			if (indices[i] == -1) { continue; }
			cssid = WiFi.SSID(indices[i]);
			for (int j = i + 1; j < n; j++) {
				if (cssid == WiFi.SSID(indices[j])) {
					indices[j] = -1; // set dup aps to index -1
				}
			}
		}
		page_content += F("<br/><table>");
		//if(n > 30) n=30;
		for (int i = 0; i < n; ++i) {
			if (indices[i] == -1) { continue; }
			// Print SSID and RSSI for each network found
			page_content += wlan_ssid_to_table_row(WiFi.SSID(indices[i]), ((WiFi.encryptionType(indices[i]) == ENC_TYPE_NONE) ? " " : "*"), WiFi.RSSI(indices[i]));
		}
		page_content += F("</table><br/><br/>");
	}
	server.send(200, FPSTR(TXT_CONTENT_TYPE_TEXT_HTML), page_content);
}
/*****************************************************************
/* Webserver root: show latest values                            *
/*****************************************************************/
void webserver_values() {
#if defined(ESP8266)
	if (WiFi.status() != WL_CONNECTED) {
		server.sendHeader(F("Location"), F("http://192.168.4.1/config"));
		server.send(302, FPSTR(TXT_CONTENT_TYPE_TEXT_HTML), "");
	} else {
		String page_content = "";
		String empty_row = F("<tr><td colspan='3'>&nbsp;</td></tr>");
		last_page_load = millis();
		long signal_strength = WiFi.RSSI();
		if (signal_strength > -50) {signal_strength = -50; }
		if (signal_strength < -100) {signal_strength = -100; }
		int signal_quality = (signal_strength + 100) * 2;
		debug_out(F("output values to web page..."), DEBUG_MIN_INFO, 1);
		page_content += make_header(FPSTR(INTL_AKTUELLE_WERTE));
		if (first_cycle) {
			page_content += F("<b style='color: red'>");
			page_content += warning_first_cycle();
			page_content += F("</b><br/><br/>");
		}
		page_content += F("<table cellspacing='0' border='1' cellpadding='5'>");
		page_content += tmpl(F("<tr><th>{v1}</th><th>{v2}</th><th>{v3}</th>"), FPSTR(INTL_SENSOR), FPSTR(INTL_PARAMETER), FPSTR(INTL_WERT));
		if (ppd_read) {
			page_content += empty_row;
			page_content += table_row_from_value("PPD42NS", "PM1",  last_value_PPD_P1, FPSTR(INTL_PARTIKEL_LITER));
			page_content += table_row_from_value("PPD42NS", "PM2.5", last_value_PPD_P2, FPSTR(INTL_PARTIKEL_LITER));
		}
		if (sds_read) {
			page_content += empty_row;
			page_content += table_row_from_value("SDS011", "PM2.5", last_value_SDS_P2, "µg/m³");
			page_content += table_row_from_value("SDS011", "PM10", last_value_SDS_P1, "µg/m³");
		}
		if (dht_read) {
			page_content += empty_row;
			page_content += table_row_from_value("DHT22", FPSTR(INTL_TEMPERATUR), last_value_DHT_T, "°C");
			page_content += table_row_from_value("DHT22", FPSTR(INTL_LUFTFEUCHTE), last_value_DHT_H, "%");
		}
		if (bmp_read) {
			page_content += empty_row;
			page_content += table_row_from_value("BMP180", FPSTR(INTL_TEMPERATUR), last_value_BMP_T, "°C");
			page_content += table_row_from_value("BMP180", FPSTR(INTL_LUFTDRUCK), Float2String(last_value_BMP_P.toFloat() / 100.0), "hPa");
		}
		if (bme280_read) {
			page_content += empty_row;
			page_content += table_row_from_value("BME280", FPSTR(INTL_TEMPERATUR), last_value_BME280_T, "°C");
			page_content += table_row_from_value("BME280", FPSTR(INTL_LUFTFEUCHTE), last_value_BME280_H, "%");
			page_content += table_row_from_value("BME280", FPSTR(INTL_LUFTDRUCK),  Float2String(last_value_BME280_P.toFloat() / 100.0), "hPa");
		}
    if (ds18b20_read) {
      page_content += empty_row;
      page_content += table_row_from_value("DS18B20", FPSTR(INTL_TEMPERATUR), last_value_DS18B20_T, "°C");
    }

		page_content += empty_row;
		page_content += table_row_from_value("WiFi", FPSTR(INTL_SIGNAL),  String(signal_strength), "dBm");
		page_content += table_row_from_value("WiFi", FPSTR(INTL_QUALITAT), String(signal_quality), "%");
		page_content += F("</table>");
		page_content += make_footer();
		server.send(200, FPSTR(TXT_CONTENT_TYPE_TEXT_HTML), page_content);
	}
#endif
}

/*****************************************************************
/* Webserver set debug level                                     *
/*****************************************************************/
void webserver_debug_level() {
	webserver_request_auth();

	String page_content = "";
	String message_string = F("<h3>{v1} {v2}.</h3>");
	last_page_load = millis();
	debug_out(F("output change debug level page..."), DEBUG_MIN_INFO, 1);
	page_content += make_header(FPSTR(INTL_DEBUG_LEVEL));

	if (server.hasArg("level")) {
		switch (server.arg("level").toInt()) {
		case (0): debug = 0; page_content += tmpl(message_string, FPSTR(INTL_SETZE_DEBUG_AUF), FPSTR(INTL_NONE)); break;
		case (1): debug = 1; page_content += tmpl(message_string, FPSTR(INTL_SETZE_DEBUG_AUF), FPSTR(INTL_ERROR)); break;
		case (2): debug = 2; page_content += tmpl(message_string, FPSTR(INTL_SETZE_DEBUG_AUF), FPSTR(INTL_WARNING)); break;
		case (3): debug = 3; page_content += tmpl(message_string, FPSTR(INTL_SETZE_DEBUG_AUF), FPSTR(INTL_MIN_INFO)); break;
		case (4): debug = 4; page_content += tmpl(message_string, FPSTR(INTL_SETZE_DEBUG_AUF), FPSTR(INTL_MED_INFO)); break;
		case (5): debug = 5; page_content += tmpl(message_string, FPSTR(INTL_SETZE_DEBUG_AUF), FPSTR(INTL_MAX_INFO)); break;
		}
	}
	page_content += make_footer();
	server.send(200, FPSTR(TXT_CONTENT_TYPE_TEXT_HTML), page_content);
}

/*****************************************************************
/* Webserver remove config                                       *
/*****************************************************************/
void webserver_removeConfig() {
	webserver_request_auth();

	String page_content = "";
	String message_string = F("<h3>{v}.</h3>");
	last_page_load = millis();
	debug_out(F("output remove config page..."), DEBUG_MIN_INFO, 1);
	page_content += make_header(FPSTR(INTL_CONFIG_LOSCHEN));

	if (server.method() == HTTP_GET) {
		page_content += FPSTR(WEB_REMOVE_CONFIG_CONTENT);
		page_content.replace("{t}", FPSTR(INTL_KONFIGURATION_WIRKLICH_LOSCHEN));
		page_content.replace("{b}", FPSTR(INTL_LOSCHEN));
		page_content.replace("{c}", FPSTR(INTL_ABBRECHEN));

	} else {
#if defined(ESP8266)
		if (SPIFFS.exists("/config.json")) {	//file exists
			debug_out(F("removing config.json..."), DEBUG_MIN_INFO, 1);
			if (SPIFFS.remove("/config.json")) {
				page_content += tmpl(message_string, FPSTR(INTL_CONFIG_GELOSCHT));
			} else {
				page_content += tmpl(message_string, FPSTR(INTL_CONFIG_KONNTE_NICHT_GELOSCHT_WERDEN));
			}
		} else {
			page_content += tmpl(message_string, FPSTR(INTL_CONFIG_NICHT_GEFUNDEN));
		}
#endif
	}
	page_content += make_footer();
	server.send(200, FPSTR(TXT_CONTENT_TYPE_TEXT_HTML), page_content);
}

/*****************************************************************
/* Webserver reset NodeMCU                                       *
/*****************************************************************/
void webserver_reset() {
	webserver_request_auth();

	String page_content = "";
	last_page_load = millis();
	debug_out(F("output reset NodeMCU page..."), DEBUG_MIN_INFO, 1);
	page_content += make_header(FPSTR(INTL_SENSOR_NEU_STARTEN));

	if (server.method() == HTTP_GET) {
		page_content += FPSTR(WEB_RESET_CONTENT);
		page_content.replace("{t}", FPSTR(INTL_SENSOR_WIRKLICH_NEU_STARTEN));
		page_content.replace("{b}", FPSTR(INTL_NEU_STARTEN));
		page_content.replace("{c}", FPSTR(INTL_ABBRECHEN));
	} else {
#if defined(ESP8266)
		ESP.restart();
#endif
	}
	page_content += make_footer();
	server.send(200, FPSTR(TXT_CONTENT_TYPE_TEXT_HTML), page_content);
}

/*****************************************************************
/* Webserver data.json                                           *
/*****************************************************************/
void webserver_data_json() {
	debug_out(F("output data json..."), DEBUG_MIN_INFO, 1);
	server.send(200, FPSTR(TXT_CONTENT_TYPE_JSON), last_data_string);
}

/*****************************************************************
/* Webserver Images                                              *
/*****************************************************************/
void webserver_images() {
	if (server.hasArg("name")) {
		if (server.arg("name") == "luftdaten_logo") {
			debug_out(F("output luftdaten.info logo..."), DEBUG_MIN_INFO, 1);
			server.send(200, FPSTR(TXT_CONTENT_TYPE_IMAGE_SVG), FPSTR(LUFTDATEN_INFO_LOGO_SVG));
		} else if (server.arg("name") == "cfg_logo") {
			debug_out(F("output codefor.de logo..."), DEBUG_MIN_INFO, 1);
			server.send(200, FPSTR(TXT_CONTENT_TYPE_IMAGE_SVG), FPSTR(CFG_LOGO_SVG));
		} else {
			webserver_not_found();
		}
	} else {
		webserver_not_found();
	}
//		server.client().setNoDelay(1);
//		server.sendHeader(F("Content-Encoding"),"gzip");
//		server.send_P(200, TXT_CONTENT_TYPE_IMAGE_SVG, CFG_LOGO_SVG_GZIP, CFG_LOGO_SVG_GZIP_LEN);
//		server.client().setNoDelay(0);
}

/*****************************************************************
/* Webserver page not found                                      *
/*****************************************************************/
void webserver_not_found() {
	last_page_load = millis();
	debug_out(F("output not found page..."), DEBUG_MIN_INFO, 1);
	server.send(404, FPSTR(TXT_CONTENT_TYPE_TEXT_PLAIN), F("Not found."));
}

/*****************************************************************
/* Webserver setup                                               *
/*****************************************************************/
void setup_webserver() {
	server_name  = F("Feinstaubsensor-");
	server_name += esp_chipid;

	server.on("/", webserver_root);
	server.on("/config", webserver_config);
	server.on("/wifi", webserver_wifi);
	server.on("/values", webserver_values);
	server.on("/generate_204", webserver_config);
	server.on("/fwlink", webserver_config);
	server.on("/debug", webserver_debug_level);
	server.on("/removeConfig", webserver_removeConfig);
	server.on("/reset", webserver_reset);
	server.on("/data.json", webserver_data_json);
	server.on("/images", webserver_images);
	server.onNotFound(webserver_not_found);

	debug_out(F("Starte Webserver... "), DEBUG_MIN_INFO, 0);
	debug_out(IPAddress2String(WiFi.localIP()), DEBUG_MIN_INFO, 1);
	server.begin();
}

/*****************************************************************
/* WifiConfig                                                    *
/*****************************************************************/
void wifiConfig() {
#if defined(ESP8266)
	const char *softAP_password = "";
	const byte DNS_PORT = 53;
	int retry_count = 0;
	DNSServer dnsServer;
	IPAddress apIP(192, 168, 4, 1);
	IPAddress netMsk(255, 255, 255, 0);

	debug_out(F("Starting WiFiManager"), DEBUG_MIN_INFO, 1);
	debug_out(F("AP ID: Feinstaubsensor-"), DEBUG_MIN_INFO, 0);
	debug_out(String(ESP.getChipId()), DEBUG_MIN_INFO, 1);

	wificonfig_loop = true;

	WiFi.softAPConfig(apIP, apIP, netMsk);
	WiFi.softAP(server_name.c_str(), "");

	dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
	dnsServer.start(DNS_PORT, "*", apIP);

	// 10 minutes timeout for wifi config
	last_page_load = millis();
	while (((millis() - last_page_load) < time_for_wifi_config) && (! config_needs_write)) {
		dnsServer.processNextRequest();
		server.handleClient();
		wdt_reset(); // nodemcu is alive
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

	dnsServer.stop();

	delay(100);

	debug_out(F("Connecting to "), DEBUG_MIN_INFO, 0);
	debug_out(wlanssid, DEBUG_MIN_INFO, 1);

	WiFi.begin(wlanssid, wlanpwd);

	while ((WiFi.status() != WL_CONNECTED) && (retry_count < 20)) {
		delay(500);
		debug_out(".", DEBUG_MIN_INFO, 0);
		retry_count++;
	}
	debug_out("", DEBUG_MIN_INFO, 1);


	debug_out(F("------ Result from Webconfig ------"), DEBUG_MIN_INFO, 1);
	debug_out(F("WLANSSID: "), DEBUG_MIN_INFO, 0); debug_out(wlanssid, DEBUG_MIN_INFO, 1);
	debug_out(F("DHT_read: "), DEBUG_MIN_INFO, 0); debug_out(String(dht_read), DEBUG_MIN_INFO, 1);
	debug_out(F("PPD_read: "), DEBUG_MIN_INFO, 0); debug_out(String(ppd_read), DEBUG_MIN_INFO, 1);
	debug_out(F("SDS_read: "), DEBUG_MIN_INFO, 0); debug_out(String(sds_read), DEBUG_MIN_INFO, 1);
	debug_out(F("BMP_read: "), DEBUG_MIN_INFO, 0); debug_out(String(bmp_read), DEBUG_MIN_INFO, 1);
  debug_out(F("DS18B20_read: "), DEBUG_MIN_INFO, 0); debug_out(String(ds18b20_read), DEBUG_MIN_INFO, 1);
	debug_out(F("Dusti: "), DEBUG_MIN_INFO, 0); debug_out(String(send2dusti), DEBUG_MIN_INFO, 1);
	debug_out(F("Madavi: "), DEBUG_MIN_INFO, 0); debug_out(String(send2madavi), DEBUG_MIN_INFO, 1);
	debug_out(F("CSV: "), DEBUG_MIN_INFO, 0); debug_out(String(send2csv), DEBUG_MIN_INFO, 1);
	debug_out(F("Autoupdate: "), DEBUG_MIN_INFO, 0); debug_out(String(auto_update), DEBUG_MIN_INFO, 1);
	debug_out(F("Display: "), DEBUG_MIN_INFO, 0); debug_out(String(has_display), DEBUG_MIN_INFO, 1);
	debug_out(F("LCD 1602: "), DEBUG_MIN_INFO, 0); debug_out(String(has_lcd1602), DEBUG_MIN_INFO, 1);
	debug_out(F("Debug: "), DEBUG_MIN_INFO, 0); debug_out(String(debug), DEBUG_MIN_INFO, 1);
	debug_out(F("------"), DEBUG_MIN_INFO, 1);
	debug_out(F("Restart needed ..."), DEBUG_MIN_INFO, 1);
	wificonfig_loop = false;
	restart_needed = true;
#endif
}

/*****************************************************************
/* WiFi auto connecting script                                   *
/*****************************************************************/
void connectWifi() {
#if defined(ESP8266)
	int retry_count = 0;
	debug_out(String(WiFi.status()), DEBUG_MIN_INFO, 1);
	WiFi.mode(WIFI_STA);
	WiFi.begin(wlanssid, wlanpwd); // Start WiFI

	debug_out(F("Connecting to "), DEBUG_MIN_INFO, 0);
	debug_out(wlanssid, DEBUG_MIN_INFO, 1);

	while ((WiFi.status() != WL_CONNECTED) && (retry_count < 40)) {
		delay(500);
		debug_out(".", DEBUG_MIN_INFO, 0);
		retry_count++;
	}
	debug_out("", DEBUG_MIN_INFO, 1);
	if (WiFi.status() != WL_CONNECTED) {
		display_debug("AP ID: Feinstaubsensor-" + esp_chipid + " - IP: 192.168.4.1");
		wifiConfig();
		if (WiFi.status() != WL_CONNECTED) {
			retry_count = 0;
			while ((WiFi.status() != WL_CONNECTED) && (retry_count < 20)) {
				delay(500);
				debug_out(".", DEBUG_MIN_INFO, 0);
				retry_count++;
			}
			debug_out("", DEBUG_MIN_INFO, 1);
		}
	}
	WiFi.softAPdisconnect(true);
	debug_out(F("WiFi connected\nIP address: "), DEBUG_MIN_INFO, 0);
	debug_out(IPAddress2String(WiFi.localIP()), DEBUG_MIN_INFO, 1);
#endif
}

/*****************************************************************
/* send data to rest api                                         *
/*****************************************************************/
void sendData(const String& data, const int pin, const char* host, const int httpPort, const char* url, const char* basic_auth_string, const String& contentType) {
#if defined(ESP8266)

	debug_out(F("Start connecting to "), DEBUG_MIN_INFO, 0);
	debug_out(host, DEBUG_MIN_INFO, 1);

	String request_head = F("POST "); request_head += String(url); request_head += F(" HTTP/1.1\r\n");
	request_head += F("Host: "); request_head += String(host) + "\r\n";
	request_head += F("Content-Type: "); request_head += contentType + "\r\n";
	if (basic_auth_string != "") { request_head += F("Authorization: Basic "); request_head += String(basic_auth_string) + "\r\n";}
	request_head += F("X-PIN: "); request_head += String(pin) + "\r\n";
	request_head += F("X-Sensor: esp8266-"); request_head += esp_chipid + "\r\n";
	request_head += F("Content-Length: "); request_head += String(data.length(), DEC) + "\r\n";
	request_head += F("Connection: close\r\n\r\n");

	// Use WiFiClient class to create TCP connections

	if (httpPort == 443) {

		WiFiClientSecure client_s;

		client_s.setNoDelay(true);
		client_s.setTimeout(20000);

		if (!client_s.connect(host, httpPort)) {
			debug_out(F("connection failed"), DEBUG_ERROR, 1);
			return;
		}

		debug_out(F("Requesting URL: "), DEBUG_MIN_INFO, 0);
		debug_out(url, DEBUG_MIN_INFO, 1);
		debug_out(esp_chipid, DEBUG_MIN_INFO, 1);
		debug_out(data, DEBUG_MIN_INFO, 1);

		// send request to the server

		client_s.print(request_head);

		client_s.println(data);

		delay(10);

		// Read reply from server and print them
		while(client_s.available()) {
			char c = client_s.read();
			debug_out(String(c), DEBUG_MAX_INFO, 0);
		}

		debug_out(F("\nclosing connection\n------\n\n"), DEBUG_MIN_INFO, 1);

	} else {

		WiFiClient client;

		client.setNoDelay(true);
		client.setTimeout(20000);

		if (!client.connect(host, httpPort)) {
			debug_out(F("connection failed"), DEBUG_ERROR, 1);
			return;
		}

		debug_out(F("Requesting URL: "), DEBUG_MIN_INFO, 0);
		debug_out(url, DEBUG_MIN_INFO, 1);
		debug_out(esp_chipid, DEBUG_MIN_INFO, 1);
		debug_out(data, DEBUG_MIN_INFO, 1);

		client.print(request_head);

		client.println(data);

		delay(10);

		// Read reply from server and print them
		while(client.available()) {
			char c = client.read();
			debug_out(String(c), DEBUG_MAX_INFO, 0);
		}

		debug_out(F("\nclosing connection\n------\n\n"), DEBUG_MIN_INFO, 1);

	}

	debug_out(F("End connecting to "), DEBUG_MIN_INFO, 0);
	debug_out(host, DEBUG_MIN_INFO, 1);

	wdt_reset(); // nodemcu is alive
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

	debug_out(F("Start connecting to LoRa gateway"), DEBUG_MIN_INFO, 1);

	debug_out(F("data.length(): "), DEBUG_MAX_INFO, 0);
	debug_out(String(data.length()), DEBUG_MAX_INFO, 1);

	if (manager.sendtoWait(message_start, sizeof(message_start), SERVER_ADDRESS)) {
		// Now wait for a reply from the server
		uint8_t len = sizeof(buf);
		uint8_t from;
		if (manager.recvfromAckTimeout(buf, &len, 2000, &from)) {
			debug_out(txt_got_reply_from, DEBUG_MAX_INFO, 0);
			debug_out(String(from, HEX), DEBUG_MAX_INFO, 1);
		} else {
			debug_out(txt_no_reply, DEBUG_MIN_INFO, 1);
		}
	} else
	{ debug_out(txt_sentToWait_failed, DEBUG_MIN_INFO, 1); }

	while ((counter * (RH_RF69_MAX_MESSAGE_LEN - 1)) < data.length() + 1) {

		part2send = data.substring(counter * (RH_RF69_MAX_MESSAGE_LEN - 1), (counter * (RH_RF69_MAX_MESSAGE_LEN - 1) + (RH_RF69_MAX_MESSAGE_LEN - 1) <= (data.length() + 1) ? counter * (RH_RF69_MAX_MESSAGE_LEN - 1) + (RH_RF69_MAX_MESSAGE_LEN - 1) : (data.length() + 1) ) ) + "\0";

		debug_out("Data part: ", DEBUG_MAX_INFO, 0);
		debug_out(part2send, DEBUG_MAX_INFO, 1);
		debug_out("part2send.length(): ", DEBUG_MAX_INFO, 0);
		debug_out(String(part2send.length()), DEBUG_MAX_INFO, 1);

		if (manager.sendtoWait((uint8_t*)(part2send.c_str()), part2send.length(), SERVER_ADDRESS)) {
			// Now wait for a reply from the server
			uint8_t len = sizeof(buf);
			uint8_t from;
			if (manager.recvfromAckTimeout(buf, &len, 2000, &from)) {
				debug_out(txt_got_reply_from, DEBUG_MAX_INFO, 0);
				debug_out(String(from, HEX), DEBUG_MAX_INFO, 1);
			} else {
				debug_out(txt_no_reply, DEBUG_MIN_INFO, 1);
			}
		} else
		{ debug_out(txt_sentToWait_failed, DEBUG_MIN_INFO, 1); }

		counter++;
	}

	if (manager.sendtoWait(message_end, sizeof(message_end), SERVER_ADDRESS)) {
		// Now wait for a reply from the server
		uint8_t len = sizeof(buf);
		uint8_t from;
		if (manager.recvfromAckTimeout(buf, &len, 2000, &from)) {
			debug_out(txt_got_reply_from, DEBUG_MAX_INFO, 0);
			debug_out(String(from, HEX), DEBUG_MAX_INFO, 1);
		} else {
			debug_out(txt_no_reply, DEBUG_MIN_INFO, 1);
		}
	} else
	{ debug_out(txt_sentToWait_failed, DEBUG_MIN_INFO, 1); }

	debug_out(F("\nclosing connection\n------\n\n"), DEBUG_MIN_INFO, 1);

	debug_out(F("End connecting to LoRa gateway"), DEBUG_MIN_INFO, 1);

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
		data_4_influxdb += esp_chipid + " ";
		for (int i = 0; i < json2data["sensordatavalues"].size() - 1; i++) {
			tmp_str = jsonBuffer.strdup(json2data["sensordatavalues"][i]["value_type"].as<char*>());
			data_4_influxdb += tmp_str + "=";
			tmp_str = jsonBuffer.strdup(json2data["sensordatavalues"][i]["value"].as<char*>());
			data_4_influxdb += tmp_str;
			if (i < (json2data["sensordatavalues"].size() - 2)) { data_4_influxdb += ","; }
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
	debug_out(F("CSV Output"), DEBUG_MIN_INFO, 1);
	debug_out(data, DEBUG_MIN_INFO, 1);
	if (json2data.success()) {
		headline = F("Timestamp_ms;");
		valueline = String(act_milli) + ";";
		for (int i = 0; i < json2data["sensordatavalues"].size(); i++) {
			tmp_str = jsonBuffer.strdup(json2data["sensordatavalues"][i]["value_type"].as<char*>());
			headline += tmp_str + ";";
			tmp_str = jsonBuffer.strdup(json2data["sensordatavalues"][i]["value"].as<char*>());
			valueline += tmp_str + ";";
		}
		if (first_csv_line) {
			if (headline.length() > 0) { headline.remove(headline.length() - 1); }
			Serial.println(headline);
			first_csv_line = 0;
		}
		if (valueline.length() > 0) { valueline.remove(valueline.length() - 1); }
		Serial.println(valueline);
	} else {
		debug_out(F("Data read failed"), DEBUG_ERROR, 1);
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

	debug_out(F("Start reading DHT11/22"), DEBUG_MED_INFO, 1);

	// Check if valid number if non NaN (not a number) will be send.

	last_value_DHT_T = "";
	last_value_DHT_H = "";

	while ((i++ < 5) && (s == "")) {
		h = dht.readHumidity(); //Read Humidity
		t = dht.readTemperature(); //Read Temperature
		if (isnan(t) || isnan(h)) {
			delay(100);
			h = dht.readHumidity(true); //Read Humidity
			t = dht.readTemperature(false, true); //Read Temperature
		}
		if (isnan(t) || isnan(h)) {
			debug_out(F("DHT22 couldn't be read"), DEBUG_ERROR, 1);
		} else {
			debug_out(F("Humidity    : "), DEBUG_MIN_INFO, 0);
			debug_out(String(h) + "%", DEBUG_MIN_INFO, 1);
			debug_out(F("Temperature : "), DEBUG_MIN_INFO, 0);
			debug_out(String(t) + char(223) + "C", DEBUG_MIN_INFO, 1);
			last_value_DHT_T = Float2String(t);
			last_value_DHT_H = Float2String(h);
			s += Value2Json(F("temperature"), last_value_DHT_T);
			s += Value2Json(F("humidity"), last_value_DHT_H);
			last_value_DHT_T.remove(last_value_DHT_T.length() - 1);
			last_value_DHT_H.remove(last_value_DHT_H.length() - 1);
		}
	}
	debug_out(F("------"), DEBUG_MIN_INFO, 1);

	debug_out(F("End reading DHT11/22"), DEBUG_MED_INFO, 1);

	return s;
}

/*****************************************************************
/* read BMP180 sensor values                                     *
/*****************************************************************/
String sensorBMP() {
	String s = "";
	int p;
	float t;

	debug_out(F("Start reading BMP180"), DEBUG_MED_INFO, 1);

	p = bmp.readPressure();
	t = bmp.readTemperature();
	last_value_BMP_T = "";
	last_value_BMP_P = "";
	if (isnan(p) || isnan(t)) {
		debug_out(F("BMP180 couldn't be read"), DEBUG_ERROR, 1);
	} else {
		debug_out(F("Pressure    : "), DEBUG_MIN_INFO, 0);
		debug_out(Float2String(float(p) / 100) + " hPa", DEBUG_MIN_INFO, 1);
		debug_out(F("Temperature : "), DEBUG_MIN_INFO, 0);
		debug_out(String(t) + " C", DEBUG_MIN_INFO, 1);
		last_value_BMP_T = Float2String(t);
		last_value_BMP_P = String(p);
		s += Value2Json(F("BMP_pressure"), last_value_BMP_P);
		s += Value2Json(F("BMP_temperature"), last_value_BMP_T);
		last_value_BMP_T.remove(last_value_BMP_T.length() - 1);
	}
	debug_out(F("------"), DEBUG_MIN_INFO, 1);

	debug_out(F("End reading BMP180"), DEBUG_MED_INFO, 1);

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

	debug_out(F("Start reading BME280"), DEBUG_MED_INFO, 1);

	t = bme280.readTemperature();
	h = bme280.readHumidity();
	p = bme280.readPressure();
	last_value_BME280_T = "";
	last_value_BME280_H = "";
	last_value_BME280_P = "";
	if (isnan(t) || isnan(h) || isnan(p)) {
		debug_out(F("BME280 couldn't be read"), DEBUG_ERROR, 1);
	} else {
		debug_out(F("Temperature : "), DEBUG_MIN_INFO, 0);
		debug_out(Float2String(t) + " C", DEBUG_MIN_INFO, 1);
		debug_out(F("humidity : "), DEBUG_MIN_INFO, 0);
		debug_out(Float2String(h) + " %", DEBUG_MIN_INFO, 1);
		debug_out(F("Pressure    : "), DEBUG_MIN_INFO, 0);
		debug_out(Float2String(float(p) / 100) + " hPa", DEBUG_MIN_INFO, 1);
		last_value_BME280_T = Float2String(t);
		last_value_BME280_H = Float2String(h);
		last_value_BME280_P = Float2String(p);
		s += Value2Json(F("BME280_temperature"), last_value_BME280_T);
		s += Value2Json(F("BME280_humidity"), last_value_BME280_H);
		s += Value2Json(F("BME280_pressure"), last_value_BME280_P);
		last_value_BME280_T.remove(last_value_BME280_T.length() - 1);
		last_value_BME280_H.remove(last_value_BME280_H.length() - 1);
		last_value_BME280_P.remove(last_value_BME280_P.length() - 1);
	}
	debug_out(F("------"), DEBUG_MIN_INFO, 1);

	debug_out(F("End reading BME280"), DEBUG_MED_INFO, 1);

	return s;
}

/*****************************************************************
/* read DS18B20 sensor values                                     *
/*****************************************************************/
String sensorDS18B20() {
  String s = "";
  int i = 0;
  float t;
  debug_out(F("Start reading DS18B20"), DEBUG_MED_INFO, 1);

  //it's very unlikely (-127: impossible) to get these temperatures in reality. Most times this means that the sensor is currently faulty
  //try 5 times to read the sensor, otherwise fail
  do
  {
    ds18b20.requestTemperatures();
    //for now, we want to read only the first sensor
    t = ds18b20.getTempCByIndex(0);
    last_value_DS18B20_T = "";
    i++;
    debug_out(F("DS18B20 trying...."), DEBUG_MIN_INFO, 0);
    debug_out(String(i), DEBUG_MIN_INFO, 1);
  } while(i<5 && (isnan(t) || t == 85.0 || t == (-127.0)));
  if(i==5)
  {
    debug_out(F("DS18B20 couldn't be read."), DEBUG_ERROR, 1);
  } else { 
    debug_out(F("Temperature : "), DEBUG_MIN_INFO, 0);
    debug_out(Float2String(t) + " C", DEBUG_MIN_INFO, 1);
    last_value_DS18B20_T = Float2String(t);
    s += Value2Json(F("DS18B20_temperature"), last_value_DS18B20_T);
    last_value_DS18B20_T.remove(last_value_DS18B20_T.length() - 1);
  }
  debug_out(F("------"), DEBUG_MIN_INFO, 1);

  debug_out(F("End reading DS18B20"), DEBUG_MED_INFO, 1);

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

/*****************************************************************
/* read PPD42NS sensor values                                    *
/*****************************************************************/
String sensorPPD() {
	boolean valP1 = HIGH;
	boolean valP2 = HIGH;
	float ratio = 0;
	float concentration = 0;
	String s = "";

	debug_out(F("Start reading PPD42NS"), DEBUG_MED_INFO, 1);

	if ((act_milli - starttime) <= sampletime_ms) {

		// Read pins connected to ppd42ns
		valP1 = digitalRead(PPD_PIN_PM1);
		valP2 = digitalRead(PPD_PIN_PM2);

		if(valP1 == LOW && trigP1 == false) {
			trigP1 = true;
			trigOnP1 = act_micro;
		}

		if (valP1 == HIGH && trigP1 == true) {
			durationP1 = act_micro - trigOnP1;
			lowpulseoccupancyP1 = lowpulseoccupancyP1 + durationP1;
			trigP1 = false;
		}

		if(valP2 == LOW && trigP2 == false) {
			trigP2 = true;
			trigOnP2 = act_micro;
		}

		if (valP2 == HIGH && trigP2 == true) {
			durationP2 = act_micro - trigOnP2;
			lowpulseoccupancyP2 = lowpulseoccupancyP2 + durationP2;
			trigP2 = false;
		}

	}
	// Checking if it is time to sample
	if (send_now) {
		last_value_PPD_P1 = "";
		last_value_PPD_P2 = "";
		ratio = lowpulseoccupancyP1 / (sampletime_ms * 10.0);					// int percentage 0 to 100
		concentration = (1.1 * pow(ratio, 3) - 3.8 * pow(ratio, 2) + 520 * ratio + 0.62);	// spec sheet curve
		// Begin printing
		debug_out(F("LPO P10    : "), DEBUG_MIN_INFO, 0);
		debug_out(String(lowpulseoccupancyP1), DEBUG_MIN_INFO, 1);
		debug_out(F("Ratio PM10 : "), DEBUG_MIN_INFO, 0);
		debug_out(Float2String(ratio) + " %", DEBUG_MIN_INFO, 1);
		debug_out(F("PM10 Count : "), DEBUG_MIN_INFO, 0);
		debug_out(Float2String(concentration), DEBUG_MIN_INFO, 1);

		// json for push to api / P1
		last_value_PPD_P1 = Float2String(concentration);
		s += Value2Json("durP1", String(long(lowpulseoccupancyP1)));
		s += Value2Json("ratioP1", Float2String(ratio));
		s += Value2Json("P1", last_value_PPD_P1);

		ratio = lowpulseoccupancyP2 / (sampletime_ms * 10.0);
		concentration = (1.1 * pow(ratio, 3) - 3.8 * pow(ratio, 2) + 520 * ratio + 0.62);
		// Begin printing
		debug_out(F("LPO PM25   : "), DEBUG_MIN_INFO, 0);
		debug_out(String(lowpulseoccupancyP2), DEBUG_MIN_INFO, 1);
		debug_out(F("Ratio PM25 : "), DEBUG_MIN_INFO, 0);
		debug_out(Float2String(ratio) + " %", DEBUG_MIN_INFO, 1);
		debug_out(F("PM25 Count : "), DEBUG_MIN_INFO, 0);
		debug_out(Float2String(concentration), DEBUG_MIN_INFO, 1);

		// json for push to api / P2
		last_value_PPD_P2 = Float2String(concentration);
		s += Value2Json("durP2", String(long(lowpulseoccupancyP2)));
		s += Value2Json("ratioP2", Float2String(ratio));
		s += Value2Json("P2", last_value_PPD_P2);

		debug_out(F("------"), DEBUG_MIN_INFO, 1);
	}

	debug_out(F("End reading PPD42NS"), DEBUG_MED_INFO, 1);

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

	debug_out(F("Start reading GPS"), DEBUG_MED_INFO, 1);

	while (serialGPS.available() > 0) {
		if (gps.encode(serialGPS.read())) {
			if (gps.location.isValid()) {
				last_gps_lat = String(gps.location.lat(), 6);
				last_gps_lng = String(gps.location.lng(), 6);
			} else {
				debug_out(F("Lat/Lng INVALID"), DEBUG_MAX_INFO, 1);
			}
			if (gps.altitude.isValid()) {
				last_gps_alt = String(gps.altitude.meters(), 2);
			} else {
				debug_out(F("Altitude INVALID"), DEBUG_MAX_INFO, 1);
			}
			if (gps.date.isValid()) {
				gps_date = "";
				if (gps.date.month() < 10) { gps_date += "0"; }
				gps_date += String(gps.date.month());
				gps_date += "/";
				if (gps.date.day() < 10) { gps_date += "0"; }
				gps_date += String(gps.date.day());
				gps_date += "/";
				gps_date += String(gps.date.year());
				last_gps_date = gps_date;
			} else {
				debug_out(F("Date INVALID"), DEBUG_MAX_INFO, 1);
			}
			if (gps.time.isValid()) {
				gps_time = "";
				if (gps.time.hour() < 10) { gps_time += "0"; }
				gps_time += String(gps.time.hour());
				gps_time += ":";
				if (gps.time.minute() < 10) { gps_time += "0"; }
				gps_time += String(gps.time.minute());
				gps_time += ":";
				if (gps.time.second() < 10) { gps_time += "0"; }
				gps_time += String(gps.time.second());
				gps_time += ".";
				if (gps.time.centisecond() < 10) { gps_time += "0"; }
				gps_time += String(gps.time.centisecond());
				last_gps_time = gps_time;
			} else {
				debug_out(F("Time: INVALID"), DEBUG_MAX_INFO, 1);
			}
		}
	}

	if (send_now) {
		debug_out("Lat/Lng: " + last_gps_lat + "," + last_gps_lng, DEBUG_MIN_INFO, 1);
		debug_out("Altitude: " + last_gps_alt, DEBUG_MIN_INFO, 1);
		debug_out("Date: " + last_gps_date, DEBUG_MIN_INFO, 1);
		debug_out("Time " + last_gps_time, DEBUG_MIN_INFO, 1);
		debug_out("------", DEBUG_MIN_INFO, 1);
		s += Value2Json(F("GPS_lat"), last_gps_lat);
		s += Value2Json(F("GPS_lon"), last_gps_lng);
		s += Value2Json(F("GPS_height"), last_gps_alt);
		s += Value2Json(F("GPS_date"), last_gps_date);
		s += Value2Json(F("GPS_time"), last_gps_time);
		last_gps_lat = "";
		last_gps_lng = "";
		last_gps_alt = "";
		last_gps_date = "";
		last_gps_time = "";
	}

	if ( gps.charsProcessed() < 10) {
		debug_out(F("No GPS data received: check wiring"), DEBUG_ERROR, 1);
	}

	debug_out(F("End reading GPS"), DEBUG_MED_INFO, 1);

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
		debug_out(F("Starting OTA update ..."), DEBUG_MIN_INFO, 1);
		debug_out(F("NodeMCU firmware : "), DEBUG_MIN_INFO, 0);
		debug_out(String(SOFTWARE_VERSION), DEBUG_MIN_INFO, 1);
		debug_out(String(update_host), DEBUG_MED_INFO, 1);
		debug_out(String(update_url), DEBUG_MED_INFO, 1);

		if (sds_read) { SDS_version = SDS_version_date();}
		//SDS_version = "999";
		display_debug(F("Looking for OTA update"));
		last_update_attempt = millis();
		t_httpUpdate_return ret = ESPhttpUpdate.update(update_host, update_port, update_url, String(SOFTWARE_VERSION) + String(" ") + esp_chipid + String(" ") + SDS_version + String(" ") + String(current_lang) + String(" ") + String(INTL_LANG));
		switch(ret) {
		case HTTP_UPDATE_FAILED:
			debug_out(F("[update] Update failed."), DEBUG_ERROR, 0);
			debug_out(ESPhttpUpdate.getLastErrorString().c_str(), DEBUG_ERROR, 1);
			display_debug(F("Update failed."));
			break;
		case HTTP_UPDATE_NO_UPDATES:
			debug_out(F("[update] No Update."), DEBUG_MIN_INFO, 1);
			display_debug(F("No update found."));
			break;
		case HTTP_UPDATE_OK:
			debug_out(F("[update] Update ok."), DEBUG_MIN_INFO, 1); // may not called we reboot the ESP
			break;
		}
	}
	will_check_for_update = false;
#endif
}

/*****************************************************************
/* display values                                                *
/*****************************************************************/
void display_values(const String& value_DHT_T, const String& value_DHT_H, const String& value_BMP_T, const String& value_BMP_P, const String& value_BME280_T, const String& value_BME280_H, const String& value_BME280_P, const String& value_PPD_P1, const String& value_PPD_P2, const String& value_SDS_P1, const String& value_SDS_P2) {
#if defined(ESP8266)
	int value_count = 0;
	String t_value = "";
	String h_value = "";
	String p_value = "";
	String t_sensor = "";
	String h_sensor = "";
	String p_sensor = "";
	debug_out(F("output values to display..."), DEBUG_MIN_INFO, 1);
	if (dht_read) {
		t_value = value_DHT_T; t_sensor = "DHT22";
		h_value = value_DHT_H; h_sensor = "DHT22";
	}
	if (bmp_read) {
		t_value = value_BMP_T; t_sensor = "BMP180";
		p_value = value_BMP_P; p_sensor = "BMP180";
	}
	if (bme280_read) {
		t_value = value_BME280_T; t_sensor = "BME280";
		h_value = value_BME280_H; h_sensor = "BME280";
		p_value = value_BME280_P; p_sensor = "BME280";
	}
	if (t_value == "") { t_value = "-";}
	if (h_value == "") { h_value = "-";}
	if (p_value == "") { p_value = "-";}

	if (has_display) {
		display.resetDisplay();
		display.clear();
		display.displayOn();
		display.setFont(Monospaced_plain_9);
		display.setTextAlignment(TEXT_ALIGN_LEFT);
		value_count = 0;
		display.drawString(0, 10 * (value_count++), "Temp:" + t_value + "  Hum.:" + h_value);
		if (ppd_read) {
			display.drawString(0, 10 * (value_count++), "PPD P1: " + value_PPD_P1);
			display.drawString(0, 10 * (value_count++), "PPD P2: " + value_PPD_P2);
		}
		if (sds_read) {
			display.drawString(0, 10 * (value_count++), "SDS P1: " + value_SDS_P1);
			display.drawString(0, 10 * (value_count++), "SDS P2: " + value_SDS_P2);
		}
		if (gps_read) {
			if(gps.location.isValid()) {
				display.drawString(0, 10 * (value_count++), "lat: " + String(gps.location.lat(), 6));
				display.drawString(0, 10 * (value_count++), "long: " + String(gps.location.lng(), 6));
			}
			display.drawString(0, 10 * (value_count++), "satellites: " + String(gps.satellites.value()));
		}
		display.display();
	}
	if (has_lcd1602) {
		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print("PM: " + (value_SDS_P1 != "" ? value_SDS_P1 : "-") + " " + (value_SDS_P2 != "" ? value_SDS_P2 : "-"));
		lcd.setCursor(0, 1);
		lcd.print("T/H:" + t_value + char(223) + "C " + h_value + "%");
	}
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
/* Init display                                                  *
/*****************************************************************/
void init_lcd1602() {
#if defined(ESP8266)
	lcd.init();
	lcd.backlight();
#endif
}

/*****************************************************************
/* Init BME280                                                   *
/*****************************************************************/
bool initBME280(char addr) {
	debug_out(F("Trying BME280 sensor on "), DEBUG_MIN_INFO, 0);
	debug_out(String(addr, HEX), DEBUG_MIN_INFO, 0);

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
	Wire.begin(D3, D4);
	esp_chipid = String(ESP.getChipId());
	WiFi.persistent(false);
#endif
#if defined(ARDUINO_SAMD_ZERO)
	Wire.begin();
#endif
	init_display();
	init_lcd1602();
	copyExtDef();
	display_debug(F("Reading config from SPIFFS"));
	readConfig();
	setup_webserver();
	display_debug("Connecting to " + String(wlanssid));
	connectWifi();						// Start ConnectWifi
	if (restart_needed) {
		display_debug(F("Writing config to SPIFFS and restarting sensor"));
		writeConfig();
		delay(500);
		ESP.restart();
	}
	autoUpdate();
	create_basic_auth_strings();
	serialSDS.begin(9600);
	serialGPS.begin(9600);
  ds18b20.begin();
	pinMode(PPD_PIN_PM1, INPUT_PULLUP);	// Listen at the designated PIN
	pinMode(PPD_PIN_PM2, INPUT_PULLUP);	// Listen at the designated PIN
	dht.begin();	// Start DHT
	delay(10);
#if defined(ESP8266)
	debug_out(F("\nChipId: "), DEBUG_MIN_INFO, 0);
	debug_out(esp_chipid, DEBUG_MIN_INFO, 1);
#endif
#if defined(ARDUINO_SAMD_ZERO)
	if (!manager.init())
	{ debug_out("Manager init failed", DEBUG_MIN_INFO, 1); }
	if (!rf69.setFrequency(RF69_FREQ)) {
		debug_out("setFrequency failed", DEBUG_MIN_INFO, 1);
		while (1);
	}
	debug_out(F("Set Freq to: "), DEBUG_MIN_INFO, 0);
	debug_out(String(RF69_FREQ), DEBUG_MIN_INFO, 1);
	rf69.setTxPower(20);
	debug_out(F("\nChipId: "), DEBUG_MIN_INFO, 0);
	debug_out(FeatherChipId(), DEBUG_MIN_INFO, 1);
#endif

	if (ppd_read) { debug_out(F("Lese PPD..."), DEBUG_MIN_INFO, 1); }
	if (sds_read) { debug_out(F("Lese SDS..."), DEBUG_MIN_INFO, 1); }
	if (dht_read) { debug_out(F("Lese DHT..."), DEBUG_MIN_INFO, 1); }
	if (bmp_read) { debug_out(F("Lese BMP..."), DEBUG_MIN_INFO, 1); }
	if (bme280_read) { debug_out(F("Lese BME280..."), DEBUG_MIN_INFO, 1); }
  if (ds18b20_read) { debug_out(F("Lese DS18B20..."), DEBUG_MIN_INFO, 1); }
	if (gps_read) { debug_out(F("Lese GPS..."), DEBUG_MIN_INFO, 1); }
	if (send2dusti) { debug_out(F("Sende an luftdaten.info..."), DEBUG_MIN_INFO, 1); }
	if (send2madavi) { debug_out(F("Sende an madavi.de..."), DEBUG_MIN_INFO, 1); }
	if (send2lora) { debug_out(F("Sende an LoRa gateway..."), DEBUG_MIN_INFO, 1); }
	if (send2csv) { debug_out(F("Sende als CSV an Serial..."), DEBUG_MIN_INFO, 1); }
	if (send2custom) { debug_out(F("Sende an custom API..."), DEBUG_MIN_INFO, 1); }
	if (send2influx) { debug_out(F("Sende an custom influx DB..."), DEBUG_MIN_INFO, 1); }
	if (auto_update) { debug_out(F("Auto-Update wird ausgeführt..."), DEBUG_MIN_INFO, 1); }
	if (has_display) { debug_out(F("Zeige auf Display..."), DEBUG_MIN_INFO, 1); }
	if (has_lcd1602) { debug_out(F("Zeige auf LCD 1602..."), DEBUG_MIN_INFO, 1); }
	if (bmp_read) {
		if (!bmp.begin()) {
			debug_out(F("No valid BMP085 sensor, check wiring!"), DEBUG_MIN_INFO, 1);
			bmp_read = 0;
		}
	}
	if (bme280_read && !initBME280(0x76) && !initBME280(0x77)) {
		debug_out(F("Check BME280 wiring"), DEBUG_MIN_INFO, 1);
		bme280_read = 0;
	}
	if (sds_read) {
		debug_out(F("Stoppe SDS011..."), DEBUG_MIN_INFO, 1);
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

	// sometimes parallel sending data and web page will stop nodemcu, watchdogtimer set to 30 seconds
	wdt_disable();
	wdt_enable(30000);// 30 sec

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
	String data_4_custom = "";
	String data_sample_times = "";

	String sensemap_path = "";

	String result_PPD = "";
	String result_SDS = "";
	String result_DHT = "";
	String result_BMP = "";
	String result_BME280 = "";
  String result_DS18B20 = "";
	String result_GPS = "";
	String signal_strength = "";

	unsigned long sum_send_time = 0;
	unsigned long start_send;

	send_failed = false;

	act_micro = micros();
	act_milli = millis();
	send_now = (act_milli - starttime) > sending_intervall_ms;

	sample_count++;

	wdt_reset(); // nodemcu is alive

	if (last_micro != 0) {
		diff_micro = act_micro - last_micro;
		if (max_micro < diff_micro) { max_micro = diff_micro;}
		if (min_micro > diff_micro) { min_micro = diff_micro;}
		last_micro = act_micro;
	} else {
		last_micro = act_micro;
	}

	if (ppd_read) {
		debug_out(F("Call sensorPPD"), DEBUG_MAX_INFO, 1);
		result_PPD = sensorPPD();
	}

	if (sds_read && (((act_milli - starttime_SDS) > sampletime_SDS_ms) || ((act_milli - starttime) > sending_intervall_ms))) {
		debug_out(F("Call sensorSDS"), DEBUG_MAX_INFO, 1);
		result_SDS = sensorSDS();
		starttime_SDS = act_milli;
	}

	if (send_now) {
		if (dht_read) {
			debug_out(F("Call sensorDHT"), DEBUG_MAX_INFO, 1);
			result_DHT = sensorDHT();			// getting temperature and humidity (optional)
		}

		if (bmp_read) {
			debug_out(F("Call sensorBMP"), DEBUG_MAX_INFO, 1);
			result_BMP = sensorBMP();			// getting temperature and pressure (optional)
		}

		if (bme280_read) {
			debug_out(F("Call sensorBME280"), DEBUG_MAX_INFO, 1);
			result_BME280 = sensorBME280();			// getting temperature, humidity and pressure (optional)
		}

   if (ds18b20_read) {
      debug_out(F("Call sensorDS18B20"), DEBUG_MAX_INFO, 1);
      result_DS18B20 = sensorDS18B20();     // getting temperature (optional)
   }
	}

	if (gps_read && (((act_milli - starttime_GPS) > sampletime_GPS_ms) || ((act_milli - starttime) > sending_intervall_ms))) {
		debug_out(F("Call sensorGPS"), DEBUG_MAX_INFO, 1);
		result_GPS = sensorGPS();			// getting GPS coordinates
		starttime_GPS = act_milli;
	}

	if (send_now) {
		if (WiFi.psk() != "") {
			httpPort_madavi = 80;
			httpPort_dusti = 80;
		}
		debug_out(F("Creating data string:"), DEBUG_MIN_INFO, 1);
		data = data_first_part;
		data_sample_times  = Value2Json("samples", String(long(sample_count)));
		data_sample_times += Value2Json("min_micro", String(long(min_micro)));
		data_sample_times += Value2Json("max_micro", String(long(max_micro)));

		signal_strength = String(WiFi.RSSI());
		debug_out(F("WLAN signal strength: "), DEBUG_MIN_INFO, 0);
		debug_out(signal_strength, DEBUG_MIN_INFO, 0);
		debug_out(F(" dBm"), DEBUG_MIN_INFO, 1);
		debug_out(F("------"), DEBUG_MIN_INFO, 1);

		server.handleClient();
		yield();
		server.stop();
		if (ppd_read) {
			data += result_PPD;
			data_4_dusti  = data_first_part + result_PPD;
			data_4_dusti.remove(data_4_dusti.length() - 1);
			data_4_dusti += "]}";
			if (send2dusti) {
				debug_out(F("## Sending to luftdaten.info (PPD): "), DEBUG_MIN_INFO, 1);
				start_send = micros();
				if (result_PPD != "") {
					sendData(data_4_dusti, PPD_API_PIN, host_dusti, httpPort_dusti, url_dusti, "", FPSTR(TXT_CONTENT_TYPE_JSON));
				} else {
					debug_out(F("No data sent..."), DEBUG_MIN_INFO, 1);
				}
				sum_send_time += micros() - start_send;
			}
		}
		if (sds_read) {
			data += result_SDS;
			data_4_dusti  = data_first_part + result_SDS;
			data_4_dusti.remove(data_4_dusti.length() - 1);
			data_4_dusti.replace("SDS_", "");
			data_4_dusti += "]}";
			if (send2dusti) {
				debug_out(F("## Sending to luftdaten.info (SDS): "), DEBUG_MIN_INFO, 1);
				start_send = micros();
				if (result_SDS != "") {
					sendData(data_4_dusti, SDS_API_PIN, host_dusti, httpPort_dusti, url_dusti, "", FPSTR(TXT_CONTENT_TYPE_JSON));
				} else {
					debug_out(F("No data sent..."), DEBUG_MIN_INFO, 1);
				}
				sum_send_time += micros() - start_send;
			}
		}
		if (dht_read) {
			data += result_DHT;
			data_4_dusti  = data_first_part + result_DHT;
			data_4_dusti.remove(data_4_dusti.length() - 1);
			data_4_dusti += "]}";
			if (send2dusti) {
				debug_out(F("## Sending to luftdaten.info (DHT): "), DEBUG_MIN_INFO, 1);
				start_send = micros();
				if (result_DHT != "") {
					sendData(data_4_dusti, DHT_API_PIN, host_dusti, httpPort_dusti, url_dusti, "", FPSTR(TXT_CONTENT_TYPE_JSON));
				} else {
					debug_out(F("No data sent..."), DEBUG_MIN_INFO, 1);
				}
				sum_send_time += micros() - start_send;
			}
		}
		if (bmp_read) {
			data += result_BMP;
			data_4_dusti  = data_first_part + result_BMP;
			data_4_dusti.remove(data_4_dusti.length() - 1);
			data_4_dusti.replace("BMP_", "");
			data_4_dusti += "]}";
			if (send2dusti) {
				debug_out(F("## Sending to luftdaten.info (BMP): "), DEBUG_MIN_INFO, 1);
				start_send = micros();
				if (result_BMP != "") {
					sendData(data_4_dusti, BMP_API_PIN, host_dusti, httpPort_dusti, url_dusti, "", FPSTR(TXT_CONTENT_TYPE_JSON));
				} else {
					debug_out(F("No data sent..."), DEBUG_MIN_INFO, 1);
				}
				sum_send_time += micros() - start_send;
			}
		}
		if (bme280_read) {
			data += result_BME280;
			data_4_dusti  = data_first_part + result_BME280;
			data_4_dusti.remove(data_4_dusti.length() - 1);
			data_4_dusti.replace("BME280_", "");
			data_4_dusti += "]}";
			if (send2dusti) {
				debug_out(F("## Sending to luftdaten.info (BME280): "), DEBUG_MIN_INFO, 1);
				start_send = micros();
				if (result_BME280 != "") {
					sendData(data_4_dusti, BME280_API_PIN, host_dusti, httpPort_dusti, url_dusti, "", FPSTR(TXT_CONTENT_TYPE_JSON));
				} else {
					debug_out(F("No data sent..."), DEBUG_MIN_INFO, 1);
				}
				sum_send_time += micros() - start_send;
			}
		}

   if (ds18b20_read) {
      data += result_DS18B20;
      data_4_dusti = data_first_part + result_DS18B20;
      data_4_dusti.remove(data_4_dusti.length() - 1);
      data_4_dusti.replace("DS18B20_", "");
      data_4_dusti += "]}";
      if (send2dusti) {
        debug_out(F("## Sending to luftdaten.info (DS18B20): "), DEBUG_MIN_INFO, 1);
        start_send = micros();
        if (result_DS18B20 != "") {
          sendData(data_4_dusti, BME280_API_PIN, host_dusti, httpPort_dusti, url_dusti, "", FPSTR(TXT_CONTENT_TYPE_JSON));
        } else {
          debug_out(F("No data sent..."), DEBUG_MIN_INFO, 1);
        }
        sum_send_time += micros() - start_send;
      }
   }

		if (gps_read) {
			data += result_GPS;
			data_4_dusti  = data_first_part + result_GPS;
			data_4_dusti.remove(data_4_dusti.length() - 1);
			data_4_dusti.replace("GPS_", "");
			data_4_dusti += "]}";
			if (send2dusti) {
				debug_out(F("## Sending to luftdaten.info (GPS): "), DEBUG_MIN_INFO, 1);
				start_send = micros();
				if (result_GPS != "") {
					sendData(data_4_dusti, GPS_API_PIN, host_dusti, httpPort_dusti, url_dusti, "", FPSTR(TXT_CONTENT_TYPE_JSON));
				} else {
					debug_out(F("No data sent..."), DEBUG_MIN_INFO, 1);
				}
				sum_send_time += micros() - start_send;
			}
		}

		data_sample_times += Value2Json("signal", signal_strength);
		data += data_sample_times;

		if (data.lastIndexOf(',') == (data.length() - 1)) {
			data.remove(data.length() - 1);
		}
		data += "]}";

		//sending to api(s)

		if ((act_milli - last_update_attempt) > pause_between_update_attempts) {
			will_check_for_update = true;
		}

		if (has_display || has_lcd1602) {
			display_values(last_value_DHT_T, last_value_DHT_H, last_value_BMP_T, last_value_BMP_P, last_value_BME280_T, last_value_BME280_H, last_value_BME280_P, last_value_PPD_P1, last_value_PPD_P2, last_value_SDS_P1, last_value_SDS_P2);
		}

		if (send2madavi) {
			debug_out(F("## Sending to madavi.de: "), DEBUG_MIN_INFO, 1);
			start_send = micros();
			sendData(data, 0, host_madavi, httpPort_madavi, url_madavi, "", FPSTR(TXT_CONTENT_TYPE_JSON));
			sum_send_time += micros() - start_send;
		}

		if (send2sensemap && (senseboxid != SENSEBOXID)) {
			debug_out(F("## Sending to opensensemap: "), DEBUG_MIN_INFO, 1);
			start_send = micros();
			sensemap_path = url_sensemap;
			sensemap_path.replace("BOXID", senseboxid);
			sendData(data, 0, host_sensemap, httpPort_sensemap, sensemap_path.c_str(), "", FPSTR(TXT_CONTENT_TYPE_JSON));
			sum_send_time += micros() - start_send;
		}

		if (send2influx) {
			debug_out(F("## Sending to custom influx db: "), DEBUG_MIN_INFO, 1);
			start_send = micros();
			data_4_influxdb = create_influxdb_string(data);
			sendData(data_4_influxdb, 0, host_influx, port_influx, url_influx, basic_auth_influx.c_str(), FPSTR(TXT_CONTENT_TYPE_INFLUXDB));
			sum_send_time += micros() - start_send;
		}

		if (send2lora) {
			debug_out(F("## Sending to LoRa gateway: "), DEBUG_MIN_INFO, 1);
			send_lora(data);
		}

		if (send2csv) {
			debug_out(F("## Sending as csv: "), DEBUG_MIN_INFO, 1);
			send_csv(data);
		}

		if (send2custom) {
			data_4_custom = data;
			data_4_custom.remove(0, 1);
			data_4_custom = "{\"esp8266id\": \"" + String(esp_chipid) + "\", " + data_4_custom;
			debug_out(F("## Sending to custom api: "), DEBUG_MIN_INFO, 1);
			start_send = micros();
			sendData(data_4_custom, 0, host_custom, port_custom, url_custom, basic_auth_custom.c_str(), FPSTR(TXT_CONTENT_TYPE_JSON));
			sum_send_time += micros() - start_send;
		}

		server.begin();

		if ((act_milli - last_update_attempt) > (28 * pause_between_update_attempts)) {
			ESP.restart();
		}

		if ((act_milli - last_update_attempt) > pause_between_update_attempts) {
			autoUpdate();
		}

		if (! send_failed) { sending_time = (4 * sending_time + sum_send_time) / 5; }
		debug_out(F("Time for sending data: "), DEBUG_MIN_INFO, 0);
		debug_out(String(sending_time), DEBUG_MIN_INFO, 1);
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
			debug_out(F("Connection lost, reconnecting "), DEBUG_MIN_INFO, 0);
			WiFi.reconnect();
			while ((WiFi.status() != WL_CONNECTED) && (retry_count < 20)) {
				delay(500);
				debug_out(".", DEBUG_MIN_INFO, 0);
				retry_count++;
			}
			debug_out("", DEBUG_MIN_INFO, 1);
		}
		first_cycle = false;
	}
	if (config_needs_write) { writeConfig(); create_basic_auth_strings(); }
	server.handleClient();
	yield();
}
