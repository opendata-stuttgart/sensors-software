/************************************************************************
 *                                                                      *
 *  This source code needs to be compiled for the board                 *
 *  NodeMCU 1.0 (ESP-12E Module)                                        *
 *                                                                      *
 ************************************************************************
 *                                                                      *
 *    airRohr firmware                                                  *
 *    Copyright (C) 2016-2018  Code for Stuttgart a.o.                  *
 *                                                                      *
 * This program is free software: you can redistribute it and/or modify *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation, either version 3 of the License, or    *
 * (at your option) any later version.                                  *
 *                                                                      *
 * This program is distributed in the hope that it will be useful,      *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with this program. If not, see <http://www.gnu.org/licenses/>. *
 *                                                                      *
 ************************************************************************
 * OK LAB Particulate Matter Sensor                                     *
 *      - nodemcu-LoLin board                                           *
 *      - Nova SDS0111                                                  *
 *  http://inovafitness.com/en/Laser-PM2-5-Sensor-SDS011-35.html        *
 *                                                                      *
 * Wiring Instruction:                                                  *
 *      - SDS011 Pin 1  (TX)   -> Pin D1 / GPIO5                        *
 *      - SDS011 Pin 2  (RX)   -> Pin D2 / GPIO4                        *
 *      - SDS011 Pin 3  (GND)  -> GND                                   *
 *      - SDS011 Pin 4  (2.5m) -> unused                                *
 *      - SDS011 Pin 5  (5V)   -> VU                                    *
 *      - SDS011 Pin 6  (1m)   -> unused                                *
 *                                                                      *
 ************************************************************************
 *                                                                      *
 * Alternative                                                          *
 *      - nodemcu-LoLin board                                           *
 *      - Shinyei PPD42NS                                               *
 *      http://www.sca-shinyei.com/pdf/PPD42NS.pdf                      *
 *                                                                      *
 * Wiring Instruction:                                                  *
 *      Pin 2 of dust sensor PM2.5 -> Digital 6 (PWM)                   *
 *      Pin 3 of dust sensor       -> +5V                               *
 *      Pin 4 of dust sensor PM1   -> Digital 3 (PMW)                   *
 *                                                                      *
 *      - PPD42NS Pin 1 (grey or green)  => GND                         *
 *      - PPD42NS Pin 2 (green or white)) => Pin D5 /GPIO14             *
 *        counts particles PM25                                         *
 *      - PPD42NS Pin 3 (black or yellow) => Vin                        *
 *      - PPD42NS Pin 4 (white or black) => Pin D6 / GPIO12             *
 *        counts particles PM10                                         *
 *      - PPD42NS Pin 5 (red)   => unused                               *
 *                                                                      *
 ************************************************************************
 * Extension: DHT22 (AM2303)                                            *
 *  http://www.aosong.com/en/products/details.asp?id=117                *
 *                                                                      *
 * DHT22 Wiring Instruction                                             *
 * (left to right, front is perforated side):                           *
 *      - DHT22 Pin 1 (VDD)     -> Pin 3V3 (3.3V)                       *
 *      - DHT22 Pin 2 (DATA)    -> Pin D7 (GPIO13)                      *
 *      - DHT22 Pin 3 (NULL)    -> unused                               *
 *      - DHT22 Pin 4 (GND)     -> Pin GND                              *
 *                                                                      *
 ************************************************************************
 * Extensions connected via I2C:                                        *
 * HTU21D (https://www.sparkfun.com/products/13763),                    *
 * BMP180, BMP280, BME280, OLED Display with SSD1306 (128x64 px)        *
 *                                                                      *
 * Wiring Instruction                                                   *
 * (see labels on display or sensor board)                              *
 *      VCC       ->     Pin 3V3                                        *
 *      GND       ->     Pin GND                                        *
 *      SCL       ->     Pin D4 (GPIO2)                                 *
 *      SDA       ->     Pin D3 (GPIO0)                                 *
 *                                                                      *
 ************************************************************************
 *                                                                      *
 * Please check Readme.md for other sensors and hardware                *
 *                                                                      *
 ************************************************************************
 *
 * latest mit lib 2.4.2
 * Der Sketch verwendet 511608 Bytes (48%) des Programmspeicherplatzes. Das Maximum sind 1044464 Bytes.
 * Globale Variablen verwenden 37264 Bytes (45%) des dynamischen Speichers, 44656 Bytes für lokale Variablen verbleiben. Das Maximum sind 81920 Bytes.
 *
 * Der Sketch verwendet 506304 Bytes (48%) des Programmspeicherplatzes. Das Maximum sind 1044464 Bytes.
 * Globale Variablen verwenden 37128 Bytes (45%) des dynamischen Speichers, 44792 Bytes für lokale Variablen verbleiben. Das Maximum sind 81920 Bytes.
 *
 * Der Sketch verwendet 505504 Bytes (48%) des Programmspeicherplatzes. Das Maximum sind 1044464 Bytes.
 * Globale Variablen verwenden 37128 Bytes (45%) des dynamischen Speichers, 44792 Bytes für lokale Variablen verbleiben. Das Maximum sind 81920 Bytes.
 *
 * Attention:
 * the driver for the Sensirion PM Sensor SPS30 needs I²C lransmission of 64 Bytes
 *
 * in Wire.h set BUFFER_LENGTH to 64 !!!!
 *
 * #define BUFFER_LENGTH 64
 *
 *
 *
 ************************************************************************/
// increment on change
#define SOFTWARE_VERSION_STR "NRZ-2019-124-B7"
const String SOFTWARE_VERSION(SOFTWARE_VERSION_STR);

/*****************************************************************
 * Includes                                                      *
 *****************************************************************/

// Workaround for FPSTR bug in espressif32 versions < 1.0.3-rc2
// see https://github.com/espressif/arduino-esp32/issues/1371
//     https://github.com/bxparks/arduino-esp32/commit/0906aedcf9fe8df3969cd336117c1219b507be14
// TODO: Workaround can be removed once using a espressif32 version newer than 1.0.3-rc2.
// Make sure the includes Wstring.h and pgmspace.h are already loaded before the #define is redefined!
#include <WString.h>
#include <pgmspace.h>
#if defined(ESP32)
#undef FPSTR
#define FPSTR(pstr_pointer) (reinterpret_cast<const __FlashStringHelper *>(pstr_pointer))
#undef F
#define F(string_literal) (FPSTR(PSTR(string_literal)))
#endif

#if defined(ESP8266)
#include <FS.h>                     // must be first
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266httpUpdate.h>
#include <SoftwareSerial.h>
#include <Hash.h>
#include <time.h>
#include <coredecls.h>
#include <assert.h>
#endif

#if defined(ESP32)
#define FORMAT_SPIFFS_IF_FAILED true
#include <FS.h>
#include <SPIFFS.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <HardwareSerial.h>
#include <hwcrypto/sha.h>
#include <HTTPUpdate.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#endif

// includes common to ESP8266 and ESP32 (especially external libraries)
#include <base64.h>
#include "./oledfont.h"				// avoids including the default Arial font, needs to be included before SSD1306.h
#include <SSD1306.h>
#include <SH1106.h>
#include <LiquidCrystal_I2C.h>
#include <ArduinoJson.h>
#include <DNSServer.h>
#include "./DHT.h"
#include <Adafruit_HTU21DF.h>
#include <Adafruit_BMP085.h>
#include <DallasTemperature.h>
#include <TinyGPS++.h>
#include "./bmx280_i2c.h"
#include "./sps30_i2c.h"
#include "./dnms_i2c.h"

#if defined(INTL_BG)
#include "intl_bg.h"
#elif defined(INTL_CZ)
#include "intl_cz.h"
#elif defined(INTL_DE)
#include "intl_de.h"
#elif defined(INTL_DK)
#include "intl_dk.h"
#elif defined(INTL_EN)
#include "intl_en.h"
#elif defined(INTL_ES)
#include "intl_es.h"
#elif defined(INTL_FR)
#include "intl_fr.h"
#elif defined(INTL_IT)
#include "intl_it.h"
#elif defined(INTL_LU)
#include "intl_lu.h"
#elif defined(INTL_NL)
#include "intl_nl.h"
#elif defined(INTL_PL)
#include "intl_pl.h"
#elif defined(INTL_PT)
#include "intl_pt.h"
#elif defined(INTL_RU)
#include "intl_ru.h"
#elif defined(INTL_SE)
#include "intl_se.h"
#elif defined(INTL_TR)
#include "intl_tr.h"
#elif defined(INTL_UA)
#include "intl_ua.h"
#else
#warning No language defined
#include "intl_en.h"
#endif

#include "defines.h"
#include "ext_def.h"
#include "html-content.h"

/******************************************************************
 * Constants                                                      *
 ******************************************************************/
constexpr unsigned SMALL_STR = 64-1;
constexpr unsigned MED_STR = 256-1;
constexpr unsigned LARGE_STR = 512-1;
constexpr unsigned XLARGE_STR = 1024-1;

#define RESERVE_STRING(name, size) String name((const char*)nullptr); name.reserve(size);

const unsigned long SAMPLETIME_MS = 30000;									// time between two measurements of the PPD42NS
const unsigned long SAMPLETIME_SDS_MS = 1000;								// time between two measurements of the SDS011, PMSx003, Honeywell PM sensor
const unsigned long WARMUPTIME_SDS_MS = 15000;								// time needed to "warm up" the sensor before we can take the first measurement
const unsigned long READINGTIME_SDS_MS = 5000;								// how long we read data from the PM sensors
const unsigned long SAMPLETIME_GPS_MS = 50;
const unsigned long DISPLAY_UPDATE_INTERVAL_MS = 5000;						// time between switching display to next "screen"
const unsigned long ONE_DAY_IN_MS = 24 * 60 * 60 * 1000;
const unsigned long PAUSE_BETWEEN_UPDATE_ATTEMPTS_MS = ONE_DAY_IN_MS;		// check for firmware updates once a day
const unsigned long DURATION_BEFORE_FORCED_RESTART_MS = ONE_DAY_IN_MS * 28;	// force a reboot every ~4 weeks

/******************************************************************
 * The variables inside the cfg namespace are persistent          *
 * configuration values. They have defaults which can be          *
 * configured at compile-time via the ext_def.h file              *
 * They can be changed by the user via the web interface, the     *
 * changes are persisted to the flash and read back after reboot. *
 * Note that the names of these variables can't be easily changed *
 * as they are part of the json format used to persist the data.  *
 ******************************************************************/
namespace cfg {
	unsigned debug = DEBUG;

	unsigned int time_for_wifi_config = 600000;
	unsigned int sending_intervall_ms = 145000;

	char current_lang[3];

	// credentials for basic auth of internal web server
	bool www_basicauth_enabled = WWW_BASICAUTH_ENABLED;
	char www_username[LEN_WWW_USERNAME];
	char www_password[LEN_CFG_PASSWORD];

	// wifi credentials
	char wlanssid[LEN_WLANSSID];
	char wlanpwd[LEN_CFG_PASSWORD];

	// credentials of the sensor in access point mode
	char fs_ssid[LEN_FS_SSID] = FS_SSID;
	char fs_pwd[LEN_CFG_PASSWORD] = FS_PWD;

	// (in)active sensors
	bool dht_read = DHT_READ;
	bool htu21d_read = HTU21D_READ;
	bool ppd_read = PPD_READ;
	bool sds_read = SDS_READ;
	bool pms_read = PMS_READ;
	bool hpm_read = HPM_READ;
	bool sps30_read = SPS30_READ;
	bool bmp_read = BMP_READ;
	bool bmx280_read = BMX280_READ;
	bool ds18b20_read = DS18B20_READ;
	bool dnms_read = DNMS_READ;
	char dnms_correction[LEN_DNMS_CORRECTION] = DNMS_CORRECTION;
	bool gps_read = GPS_READ;

	// send to "APIs"
	bool send2dusti = SEND2DUSTI;
	bool send2madavi = SEND2MADAVI;
	bool send2sensemap = SEND2SENSEMAP;
	bool send2fsapp = SEND2FSAPP;
	bool send2aircms = SEND2AIRCMS;
	bool send2custom = SEND2CUSTOM;
	bool send2influx = SEND2INFLUX;
	bool send2csv = SEND2CSV;

	bool auto_update = AUTO_UPDATE;
	bool use_beta = USE_BETA;

	// (in)active displays
	bool has_display = HAS_DISPLAY;											// OLED with SSD1306 and I2C
	bool has_sh1106 = HAS_SH1106;
	bool has_flipped_display = HAS_FLIPPED_DISPLAY;
	bool has_lcd1602 = HAS_LCD1602;
	bool has_lcd1602_27 = HAS_LCD1602_27;
	bool has_lcd2004_27 = HAS_LCD2004_27;

	bool display_wifi_info = DISPLAY_WIFI_INFO;
	bool display_device_info = DISPLAY_DEVICE_INFO;

	// API settings
	bool ssl_madavi = SSL_MADAVI;
	bool ssl_dusti = SSL_DUSTI;
	char senseboxid[LEN_SENSEBOXID] = SENSEBOXID;

	char host_influx[LEN_HOST_INFLUX];
	char url_influx[LEN_URL_INFLUX];
	unsigned int port_influx = PORT_INFLUX;
	char user_influx[LEN_USER_INFLUX] = USER_INFLUX;
	char pwd_influx[LEN_CFG_PASSWORD] = PWD_INFLUX;
	char measurement_name_influx[LEN_MEASUREMENT_NAME_INFLUX];
	bool ssl_influx = SSL_INFLUX;

	char host_custom[LEN_HOST_CUSTOM];
	char url_custom[LEN_URL_CUSTOM];
	bool ssl_custom = SSL_CUSTOM;
	unsigned int port_custom = PORT_CUSTOM;
	char user_custom[LEN_USER_CUSTOM] = USER_CUSTOM;
	char pwd_custom[LEN_CFG_PASSWORD] = PWD_CUSTOM;

	void initNonTrivials(const char* id) {
		strcpy(cfg::current_lang, CURRENT_LANG);
		strcpy_P(www_username, WWW_USERNAME);
		strcpy_P(www_password, WWW_PASSWORD);
		strcpy_P(wlanssid, WLANSSID);
		strcpy_P(wlanpwd, WLANPWD);
		strcpy_P(host_custom, HOST_CUSTOM);
		strcpy_P(url_custom, URL_CUSTOM);
		strcpy_P(host_influx, HOST_INFLUX);
		strcpy_P(url_influx, URL_INFLUX);
		strcpy_P(measurement_name_influx, MEASUREMENT_NAME_INFLUX);

		if (fs_ssid[0] == '\0') {
			strcpy(fs_ssid, SSID_BASENAME);
			strcat(fs_ssid, id);
		}
	}
}

#define JSON_BUFFER_SIZE 2300

String empty_String;

enum class PmSensorCmd {
	Start,
	Stop,
	ContinuousMode,
	VersionDate
};

String basic_auth_influx;
String basic_auth_custom;

long int sample_count = 0;
bool htu21d_init_failed = false;
bool bmp_init_failed = false;
bool bmx280_init_failed = false;
bool dnms_init_failed = false;
bool gps_init_failed = false;

#if defined(ESP8266)
ESP8266WebServer server(80);
#endif
#if defined(ESP32)
WebServer server(80);
#endif

#include "./airrohr-cfg.h"

/*****************************************************************
 * Variables for Noise Measurement DNMS                          *
 *****************************************************************/
float last_value_dnms_laeq = -1.0;
float last_value_dnms_la_min = -1.0;
float last_value_dnms_la_max = -1.0;

/*****************************************************************
 * Display definitions                                           *
 *****************************************************************/
SSD1306 display(0x3c, I2C_PIN_SDA, I2C_PIN_SCL);
SH1106 display_sh1106(0x3c, I2C_PIN_SDA, I2C_PIN_SCL);
LiquidCrystal_I2C lcd_1602_27(0x27, 16, 2);
LiquidCrystal_I2C lcd_1602_3f(0x3F, 16, 2);
LiquidCrystal_I2C lcd_2004_27(0x27, 20, 4);

/*****************************************************************
 * SDS011 declarations                                           *
 *****************************************************************/
#if defined(ESP8266)
SoftwareSerial serialSDS(PM_SERIAL_RX, PM_SERIAL_TX, false, 128);
SoftwareSerial* serialGPS;
#endif
#if defined(ESP32)
#define serialSDS (Serial1)
#define serialGPS (Serial2)
#endif

/*****************************************************************
 * DHT declaration                                               *
 *****************************************************************/
DHT dht(ONEWIRE_PIN, DHT_TYPE);

/*****************************************************************
 * HTU21D declaration                                            *
 *****************************************************************/
Adafruit_HTU21DF htu21d;

/*****************************************************************
 * BMP declaration                                               *
 *****************************************************************/
Adafruit_BMP085 bmp;

/*****************************************************************
 * BMP/BME280 declaration                                        *
 *****************************************************************/
BMX280 bmx280;

/*****************************************************************
 * DS18B20 declaration                                            *
 *****************************************************************/
OneWire oneWire(ONEWIRE_PIN);
DallasTemperature ds18b20(&oneWire);

/*****************************************************************
 * GPS declaration                                               *
 *****************************************************************/
TinyGPSPlus gps;

/*****************************************************************
 * Variable Definitions for PPD24NS                              *
 * P1 for PM10 & P2 for PM25                                     *
 *****************************************************************/

boolean trigP1 = false;
boolean trigP2 = false;
unsigned long trigOnP1;
unsigned long trigOnP2;

unsigned long lowpulseoccupancyP1 = 0;
unsigned long lowpulseoccupancyP2 = 0;

bool send_now = false;
unsigned long starttime;
unsigned long time_point_device_start_ms;
unsigned long starttime_SDS;
unsigned long starttime_GPS;
unsigned long act_micro;
unsigned long act_milli;
unsigned long last_micro = 0;
unsigned long min_micro = 1000000000;
unsigned long max_micro = 0;

bool is_SDS_running = true;
bool is_PMS_running = true;
bool is_HPM_running = true;

unsigned long sending_time = 0;
unsigned long last_update_attempt;

float last_value_BMP_T = -128.0;
float last_value_BMP_P = -1.0;
float last_value_BMX280_T = -128.0;
float last_value_BMX280_P = -1.0;
float last_value_BME280_H = -1.0;
float last_value_DHT_T = -128.0;
float last_value_DHT_H = -1.0;
float last_value_DS18B20_T = -1.0;
float last_value_HTU21D_T = -128.0;
float last_value_HTU21D_H = -1.0;

int sds_pm10_sum = 0;
int sds_pm25_sum = 0;
int sds_val_count = 0;
int sds_pm10_max = 0;
int sds_pm10_min = 20000;
int sds_pm25_max = 0;
int sds_pm25_min = 20000;

int pms_pm1_sum = 0;
int pms_pm10_sum = 0;
int pms_pm25_sum = 0;
int pms_val_count = 0;
int pms_pm1_max = 0;
int pms_pm1_min = 20000;
int pms_pm10_max = 0;
int pms_pm10_min = 20000;
int pms_pm25_max = 0;
int pms_pm25_min = 20000;

int hpm_pm10_sum = 0;
int hpm_pm25_sum = 0;
int hpm_val_count = 0;
int hpm_pm10_max = 0;
int hpm_pm10_min = 20000;
int hpm_pm25_max = 0;
int hpm_pm25_min = 20000;

float last_value_SPS30_P0 = -1.0;
float last_value_SPS30_P1 = -1.0;
float last_value_SPS30_P2 = -1.0;
float last_value_SPS30_P3 = -1.0;
float last_value_SPS30_N0 = -1.0;
float last_value_SPS30_N1 = -1.0;
float last_value_SPS30_N2 = -1.0;
float last_value_SPS30_N3 = -1.0;
float last_value_SPS30_N4 = -1.0;
float last_value_SPS30_TS = -1.0;
float value_SPS30_P0 = 0.0;
float value_SPS30_P1 = 0.0;
float value_SPS30_P2 = 0.0;
float value_SPS30_P3 = 0.0;
float value_SPS30_N0 = 0.0;
float value_SPS30_N1 = 0.0;
float value_SPS30_N2 = 0.0;
float value_SPS30_N3 = 0.0;
float value_SPS30_N4 = 0.0;
float value_SPS30_TS = 0.0;


uint16_t SPS30_measurement_count = 0;
unsigned long SPS30_read_counter = 0;
unsigned long SPS30_read_error_counter = 0;
unsigned long SPS30_read_timer = 0;
bool sps30_init_failed = false;

float last_value_PPD_P1 = -1.0;
float last_value_PPD_P2 = -1.0;
double last_value_SDS_P1 = -1.0;
double last_value_SDS_P2 = -1.0;
double last_value_PMS_P0 = -1.0;
double last_value_PMS_P1 = -1.0;
double last_value_PMS_P2 = -1.0;
double last_value_HPM_P1 = -1.0;
double last_value_HPM_P2 = -1.0;
double last_value_GPS_lat = -200.0;
double last_value_GPS_lon = -200.0;
double last_value_GPS_alt = -1000.0;
String last_value_GPS_date;
String last_value_GPS_time;
String last_data_string;

String esp_chipid;

unsigned long last_page_load = millis();

bool wificonfig_loop = false;
bool first_cycle = true;
bool sntp_time_is_set = false;

unsigned long count_sends = 0;
unsigned long next_display_millis = 0;
uint8_t next_display_count = 0;

struct struct_wifiInfo {
	char ssid[LEN_WLANSSID];
	uint8_t encryptionType;
	int32_t RSSI;
	int32_t channel;
#if defined(ESP8266)
	bool isHidden;
#endif
};

struct struct_wifiInfo *wifiInfo;
uint8_t count_wifiInfo;

template<typename T, std::size_t N> constexpr std::size_t array_num_elements(const T(&)[N]) {
	return N;
}

#define msSince(timestamp_before) (act_milli - (timestamp_before))

const char data_first_part[] PROGMEM = "{\"software_version\": \"" SOFTWARE_VERSION_STR "\", \"sensordatavalues\":[";

/*****************************************************************
 * Debug output                                                  *
 *****************************************************************/

#define debug_level_check(level) if(level > cfg::debug) return;

static void debug_out(const String& text, unsigned int level) {
	debug_level_check(level); Serial.print(text);
}

static void debug_out(const __FlashStringHelper* text, unsigned int level) {
	debug_level_check(level); Serial.print(text);
}

static void debug_outln(const String& text, unsigned int level) {
	debug_level_check(level); Serial.println(text);
}

static void debug_outln_info(const String& text) {
	debug_level_check(DEBUG_MIN_INFO); Serial.println(text);
}

static void debug_outln_verbose(const String& text) {
	debug_level_check(DEBUG_MED_INFO); Serial.println(text);
}

static void debug_outln_error(const __FlashStringHelper* text) {
	debug_level_check(DEBUG_ERROR); Serial.println(text);
}

static void debug_outln_info(const __FlashStringHelper* text) {
	debug_level_check(DEBUG_MIN_INFO); Serial.println(text);
}

static void debug_outln_verbose(const __FlashStringHelper* text) {
	debug_level_check(DEBUG_MED_INFO); Serial.println(text);
}

static void debug_outln_info(const __FlashStringHelper* text, const String& option) {
	debug_level_check(DEBUG_MIN_INFO);
	Serial.print(text);
	Serial.println(option);
}

static void debug_outln_info(const __FlashStringHelper* text, float value) {
	debug_outln_info(text, String(value));
}

static void debug_outln_verbose(const __FlashStringHelper* text, const String& option) {
	debug_level_check(DEBUG_MED_INFO);
	Serial.print(text);
	Serial.println(option);
}

static void debug_outln_info_bool(const __FlashStringHelper* text, const bool option) {
	debug_level_check(DEBUG_MIN_INFO);
	Serial.print(text);
	Serial.println(String(option));
}

#undef debug_level_check

/*****************************************************************
 * display values                                                *
 *****************************************************************/
static void display_debug(const String& text1, const String& text2) {
	debug_outln_info(F("output debug text to displays..."));
	if (cfg::has_display) {
		display.clear();
		display.displayOn();
		display.setTextAlignment(TEXT_ALIGN_LEFT);
		display.drawString(0, 12, text1);
		display.drawString(0, 24, text2);
		display.display();
	}
	if (cfg::has_sh1106) {
		display_sh1106.clear();
		display_sh1106.displayOn();
		display_sh1106.setTextAlignment(TEXT_ALIGN_LEFT);
		display_sh1106.drawString(0, 12, text1);
		display_sh1106.drawString(0, 24, text2);
		display_sh1106.display();
	}
	if (cfg::has_lcd1602) {
		lcd_1602_3f.clear();
		lcd_1602_3f.setCursor(0, 0);
		lcd_1602_3f.print(text1);
		lcd_1602_3f.setCursor(0, 1);
		lcd_1602_3f.print(text2);
	}
	if (cfg::has_lcd1602_27) {
		lcd_1602_27.clear();
		lcd_1602_27.setCursor(0, 0);
		lcd_1602_27.print(text1);
		lcd_1602_27.setCursor(0, 1);
		lcd_1602_27.print(text2);
	}
	if (cfg::has_lcd2004_27) {
		lcd_2004_27.clear();
		lcd_2004_27.setCursor(0, 0);
		lcd_2004_27.print(text1);
		lcd_2004_27.setCursor(0, 1);
		lcd_2004_27.print(text2);
	}
}

/*****************************************************************
 * check display values, return '-' if undefined                 *
 *****************************************************************/
static String check_display_value(double value, double undef, uint8_t len, uint8_t str_len) {
	RESERVE_STRING(s, 15);
	s = (value != undef ? String(value, len) : "-");
	while (s.length() < str_len) {
		s = " " + s;
	}
	return s;
}

/*****************************************************************
 * add value to json string                                  *
 *****************************************************************/
static void add_Value2Json(String& res, const __FlashStringHelper* type, const String& value) {
	RESERVE_STRING(s, SMALL_STR);

	s = F("{\"value_type\":\"{t}\",\"value\":\"{v}\"},");
	s.replace("{t}", String(type));
	s.replace("{v}", value);
	res += s;
}

static void add_Value2Json(String& res, const __FlashStringHelper* type, const float& value) {
	add_Value2Json(res, type, String(value));
}

/*****************************************************************
 * send SDS011 command (start, stop, continuous mode, version    *
 *****************************************************************/
static bool SDS_cmd(PmSensorCmd cmd) {
	static constexpr uint8_t start_cmd[] PROGMEM = {
		0xAA, 0xB4, 0x06, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x06, 0xAB
	};
	static constexpr uint8_t stop_cmd[] PROGMEM = {
		0xAA, 0xB4, 0x06, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x05, 0xAB
	};
	static constexpr uint8_t continuous_mode_cmd[] PROGMEM = {
		0xAA, 0xB4, 0x08, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x07, 0xAB
	};
	static constexpr uint8_t version_cmd[] PROGMEM = {
		0xAA, 0xB4, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x05, 0xAB
	};
	constexpr uint8_t cmd_len = array_num_elements(start_cmd);

	uint8_t buf[cmd_len];
	switch (cmd) {
	case PmSensorCmd::Start:
		memcpy_P(buf, start_cmd, cmd_len);
		break;
	case PmSensorCmd::Stop:
		memcpy_P(buf, stop_cmd, cmd_len);
		break;
	case PmSensorCmd::ContinuousMode:
		memcpy_P(buf, continuous_mode_cmd, cmd_len);
		break;
	case PmSensorCmd::VersionDate:
		memcpy_P(buf, version_cmd, cmd_len);
		break;
	}
	serialSDS.write(buf, cmd_len);
	return cmd != PmSensorCmd::Stop;
}

/*****************************************************************
 * send Plantower PMS sensor command start, stop, cont. mode     *
 *****************************************************************/
static bool PMS_cmd(PmSensorCmd cmd) {
	static constexpr uint8_t start_cmd[] PROGMEM = {
		0x42, 0x4D, 0xE4, 0x00, 0x01, 0x01, 0x74
	};
	static constexpr uint8_t stop_cmd[] PROGMEM = {
		0x42, 0x4D, 0xE4, 0x00, 0x00, 0x01, 0x73
	};
	static constexpr uint8_t continuous_mode_cmd[] PROGMEM = {
		0x42, 0x4D, 0xE1, 0x00, 0x01, 0x01, 0x71
	};
	constexpr uint8_t cmd_len = array_num_elements(start_cmd);

	uint8_t buf[cmd_len];
	switch (cmd) {
	case PmSensorCmd::Start:
		memcpy_P(buf, start_cmd, cmd_len);
		break;
	case PmSensorCmd::Stop:
		memcpy_P(buf, stop_cmd, cmd_len);
		break;
	case PmSensorCmd::ContinuousMode:
		memcpy_P(buf, continuous_mode_cmd, cmd_len);
		break;
	case PmSensorCmd::VersionDate:
		assert(false && "not supported by this sensor");
		break;
	}
	serialSDS.write(buf, cmd_len);
	return cmd != PmSensorCmd::Stop;
}

/*****************************************************************
 * send Honeywell PMS sensor command start, stop, cont. mode     *
 *****************************************************************/
static bool HPM_cmd(PmSensorCmd cmd) {
	static constexpr uint8_t start_cmd[] PROGMEM = {
		0x68, 0x01, 0x01, 0x96
	};
	static constexpr uint8_t stop_cmd[] PROGMEM = {
		0x68, 0x01, 0x02, 0x95
	};
	static constexpr uint8_t continuous_mode_cmd[] PROGMEM = {
		0x68, 0x01, 0x40, 0x57
	};
	constexpr uint8_t cmd_len = array_num_elements(start_cmd);

	uint8_t buf[cmd_len];
	switch (cmd) {
	case PmSensorCmd::Start:
		memcpy_P(buf, start_cmd, cmd_len);
		break;
	case PmSensorCmd::Stop:
		memcpy_P(buf, stop_cmd, cmd_len);
		break;
	case PmSensorCmd::ContinuousMode:
		memcpy_P(buf, continuous_mode_cmd, cmd_len);
		break;
	case PmSensorCmd::VersionDate:
		assert(false && "not supported by this sensor");
		break;
	}
	serialSDS.write(buf, cmd_len);
	return cmd != PmSensorCmd::Stop;
}

/*****************************************************************
 * read SDS011 sensor serial and firmware date                   *
 *****************************************************************/
static String SDS_version_date() {
	char buffer;
	int value;
	int len = 0;
	String s, version_date, device_id;
	int checksum_is = 0;
	int checksum_ok = 0;

	debug_outln_verbose(FPSTR(DBG_TXT_END_READING), FPSTR(DBG_TXT_SDS011_VERSION_DATE));

	is_SDS_running = SDS_cmd(PmSensorCmd::Start);

	delay(100);

	is_SDS_running = SDS_cmd(PmSensorCmd::VersionDate);

	delay(500);

	while (serialSDS.available() > 0) {
		buffer = serialSDS.read();
		debug_outln(String(len) + " - " + String(buffer, DEC) + " - " + String(buffer, HEX) + " - " + int(buffer) + " .", DEBUG_MED_INFO);
//		"aa" = 170, "ab" = 171, "c0" = 192
		value = int(buffer);
		switch (len) {
		case 0:
			if (value != 170) {
				len = -1;
			};
			break;
		case 1:
			if (value != 197) {
				len = -1;
			};
			break;
		case 2:
			if (value != 7) {
				len = -1;
			};
			checksum_is = 7;
			break;
		case 3:
			version_date = String(value);
			break;
		case 4:
			version_date += '-';
			version_date += String(value);
			break;
		case 5:
			version_date += '-';
			version_date += String(value);
			break;
		case 6:
			if (value < 0x10) {
				device_id = "0" + String(value, HEX);
			} else {
				device_id = String(value, HEX);
			};
			break;
		case 7:
			if (value < 0x10) {
				device_id += '0';
			};
			device_id += String(value, HEX);
			break;
		case 8:
			debug_outln_verbose(FPSTR(DBG_TXT_CHECKSUM_IS), String(checksum_is % 256));
			debug_outln_verbose(FPSTR(DBG_TXT_CHECKSUM_SHOULD), String(value));
			if (value == (checksum_is % 256)) {
				checksum_ok = 1;
			} else {
				len = -1;
			};
			break;
		case 9:
			if (value != 171) {
				len = -1;
			};
			break;
		}
		if (len > 2) { checksum_is += value; }
		len++;
		if (len == 10 && checksum_ok == 1) {
			s = version_date + '(' + device_id + ')';
			debug_outln_info(F("SDS version date : "), version_date);
			debug_outln_info(F("SDS device ID: "), device_id);
			len = 0;
			checksum_ok = 0;
			version_date = "";
			device_id = "";
			checksum_is = 0;
		}
		yield();
	}

	debug_outln_verbose(FPSTR(DBG_TXT_END_READING), FPSTR(DBG_TXT_SDS011_VERSION_DATE));

	return s;
}

/*****************************************************************
 * disable unneeded NMEA sentences, TinyGPS++ needs GGA, RMC     *
 *****************************************************************/
static void disable_unneeded_nmea() {
	serialGPS->println(F("$PUBX,40,GLL,0,0,0,0*5C"));       // Geographic position, latitude / longitude
//	serialGPS->println(F("$PUBX,40,GGA,0,0,0,0*5A"));       // Global Positioning System Fix Data
	serialGPS->println(F("$PUBX,40,GSA,0,0,0,0*4E"));       // GPS DOP and active satellites
//	serialGPS->println(F("$PUBX,40,RMC,0,0,0,0*47"));       // Recommended minimum specific GPS/Transit data
	serialGPS->println(F("$PUBX,40,GSV,0,0,0,0*59"));       // GNSS satellites in view
	serialGPS->println(F("$PUBX,40,VTG,0,0,0,0*5E"));       // Track made good and ground speed
}


/*****************************************************************
 * read config from spiffs                                       *
 *****************************************************************/

/* backward compatibility for the times when we stored booleans as strings */
static bool boolFromJSON(const DynamicJsonDocument& json, const char* key)
{
	if (json[key].is<char*>()) {
		return !strcmp(json[key].as<char*>(), "true");
	}
	return json[key].as<bool>();
}

static void readConfig() {
	debug_outln_info(F("mounting FS..."));

#if defined(ESP32)
	bool spiffs_begin_ok = SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED);
#else
	bool spiffs_begin_ok = SPIFFS.begin();
#endif

	if (!spiffs_begin_ok) {
		debug_outln_error(F("failed to mount FS"));
		return;
	}

	File configFile = SPIFFS.open("/config.json", "r");
	if (!configFile) {
		debug_outln_error(F("config file not found ..."));
		return;
	}

	debug_outln_info(F("opened config file..."));
	DynamicJsonDocument json(JSON_BUFFER_SIZE);
	DeserializationError err = deserializeJson(json, configFile);
	configFile.close();

	if (!err) {
		debug_outln_info(F("parsed json..."));
		for (unsigned e = 0; e < sizeof(configShape)/sizeof(configShape[0]); ++e) {
			ConfigShapeEntry c;
			memcpy_P(&c, &configShape[e], sizeof(ConfigShapeEntry));
			char* cfg_key = const_cast<char*>(c.cfg_key);
			if (json[cfg_key].isNull()) {
				continue;
			}
			switch (c.cfg_type) {
				case Config_Type_Bool:
					*(c.cfg_val.as_bool) = boolFromJSON(json, cfg_key);
					break;
				case Config_Type_UInt:
					*(c.cfg_val.as_uint) = json[cfg_key].as<unsigned int>();
					break;
				case Config_Type_String:
				case Config_Type_Password:
					strcpy(c.cfg_val.as_str, json[cfg_key].as<char*>());
					break;
			};
		}

		if (strcmp_P(cfg::senseboxid, PSTR("00112233445566778899aabb")) == 0) {
			cfg::senseboxid[0] = '\0';
			cfg::send2sensemap = false;
		}
		if (strlen(cfg::measurement_name_influx) == 0) {
			strcpy_P(cfg::measurement_name_influx, MEASUREMENT_NAME_INFLUX);
		}
		if (strcmp_P(cfg::host_influx, PSTR("api.luftdaten.info")) == 0) {
			cfg::host_influx[0] = '\0';
			cfg::send2influx = false;
		}
		if (boolFromJSON(json, "pm24_read") || boolFromJSON(json, "pms32_read")) {
			cfg::pms_read = true;
			writeConfig();
		}
		if (boolFromJSON(json, "bmp280_read") || boolFromJSON(json, "bme280_read")) {
			cfg::bmx280_read = true;
			writeConfig();
		}

	} else {
		debug_outln_error(F("failed to load json config"));
	}
}

/*****************************************************************
 * write config to spiffs                                        *
 *****************************************************************/
void writeConfig() {
	DynamicJsonDocument json(JSON_BUFFER_SIZE);
	debug_outln_info(F("Saving config..."));
	json["SOFTWARE_VERSION"] = SOFTWARE_VERSION;

	for (unsigned e = 0; e < sizeof(configShape)/sizeof(configShape[0]); ++e) {
		ConfigShapeEntry c;
		memcpy_P(&c, &configShape[e], sizeof(ConfigShapeEntry));
		char* cfg_key = const_cast<char*>(c.cfg_key);
		switch (c.cfg_type) {
		case Config_Type_Bool:
			json[cfg_key].set(*c.cfg_val.as_bool);
			break;
		case Config_Type_UInt:
			json[cfg_key].set(*c.cfg_val.as_uint);
			break;
		case Config_Type_Password:
		case Config_Type_String:
			json[cfg_key].set(c.cfg_val.as_str);
			break;
		};
	}

	File configFile = SPIFFS.open("/config.json", "w");
	if (configFile) {
		debug_outln_info(F("Before writing config.."));
		serializeJson(json, configFile);
		configFile.close();
		debug_outln_info(F("Config written successfully."));
	} else {
		debug_outln_error(F("failed to open config file for writing"));
	}
}

/*****************************************************************
 * Base64 encode user:password                                   *
 *****************************************************************/
static void create_basic_auth_strings() {
	basic_auth_custom = "";
	if (cfg::user_custom[0] != '\0' || cfg::pwd_custom[0] != '\0') {
		basic_auth_custom = base64::encode(String(cfg::user_custom) + ':' + String(cfg::pwd_custom));
	}
	basic_auth_influx = "";
	if (cfg::user_influx[0] != '\0' || cfg::pwd_influx[0] != '\0') {
		basic_auth_influx = base64::encode(String(cfg::user_influx) + ':' + String(cfg::pwd_influx));
	}
}

/*****************************************************************
 * aircms.online helper functions                                *
 *****************************************************************/
static String sha1Hex(const String& s) {
#if defined(ESP8266)
	return sha1(s);
#endif
#if defined(ESP32)
	char sha1sum_output[21];
	esp_sha(SHA1, (const unsigned char*) s.c_str(), s.length(), (unsigned char*)sha1sum_output);
	return String(sha1sum_output);
#endif
}

static String hmac1(const String& secret, const String& s) {
	String str = sha1Hex(s);
	str = secret + str;
	return sha1Hex(str);
}

/*****************************************************************
 * html helper functions                                         *
 *****************************************************************/

static void start_html_page(String& page_content, const String& title) {
	last_page_load = millis();

	RESERVE_STRING(s, LARGE_STR);
	s = FPSTR(WEB_PAGE_HEADER);
	s.replace("{t}", title);
	server.setContentLength(CONTENT_LENGTH_UNKNOWN);
	server.send(200, FPSTR(TXT_CONTENT_TYPE_TEXT_HTML), s);

	server.sendContent_P(WEB_PAGE_HEADER_HEAD);

	s = FPSTR(WEB_PAGE_HEADER_BODY);
	s.replace("{t}", title);
	if(title != " ") {
		s.replace("{n}", F("&raquo;"));
	} else {
		s.replace("{n}", empty_String);
	}
	s.replace("{id}", esp_chipid);
	s.replace("{mac}", WiFi.macAddress());
	page_content += s;
}

static void end_html_page(String& page_content) {
	if (page_content.length()) {
		server.sendContent(page_content);
	}
	server.sendContent_P(WEB_PAGE_FOOTER);
}

static void add_form_input(String& page_content, const char* name, const __FlashStringHelper* info, const String& value, const int length) {
	RESERVE_STRING(s, MED_STR);
	s = F(	"<tr>"
					"<td>{i} </td>"
					"<td style='width:90%;'>"
					"<input type='text' name='{n}' id='{n}' placeholder='{i}' value='{v}' maxlength='{l}'/>"
					"</td>"
					"</tr>");
	String t_value = value;
	t_value.replace("'", "&#39;");
	s.replace("{i}", info);
	s.replace("{n}", String(name));
	s.replace("{v}", t_value);
	s.replace("{l}", String(length));
	page_content += s;
}

static String form_password(const char* name, const String& info, const String& value, const int length) {
	String s = F(	"<tr>"
					"<td>{i} </td>"
					"<td style='width:90%;'>"
					"<input type='password' name='{n}' id='{n}' placeholder='{i}' value='{v}' maxlength='{l}'/>"
					"</td>"
					"</tr>");
	String password;
	for (uint8_t i = 0; i < value.length(); i++) {
		password += '*';
	}
	s.replace("{i}", info);
	s.replace("{n}", name);
	s.replace("{v}", password);
	s.replace("{l}", String(length));
	return s;
}

static String form_checkbox(const char* name, const String& info, const bool checked, const bool linebreak) {
	RESERVE_STRING(s, MED_STR);
	s = F("<label for='{n}'>"
	"<input type='checkbox' name='{n}' value='1' id='{n}' {c}/>"
	"<input type='hidden' name='{n}' value='0'/>"
	"{i}</label><br/>");
	if (checked) {
		s.replace("{c}", F(" checked='checked'"));
	} else {
		s.replace("{c}", empty_String);
	};
	s.replace("{i}", info);
	s.replace("{n}", name);
	if (! linebreak) {
		s.replace("<br/>", empty_String);
	}
	return s;
}

static void add_form_checkbox(String& page_content, const char* name, const String& info, const bool checked) {
	page_content += form_checkbox(name, info, checked, true);
}

static void add_form_checkbox_sensor(String& page_content, const char* name, const __FlashStringHelper* info, const bool checked) {
	add_form_checkbox(page_content, name, add_sensor_type(info), checked);
}

static String form_submit(const String& value) {
	String s = F(	"<tr>"
					"<td>&nbsp;</td>"
					"<td>"
					"<input type='submit' name='submit' value='{v}' />"
					"</td>"
					"</tr>");
	s.replace("{v}", value);
	return s;
}

static String form_select_lang() {
	String s_select = F(" selected='selected'");
	String s = F(	"<tr>"
					"<td>" INTL_LANGUAGE "</td>"
					"<td>"
					"<select name='current_lang'>"
					"<option value='DE'>Deutsch (DE)</option>"
					"<option value='BG'>Bulgarian (BG)</option>"
					"<option value='CZ'>Český (CZ)</option>"
					"<option value='DK'>Dansk (DK)</option>"
					"<option value='EN'>English (EN)</option>"
					"<option value='ES'>Español (ES)</option>"
					"<option value='FR'>Français (FR)</option>"
					"<option value='IT'>Italiano (IT)</option>"
					"<option value='LU'>Lëtzebuergesch (LU)</option>"
					"<option value='NL'>Nederlands (NL)</option>"
					"<option value='PL'>Polski (PL)</option>"
					"<option value='PT'>Português (PT)</option>"
					"<option value='RU'>Русский (RU)</option>"
					"<option value='SE'>Svenska (SE)</option>"
					"<option value='TR'>Türkçe (TR)</option>"
					"<option value='UA'>Мова (UA)</option>"
					"</select>"
					"</td>"
					"</tr>");

	s.replace("'" + String(cfg::current_lang) + "'>", "'" + String(cfg::current_lang) + "'" + s_select + ">");
	return s;
}

static String tmpl(const __FlashStringHelper* patt, const String& value) {
	String s = patt;
	s.replace("{v}", value);
	return s;
}

static void add_line_value(String& s, const __FlashStringHelper* name, const String& value) {
	s += F("<br/>");
	s += name;
	s += ": ";
	s += value;
}

static void add_line_value_bool(String& s, const __FlashStringHelper* name, const bool value) {
	add_line_value(s, name, String(value));
}

static void add_line_value_bool(String&s, const __FlashStringHelper* patt, const __FlashStringHelper* name, const bool value) {
	s += F("<br/>");
	s += tmpl(patt, name);
	s += ": ";
	s += String(value);
}

static void add_table_row_from_value(String& page_content, const __FlashStringHelper* sensor, const __FlashStringHelper* param, const String& value, const String& unit) {
	RESERVE_STRING(s, MED_STR);
	s = F("<tr><td>{s}</td><td>{p}</td><td class='r'>{v}&nbsp;{u}</td></tr>");
	s.replace("{s}", sensor);
	s.replace("{p}", param);
	s.replace("{v}", value);
	s.replace("{u}", unit);
	page_content += s;
}

static int32_t calcWiFiSignalQuality(int32_t rssi) {
	if (rssi > -50) {
		rssi = -50;
	}
	if (rssi < -100) {
		rssi = -100;
	}
	return (rssi + 100) * 2;
}

static String wlan_ssid_to_table_row(const String& ssid, const String& encryption, int32_t rssi) {
	String s = F(	"<tr>"
					"<td>"
					"<a href='#wlanpwd' onclick='setSSID(this)' class='wifi'>{n}</a>&nbsp;{e}"
					"</td>"
					"<td style='width:80%;vertical-align:middle;'>"
					"{v}%"
					"</td>"
					"</tr>");
	s.replace("{n}", ssid);
	s.replace("{e}", encryption);
	s.replace("{v}", String(calcWiFiSignalQuality(rssi)));
	return s;
}

static void add_warning_first_cycle(String& page_content) {
	String s = FPSTR(INTL_TIME_TO_FIRST_MEASUREMENT);
	unsigned int time_to_first = cfg::sending_intervall_ms - msSince(starttime);
	if (time_to_first > cfg::sending_intervall_ms) {
		time_to_first = 0;
	}
	s.replace("{v}", String(((time_to_first + 500) / 1000)));
	page_content += s;
}

static void add_age_last_values(String& s) {
	s += "<b>";
	unsigned int time_since_last = msSince(starttime);
	if (time_since_last > cfg::sending_intervall_ms) {
		time_since_last = 0;
	}
	s += String((time_since_last + 500) / 1000);
	s += FPSTR(INTL_TIME_SINCE_LAST_MEASUREMENT);
	s += FPSTR(WEB_B_BR_BR);
}

static String add_sensor_type(const String& sensor_text) {
	RESERVE_STRING(s, SMALL_STR);
	s = sensor_text;
	s.replace("{pm}", FPSTR(INTL_PARTICULATE_MATTER));
	s.replace("{t}", FPSTR(INTL_TEMPERATURE));
	s.replace("{h}", FPSTR(INTL_HUMIDITY));
	s.replace("{p}", FPSTR(INTL_PRESSURE));
	s.replace("{l_a}", FPSTR(INTL_LEQ_A));
	return s;
}

/*****************************************************************
 * Webserver request auth: prompt for BasicAuth
 *
 * -Provide BasicAuth for all page contexts except /values and images
 *****************************************************************/
static bool webserver_request_auth() {
	if (cfg::www_basicauth_enabled && ! wificonfig_loop) {
		debug_outln_info(F("validate request auth..."));
		if (!server.authenticate(cfg::www_username, cfg::www_password)) {
			server.requestAuthentication(BASIC_AUTH, "Sensor Login", F("Authentication failed"));
			return false;
		}
	}
	return true;
}

static void sendHttpRedirect() {
	server.sendHeader(F("Location"), F("http://192.168.4.1/config"));
	server.send(302, FPSTR(TXT_CONTENT_TYPE_TEXT_HTML), empty_String);
}

/*****************************************************************
 * Webserver root: show all options                              *
 *****************************************************************/
static void webserver_root() {
	if (WiFi.status() != WL_CONNECTED) {
		sendHttpRedirect();
	} else {
		if (!webserver_request_auth())
		{ return; }

		RESERVE_STRING(page_content, XLARGE_STR);
		start_html_page(page_content, empty_String);
		debug_outln_info(F("ws: root ..."));

		// Enable Pagination
		page_content += FPSTR(WEB_ROOT_PAGE_CONTENT);
		page_content.replace(F("{t}"), FPSTR(INTL_CURRENT_DATA));
		page_content.replace(F("{conf}"), FPSTR(INTL_CONFIGURATION));
		page_content.replace(F("{restart}"), FPSTR(INTL_RESTART_SENSOR));
		page_content.replace(F("{debug_setting}"), FPSTR(INTL_DEBUG_SETTING_TO));
		end_html_page(page_content);
	}
}

/*****************************************************************
 * Webserver config: show config page                            *
 *****************************************************************/

static void webserver_config_send_body_get(String& page_content) {
	using namespace cfg;

	debug_outln_info(F("begin webserver_config_body_get ..."));
	page_content += F("<form method='POST' action='/config' style='width:100%;'>\n<b>" INTL_WIFI_SETTINGS "</b><br/>");
	debug_outln_info(F("ws: config page 1"));
	if (wificonfig_loop) {  // scan for wlan ssids
		page_content += F("<div id='wifilist'>" INTL_WIFI_NETWORKS "</div><br/>");
	}
	page_content += FPSTR(TABLE_TAG_OPEN);
	add_form_input(page_content, "wlanssid", FPSTR(INTL_FS_WIFI_NAME), wlanssid, LEN_WLANSSID);
	page_content += form_password("wlanpwd", FPSTR(INTL_PASSWORD), wlanpwd, LEN_WLANSSID);
	page_content += FPSTR(TABLE_TAG_CLOSE_BR);
	page_content += F("<hr/>\n<br/><b>");

	page_content += FPSTR(INTL_AB_HIER_NUR_ANDERN);
	page_content += F("</b><br/><br/>\n<b>");

	// Paginate page after ~ 1500 Bytes
	server.sendContent(page_content);
	page_content = empty_String;

	if (! wificonfig_loop) {
		page_content += FPSTR(INTL_BASICAUTH);
		page_content += FPSTR(WEB_B_BR);
		add_form_checkbox(page_content, "www_basicauth_enabled", FPSTR(INTL_BASICAUTH), www_basicauth_enabled);
		page_content += FPSTR(TABLE_TAG_OPEN);
		add_form_input(page_content, "www_username", FPSTR(INTL_USER), www_username, LEN_WWW_USERNAME);
		page_content += form_password("www_password", FPSTR(INTL_PASSWORD), www_password, LEN_CFG_PASSWORD-1);
		page_content += FPSTR(TABLE_TAG_CLOSE_BR);

		// Paginate page after ~ 1500 Bytes
		server.sendContent(page_content);
		page_content = FPSTR(WEB_BR_LF_B);

		page_content += FPSTR(INTL_FS_WIFI);
		page_content += FPSTR(WEB_B_BR);
		page_content += FPSTR(INTL_FS_WIFI_DESCRIPTION);
		page_content += FPSTR(BR_TAG);
		page_content += FPSTR(TABLE_TAG_OPEN);
		add_form_input(page_content, "fs_ssid", FPSTR(INTL_FS_WIFI_NAME), fs_ssid, LEN_FS_SSID);
		page_content += form_password("fs_pwd", FPSTR(INTL_PASSWORD), fs_pwd, LEN_CFG_PASSWORD-1);
		page_content += FPSTR(TABLE_TAG_CLOSE_BR);

		page_content += FPSTR(WEB_BR_LF_B);

		page_content += F("APIs");
		page_content += FPSTR(WEB_B_BR);

		// Paginate page after ~ 1500 Bytes
		server.sendContent(page_content);
		page_content = form_checkbox("send2dusti", F("API Luftdaten.info"), send2dusti, false);
		page_content += FPSTR(WEB_NBSP_NBSP_BRACE);
		page_content += form_checkbox("ssl_dusti", FPSTR(WEB_HTTPS), ssl_dusti, false);
		page_content += FPSTR(WEB_BRACE_BR);
		page_content += form_checkbox("send2madavi", F("API Madavi.de"), send2madavi, false);
		page_content += FPSTR(WEB_NBSP_NBSP_BRACE);
		page_content += form_checkbox("ssl_madavi", FPSTR(WEB_HTTPS), ssl_madavi, false);
		page_content += FPSTR(WEB_BRACE_BR);

		page_content += FPSTR(WEB_BR_LF_B);

		// Paginate page after ~ 1500 Bytes
		server.sendContent(page_content);
		page_content = FPSTR(INTL_SENSORS);

		page_content += FPSTR(WEB_B_BR);
		add_form_checkbox_sensor(page_content, "sds_read", FPSTR(INTL_SDS011), sds_read);
		add_form_checkbox_sensor(page_content, "pms_read", FPSTR(INTL_PMS), pms_read);
		add_form_checkbox_sensor(page_content, "hpm_read", FPSTR(INTL_HPM), hpm_read);
		add_form_checkbox_sensor(page_content, "sps30_read", FPSTR(INTL_SPS30), sps30_read);
		add_form_checkbox_sensor(page_content, "ppd_read", FPSTR(INTL_PPD42NS), ppd_read);

		// Paginate page after ~ 1500 Bytes
		server.sendContent(page_content);
		page_content = empty_String;

		add_form_checkbox_sensor(page_content, "dht_read", FPSTR(INTL_DHT22), dht_read);
		add_form_checkbox_sensor(page_content, "htu21d_read", FPSTR(INTL_HTU21D), htu21d_read);
		add_form_checkbox_sensor(page_content, "bmp_read", FPSTR(INTL_BMP180), bmp_read);
		add_form_checkbox_sensor(page_content, "bmx280_read", FPSTR(INTL_BMX280), bmx280_read);
		add_form_checkbox_sensor(page_content, "ds18b20_read", FPSTR(INTL_DS18B20), ds18b20_read);

		// Paginate page after ~ 1500 Bytes
		server.sendContent(page_content);
		page_content = empty_String;

		add_form_checkbox_sensor(page_content, "dnms_read", FPSTR(INTL_DNMS), dnms_read);
		page_content += FPSTR(TABLE_TAG_OPEN);
		add_form_input(page_content, "dnms_correction", FPSTR(INTL_DNMS_CORRECTION), dnms_correction, LEN_DNMS_CORRECTION);
		page_content += FPSTR(TABLE_TAG_CLOSE_BR);
		add_form_checkbox(page_content, "gps_read", FPSTR(INTL_NEO6M), gps_read);

		page_content += FPSTR(WEB_BR_LF_B);

		// Paginate page after ~ 1500 Bytes
		server.sendContent(page_content);
		page_content = empty_String;
	}

	page_content += FPSTR(INTL_MORE_SETTINGS);
	page_content += FPSTR(WEB_B_BR);
	add_form_checkbox(page_content, "auto_update", FPSTR(INTL_AUTO_UPDATE), auto_update);
	add_form_checkbox(page_content, "use_beta", FPSTR(INTL_USE_BETA), use_beta);
	add_form_checkbox(page_content, "has_display", FPSTR(INTL_DISPLAY), has_display);
	add_form_checkbox(page_content, "has_sh1106", FPSTR(INTL_SH1106), has_sh1106);
	add_form_checkbox(page_content, "has_flipped_display", FPSTR(INTL_FLIP_DISPLAY), has_flipped_display);
	add_form_checkbox(page_content, "has_lcd1602_27", FPSTR(INTL_LCD1602_27), has_lcd1602_27);
	add_form_checkbox(page_content, "has_lcd1602", FPSTR(INTL_LCD1602_3F), has_lcd1602);
	add_form_checkbox(page_content, "has_lcd2004_27", FPSTR(INTL_LCD2004_27), has_lcd2004_27);
	add_form_checkbox(page_content, "display_wifi_info", FPSTR(INTL_DISPLAY_WIFI_INFO), display_wifi_info);
	add_form_checkbox(page_content, "display_device_info", FPSTR(INTL_DISPLAY_DEVICE_INFO), display_device_info);

	// Paginate page after ~ 1500 Bytes
	server.sendContent(page_content);
	page_content = empty_String;

	if (! wificonfig_loop) {
		page_content += FPSTR(TABLE_TAG_OPEN);
		page_content += form_select_lang();
		add_form_input(page_content, "debug", FPSTR(INTL_DEBUG_LEVEL), String(debug), 1);
		add_form_input(page_content, "sending_intervall_ms", FPSTR(INTL_MEASUREMENT_INTERVAL), String(sending_intervall_ms / 1000), 5);
		add_form_input(page_content, "time_for_wifi_config", FPSTR(INTL_DURATION_ROUTER_MODE), String(time_for_wifi_config / 1000), 5);
		page_content += FPSTR(TABLE_TAG_CLOSE_BR);
		page_content += FPSTR(WEB_BR_LF_B);

		server.sendContent(page_content);
		page_content = FPSTR(INTL_MORE_APIS);

		page_content += FPSTR(WEB_B_BR);
		add_form_checkbox(page_content, "send2csv", tmpl(FPSTR(INTL_SEND_TO), FPSTR(WEB_CSV)), send2csv);
		add_form_checkbox(page_content, "send2fsapp", tmpl(FPSTR(INTL_SEND_TO), FPSTR(WEB_FEINSTAUB_APP)), send2fsapp);
		add_form_checkbox(page_content, "send2aircms", tmpl(FPSTR(INTL_SEND_TO), F("aircms.online")), send2aircms);
		add_form_checkbox(page_content, "send2sensemap", tmpl(FPSTR(INTL_SEND_TO), F("OpenSenseMap")), send2sensemap);
		page_content += FPSTR(TABLE_TAG_OPEN);
		add_form_input(page_content, "senseboxid", F("senseBox&nbsp;ID: "), senseboxid, LEN_SENSEBOXID);

		server.sendContent(page_content);
		page_content = FPSTR(TABLE_TAG_CLOSE_BR);
		page_content += FPSTR(BR_TAG);
		page_content += form_checkbox("send2custom", FPSTR(INTL_SEND_TO_OWN_API), send2custom, false);
		page_content += FPSTR(WEB_NBSP_NBSP_BRACE);
		page_content += form_checkbox("ssl_custom", FPSTR(WEB_HTTPS), ssl_custom, false);
		page_content += FPSTR(WEB_BRACE_BR);

		server.sendContent(page_content);
		page_content = FPSTR(TABLE_TAG_OPEN);
		add_form_input(page_content, "host_custom", FPSTR(INTL_SERVER), host_custom, LEN_HOST_CUSTOM);
		add_form_input(page_content, "url_custom", FPSTR(INTL_PATH), url_custom, LEN_URL_CUSTOM);
		add_form_input(page_content, "port_custom", FPSTR(INTL_PORT), String(port_custom), MAX_PORT_DIGITS);
		add_form_input(page_content, "user_custom", FPSTR(INTL_USER), user_custom, LEN_USER_CUSTOM);
		page_content += form_password("pwd_custom", FPSTR(INTL_PASSWORD), pwd_custom, LEN_CFG_PASSWORD-1);
		page_content += FPSTR(TABLE_TAG_CLOSE_BR);

		page_content += FPSTR(BR_TAG);

		server.sendContent(page_content);
		page_content = form_checkbox("send2influx", tmpl(FPSTR(INTL_SEND_TO), F("InfluxDB")), send2influx, false);

		page_content += FPSTR(WEB_NBSP_NBSP_BRACE);
		page_content += form_checkbox("ssl_influx", FPSTR(WEB_HTTPS), ssl_influx, false);
		page_content += FPSTR(WEB_BRACE_BR);
		page_content += FPSTR(TABLE_TAG_OPEN);
		add_form_input(page_content, "host_influx", FPSTR(INTL_SERVER), host_influx, LEN_HOST_INFLUX);
		add_form_input(page_content, "url_influx", FPSTR(INTL_PATH), url_influx, LEN_URL_INFLUX);
		add_form_input(page_content, "port_influx", FPSTR(INTL_PORT), String(port_influx), MAX_PORT_DIGITS);
		add_form_input(page_content, "user_influx", FPSTR(INTL_USER), user_influx, LEN_USER_INFLUX);
		page_content += form_password("pwd_influx", FPSTR(INTL_PASSWORD), pwd_influx, LEN_CFG_PASSWORD-1);
		add_form_input(page_content, "measurement_name_influx", F("Measurement"), measurement_name_influx, LEN_MEASUREMENT_NAME_INFLUX);
		page_content += form_submit(FPSTR(INTL_SAVE_AND_RESTART));
		page_content += FPSTR(TABLE_TAG_CLOSE_BR);
		page_content += FPSTR(BR_TAG);
		page_content += FPSTR(WEB_BR_FORM);
	}
	if (wificonfig_loop) {  // scan for wlan ssids
		page_content += FPSTR(TABLE_TAG_OPEN);
		page_content += form_submit(FPSTR(INTL_SAVE_AND_RESTART));
		page_content += FPSTR(TABLE_TAG_CLOSE_BR);
		page_content += FPSTR(WEB_BR_FORM);
		page_content += F("<script>window.setTimeout(load_wifi_list,1000);</script>");
	}

	server.sendContent(page_content);
	page_content = empty_String;
}

static void webserver_config_send_body_post(String& page_content) {
	String masked_pwd;

	using namespace cfg;

#define readIntParam(param) \
		{ \
			int val = server.arg(#param).toInt(); \
			if (val != 0){ \
				param = val; \
			} \
		}

#define readTimeParam(param) { \
		const String s_param(#param); \
		if (server.hasArg(s_param)){ \
			param = server.arg(s_param).toInt() * 1000; \
		} \
	}

	if (! wificonfig_loop) {
		readIntParam(debug);
		readTimeParam(sending_intervall_ms);
		readTimeParam(time_for_wifi_config);
		readIntParam(port_custom);
		readIntParam(port_influx);
	}

	for (unsigned e = 0; e < sizeof(configShape)/sizeof(configShape[0]); ++e) {
		ConfigShapeEntry c;
		memcpy_P(&c, &configShape[e], sizeof(ConfigShapeEntry));
		const String s_param(c.cfg_key);

		switch (c.cfg_type) {
		case Config_Type_UInt:
			break;
		case Config_Type_Bool:
			if (server.hasArg(c.cfg_key)) {
				*(c.cfg_val.as_bool) = (server.arg(s_param) == "1");
			}
			break;
		case Config_Type_String:
			if (server.hasArg(s_param)) {
				strcpy(c.cfg_val.as_str, server.arg(s_param).c_str());
			}
			break;
		case Config_Type_Password:
			if (server.hasArg(s_param)) {
				const String server_arg(server.arg(s_param));
				masked_pwd = "";
				for (uint8_t i=0;i<server_arg.length();i++)
					masked_pwd += '*';
				if (masked_pwd != server_arg || !server_arg.length()) {
					server_arg.toCharArray(c.cfg_val.as_str, LEN_CFG_PASSWORD);
				}
			}
			break;
		}
	}

#undef readIntParam
#undef readTimeParam

	add_line_value_bool(page_content, FPSTR(INTL_SEND_TO), F("Luftdaten.info"), send2dusti);
	add_line_value_bool(page_content, FPSTR(INTL_SEND_TO), F("Madavi"), send2madavi);
	add_line_value_bool(page_content, FPSTR(INTL_READ_FROM), F("DHT"), dht_read);
	add_line_value_bool(page_content, FPSTR(INTL_READ_FROM), F("HTU21D"), htu21d_read);
	add_line_value_bool(page_content, FPSTR(INTL_READ_FROM), F("SDS"), sds_read);
	add_line_value_bool(page_content, FPSTR(INTL_READ_FROM), F("PMS(1,3,5,6,7)003"), pms_read);
	add_line_value_bool(page_content, FPSTR(INTL_READ_FROM), F("HPM"), hpm_read);
	add_line_value_bool(page_content, FPSTR(INTL_READ_FROM), F("SPS30"), sps30_read);
	add_line_value_bool(page_content, FPSTR(INTL_READ_FROM), F("PPD"), ppd_read);
	add_line_value_bool(page_content, FPSTR(INTL_READ_FROM), FPSTR(SENSORS_BMX280), bmx280_read);
	add_line_value_bool(page_content, FPSTR(INTL_READ_FROM), F("DS18B20"), ds18b20_read);
	add_line_value_bool(page_content, FPSTR(INTL_READ_FROM), F("DNMS"), dnms_read);
	add_line_value_bool(page_content, FPSTR(INTL_DNMS_CORRECTION), String(dnms_correction));
	add_line_value_bool(page_content, FPSTR(INTL_READ_FROM), F("GPS"), gps_read);

	// Paginate after ~ 1500 bytes
	server.sendContent(page_content);
	page_content = empty_String;

	add_line_value_bool(page_content, FPSTR(INTL_AUTO_UPDATE), auto_update);
	add_line_value_bool(page_content, FPSTR(INTL_USE_BETA), use_beta);
	add_line_value_bool(page_content, FPSTR(INTL_DISPLAY), has_display);
	add_line_value_bool(page_content, FPSTR(INTL_SH1106), has_sh1106);
	add_line_value_bool(page_content, FPSTR(INTL_FLIP_DISPLAY), has_flipped_display);
	add_line_value_bool(page_content, FPSTR(INTL_LCD1602_27), has_lcd1602_27);
	add_line_value_bool(page_content, FPSTR(INTL_LCD1602_3F), has_lcd1602);
	add_line_value_bool(page_content, FPSTR(INTL_LCD2004_27), has_lcd2004_27);
	add_line_value_bool(page_content, FPSTR(INTL_DISPLAY_WIFI_INFO), display_wifi_info);
	add_line_value_bool(page_content, FPSTR(INTL_DISPLAY_DEVICE_INFO), display_device_info);
	add_line_value(page_content, FPSTR(INTL_DEBUG_LEVEL), String(debug));
	add_line_value(page_content, FPSTR(INTL_MEASUREMENT_INTERVAL), String(sending_intervall_ms));
	add_line_value_bool(page_content, FPSTR(INTL_SEND_TO), F("Feinstaub-App"), send2fsapp);
	add_line_value_bool(page_content, FPSTR(INTL_SEND_TO), F("aircms.online"), send2aircms);
	add_line_value_bool(page_content, FPSTR(INTL_SEND_TO), FPSTR(WEB_CSV), send2csv);
	add_line_value_bool(page_content, FPSTR(INTL_SEND_TO), FPSTR(WEB_FEINSTAUB_APP), send2fsapp);
	add_line_value_bool(page_content, FPSTR(INTL_SEND_TO), F("opensensemap"), send2sensemap);

	// Paginate after ~ 1500 bytes
	server.sendContent(page_content);
	page_content = empty_String;

	page_content += F("<br/>senseBox-ID ");
	page_content += senseboxid;
	page_content += FPSTR(WEB_BR_BR);
	add_line_value_bool(page_content, FPSTR(INTL_SEND_TO_OWN_API), send2custom);
	add_line_value(page_content, FPSTR(INTL_SERVER), host_custom);
	add_line_value(page_content, FPSTR(INTL_PATH), url_custom);
	add_line_value(page_content, FPSTR(INTL_PORT), String(port_custom));
	add_line_value(page_content, FPSTR(INTL_USER), user_custom);
	add_line_value(page_content, FPSTR(INTL_PASSWORD), pwd_custom);
	page_content += F("<br/><br/>InfluxDB: ");
	page_content += String(send2influx);
	add_line_value(page_content, FPSTR(INTL_SERVER), host_influx);
	add_line_value(page_content, FPSTR(INTL_PATH), url_influx);
	add_line_value(page_content, FPSTR(INTL_PORT), String(port_influx));
	add_line_value(page_content, FPSTR(INTL_USER), user_influx);
	add_line_value(page_content, FPSTR(INTL_PASSWORD), pwd_influx);
	add_line_value(page_content, F("Measurement"), measurement_name_influx);
	add_line_value(page_content, F("SSL"), String(ssl_influx));
	page_content += FPSTR(WEB_BR_BR);
	page_content += FPSTR(INTL_SENSOR_IS_REBOOTING);

	server.sendContent(page_content);
	page_content = empty_String;
}

static void webserver_config() {
	if (!webserver_request_auth())
	{ return; }

	debug_outln_info(F("ws: config page ..."));

	server.sendHeader(F("Cache-Control"), F("no-cache, no-store, must-revalidate"));
	server.sendHeader(F("Pragma"), F("no-cache"));
	server.sendHeader(F("Expires"), F("0"));
	// Enable Pagination (Chunked Transfer)
	server.setContentLength(CONTENT_LENGTH_UNKNOWN);

	RESERVE_STRING(page_content, XLARGE_STR);

	start_html_page(page_content, FPSTR(INTL_CONFIGURATION));
	if (wificonfig_loop) {  // scan for wlan ssids
		page_content += FPSTR(WEB_CONFIG_SCRIPT);
	}

	if (server.method() == HTTP_GET) {
		webserver_config_send_body_get(page_content);
	} else {
		webserver_config_send_body_post(page_content);
	}
	end_html_page(page_content);

	if (server.method() == HTTP_POST) {
		display_debug(F("Writing config"), F("and restarting"));
		writeConfig();
		delay(100);
		SPIFFS.end();
		delay(500);
		ESP.restart();
	}
}

/*****************************************************************
 * Webserver wifi: show available wifi networks                  *
 *****************************************************************/
static void webserver_wifi() {
	String page_content;

	debug_outln_info(F("wifi networks found: "), String(count_wifiInfo));
	if (count_wifiInfo == 0) {
		page_content += FPSTR(BR_TAG);
		page_content += FPSTR(INTL_NO_NETWORKS);
		page_content += FPSTR(BR_TAG);
	} else {
		std::unique_ptr<int[]> indices(new int[count_wifiInfo]);
		debug_outln_info(F("ws: wifi ..."));
		for (unsigned i = 0; i < count_wifiInfo; ++i) {
			indices[i] = i;
		}
		for (unsigned i = 0; i < count_wifiInfo; i++) {
			for (unsigned j = i + 1; j < count_wifiInfo; j++) {
				if (wifiInfo[indices[j]].RSSI > wifiInfo[indices[i]].RSSI) {
					std::swap(indices[i], indices[j]);
				}
			}
		}
		int duplicateSsids = 0;
		for (int i = 0; i < count_wifiInfo; i++) {
			if (indices[i] == -1) {
				continue;
			}
			for (int j = i + 1; j < count_wifiInfo; j++) {
				if (strncmp(wifiInfo[indices[i]].ssid, wifiInfo[indices[j]].ssid, sizeof(wifiInfo[0].ssid)) == 0) {
					indices[j] = -1; // set dup aps to index -1
					++duplicateSsids;
				}
			}
		}

		page_content += FPSTR(INTL_NETWORKS_FOUND);
		page_content += String(count_wifiInfo - duplicateSsids);
		page_content += FPSTR(BR_TAG);
		page_content += FPSTR(BR_TAG);
		page_content += FPSTR(TABLE_TAG_OPEN);
		//if(n > 30) n=30;
		for (int i = 0; i < count_wifiInfo; ++i) {
			if (indices[i] == -1
 #if defined (ESP8266)
				|| wifiInfo[indices[i]].isHidden
 #endif
			) {
				continue;
			}
			// Print SSID and RSSI for each network found
#if defined(ESP8266)
			page_content += wlan_ssid_to_table_row(wifiInfo[indices[i]].ssid, ((wifiInfo[indices[i]].encryptionType == ENC_TYPE_NONE) ? " " : u8"🔒"), wifiInfo[indices[i]].RSSI);
#endif
#if defined(ESP32)
			page_content += wlan_ssid_to_table_row(wifiInfo[indices[i]].ssid, ((wifiInfo[indices[i]].encryptionType == WIFI_AUTH_OPEN) ? " " : u8"🔒"), wifiInfo[indices[i]].RSSI);
#endif
		}
		page_content += FPSTR(TABLE_TAG_CLOSE_BR);
		page_content += FPSTR(BR_TAG);
	}
	server.send(200, FPSTR(TXT_CONTENT_TYPE_TEXT_HTML), page_content);
}

/*****************************************************************
 * Webserver root: show latest values                            *
 *****************************************************************/
static void webserver_values() {
	if (WiFi.status() != WL_CONNECTED) {
		sendHttpRedirect();
	} else {
		RESERVE_STRING(page_content, XLARGE_STR);
		start_html_page(page_content, FPSTR(INTL_CURRENT_DATA));
		const String unit_PM = "µg/m³";
		const String unit_T = "°C";
		const String unit_H = "%";
		const String unit_P = "hPa";
		const String unit_NC = "#/cm³";
		const String unit_TS = "µm";
		const String unit_LA = "dB(A)";

		const int signal_quality = calcWiFiSignalQuality(WiFi.RSSI());
		debug_outln_info(F("ws: values ..."));
		if (first_cycle) {
			page_content += F("<b style='color:red'>");
			add_warning_first_cycle(page_content);
			page_content += FPSTR(WEB_B_BR_BR);
		} else {
			add_age_last_values(page_content);
		}

		server.sendContent(page_content);
		page_content = F("<table cellspacing='0' border='1' cellpadding='5'>\n"
				  "<tr><th>" INTL_SENSOR "</th><th> " INTL_PARAMETER "</th><th>" INTL_VALUE "</th></tr>");
		if (cfg::ppd_read) {
			page_content += FPSTR(EMPTY_ROW);
			add_table_row_from_value(page_content, FPSTR(SENSORS_PPD42NS), FPSTR(WEB_PM1), check_display_value(last_value_PPD_P1, -1, 1, 0), FPSTR(INTL_PARTICLES_PER_LITER));
			add_table_row_from_value(page_content, FPSTR(SENSORS_PPD42NS), FPSTR(WEB_PM25), check_display_value(last_value_PPD_P2, -1, 1, 0), FPSTR(INTL_PARTICLES_PER_LITER));
		}
		if (cfg::sds_read) {
			page_content += FPSTR(EMPTY_ROW);
			add_table_row_from_value(page_content, FPSTR(SENSORS_SDS011), FPSTR(WEB_PM25), check_display_value(last_value_SDS_P2, -1, 1, 0), unit_PM);
			add_table_row_from_value(page_content, FPSTR(SENSORS_SDS011), FPSTR(WEB_PM10), check_display_value(last_value_SDS_P1, -1, 1, 0), unit_PM);
		}
		if (cfg::pms_read) {
			page_content += FPSTR(EMPTY_ROW);
			add_table_row_from_value(page_content, FPSTR(SENSORS_PMSx003), FPSTR(WEB_PM1), check_display_value(last_value_PMS_P0, -1, 1, 0), unit_PM);
			add_table_row_from_value(page_content, FPSTR(SENSORS_PMSx003), FPSTR(WEB_PM25), check_display_value(last_value_PMS_P2, -1, 1, 0), unit_PM);
			add_table_row_from_value(page_content, FPSTR(SENSORS_PMSx003), FPSTR(WEB_PM10), check_display_value(last_value_PMS_P1, -1, 1, 0), unit_PM);
		}
		if (cfg::hpm_read) {
			page_content += FPSTR(EMPTY_ROW);
			add_table_row_from_value(page_content, FPSTR(SENSORS_HPM), FPSTR(WEB_PM25), check_display_value(last_value_HPM_P2, -1, 1, 0), unit_PM);
			add_table_row_from_value(page_content, FPSTR(SENSORS_HPM), FPSTR(WEB_PM10), check_display_value(last_value_HPM_P1, -1, 1, 0), unit_PM);
		}
		if (cfg::sps30_read) {
			page_content += FPSTR(EMPTY_ROW);
			add_table_row_from_value(page_content, FPSTR(SENSORS_SPS30), FPSTR(WEB_PM1), check_display_value(last_value_SPS30_P0, -1, 1, 0), unit_PM);
			add_table_row_from_value(page_content, FPSTR(SENSORS_SPS30), FPSTR(WEB_PM25), check_display_value(last_value_SPS30_P1, -1, 1, 0), unit_PM);
			add_table_row_from_value(page_content, FPSTR(SENSORS_SPS30), FPSTR(WEB_PM4), check_display_value(last_value_SPS30_P2, -1, 1, 0), unit_PM);
			add_table_row_from_value(page_content, FPSTR(SENSORS_SPS30), FPSTR(WEB_PM10), check_display_value(last_value_SPS30_P3, -1, 1, 0), unit_PM);
			add_table_row_from_value(page_content, FPSTR(SENSORS_SPS30), FPSTR(WEB_NC0k5), check_display_value(last_value_SPS30_N0, -1, 0, 0), unit_NC);
			add_table_row_from_value(page_content, FPSTR(SENSORS_SPS30), FPSTR(WEB_NC1k0), check_display_value(last_value_SPS30_N1, -1, 0, 0), unit_NC);
			add_table_row_from_value(page_content, FPSTR(SENSORS_SPS30), FPSTR(WEB_NC2k5), check_display_value(last_value_SPS30_N2, -1, 0, 0), unit_NC);
			add_table_row_from_value(page_content, FPSTR(SENSORS_SPS30), FPSTR(WEB_NC4k0), check_display_value(last_value_SPS30_N3, -1, 0, 0), unit_NC);
			add_table_row_from_value(page_content, FPSTR(SENSORS_SPS30), FPSTR(WEB_NC10), check_display_value(last_value_SPS30_N4, -1, 0, 0), unit_NC);
			add_table_row_from_value(page_content, FPSTR(SENSORS_SPS30), FPSTR(WEB_TPS), check_display_value(last_value_SPS30_TS, -1, 1, 0), unit_TS);
		}

		if (cfg::dht_read) {
			page_content += FPSTR(EMPTY_ROW);
			add_table_row_from_value(page_content, FPSTR(SENSORS_DHT22), FPSTR(INTL_TEMPERATURE), check_display_value(last_value_DHT_T, -128, 1, 0), unit_T);
			add_table_row_from_value(page_content, FPSTR(SENSORS_DHT22), FPSTR(INTL_HUMIDITY), check_display_value(last_value_DHT_H, -1, 1, 0), unit_H);
		}
		if (cfg::htu21d_read) {
			page_content += FPSTR(EMPTY_ROW);
			add_table_row_from_value(page_content, FPSTR(SENSORS_HTU21D), FPSTR(INTL_TEMPERATURE), check_display_value(last_value_HTU21D_T, -128, 1, 0), unit_T);
			add_table_row_from_value(page_content, FPSTR(SENSORS_HTU21D), FPSTR(INTL_HUMIDITY), check_display_value(last_value_HTU21D_H, -1, 1, 0), unit_H);
		}
		if (cfg::bmp_read) {
			page_content += FPSTR(EMPTY_ROW);
			add_table_row_from_value(page_content, FPSTR(SENSORS_BMP180), FPSTR(INTL_TEMPERATURE), check_display_value(last_value_BMP_T, -128, 1, 0), unit_T);
			add_table_row_from_value(page_content, FPSTR(SENSORS_BMP180), FPSTR(INTL_PRESSURE), check_display_value(last_value_BMP_P / 100.0f, (-1 / 100.0f), 2, 0), unit_P);
		}
		if (cfg::bmx280_read) {
			page_content += FPSTR(EMPTY_ROW);
			add_table_row_from_value(page_content, FPSTR(SENSORS_BMX280), FPSTR(INTL_TEMPERATURE), check_display_value(last_value_BMX280_T, -128, 1, 0), unit_T);
			add_table_row_from_value(page_content, FPSTR(SENSORS_BMX280), FPSTR(INTL_PRESSURE), check_display_value(last_value_BMX280_P / 100.0f, (-1 / 100.0f), 2, 0), unit_P);
			if (bmx280.sensorID() == BME280_SENSOR_ID) {
				add_table_row_from_value(page_content, FPSTR(SENSORS_BMX280), FPSTR(INTL_HUMIDITY), check_display_value(last_value_BME280_H, -1, 1, 0), unit_H);
			}
		}
		if (cfg::ds18b20_read) {
			page_content += FPSTR(EMPTY_ROW);
			add_table_row_from_value(page_content, FPSTR(SENSORS_DS18B20), FPSTR(INTL_TEMPERATURE), check_display_value(last_value_DS18B20_T, -128, 1, 0), unit_T);
		}
		if (cfg::dnms_read) {
			page_content += FPSTR(EMPTY_ROW);
			add_table_row_from_value(page_content, FPSTR(SENSORS_DNMS), FPSTR(INTL_LEQ_A), check_display_value(last_value_dnms_laeq, -1, 1, 0), unit_LA);
			add_table_row_from_value(page_content, FPSTR(SENSORS_DNMS), FPSTR(INTL_LA_MIN), check_display_value(last_value_dnms_la_min, -1, 1, 0), unit_LA);
			add_table_row_from_value(page_content, FPSTR(SENSORS_DNMS), FPSTR(INTL_LA_MAX), check_display_value(last_value_dnms_la_max, -1, 1, 0), unit_LA);
		}
		if (cfg::gps_read) {
			page_content += FPSTR(EMPTY_ROW);
			add_table_row_from_value(page_content, FPSTR(WEB_GPS), FPSTR(INTL_LATITUDE), check_display_value(last_value_GPS_lat, -200.0, 6, 0), "°");
			add_table_row_from_value(page_content, FPSTR(WEB_GPS), FPSTR(INTL_LONGITUDE), check_display_value(last_value_GPS_lon, -200.0, 6, 0), "°");
			add_table_row_from_value(page_content, FPSTR(WEB_GPS), FPSTR(INTL_ALTITUDE), check_display_value(last_value_GPS_alt, -1000.0, 2, 0), "m");
			add_table_row_from_value(page_content, FPSTR(WEB_GPS), FPSTR(INTL_DATE), last_value_GPS_date, empty_String);
			add_table_row_from_value(page_content, FPSTR(WEB_GPS), FPSTR(INTL_TIME), last_value_GPS_time, empty_String);
		}

		server.sendContent(page_content);
		page_content = FPSTR(EMPTY_ROW);
		add_table_row_from_value(page_content, F("WiFi"), FPSTR(INTL_SIGNAL_STRENGTH), String(WiFi.RSSI()), "dBm");
		add_table_row_from_value(page_content, F("WiFi"), FPSTR(INTL_SIGNAL_QUALITY), String(signal_quality), "%");
		page_content += FPSTR(EMPTY_ROW);
		page_content += F("<tr><td colspan='2'>" INTL_NUMBER_OF_MEASUREMENTS "</td><td class='r'>");
		page_content += count_sends;
		page_content += F("</td></tr>");
		page_content += FPSTR(TABLE_TAG_CLOSE_BR);
		end_html_page(page_content);
	}
}

/*****************************************************************
 * Webserver set debug level                                     *
 *****************************************************************/
static void webserver_debug_level() {
	if (!webserver_request_auth())
	{ return; }

	RESERVE_STRING(page_content, LARGE_STR);
	start_html_page(page_content, FPSTR(INTL_DEBUG_LEVEL));
	debug_outln_info(F("ws: debug level ..."));

	if (server.hasArg("lvl")) {
		const int lvl = server.arg("lvl").toInt();
		if (lvl >= 0 && lvl <= 5) {
			cfg::debug = lvl;
			page_content += F("<h3>");
			page_content += FPSTR(INTL_DEBUG_SETTING_TO);
			page_content += ' ';

			static constexpr const char * lvlText[6] PROGMEM = {
				INTL_NONE, INTL_ERROR, INTL_WARNING, INTL_MIN_INFO, INTL_MED_INFO, INTL_MAX_INFO
			};

			page_content += FPSTR(lvlText[lvl]);
			page_content += F(".</h3>");
		}
	}
	end_html_page(page_content);
}

/*****************************************************************
 * Webserver remove config                                       *
 *****************************************************************/
static void webserver_removeConfig() {
	if (!webserver_request_auth())
	{ return; }

	RESERVE_STRING(page_content, LARGE_STR);
	start_html_page(page_content, FPSTR(INTL_DELETE_CONFIG));
	debug_outln_info(F("ws: removeConfig ..."));

	if (server.method() == HTTP_GET) {
		page_content += FPSTR(WEB_REMOVE_CONFIG_CONTENT);

	} else {
		if (SPIFFS.exists("/config.json")) {	//file exists
			debug_outln_info(F("removing config.json..."));
			if (SPIFFS.remove("/config.json")) {
				page_content += F("<h3>" INTL_CONFIG_DELETED ".</h3>");
			} else {
				page_content += F("<h3>" INTL_CONFIG_CAN_NOT_BE_DELETED ".</h3>");
			}
		} else {
			page_content += F("<h3>" INTL_CONFIG_NOT_FOUND ".</h3>");
		}
	}
	end_html_page(page_content);
}

/*****************************************************************
 * Webserver reset NodeMCU                                       *
 *****************************************************************/
static void webserver_reset() {
	if (!webserver_request_auth())
	{ return; }

	String page_content;
	page_content.reserve(512);

	start_html_page(page_content, FPSTR(INTL_RESTART_SENSOR));
	debug_outln_info(F("ws: reset ..."));

	if (server.method() == HTTP_GET) {
		page_content += FPSTR(WEB_RESET_CONTENT);
	} else {
		ESP.restart();
	}
	end_html_page(page_content);
}

/*****************************************************************
 * Webserver data.json                                           *
 *****************************************************************/
static void webserver_data_json() {
	String s1;
	unsigned long age = 0;

	debug_outln_info(F("ws: data json..."));
	if (first_cycle) {
		s1 = FPSTR(data_first_part);
		s1 += "]}";
		age = cfg::sending_intervall_ms - msSince(starttime);
		if (age > cfg::sending_intervall_ms) {
			age = 0;
		}
		age = 0 - age;
	} else {
		s1 = last_data_string;
		debug_outln(last_data_string, DEBUG_MED_INFO);
		age = msSince(starttime);
		if (age > cfg::sending_intervall_ms) {
			age = 0;
		}
	}
	String s2 = F(", \"age\":\"");
	s2 += String((long)((age + 500) / 1000));
	s2 += F("\", \"sensordatavalues\"");
	s1.replace(F(", \"sensordatavalues\""), s2);
	server.send(200, FPSTR(TXT_CONTENT_TYPE_JSON), s1);
}

/*****************************************************************
 * Webserver prometheus metrics endpoint                         *
 *****************************************************************/
static void webserver_prometheus_endpoint() {
	debug_outln_info(F("ws: prometheus endpoint..."));
	String data_4_prometheus = F("software_version{version=\"" SOFTWARE_VERSION_STR "\",node=\"-{id}\"} 1\nuptime_ms{{id}} {up}\nsending_intervall_ms{{id}} {si}\nnumber_of_measurements{{id}} {cs}\n");
	debug_outln_info(F("Parse JSON for Prometheus"));
	String id(F("node=\"" SENSOR_BASENAME));
	id += esp_chipid + "\"";
	data_4_prometheus.replace("{id}", esp_chipid);
	data_4_prometheus.replace("{up}", String(msSince(time_point_device_start_ms)));
	data_4_prometheus.replace("{si}", String(cfg::sending_intervall_ms));
	data_4_prometheus.replace("{cs}", String(count_sends));
	DynamicJsonDocument json2data(JSON_BUFFER_SIZE);
	DeserializationError err = deserializeJson(json2data, last_data_string);
	if (!err) {
		for (JsonObject measurement : json2data["sensordatavalues"].as<JsonArray>()) {
			data_4_prometheus += measurement["value_type"].as<char*>();
			data_4_prometheus += '{';
			data_4_prometheus += id;
			data_4_prometheus += "} ";
			data_4_prometheus += measurement["value"].as<char*>();
			data_4_prometheus += '\n';
		}
		data_4_prometheus += F("last_sample_age_ms{");
		data_4_prometheus += id;
		data_4_prometheus += "} ";
		data_4_prometheus += String(msSince(starttime));
		data_4_prometheus += '\n';
	} else {
		debug_outln_error(FPSTR(DBG_TXT_DATA_READ_FAILED));
	}
	debug_outln(data_4_prometheus, DEBUG_MED_INFO);
	server.send(200, FPSTR(TXT_CONTENT_TYPE_TEXT_PLAIN), data_4_prometheus);
}

/*****************************************************************
 * Webserver Images                                              *
 *****************************************************************/
static void webserver_images() {
	server.sendHeader(F("Cache-Control"), F("max-age=2592000, public"));

	if (server.arg("name") == F("luftdaten_logo")) {
		debug_outln_info(F("ws: luftdaten_logo..."));
		server.send_P(200, TXT_CONTENT_TYPE_IMAGE_PNG,
			LUFTDATEN_INFO_LOGO_PNG, LUFTDATEN_INFO_LOGO_PNG_SIZE);
	} else {
		webserver_not_found();
	}
}

/*****************************************************************
 * Webserver page not found                                      *
 *****************************************************************/
static void webserver_not_found() {
	last_page_load = millis();
	debug_outln_info(F("ws: not found ..."));
	if (WiFi.status() != WL_CONNECTED) {
		if ((server.uri().indexOf(F("success.html")) != -1) || (server.uri().indexOf(F("detect.html")) != -1)) {
			server.send(200, FPSTR(TXT_CONTENT_TYPE_TEXT_HTML), FPSTR(WEB_IOS_REDIRECT));
		} else {
			sendHttpRedirect();
		}
	} else {
		server.send(404, FPSTR(TXT_CONTENT_TYPE_TEXT_PLAIN), F("Not found."));
	}
}

/*****************************************************************
 * Webserver setup                                               *
 *****************************************************************/
static void setup_webserver() {
	server.on("/", webserver_root);
	server.on(F("/config"), webserver_config);
	server.on(F("/wifi"), webserver_wifi);
	server.on(F("/values"), webserver_values);
	server.on(F("/generate_204"), webserver_config);
	server.on(F("/fwlink"), webserver_config);
	server.on(F("/debug"), webserver_debug_level);
	server.on(F("/removeConfig"), webserver_removeConfig);
	server.on(F("/reset"), webserver_reset);
	server.on(F("/data.json"), webserver_data_json);
	server.on(F("/metrics"), webserver_prometheus_endpoint);
	server.on(F("/images"), webserver_images);
	server.onNotFound(webserver_not_found);

	debug_outln_info(F("Starting Webserver... "), WiFi.localIP().toString());
	server.begin();
}

static int selectChannelForAp() {
	std::array<int, 14> channels_rssi;
	std::fill(channels_rssi.begin(), channels_rssi.end(), -100);

	for (unsigned i = 0; i < count_wifiInfo; i++) {
		if (wifiInfo[i].RSSI > channels_rssi[wifiInfo[i].channel]) {
			channels_rssi[wifiInfo[i].channel] = wifiInfo[i].RSSI;
		}
	}

	if ((channels_rssi[1] < channels_rssi[6]) && (channels_rssi[1] < channels_rssi[11])) {
		return 1;
	} else if ((channels_rssi[6] < channels_rssi[1]) && (channels_rssi[6] < channels_rssi[11])) {
		return 6;
	} else {
		return 11;
	}
}

/*****************************************************************
 * WifiConfig                                                    *
 *****************************************************************/
static void wifiConfig() {
	debug_outln_info(F("Starting WiFiManager"));
	debug_outln_info(F("AP ID: "), String(cfg::fs_ssid));
	debug_outln_info(F("Password: "), String(cfg::fs_pwd));

	wificonfig_loop = true;

	WiFi.disconnect(true);
	debug_outln_info(F("scan for wifi networks..."));
	count_wifiInfo = WiFi.scanNetworks(false /* scan async */, true /* show hidden networks */);
	delete [] wifiInfo;
	wifiInfo = new struct_wifiInfo[count_wifiInfo];

	for (int i = 0; i < count_wifiInfo; i++) {
		String SSID;
		uint8_t* BSSID;

		memset(&wifiInfo[i], 0, sizeof(struct_wifiInfo));
#if defined(ESP8266)
		WiFi.getNetworkInfo(i, SSID, wifiInfo[i].encryptionType,
			wifiInfo[i].RSSI, BSSID, wifiInfo[i].channel,
			wifiInfo[i].isHidden);
#else
		WiFi.getNetworkInfo(i, SSID, wifiInfo[i].encryptionType,
			wifiInfo[i].RSSI, BSSID, wifiInfo[i].channel);
#endif
		SSID.toCharArray(wifiInfo[i].ssid, sizeof(wifiInfo[0].ssid));
	}

	WiFi.mode(WIFI_AP);
	const IPAddress apIP(192, 168, 4, 1);
	WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
	WiFi.softAP(cfg::fs_ssid, cfg::fs_pwd, selectChannelForAp());
	// In case we create a unique password at first start
	debug_outln_info(F("AP Password is: "), cfg::fs_pwd);

	DNSServer dnsServer;
	// Ensure we don't poison the client DNS cache
	dnsServer.setTTL(0);
	dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
	dnsServer.start(53, "*", apIP);							// 53 is port for DNS server

	setup_webserver();

	// 10 minutes timeout for wifi config
	last_page_load = millis();
	while ((millis() - last_page_load) < cfg::time_for_wifi_config + 500) {
		dnsServer.processNextRequest();
		server.handleClient();
#if defined(ESP8266)
		wdt_reset(); // nodemcu is alive
		MDNS.update();
#endif
		yield();
	}

	WiFi.softAPdisconnect(true);
	WiFi.mode(WIFI_STA);

	dnsServer.stop();
	delay(100);

	debug_outln_info(FPSTR(DBG_TXT_CONNECTING_TO), cfg::wlanssid);

	WiFi.begin(cfg::wlanssid, cfg::wlanpwd);

	debug_outln_info(F("---- Result Webconfig ----"));
	debug_outln_info(F("WLANSSID: "), cfg::wlanssid);
	debug_outln_info(F("----\nReading ..."));
	debug_outln_info_bool(F("PPD: "), cfg::ppd_read);
	debug_outln_info_bool(F("SDS: "), cfg::sds_read);
	debug_outln_info_bool(F("PMS: "), cfg::pms_read);
	debug_outln_info_bool(F("HPM: "), cfg::hpm_read);
	debug_outln_info_bool(F("SPS30: "), cfg::sps30_read);
	debug_outln_info_bool(F("DHT: "), cfg::dht_read);
	debug_outln_info_bool(F("DS18B20: "), cfg::ds18b20_read);
	debug_outln_info_bool(F("HTU21D: "), cfg::htu21d_read);
	debug_outln_info_bool(F("BMP: "), cfg::bmp_read);
	debug_outln_info_bool(F("DNMS: "), cfg::dnms_read);
	debug_outln_info(F("----\nSend to ..."));
	debug_outln_info_bool(F("Dusti: "), cfg::send2dusti);
	debug_outln_info_bool(F("Madavi: "), cfg::send2madavi);
	debug_outln_info_bool(F("CSV: "), cfg::send2csv);
	debug_outln_info(F("----"));
	debug_outln_info_bool(F("Autoupdate: "), cfg::auto_update);
	debug_outln_info_bool(F("Display: "), cfg::has_display);
	debug_outln_info_bool(F("LCD 1602: "), cfg::has_lcd1602);
	debug_outln_info(F("Debug: "), String(cfg::debug));
	wificonfig_loop = false;
}

static void waitForWifiToConnect(int maxRetries) {
	int retryCount = 0;
	while ((WiFi.status() != WL_CONNECTED) && (retryCount < maxRetries)) {
		delay(500);
		debug_out(".", DEBUG_MIN_INFO);
		++retryCount;
	}
}

/*****************************************************************
 * WiFi auto connecting script                                   *
 *****************************************************************/
static void connectWifi() {
	debug_outln(String(WiFi.status()), DEBUG_MIN_INFO);
	WiFi.disconnect();
#if defined(ESP8266)
	WiFi.setOutputPower(20.5f);
	WiFi.setPhyMode(WIFI_PHY_MODE_11N);
#endif
	WiFi.mode(WIFI_STA);
	WiFi.begin(cfg::wlanssid, cfg::wlanpwd); // Start WiFI

	debug_outln_info(FPSTR(DBG_TXT_CONNECTING_TO), cfg::wlanssid);

	if (MDNS.begin(cfg::fs_ssid)) {
		MDNS.addService("http", "tcp", 80);
		MDNS.addServiceTxt("http", "tcp", "PATH", "/config");
	}

	waitForWifiToConnect(40);
	debug_outln_info(empty_String);
	if (WiFi.status() != WL_CONNECTED) {
		String fss(cfg::fs_ssid);
		display_debug(fss.substring(0, 16), fss.substring(16));
		wifiConfig();
		if (WiFi.status() != WL_CONNECTED) {
			waitForWifiToConnect(20);
			debug_outln_info(empty_String);
		}
	}
	debug_outln_info(F("WiFi connected\nIP address: "), WiFi.localIP().toString());
}

/*****************************************************************
 * send data to rest api                                         *
 *****************************************************************/
static unsigned long sendData(const String& data, const int pin, const char* host, const int httpPort, const char* url, const bool use_ssl, const char* basic_auth_string, const __FlashStringHelper* contentType) {

	unsigned long start_send = millis();
	String s_Host(FPSTR(host));
	String s_url(FPSTR(url));

	debug_outln_info(F("Start sendData to "), s_Host);

	RESERVE_STRING(buf, LARGE_STR);
	buf = F("POST ");
	buf += s_url;
	buf += F(" HTTP/1.1\r\nHost: ");
	buf += s_Host;
	buf += F("\r\nContent-Type: ");
	buf += contentType;
	buf += "\r\n";
	if (strlen(basic_auth_string) != 0) {
		buf += F("Authorization: Basic ");
		buf += String(basic_auth_string);
		buf += "\r\n";
	}
	buf += F("X-PIN: ");
	buf += pin;
	buf += F("\r\nX-Sensor: " SENSOR_BASENAME);
	buf += esp_chipid;
	buf += F("\r\nContent-Length: ");
	buf += String(data.length(), DEC);
	buf += F("\r\nConnection: close\r\n\r\n");

	// Use WiFiClient class to create TCP connections
	WiFiClient* _client;
	if (use_ssl) {
		_client = new axTLS::WiFiClientSecure;
	} else {
		_client = new WiFiClient;
	}
	std::unique_ptr<WiFiClient> client(_client);

	client->setTimeout(20000);

	if (client->connect(s_Host, httpPort)) {
		debug_outln_info(F("Requesting URL: "), s_url);
		debug_outln_verbose(esp_chipid);
		debug_outln_verbose(data);

		// send request to the server
		client->print(buf);
		client->println(data);
		client->flush();

		// Wait and read reply from server and print them
		while (client->connected()) {

			if (client->available()) {
				int r = client->read((uint8_t*) buf.begin(), buf.length()-1);
				if (r > 0) {
					buf[r] = '\0';
				}
				debug_out(buf, DEBUG_MED_INFO);
			}

			yield();
		}
		client->stop();
		debug_outln_info(F("\nclosing connection\n----\n\n"));
	}

/*		WiFiClientSecure client_s;
			if (verify) {
				if (client_s.setCACert_P(dst_root_ca_x3_bin_crt, dst_root_ca_x3_bin_crt_len)) {
					if (client_s.verifyCertChain(s_Host)) {
						debug_outln_info(F("Server cert verified"));
						doRequest(&client_s, request_head, data);
					} else {
						debug_outln_error(F("ERROR: cert verification failed!"));
					}
				} else {
					debug_outln_error(F("Failed to load root CA cert!"));
				}
			} else {
				doRequest(&client_s, request_head, data);
			}
*/
/*		BearSSL::WiFiClientSecure client_s;
		if (verify) {
			BearSSLX509List cert(dst_root_ca_x3);
			client_s.setTrustAnchors(&cert);
		} else {
			client_s.setInsecure();
		}
		if (doConnect(&client_s)) {
			doRequest(&client_s, request_head, data);
		}
*/
	debug_outln_info(F("End connecting to "), s_Host);

	return millis() - start_send;
}

/*****************************************************************
 * send single sensor data to luftdaten.info api                 *
 *****************************************************************/
static unsigned long sendLuftdaten(const String& data, const int pin, const __FlashStringHelper* sensorname, const char* replace_str) {
	unsigned long sum_send_time = 0;

	if (cfg::send2dusti && data.length()) {
		RESERVE_STRING(data_4_dusti, LARGE_STR);
		data_4_dusti = FPSTR(data_first_part);

		debug_outln_info(F("## Sending to Luftdaten.info - "), sensorname);
		data_4_dusti += data;
		data_4_dusti.remove(data_4_dusti.length() - 1);
		data_4_dusti.replace(replace_str, empty_String);
		data_4_dusti += "]}";
		const int HTTP_PORT_DUSTI = (cfg::ssl_dusti ? 443 : 80);
		sum_send_time = sendData(data_4_dusti, pin, HOST_DUSTI, HTTP_PORT_DUSTI, URL_DUSTI,
						 cfg::ssl_dusti, "", FPSTR(TXT_CONTENT_TYPE_JSON));
	}

	return sum_send_time;
}

/*****************************************************************
 * send data to mqtt api                                         *
 *****************************************************************/
// rejected (see issue #33)

/*****************************************************************
 * send data to influxdb                                         *
 *****************************************************************/
static String create_influxdb_string(const String& data) {
	String data_4_influxdb;

	debug_outln_info(F("Parse JSON for influx DB: "), data);
	DynamicJsonDocument json2data(JSON_BUFFER_SIZE);
	DeserializationError err = deserializeJson(json2data, data);
	if (!err) {
		data_4_influxdb += cfg::measurement_name_influx;
		data_4_influxdb += F(",node=" SENSOR_BASENAME);
		data_4_influxdb += esp_chipid + " ";
		for (JsonObject measurement : json2data["sensordatavalues"].as<JsonArray>()) {
			data_4_influxdb += measurement["value_type"].as<char*>();
			data_4_influxdb += '=';
			data_4_influxdb += measurement["value"].as<char*>();
			data_4_influxdb += ',';
		}
		if ((unsigned)(data_4_influxdb.lastIndexOf(',') + 1) == data_4_influxdb.length()) {
			data_4_influxdb.remove(data_4_influxdb.length() - 1);
		}

		data_4_influxdb += '\n';
	} else {
		debug_outln_error(FPSTR(DBG_TXT_DATA_READ_FAILED));
	}
	return data_4_influxdb;
}

/*****************************************************************
 * send data as csv to serial out                                *
 *****************************************************************/
static void send_csv(const String& data) {
	DynamicJsonDocument json2data(JSON_BUFFER_SIZE);
	DeserializationError err = deserializeJson(json2data, data);
	debug_outln_info(F("CSV Output: "), data);
	if (!err) {
		String headline = F("Timestamp_ms;");
		String valueline = String(act_milli) + ';';
		for (JsonObject measurement : json2data["sensordatavalues"].as<JsonArray>()) {
			headline += measurement["value_type"].as<char*>();
			headline += ';';
			valueline += measurement["value"].as<char*>();
			valueline += ';';
		}
		static bool first_csv_line = true;
		if (first_csv_line) {
			if (headline.length() > 0) {
				headline.remove(headline.length() - 1);
			}
			Serial.println(headline);
			first_csv_line = false;
		}
		if (valueline.length() > 0) {
			valueline.remove(valueline.length() - 1);
		}
		Serial.println(valueline);
	} else {
		debug_outln_error(FPSTR(DBG_TXT_DATA_READ_FAILED));
	}
}

/*****************************************************************
 * read DHT22 sensor values                                      *
 *****************************************************************/
static void fetchSensorDHT(String& s) {
	debug_outln_verbose(FPSTR(DBG_TXT_START_READING), FPSTR(SENSORS_DHT22));

	// Check if valid number if non NaN (not a number) will be send.
	last_value_DHT_T = -128;
	last_value_DHT_H = -1;

	int count = 0;
	const int MAX_ATTEMPTS = 5;
	while ((count++ < MAX_ATTEMPTS) && (s == "")) {
		auto h = dht.readHumidity();
		auto t = dht.readTemperature();
		if (isnan(t) || isnan(h)) {
			delay(100);
			h = dht.readHumidity();
			t = dht.readTemperature(false);
		}
		if (isnan(t) || isnan(h)) {
			debug_outln_error(F("DHT11/DHT22 read failed"));
		} else {
			debug_outln_info(FPSTR(DBG_TXT_TEMPERATURE), t);
			debug_outln_info(FPSTR(DBG_TXT_HUMIDITY), h);
			last_value_DHT_T = t;
			last_value_DHT_H = h;
			add_Value2Json(s, F("temperature"), last_value_DHT_T);
			add_Value2Json(s, F("humidity"), last_value_DHT_H);
		}
	}
	debug_outln_info(F("----"));

	debug_outln_verbose(FPSTR(DBG_TXT_END_READING), FPSTR(SENSORS_DHT22));
}

/*****************************************************************
 * read HTU21D sensor values                                     *
 *****************************************************************/
static void fetchSensorHTU21D(String& s) {
	debug_outln_verbose(FPSTR(DBG_TXT_START_READING), FPSTR(SENSORS_HTU21D));

	const auto t = htu21d.readTemperature();
	const auto h = htu21d.readHumidity();
	if (isnan(t) || isnan(h)) {
		last_value_HTU21D_T = -128.0;
		last_value_HTU21D_H = -1.0;
		debug_outln_error(F("HTU21D read failed"));
	} else {
		debug_outln_info(FPSTR(DBG_TXT_TEMPERATURE), t);
		debug_outln_info(FPSTR(DBG_TXT_HUMIDITY), h);
		last_value_HTU21D_T = t;
		last_value_HTU21D_H = h;
		add_Value2Json(s, F("HTU21D_temperature"), last_value_HTU21D_T);
		add_Value2Json(s, F("HTU21D_humidity"), last_value_HTU21D_H);
	}
	debug_outln_info(F("----"));

	debug_outln_verbose(FPSTR(DBG_TXT_END_READING), FPSTR(SENSORS_HTU21D));
}

/*****************************************************************
 * read BMP180 sensor values                                     *
 *****************************************************************/
static void fetchSensorBMP(String& s) {
	debug_outln_verbose(FPSTR(DBG_TXT_START_READING), FPSTR(SENSORS_BMP180));

	const auto p = bmp.readPressure();
	const auto t = bmp.readTemperature();
	if (isnan(p) || isnan(t)) {
		last_value_BMP_T = -128.0;
		last_value_BMP_P = -1.0;
		debug_outln_error(F("BMP180 read failed"));
	} else {
		debug_outln_info(FPSTR(DBG_TXT_TEMPERATURE), t);
		debug_outln_info(FPSTR(DBG_TXT_PRESSURE), (p / 100.0f));
		last_value_BMP_T = t;
		last_value_BMP_P = p;
		add_Value2Json(s, F("BMP_pressure"), last_value_BMP_P);
		add_Value2Json(s, F("BMP_temperature"), last_value_BMP_T);
	}
	debug_outln_info(F("----"));

	debug_outln_verbose(FPSTR(DBG_TXT_END_READING), FPSTR(SENSORS_BMP180));
}

/*****************************************************************
 * read BMP280/BME280 sensor values                              *
 *****************************************************************/
static void fetchSensorBMX280(String& s) {
	debug_outln_verbose(FPSTR(DBG_TXT_START_READING), FPSTR(SENSORS_BMX280));

	bmx280.takeForcedMeasurement();
	const auto t = bmx280.readTemperature();
	const auto p = bmx280.readPressure();
	const auto h = bmx280.readHumidity();
	if (isnan(t) || isnan(p)) {
		last_value_BMX280_T = -128.0;
		last_value_BMX280_P = -1.0;
		last_value_BME280_H = -1.0;
		debug_outln_error(F("BMP/BME280 read failed"));
	} else {
		debug_outln_info(FPSTR(DBG_TXT_TEMPERATURE), t);
		debug_outln_info(FPSTR(DBG_TXT_PRESSURE), (p / 100.0f));
		last_value_BMX280_T = t;
		last_value_BMX280_P = p;
		if (bmx280.sensorID() == BME280_SENSOR_ID) {
			add_Value2Json(s, F("BME280_temperature"), last_value_BMX280_T);
			add_Value2Json(s, F("BME280_pressure"), last_value_BMX280_P);
			debug_outln_info(FPSTR(DBG_TXT_HUMIDITY), h);
			last_value_BME280_H = h;
			add_Value2Json(s, F("BME280_humidity"), last_value_BME280_H);
		} else {
			add_Value2Json(s, F("BMP280_pressure"), last_value_BMX280_P);
			add_Value2Json(s, F("BMP280_temperature"), last_value_BMX280_T);
		}
	}
	debug_outln_info(F("----"));

	debug_outln_verbose(FPSTR(DBG_TXT_END_READING), FPSTR(SENSORS_BMX280));
}

/*****************************************************************
 * read DS18B20 sensor values                                    *
 *****************************************************************/
static void fetchSensorDS18B20(String& s) {
	float t;
	debug_outln_verbose(FPSTR(DBG_TXT_START_READING), FPSTR(SENSORS_DS18B20));

	//it's very unlikely (-127: impossible) to get these temperatures in reality. Most times this means that the sensor is currently faulty
	//try 5 times to read the sensor, otherwise fail
	const int MAX_ATTEMPTS = 5;
	int count = 0;
	do {
		ds18b20.requestTemperatures();
		//for now, we want to read only the first sensor
		t = ds18b20.getTempCByIndex(0);
		++count;
		debug_outln_info(F("DS18B20 trying...."));
	} while (count < MAX_ATTEMPTS && (isnan(t) || t >= 85.0f || t <= (-127.0f)));

	if (count == MAX_ATTEMPTS) {
		last_value_DS18B20_T = -128.0;
		debug_outln_error(F("DS18B20 read failed"));
	} else {
		debug_outln_info(FPSTR(DBG_TXT_TEMPERATURE), t);
		last_value_DS18B20_T = t;
		add_Value2Json(s, F("DS18B20_temperature"), last_value_DS18B20_T);
	}
	debug_outln_info(F("----"));
	debug_outln_verbose(FPSTR(DBG_TXT_END_READING), FPSTR(SENSORS_DS18B20));
}

/*****************************************************************
 * read SDS011 sensor values                                     *
 *****************************************************************/
static void fetchSensorSDS(String& s) {
	char buffer;
	int value;
	int len = 0;
	int pm10_serial = 0;
	int pm25_serial = 0;
	int checksum_is = 0;
	int checksum_ok = 0;

	debug_outln_verbose(FPSTR(DBG_TXT_START_READING), FPSTR(SENSORS_SDS011));
	if (msSince(starttime) < (cfg::sending_intervall_ms - (WARMUPTIME_SDS_MS + READINGTIME_SDS_MS))) {
		if (is_SDS_running) {
			is_SDS_running = SDS_cmd(PmSensorCmd::Stop);
		}
	} else {
		if (! is_SDS_running) {
			is_SDS_running = SDS_cmd(PmSensorCmd::Start);
		}

		while (serialSDS.available() > 0) {
			buffer = serialSDS.read();
			debug_outln(String(len) + " - " + String(buffer, DEC) + " - " + String(buffer, HEX) + " - " + int(buffer) + " .", DEBUG_MAX_INFO);
//			"aa" = 170, "ab" = 171, "c0" = 192
			value = int(buffer);
			switch (len) {
			case 0:
				if (value != 170) {
					len = -1;
				};
				break;
			case 1:
				if (value != 192) {
					len = -1;
				};
				break;
			case 2:
				pm25_serial = value;
				checksum_is = value;
				break;
			case 3:
				pm25_serial += (value << 8);
				break;
			case 4:
				pm10_serial = value;
				break;
			case 5:
				pm10_serial += (value << 8);
				break;
			case 8:
				debug_outln_verbose(FPSTR(DBG_TXT_CHECKSUM_IS), String(checksum_is % 256));
				debug_outln_verbose(FPSTR(DBG_TXT_CHECKSUM_SHOULD), String(value));
				if (value == (checksum_is % 256)) {
					checksum_ok = 1;
				} else {
					len = -1;
				};
				break;
			case 9:
				if (value != 171) {
					len = -1;
				};
				break;
			}
			if (len > 2) { checksum_is += value; }
			len++;
			if (len == 10 && checksum_ok == 1 && (msSince(starttime) > (cfg::sending_intervall_ms - READINGTIME_SDS_MS))) {
				if ((! isnan(pm10_serial)) && (! isnan(pm25_serial))) {
					sds_pm10_sum += pm10_serial;
					sds_pm25_sum += pm25_serial;
					if (sds_pm10_min > pm10_serial) {
						sds_pm10_min = pm10_serial;
					}
					if (sds_pm10_max < pm10_serial) {
						sds_pm10_max = pm10_serial;
					}
					if (sds_pm25_min > pm25_serial) {
						sds_pm25_min = pm25_serial;
					}
					if (sds_pm25_max < pm25_serial) {
						sds_pm25_max = pm25_serial;
					}
					debug_outln_verbose(F("PM10 (sec.) : "), String(pm10_serial / 10.0f));
					debug_outln_verbose(F("PM2.5 (sec.): "), String(pm25_serial / 10.0f));
					sds_val_count++;
				}
				len = 0;
				checksum_ok = 0;
				pm10_serial = 0;
				pm25_serial = 0;
				checksum_is = 0;
			}
			yield();
		}

	}
	if (send_now) {
		last_value_SDS_P1 = -1;
		last_value_SDS_P2 = -1;
		if (sds_val_count > 2) {
			sds_pm10_sum = sds_pm10_sum - sds_pm10_min - sds_pm10_max;
			sds_pm25_sum = sds_pm25_sum - sds_pm25_min - sds_pm25_max;
			sds_val_count = sds_val_count - 2;
		}
		if (sds_val_count > 0) {
			last_value_SDS_P1 = float(sds_pm10_sum) / (sds_val_count * 10.0f);
			last_value_SDS_P2 = float(sds_pm25_sum) / (sds_val_count * 10.0f);
			debug_outln_info(F("PM10:  "), last_value_SDS_P1);
			debug_outln_info(F("PM2.5: "), last_value_SDS_P2);
			debug_outln_info(F("----"));
			add_Value2Json(s, F("SDS_P1"), last_value_SDS_P1);
			add_Value2Json(s, F("SDS_P2"), last_value_SDS_P2);
		}
		sds_pm10_sum = 0;
		sds_pm25_sum = 0;
		sds_val_count = 0;
		sds_pm10_max = 0;
		sds_pm10_min = 20000;
		sds_pm25_max = 0;
		sds_pm25_min = 20000;
		if ((cfg::sending_intervall_ms > (WARMUPTIME_SDS_MS + READINGTIME_SDS_MS))) {
			is_SDS_running = SDS_cmd(PmSensorCmd::Stop);
		}
	}

	debug_outln_verbose(FPSTR(DBG_TXT_END_READING), FPSTR(SENSORS_SDS011));
}

/*****************************************************************
 * read Plantronic PM sensor sensor values                       *
 *****************************************************************/
static void fetchSensorPMS(String& s) {
	char buffer;
	int value;
	int len = 0;
	int pm1_serial = 0;
	int pm10_serial = 0;
	int pm25_serial = 0;
	int checksum_is = 0;
	int checksum_should = 0;
	int checksum_ok = 0;
	int frame_len = 24;				// min. frame length

	debug_outln_verbose(FPSTR(DBG_TXT_START_READING), FPSTR(SENSORS_PMSx003));
	if (msSince(starttime) < (cfg::sending_intervall_ms - (WARMUPTIME_SDS_MS + READINGTIME_SDS_MS))) {
		if (is_PMS_running) {
			is_PMS_running = PMS_cmd(PmSensorCmd::Stop);
		}
	} else {
		if (! is_PMS_running) {
			is_PMS_running = PMS_cmd(PmSensorCmd::Start);
		}

		while (serialSDS.available() > 0) {
			buffer = serialSDS.read();
			debug_outln(String(len) + " - " + String(buffer, DEC) + " - " + String(buffer, HEX) + " - " + int(buffer) + " .", DEBUG_MAX_INFO);
//			"aa" = 170, "ab" = 171, "c0" = 192
			value = int(buffer);
			switch (len) {
			case 0:
				if (value != 66) {
					len = -1;
				};
				break;
			case 1:
				if (value != 77) {
					len = -1;
				};
				break;
			case 2:
				checksum_is = value;
				break;
			case 3:
				frame_len = value + 4;
				break;
			case 10:
				pm1_serial += ( value << 8);
				break;
			case 11:
				pm1_serial += value;
				break;
			case 12:
				pm25_serial = ( value << 8);
				break;
			case 13:
				pm25_serial += value;
				break;
			case 14:
				pm10_serial = ( value << 8);
				break;
			case 15:
				pm10_serial += value;
				break;
			case 22:
				if (frame_len == 24) {
					checksum_should = ( value << 8 );
				};
				break;
			case 23:
				if (frame_len == 24) {
					checksum_should += value;
				};
				break;
			case 30:
				checksum_should = ( value << 8 );
				break;
			case 31:
				checksum_should += value;
				break;
			}
			if ((len > 2) && (len < (frame_len - 2))) { checksum_is += value; }
			len++;
			if (len == frame_len) {
				debug_outln_verbose(FPSTR(DBG_TXT_CHECKSUM_IS), String(checksum_is + 143));
				debug_outln_verbose(FPSTR(DBG_TXT_CHECKSUM_SHOULD), String(checksum_should));
				if (checksum_should == (checksum_is + 143)) {
					checksum_ok = 1;
				} else {
					len = 0;
				};
				if (checksum_ok == 1 && (msSince(starttime) > (cfg::sending_intervall_ms - READINGTIME_SDS_MS))) {
					if ((! isnan(pm1_serial)) && (! isnan(pm10_serial)) && (! isnan(pm25_serial))) {
						pms_pm1_sum += pm1_serial;
						pms_pm10_sum += pm10_serial;
						pms_pm25_sum += pm25_serial;
						if (pms_pm1_min > pm1_serial) {
							pms_pm1_min = pm1_serial;
						}
						if (pms_pm1_max < pm1_serial) {
							pms_pm1_max = pm1_serial;
						}
						if (pms_pm25_min > pm25_serial) {
							pms_pm25_min = pm25_serial;
						}
						if (pms_pm25_max < pm25_serial) {
							pms_pm25_max = pm25_serial;
						}
						if (pms_pm10_min > pm10_serial) {
							pms_pm10_min = pm10_serial;
						}
						if (pms_pm10_max < pm10_serial) {
							pms_pm10_max = pm10_serial;
						}
						debug_outln_verbose(F("PM1 (sec.): "), String(pm1_serial));
						debug_outln_verbose(F("PM2.5 (sec.): "), String(pm25_serial));
						debug_outln_verbose(F("PM10 (sec.) : "), String(pm10_serial));
						pms_val_count++;
					}
					len = 0;
					checksum_ok = 0;
					pm1_serial = 0;
					pm10_serial = 0;
					pm25_serial = 0;
					checksum_is = 0;
				}
			}
			yield();
		}

	}
	if (send_now) {
		last_value_PMS_P0 = -1;
		last_value_PMS_P1 = -1;
		last_value_PMS_P2 = -1;
		if (pms_val_count > 2) {
			pms_pm1_sum = pms_pm1_sum - pms_pm1_min - pms_pm1_max;
			pms_pm10_sum = pms_pm10_sum - pms_pm10_min - pms_pm10_max;
			pms_pm25_sum = pms_pm25_sum - pms_pm25_min - pms_pm25_max;
			pms_val_count = pms_val_count - 2;
		}
		if (pms_val_count > 0) {
			last_value_PMS_P0 = double(pms_pm1_sum) / (pms_val_count * 1.0);
			last_value_PMS_P1 = double(pms_pm10_sum) / (pms_val_count * 1.0);
			last_value_PMS_P2 = double(pms_pm25_sum) / (pms_val_count * 1.0);
			debug_outln_info(F("PM1:   "), last_value_PMS_P0);
			debug_outln_info(F("PM2.5: "), last_value_PMS_P2);
			debug_outln_info(F("PM10:  "), last_value_PMS_P1);
			debug_outln_info(F("-------"));
			add_Value2Json(s, F("PMS_P0"), last_value_PMS_P0);
			add_Value2Json(s, F("PMS_P1"), last_value_PMS_P1);
			add_Value2Json(s, F("PMS_P2"), last_value_PMS_P2);
		}
		pms_pm1_sum = 0;
		pms_pm10_sum = 0;
		pms_pm25_sum = 0;
		pms_val_count = 0;
		pms_pm1_max = 0;
		pms_pm1_min = 20000;
		pms_pm10_max = 0;
		pms_pm10_min = 20000;
		pms_pm25_max = 0;
		pms_pm25_min = 20000;
		if (cfg::sending_intervall_ms > (WARMUPTIME_SDS_MS + READINGTIME_SDS_MS)) {
			is_PMS_running = PMS_cmd(PmSensorCmd::Stop);
		}
	}

	debug_outln_verbose(FPSTR(DBG_TXT_END_READING), FPSTR(SENSORS_PMSx003));
}

/*****************************************************************
 * read Honeywell PM sensor sensor values                        *
 *****************************************************************/
static void fetchSensorHPM(String& s) {
	char buffer;
	int value;
	int len = 0;
	int pm10_serial = 0;
	int pm25_serial = 0;
	int checksum_is = 0;
	int checksum_should = 0;
	int checksum_ok = 0;

	debug_outln_verbose(FPSTR(DBG_TXT_START_READING), FPSTR(SENSORS_HPM));
	if (msSince(starttime) < (cfg::sending_intervall_ms - (WARMUPTIME_SDS_MS + READINGTIME_SDS_MS))) {
		if (is_HPM_running) {
			is_HPM_running = HPM_cmd(PmSensorCmd::Stop);
		}
	} else {
		if (! is_HPM_running) {
			is_HPM_running = HPM_cmd(PmSensorCmd::Start);
		}

		while (serialSDS.available() > 0) {
			buffer = serialSDS.read();
			debug_outln(String(len) + " - " + String(buffer, DEC) + " - " + String(buffer, HEX) + " - " + int(buffer) + " .", DEBUG_MAX_INFO);
//			"aa" = 170, "ab" = 171, "c0" = 192
			value = int(buffer);
			switch (len) {
			case 0:
				if (value != 66) {
					len = -1;
				};
				break;
			case 1:
				if (value != 77) {
					len = -1;
				};
				break;
			case 2:
				checksum_is = value;
				break;
			case 6:
				pm25_serial += ( value << 8);
				break;
			case 7:
				pm25_serial += value;
				break;
			case 8:
				pm10_serial = ( value << 8);
				break;
			case 9:
				pm10_serial += value;
				break;
			case 30:
				checksum_should = ( value << 8 );
				break;
			case 31:
				checksum_should += value;
				break;
			}
			if (len > 2 && len < 30) { checksum_is += value; }
			len++;
			if (len == 32) {
				debug_outln_verbose(FPSTR(DBG_TXT_CHECKSUM_IS), String(checksum_is + 143));
				debug_outln_verbose(FPSTR(DBG_TXT_CHECKSUM_SHOULD), String(checksum_should));
				if (checksum_should == (checksum_is + 143)) {
					checksum_ok = 1;
				} else {
					len = 0;
				};
				if (checksum_ok == 1 && (long(msSince(starttime)) > (long(cfg::sending_intervall_ms) - long(READINGTIME_SDS_MS)))) {
					if ((! isnan(pm10_serial)) && (! isnan(pm25_serial))) {
						hpm_pm10_sum += pm10_serial;
						hpm_pm25_sum += pm25_serial;
						if (hpm_pm10_min > pm10_serial) {
							hpm_pm10_min = pm10_serial;
						}
						if (hpm_pm10_max < pm10_serial) {
							hpm_pm10_max = pm10_serial;
						}
						if (hpm_pm25_min > pm25_serial) {
							hpm_pm25_min = pm25_serial;
						}
						if (hpm_pm25_max < pm25_serial) {
							hpm_pm25_max = pm25_serial;
						}
						debug_outln_verbose(F("PM2.5 (sec.): "), String(pm25_serial));
						debug_outln_verbose(F("PM10 (sec.) : "), String(pm10_serial));
						hpm_val_count++;
					}
					len = 0;
					checksum_ok = 0;
					pm10_serial = 0;
					pm25_serial = 0;
					checksum_is = 0;
				}
			}
			yield();
		}

	}
	if (send_now) {
		last_value_HPM_P1 = -1;
		last_value_HPM_P2 = -1;
		if (hpm_val_count > 2) {
			hpm_pm10_sum = hpm_pm10_sum - hpm_pm10_min - hpm_pm10_max;
			hpm_pm25_sum = hpm_pm25_sum - hpm_pm25_min - hpm_pm25_max;
			hpm_val_count = hpm_val_count - 2;
		}
		if (hpm_val_count > 0) {
			last_value_HPM_P1 = double(hpm_pm10_sum) / (hpm_val_count * 1.0);
			last_value_HPM_P2 = double(hpm_pm25_sum) / (hpm_val_count * 1.0);
			debug_outln_info(F("PM2.5: "), last_value_HPM_P1);
			debug_outln_info(F("PM10:  "), last_value_HPM_P2);
			debug_outln_info(F("-------"));
			add_Value2Json(s, F("HPM_P1"), last_value_HPM_P1);
			add_Value2Json(s, F("HPM_P2"), last_value_HPM_P2);
		}
		hpm_pm10_sum = 0;
		hpm_pm25_sum = 0;
		hpm_val_count = 0;
		hpm_pm10_max = 0;
		hpm_pm10_min = 20000;
		hpm_pm25_max = 0;
		hpm_pm25_min = 20000;
		if (cfg::sending_intervall_ms > (WARMUPTIME_SDS_MS + READINGTIME_SDS_MS)) {
			is_HPM_running = HPM_cmd(PmSensorCmd::Stop);
		}
	}

	debug_outln_verbose(FPSTR(DBG_TXT_END_READING), FPSTR(SENSORS_HPM));
}

/*****************************************************************
 * read PPD42NS sensor values                                    *
 *****************************************************************/
static void fetchSensorPPD(String& s) {
	debug_outln_verbose(FPSTR(DBG_TXT_START_READING), FPSTR(SENSORS_PPD42NS));

	if (msSince(starttime) <= SAMPLETIME_MS) {

		// Read pins connected to ppd42ns
		boolean valP1 = digitalRead(PPD_PIN_PM1);
		boolean valP2 = digitalRead(PPD_PIN_PM2);

		if(valP1 == LOW && trigP1 == false) {
			trigP1 = true;
			trigOnP1 = act_micro;
		}

		if (valP1 == HIGH && trigP1 == true) {
			lowpulseoccupancyP1 += act_micro - trigOnP1;
			trigP1 = false;
		}

		if(valP2 == LOW && trigP2 == false) {
			trigP2 = true;
			trigOnP2 = act_micro;
		}

		if (valP2 == HIGH && trigP2 == true) {
			unsigned long durationP2 = act_micro - trigOnP2;
			lowpulseoccupancyP2 += durationP2;
			trigP2 = false;
		}

	}
	// Checking if it is time to sample
	if (send_now) {
		auto calcConcentration = [](const float ratio) {
			/* spec sheet curve*/
			return (1.1f * ratio * ratio * ratio - 3.8f * ratio * ratio + 520.0f * ratio + 0.62f);
		};

		last_value_PPD_P1 = -1;
		last_value_PPD_P2 = -1;
		float ratio = lowpulseoccupancyP1 / (SAMPLETIME_MS * 10.0f);
		float concentration = calcConcentration(ratio);
		String s_lowpulseoccupancyP1(lowpulseoccupancyP1), s_lowpulseoccupancyP2(lowpulseoccupancyP2);

		debug_outln_info(F("LPO P10    : "), s_lowpulseoccupancyP1);
		debug_outln_info(F("Ratio PM10%: "), ratio);
		debug_outln_info(F("PM10 Count : "), concentration);

		// json for push to api / P1
		last_value_PPD_P1 = concentration;
		add_Value2Json(s, F("durP1"), s_lowpulseoccupancyP1);
		add_Value2Json(s, F("ratioP1"), ratio);
		add_Value2Json(s, F("P1"), last_value_PPD_P1);

		ratio = lowpulseoccupancyP2 / (SAMPLETIME_MS * 10.0f);
		concentration = calcConcentration(ratio);

		// Begin printing
		debug_outln_info(F("LPO PM25   : "), s_lowpulseoccupancyP2);
		debug_outln_info(F("Ratio PM25%: "), ratio);
		debug_outln_info(F("PM25 Count : "), concentration);

		// json for push to api / P2
		last_value_PPD_P2 = concentration;
		add_Value2Json(s, F("durP2"), s_lowpulseoccupancyP2);
		add_Value2Json(s, F("ratioP2"), ratio);
		add_Value2Json(s, F("P2"), last_value_PPD_P2);

		debug_outln_info(F("----"));
	}

	debug_outln_verbose(FPSTR(DBG_TXT_END_READING), FPSTR(SENSORS_PPD42NS));
}

/*****************************************************************
   read SPS30 PM sensor values
 *****************************************************************/
static void fetchSensorSPS30(String& s) {
	debug_outln_verbose(FPSTR(DBG_TXT_START_READING), FPSTR(SENSORS_SPS30));

	last_value_SPS30_P0 = value_SPS30_P0 / SPS30_measurement_count;
	last_value_SPS30_P1 = value_SPS30_P1 / SPS30_measurement_count;
	last_value_SPS30_P2 = value_SPS30_P2 / SPS30_measurement_count;
	last_value_SPS30_P3 = value_SPS30_P3 / SPS30_measurement_count;
	last_value_SPS30_N0 = value_SPS30_N0 / SPS30_measurement_count;
	last_value_SPS30_N1 = value_SPS30_N1 / SPS30_measurement_count;
	last_value_SPS30_N2 = value_SPS30_N2 / SPS30_measurement_count;
	last_value_SPS30_N3 = value_SPS30_N3 / SPS30_measurement_count;
	last_value_SPS30_N4 = value_SPS30_N4 / SPS30_measurement_count;
	last_value_SPS30_TS = value_SPS30_TS / SPS30_measurement_count;

	debug_outln_info(F("PM1.0: "), last_value_SPS30_P0);
	debug_outln_info(F("PM2.5: "), last_value_SPS30_P1);
	debug_outln_info(F("PM4.0: "), last_value_SPS30_P2);
	debug_outln_info(F("PM10:  "), last_value_SPS30_P3);
	debug_outln_info(F("NC0.5: "), last_value_SPS30_N0);
	debug_outln_info(F("NC1.0: "), last_value_SPS30_N1);
	debug_outln_info(F("NC2.5: "), last_value_SPS30_N2);
	debug_outln_info(F("NC4.0: "), last_value_SPS30_N3);
	debug_outln_info(F("NC10:  "), last_value_SPS30_N4);
	debug_outln_info(F("TPS:   "), last_value_SPS30_TS);

	add_Value2Json(s, F("SPS30_P0"), last_value_SPS30_P0);
	add_Value2Json(s, F("SPS30_P1"), last_value_SPS30_P1);
	add_Value2Json(s, F("SPS30_P2"), last_value_SPS30_P2);
	add_Value2Json(s, F("SPS30_P3"), last_value_SPS30_P3);
	add_Value2Json(s, F("SPS30_N0"), last_value_SPS30_N0);
	add_Value2Json(s, F("SPS30_N1"), last_value_SPS30_N1);
	add_Value2Json(s, F("SPS30_N2"), last_value_SPS30_N2);
	add_Value2Json(s, F("SPS30_N3"), last_value_SPS30_N3);
	add_Value2Json(s, F("SPS30_N4"), last_value_SPS30_N4);
	add_Value2Json(s, F("SPS30_TS"), last_value_SPS30_TS);

	debug_outln_info(F("SPS30 read counter: "), String(SPS30_read_counter));
	debug_outln_info(F("SPS30 read error counter: "), String(SPS30_read_error_counter));

	SPS30_measurement_count = 0;
	SPS30_read_counter = 0;
	SPS30_read_error_counter = 0;
	value_SPS30_P0 = 0.0;
	value_SPS30_P1 = 0.0;
	value_SPS30_P2 = 0.0;
	value_SPS30_P3 = 0.0;
	value_SPS30_N0 = 0.0;
	value_SPS30_N1 = 0.0;
	value_SPS30_N2 = 0.0;
	value_SPS30_N3 = 0.0;
	value_SPS30_N4 = 0.0;
	value_SPS30_TS = 0.0;

	debug_outln_info(F("----"));
	debug_outln_verbose(FPSTR(DBG_TXT_END_READING), FPSTR(SENSORS_SPS30));
}

/*****************************************************************
   read DNMS values
 *****************************************************************/

static float readDNMScorrection() {
	char* pEnd = nullptr;
	// Avoiding atof() here as this adds a lot (~ 9kb) of code size
	float r = float(strtol(cfg::dnms_correction, &pEnd, 10));
	if (pEnd && pEnd[0] == '.' && pEnd[1] >= '0' && pEnd[1] <= '9') {
		r += (r >= 0 ? 1.0 : -1.0) * ((pEnd[1] - '0') / 10.0);
	}
	return r;
}

static void fetchSensorDNMS(String& s) {
	static bool dnms_error = false;
	debug_outln_verbose(FPSTR(DBG_TXT_START_READING), FPSTR(SENSORS_DNMS));
	last_value_dnms_laeq = -1.0;
	last_value_dnms_la_min = -1.0;
	last_value_dnms_la_max = -1.0;

	if (dnms_calculate_leq() !=  0) {
		// error
		dnms_error = true;
	}
	uint16_t data_ready = 0;
	dnms_error = true;
	for (unsigned i = 0; i < 20; i++) {
		delay(2);
		int16_t ret_dnms = dnms_read_data_ready(&data_ready);
		if ((ret_dnms == 0) && (data_ready != 0)) {
			dnms_error = false;
			break;
		}
	}
	if (!dnms_error) {
		struct dnms_measurements dnms_values;
		if (dnms_read_leq(&dnms_values) == 0) {
			float dnms_corr_value = readDNMScorrection();
			last_value_dnms_laeq = dnms_values.leq_a + dnms_corr_value;
			last_value_dnms_la_min = dnms_values.leq_a_min + dnms_corr_value;
			last_value_dnms_la_max = dnms_values.leq_a_max + dnms_corr_value;
		} else {
			// error
			dnms_error = true;
		}
	}
	if (dnms_error) {
		// es gab einen Fehler
		dnms_reset(); // try to reset dnms
		debug_outln_error(F("DNMS read failed"));
	} else {
		debug_outln_info(F("LAeq: "), last_value_dnms_laeq);
		debug_outln_info(F("LA_MIN: "), last_value_dnms_la_min);
		debug_outln_info(F("LA_MAX: "), last_value_dnms_la_max);

		add_Value2Json(s, F("DNMS_noise_LAeq"), last_value_dnms_laeq);
		add_Value2Json(s, F("DNMS_noise_LA_min"), last_value_dnms_la_min);
		add_Value2Json(s, F("DNMS_noise_LA_max"), last_value_dnms_la_max);
	}
	debug_outln_info(F("----"));
	debug_outln_verbose(FPSTR(DBG_TXT_END_READING), FPSTR(SENSORS_DNMS));
}

/*****************************************************************
 * read GPS sensor values                                        *
 *****************************************************************/
static void fetchSensorGPS(String& s) {
	String gps_lat, gps_lon;

	debug_outln_verbose(FPSTR(DBG_TXT_START_READING), "GPS");

	if (gps.location.isUpdated()) {
		if (gps.location.isValid()) {
			last_value_GPS_lat = gps.location.lat();
			last_value_GPS_lon = gps.location.lng();
			gps_lat = std::move(String(last_value_GPS_lat, 6));
			gps_lon = std::move(String(last_value_GPS_lon, 6));
		} else {
			last_value_GPS_lat = -200;
			last_value_GPS_lon = -200;
			debug_outln_verbose(F("Lat/Lng INVALID"));
		}
		if (gps.altitude.isValid()) {
			last_value_GPS_alt = gps.altitude.meters();
			String gps_alt(last_value_GPS_lat);
		} else {
			last_value_GPS_alt = -1000;
			debug_outln_verbose(F("Altitude INVALID"));
		}
		if (gps.date.isValid()) {
			String gps_date;
			if (gps.date.month() < 10) {
				gps_date += '0';
			}
			gps_date += String(gps.date.month());
			gps_date += '/';
			if (gps.date.day() < 10) {
				gps_date += '0';
			}
			gps_date += String(gps.date.day());
			gps_date += '/';
			gps_date += String(gps.date.year());
			last_value_GPS_date = gps_date;
		} else {
			debug_outln_verbose(F("Date INVALID"));
		}
		if (gps.time.isValid()) {
			String gps_time;
			if (gps.time.hour() < 10) {
				gps_time += '0';
			}
			gps_time += String(gps.time.hour());
			gps_time += ':';
			if (gps.time.minute() < 10) {
				gps_time += '0';
			}
			gps_time += String(gps.time.minute());
			gps_time += ':';
			if (gps.time.second() < 10) {
				gps_time += '0';
			}
			gps_time += String(gps.time.second());
			gps_time += '.';
			if (gps.time.centisecond() < 10) {
				gps_time += '0';
			}
			gps_time += String(gps.time.centisecond());
			last_value_GPS_time = gps_time;
		} else {
			debug_outln_verbose(F("Time: INVALID"));
		}
	}

	if (send_now) {
		debug_outln_info(F("Lat: "), String(last_value_GPS_lat, 6));
		debug_outln_info(F("Lng: "), String(last_value_GPS_lon, 6));
		debug_outln_info(F("Altitude: "), last_value_GPS_alt);
		debug_outln_info(F("Date: "), last_value_GPS_date);
		debug_outln_info(F("Time "), last_value_GPS_time);
		debug_outln_info(F("----"));
		add_Value2Json(s, F("GPS_lat"), String(last_value_GPS_lat, 6));
		add_Value2Json(s, F("GPS_lon"), String(last_value_GPS_lon, 6));
		add_Value2Json(s, F("GPS_height"), last_value_GPS_alt);
		add_Value2Json(s, F("GPS_date"), last_value_GPS_date);
		add_Value2Json(s, F("GPS_time"), last_value_GPS_time);
	}

	if ( gps.charsProcessed() < 10) {
		debug_outln_error(F("No GPS data received: check wiring"));
		gps_init_failed = true;
	}

	debug_outln_verbose(FPSTR(DBG_TXT_END_READING), "GPS");
}


/*****************************************************************
 * AutoUpdate                                                    *
 *****************************************************************/

static bool fwDownloadStreamFile(const String& url, const String& fname) {

	HTTPClient http;
	String fname_new(fname + ".new");
	int bytes_written = -1;

	http.setTimeout(20 * 1000);
	const String SDS_version = cfg::sds_read ? SDS_version_date() : "";
	http.setUserAgent(SOFTWARE_VERSION + ' ' + esp_chipid + ' ' + SDS_version + ' ' +
				 String(cfg::current_lang) + ' ' + String(INTL_LANG) + ' ' +
				 String(cfg::use_beta ? "BETA" : ""));

	if (http.begin(FPSTR(FW_DOWNLOAD_HOST), 80, url)) {
		if (http.GET() == HTTP_CODE_OK) {
			File fwFile = SPIFFS.open(fname_new, "w+");
			if (fwFile) {
				bytes_written = http.writeToStream(&fwFile);
				fwFile.close();
				if (bytes_written > 0) {
					SPIFFS.remove(fname);
					SPIFFS.rename(fname_new, fname);
					debug_outln_info(F("Success downloading: "), url);
				}
			}
		}
		http.end();
	}

	if (bytes_written > 0)
		return true;

	debug_outln_info("Download failed!");
	SPIFFS.remove(fname_new);
	return false;
}

static void twoStageAutoUpdate() {

	if (!cfg::auto_update) return;

#if defined(ESP8266)
	debug_outln(F("twoStageAutoUpdate"), DEBUG_MIN_INFO);

	String lang_variant(cfg::current_lang);
	lang_variant.toLowerCase();

	String fwprefix("/airrohr/update/latest_");
	if (cfg::use_beta) {
		fwprefix = "/airrohr/beta/latest_";
	}
	fwprefix += lang_variant;

	String firmware_md5("/firmware.bin.md5");
	String fetch_md5_name = fwprefix + ".bin.md5";
	bool downloadSuccess = fwDownloadStreamFile(fetch_md5_name, firmware_md5);
	if (!downloadSuccess)
		return;

	File fwFile = SPIFFS.open(firmware_md5, "r");
	if (!fwFile || fwFile.size() >= 40) {
		debug_outln_error(F("Failed reopening md5 file.."));
		return;
	}

	String newFwmd5 = fwFile.readString();
	newFwmd5.trim();
	fwFile.close();

	debug_outln_info(F("NewFW md5: "), newFwmd5);
	debug_outln_info(F("Sketch md5    : "), ESP.getSketchMD5());

	if (newFwmd5 == ESP.getSketchMD5()) {
		debug_outln_verbose("No newer version available.");
		return;
	}

	String firmware_name("/firmware.bin");
	String fetch_name = fwprefix + ".bin";
	downloadSuccess = fwDownloadStreamFile(fetch_name, firmware_name);

	if (!downloadSuccess)
		return;

	fwFile = SPIFFS.open(firmware_name, "r");
	if (!fwFile) {
		debug_outln_error(F("Failed reopening fw file.."));
		return;
	}

	size_t fwSize = fwFile.size();
	MD5Builder md5;
	md5.begin();
	md5.addStream(fwFile, fwSize);
	md5.calculate();
	fwFile.close();

	String md5String = md5.toString();

	// Firmware is always at least 64 and padded to 16 bytes
	if (fwSize < (1<<16) || (fwSize % 16 != 0) || newFwmd5 != md5String) {
		debug_outln_info(F("FW download failed validation.. deleting"));
		SPIFFS.remove(firmware_name);
		SPIFFS.remove(firmware_md5);
		return;
	}
	debug_outln("success!", DEBUG_MIN_INFO);
	// Unmout Filesystem before reboot
	SPIFFS.end();

	debug_outln("launching 2nd stage", DEBUG_MIN_INFO);
	const HTTPUpdateResult ret = ESPhttpUpdate.update(FPSTR(FW_DOWNLOAD_HOST), 80,
		"/airrohr/loader-002.bin", String("LOADER-002"));

	String LastErrorString = ESPhttpUpdate.getLastErrorString().c_str();
	switch(ret) {
	case HTTP_UPDATE_FAILED:
		debug_outln_error(FPSTR(DBG_TXT_UPDATE));
		debug_outln_error(FPSTR(DBG_TXT_UPDATE_FAILED));
		debug_outln(LastErrorString, DEBUG_ERROR);
		display_debug(FPSTR(DBG_TXT_UPDATE), FPSTR(DBG_TXT_UPDATE_FAILED));
		break;
	case HTTP_UPDATE_NO_UPDATES:
		debug_outln_info(FPSTR(DBG_TXT_UPDATE), FPSTR(DBG_TXT_UPDATE_NO_UPDATE));
		display_debug(FPSTR(DBG_TXT_UPDATE), FPSTR(DBG_TXT_UPDATE_NO_UPDATE));
		break;
	case HTTP_UPDATE_OK:
		// may not called we reboot the ESP
		break;
	}
#endif
}

static String displayGenerateFooter(unsigned int screen_count) {
	String display_footer;
	for (unsigned int i = 0; i < screen_count; ++i) {
		display_footer += (i != (next_display_count % screen_count)) ? " . " : " o ";
	}
	return display_footer;
}

/*****************************************************************
 * display values                                                *
 *****************************************************************/
static void display_values() {
	float t_value = -128.0;
	float h_value = -1.0;
	double p_value = -1.0;
	String t_sensor, h_sensor, p_sensor;
	float pm010_value = -1.0;
	float pm040_value = -1.0;
	double pm10_value = -1.0;
	double pm25_value = -1.0;
	String pm10_sensor;
	String pm25_sensor;
	float nc005_value = -1.0;
	float nc010_value = -1.0;
	float nc025_value = -1.0;
	float nc040_value = -1.0;
	float nc100_value = -1.0;
	float la_eq_value = -1.0;
	float la_max_value = -1.0;
	float la_min_value = -1.0;
	String la_sensor;
	float tps_value = -1.0;
	double lat_value = -200.0;
	double lon_value = -200.0;
	double alt_value = -1000.0;
	String display_header;
	String display_lines[3] = { "", "", ""};
	uint8_t screen_count = 0;
	uint8_t screens[8];
	int line_count = 0;
	debug_outln_info(F("output values to display..."));
	if (cfg::ppd_read) {
		pm10_value = last_value_PPD_P1;
		pm10_sensor = FPSTR(SENSORS_PPD42NS);
		pm25_value = last_value_PPD_P2;
		pm25_sensor = FPSTR(SENSORS_PPD42NS);
	}
	if (cfg::pms_read) {
		pm10_value = last_value_PMS_P1;
		pm10_sensor = FPSTR(SENSORS_PMSx003);
		pm25_value = last_value_PMS_P2;
		pm25_sensor = FPSTR(SENSORS_PMSx003);
	}
	if (cfg::hpm_read) {
		pm10_value = last_value_HPM_P1;
		pm10_sensor = FPSTR(SENSORS_HPM);
		pm25_value = last_value_HPM_P2;
		pm25_sensor = FPSTR(SENSORS_HPM);
	}
	if (cfg::sps30_read) {
		pm10_sensor = FPSTR(SENSORS_SPS30);
		pm25_sensor = FPSTR(SENSORS_SPS30);
		pm010_value = last_value_SPS30_P0;
		pm25_value = last_value_SPS30_P1;
		pm040_value = last_value_SPS30_P2;
		pm10_value = last_value_SPS30_P3;
		nc005_value = last_value_SPS30_N0;
		nc010_value = last_value_SPS30_N1;
		nc025_value = last_value_SPS30_N2;
		nc040_value = last_value_SPS30_N3;
		nc100_value = last_value_SPS30_N4;
		tps_value = last_value_SPS30_TS;
	}
	if (cfg::sds_read) {
		pm10_sensor = pm25_sensor = FPSTR(SENSORS_SDS011);
		pm10_value = last_value_SDS_P1;
		pm25_value = last_value_SDS_P2;
	}
	if (cfg::dht_read) {
		t_sensor = h_sensor = FPSTR(SENSORS_DHT22);
		t_value = last_value_DHT_T;
		h_value = last_value_DHT_H;
	}
	if (cfg::ds18b20_read) {
		t_sensor = FPSTR(SENSORS_DS18B20);
		t_value = last_value_DS18B20_T;
	}
	if (cfg::htu21d_read) {
		h_sensor = t_sensor = FPSTR(SENSORS_HTU21D);
		t_value = last_value_HTU21D_T;
		h_value = last_value_HTU21D_H;
	}
	if (cfg::bmp_read) {
		t_sensor = h_sensor = FPSTR(SENSORS_BMP180);
		t_value = last_value_BMP_T;
		p_value = last_value_BMP_P;
	}
	if (cfg::bmx280_read) {
		t_sensor = p_sensor = FPSTR(SENSORS_BMX280);
		t_value = last_value_BMX280_T;
		p_value = last_value_BMX280_P;
		if (bmx280.sensorID() == BME280_SENSOR_ID) {
			h_sensor = FPSTR(SENSORS_BMX280);
			h_value = last_value_BME280_H;
		}
	}
	if (cfg::dnms_read) {
		la_sensor = FPSTR(SENSORS_DNMS);
		la_eq_value = last_value_dnms_laeq;
		la_max_value = last_value_dnms_la_max;
		la_min_value = last_value_dnms_la_min;
	}
	if (cfg::gps_read) {
		lat_value = last_value_GPS_lat;
		lon_value = last_value_GPS_lon;
		alt_value = last_value_GPS_alt;
	}
	if (cfg::ppd_read || cfg::pms_read || cfg::hpm_read || cfg::sds_read) {
		screens[screen_count++] = 1;
	}
	if (cfg::sps30_read) {
		screens[screen_count++] = 2;
	}
	if (cfg::dht_read || cfg::ds18b20_read || cfg::htu21d_read || cfg::bmp_read || cfg::bmx280_read) {
		screens[screen_count++] = 3;
	}
	if (cfg::gps_read) {
		screens[screen_count++] = 4;
	}
	if (cfg::dnms_read) {
		screens[screen_count++] = 5;
	}
	if (cfg::display_wifi_info) {
		screens[screen_count++] = 6;	// Wifi info
	}
	if (cfg::display_device_info) {
		screens[screen_count++] = 7;	// chipID, firmware and count of measurements
	}
	// update size of "screens" when adding more screens!

	if (cfg::has_display || cfg::has_sh1106 || cfg::has_lcd2004_27) {
		switch (screens[next_display_count % screen_count]) {
		case 1:
			display_header = pm25_sensor;
			if (pm25_sensor != pm10_sensor) {
				display_header += " / " + pm10_sensor;
			}
			display_lines[0] = std::move(tmpl(F("PM2.5: {v} µg/m³"), check_display_value(pm25_value, -1, 1, 6)));
			display_lines[1] = std::move(tmpl(F("PM10: {v} µg/m³"), check_display_value(pm10_value, -1, 1, 6)));
			display_lines[2] = empty_String;
			break;
		case 2:
			display_header = FPSTR(SENSORS_SPS30);
			display_lines[0] = "PM: " + check_display_value(pm010_value, -1, 1, 4) + " " + check_display_value(pm25_value, -1, 1, 4) + " " + check_display_value(pm040_value, -1, 1, 4) + " " + check_display_value(pm10_value, -1, 1, 4);
			display_lines[1] = "NC: " + check_display_value(nc005_value, -1, 0, 3) + " " + check_display_value(nc010_value, -1, 0, 3) + " " + check_display_value(nc025_value, -1, 0, 3) + " " + check_display_value(nc040_value, -1, 0, 3) + " " + check_display_value(nc100_value, -1, 0, 3);
			display_lines[2] = std::move(tmpl(F("TPS: {v} µm"), check_display_value(tps_value, -1, 2, 5)));
			break;
		case 3:
			display_header = t_sensor;
			if (h_sensor != "" && t_sensor != h_sensor) {
				display_header += " / " + h_sensor;
			}
			if ((h_sensor != "" && p_sensor != "" && (h_sensor != p_sensor)) || (h_sensor == "" && p_sensor != "" && (t_sensor != p_sensor))) {
				display_header += " / " + p_sensor;
			}
			if (t_sensor != "") { display_lines[line_count] = "Temp.: "; display_lines[line_count] += check_display_value(t_value, -128, 1, 6); display_lines[line_count++] += " °C"; }
			if (h_sensor != "") { display_lines[line_count] = "Hum.:  "; display_lines[line_count] += check_display_value(h_value, -1, 1, 6); display_lines[line_count++] += " %"; }
			if (p_sensor != "") { display_lines[line_count] = "Pres.: "; display_lines[line_count] += check_display_value(p_value / 100, (-1 / 100.0), 1, 6); display_lines[line_count++] += " hPa"; }
			while (line_count < 3) { display_lines[line_count++] = empty_String; }
			break;
		case 4:
			display_header = "NEO6M";
			display_lines[0] = "Lat: ";
			display_lines[0] += check_display_value(lat_value, -200.0, 6, 10);
			display_lines[1] = "Lon: ";
			display_lines[1] += check_display_value(lon_value, -200.0, 6, 10);
			display_lines[2] = "Alt: ";
			display_lines[2] += check_display_value(alt_value, -1000.0, 2, 10);
			break;
		case 5:
			display_header = FPSTR(SENSORS_DNMS);
			display_lines[0] = std::move(tmpl(F("LAeq: {v} db(A)"), check_display_value(la_eq_value, -1, 1, 6)));
			display_lines[1] = std::move(tmpl(F("LA_max: {v} db(A)"), check_display_value(la_max_value, -1, 1, 6)));
			display_lines[2] = std::move(tmpl(F("LA_min: {v} db(A)"), check_display_value(la_min_value, -1, 1, 6)));
			break;
		case 6:
			display_header = F("Wifi info");
			display_lines[0] = "IP: "; display_lines[0] += WiFi.localIP().toString();
			display_lines[1] = "SSID: "; display_lines[1] += WiFi.SSID();
			display_lines[2] = std::move(tmpl(F("Signal: {v} %"), String(calcWiFiSignalQuality(WiFi.RSSI()))));
			break;
		case 7:
			display_header = F("Device Info");
			display_lines[0] = "ID: "; display_lines[0] += esp_chipid;
			display_lines[1] = "FW: "; display_lines[1] += SOFTWARE_VERSION;
			display_lines[2] = "Measurements: "; display_lines[2] += String(count_sends);
			break;
		}

		if (cfg::has_display) {
			display.clear();
			display.displayOn();
			display.setTextAlignment(TEXT_ALIGN_CENTER);
			display.drawString(64, 1, display_header);
			display.setTextAlignment(TEXT_ALIGN_LEFT);
			display.drawString(0, 16, display_lines[0]);
			display.drawString(0, 28, display_lines[1]);
			display.drawString(0, 40, display_lines[2]);
			display.setTextAlignment(TEXT_ALIGN_CENTER);
			display.drawString(64, 52, displayGenerateFooter(screen_count));
			display.display();
		}
		if (cfg::has_sh1106) {
			display_sh1106.clear();
			display_sh1106.displayOn();
			display_sh1106.setTextAlignment(TEXT_ALIGN_CENTER);
			display_sh1106.drawString(64, 1, display_header);
			display_sh1106.setTextAlignment(TEXT_ALIGN_LEFT);
			display_sh1106.drawString(0, 16, display_lines[0]);
			display_sh1106.drawString(0, 28, display_lines[1]);
			display_sh1106.drawString(0, 40, display_lines[2]);
			display_sh1106.setTextAlignment(TEXT_ALIGN_CENTER);
			display_sh1106.drawString(64, 52, displayGenerateFooter(screen_count));
			display_sh1106.display();
		}
		if (cfg::has_lcd2004_27) {
			display_header = std::move(String((next_display_count % screen_count) + 1) + '/' + String(screen_count) + ' ' + display_header);
			display_lines[0].replace(" µg/m³", empty_String);
			display_lines[0].replace("°", String(char(223)));
			display_lines[1].replace(" µg/m³", empty_String);
			lcd_2004_27.clear();
			lcd_2004_27.setCursor(0, 0);
			lcd_2004_27.print(display_header);
			lcd_2004_27.setCursor(0, 1);
			lcd_2004_27.print(display_lines[0]);
			lcd_2004_27.setCursor(0, 2);
			lcd_2004_27.print(display_lines[1]);
			lcd_2004_27.setCursor(0, 3);
			lcd_2004_27.print(display_lines[2]);
		}
	}

// ----5----0----5----0
// PM10/2.5: 1999/999
// T/H: -10.0°C/100.0%
// T/P: -10.0°C/1000hPa

	if (cfg::has_lcd1602 || cfg::has_lcd1602_27 ) {
		switch (screens[next_display_count % screen_count]) {
		case 1:
			display_lines[0] = "PM2.5: ";
			display_lines[0] += check_display_value(pm25_value, -1, 1, 6);
			display_lines[1] = "PM10:  ";
			display_lines[1] += check_display_value(pm10_value, -1, 1, 6);
			break;
		case 2:
			display_lines[0] = "PM1.0: ";
			display_lines[0] += check_display_value(pm010_value, -1, 1, 4);
			display_lines[1] = "PM4: ";
			display_lines[1] += check_display_value(pm040_value, -1, 1, 4);
			break;
		case 3:
			display_lines[0] = std::move(tmpl(F("T: {v} °C"), check_display_value(t_value, -128, 1, 6)));
			display_lines[1] = std::move(tmpl(F("H: {v} %"), check_display_value(h_value, -1, 1, 6)));
			break;
		case 4:
			display_lines[0] = "Lat: ";
			display_lines[0] += check_display_value(lat_value, -200.0, 6, 11);
			display_lines[1] = "Lon: ";
			display_lines[1] += check_display_value(lon_value, -200.0, 6, 11);
			break;
		case 5:
			display_lines[0] = std::move(tmpl(F("LAeq: {v} db(A)"), check_display_value(la_eq_value, -1, 1, 6)));
			display_lines[1] = std::move(tmpl(F("LA_max: {v} db(A)"), check_display_value(la_max_value, -1, 1, 6)));
			break;
		case 6:
			display_lines[0] = WiFi.localIP().toString();
			display_lines[1] = WiFi.SSID();
			break;
		case 7:
			display_lines[0] = "ID: ";
			display_lines[0] += esp_chipid;
			display_lines[1] = "FW: ";
			display_lines[1] += SOFTWARE_VERSION;
			break;
		}

		display_lines[0].replace("°", String(char(223)));

		if (cfg::has_lcd1602_27) {
			lcd_1602_27.clear();
			lcd_1602_27.setCursor(0, 0);
			lcd_1602_27.print(display_lines[0]);
			lcd_1602_27.setCursor(0, 1);
			lcd_1602_27.print(display_lines[1]);
		}
		if (cfg::has_lcd1602) {
			lcd_1602_3f.clear();
			lcd_1602_3f.setCursor(0, 0);
			lcd_1602_3f.print(display_lines[0]);
			lcd_1602_3f.setCursor(0, 1);
			lcd_1602_3f.print(display_lines[1]);
		}
	}
	yield();
	next_display_count += 1;
	next_display_millis = millis() + DISPLAY_UPDATE_INTERVAL_MS;
}

/*****************************************************************
 * Init OLED display                                             *
 *****************************************************************/
static void init_display() {
	display.init();
	display_sh1106.init();
	if (cfg::has_flipped_display) {
		display.flipScreenVertically();
		display_sh1106.flipScreenVertically();
	}
}

/*****************************************************************
 * Init LCD display                                              *
 *****************************************************************/
static void init_lcd() {
	if (cfg::has_lcd1602_27) {
		lcd_1602_27.init();
		lcd_1602_27.backlight();
	}
	if (cfg::has_lcd1602) {
		lcd_1602_3f.init();
		lcd_1602_3f.backlight();
	}
	if (cfg::has_lcd2004_27) {
		lcd_2004_27.init();
		lcd_2004_27.backlight();
	}
}

/*****************************************************************
 * Init BMP280/BME280                                            *
 *****************************************************************/
static bool initBMX280(char addr) {
	debug_outln_info(F("Trying BMP280/BME280 sensor on "), String(addr, HEX));

	if (bmx280.begin(addr)) {
		debug_outln_info(FPSTR(DBG_TXT_FOUND));
		bmx280.setSampling(
			BMX280::MODE_FORCED,
			BMX280::SAMPLING_X1,
			BMX280::SAMPLING_X1,
			BMX280::SAMPLING_X1);
		return true;
	} else {
		debug_outln_info(FPSTR(DBG_TXT_NOT_FOUND));
		return false;
	}
}

/*****************************************************************
   Init SPS30 PM Sensor
 *****************************************************************/
static void initSPS30() {
	char serial[SPS_MAX_SERIAL_LEN];
	debug_out(F("Trying SPS30 sensor on 0x69H "), DEBUG_MIN_INFO);
	sps30_reset();
	delay(200);
	if ( sps30_get_serial(serial) != 0 ) {
		debug_outln_info(FPSTR(DBG_TXT_NOT_FOUND));

		debug_outln_info(F("Check SPS30 wiring"));
		sps30_init_failed = true;
		return;
	}
	debug_outln_info(F(" ... found, Serial-No.: "), String(serial));
	if (sps30_set_fan_auto_cleaning_interval(SPS30_AUTO_CLEANING_INTERVAL) != 0) {
		debug_outln_error(F("setting of Auto Cleaning Intervall SPS30 failed!"));
		sps30_init_failed = true;
		return;
	}
	delay(100);
	if (sps30_start_measurement() != 0) {
		debug_outln_error(F("SPS30 error starting measurement"));
		sps30_init_failed = true;
		return;
	}
}

/*****************************************************************
   Init DNMS - Digital Noise Measurement Sensor
 *****************************************************************/
static void initDNMS() {
	char dnms_version[DNMS_MAX_VERSION_LEN];

	debug_out(F("Trying DNMS sensor on 0x55H "), DEBUG_MIN_INFO);
	dnms_reset();
	delay(1000);
	if (dnms_read_version(dnms_version) != 0) {
		debug_outln_info(FPSTR(DBG_TXT_NOT_FOUND));
		debug_outln_error(F("Check DNMS wiring"));
		dnms_init_failed = 1;
	} else {
		debug_outln_info(FPSTR(DBG_TXT_FOUND), String(dnms_version));
	}
}

static void powerOnTestSensors() {
	if (cfg::ppd_read) {
		pinMode(PPD_PIN_PM1, INPUT_PULLUP);					// Listen at the designated PIN
		pinMode(PPD_PIN_PM2, INPUT_PULLUP);					// Listen at the designated PIN
		debug_outln_info(F("Read PPD..."));
	}

	if (cfg::sds_read) {
		debug_outln_info(F("Read SDS..."));
		SDS_cmd(PmSensorCmd::Start);
		delay(100);
		SDS_cmd(PmSensorCmd::ContinuousMode);
		delay(100);
		debug_outln_info(F("Stopping SDS011..."));
		is_SDS_running = SDS_cmd(PmSensorCmd::Stop);
	}

	if (cfg::pms_read) {
		debug_outln_info(F("Read PMS(1,3,5,6,7)003..."));
		PMS_cmd(PmSensorCmd::Start);
		delay(100);
		PMS_cmd(PmSensorCmd::ContinuousMode);
		delay(100);
		debug_outln_info(F("Stopping PMS..."));
		is_PMS_running = PMS_cmd(PmSensorCmd::Stop);
	}

	if (cfg::hpm_read) {
		debug_outln_info(F("Read HPM..."));
		HPM_cmd(PmSensorCmd::Start);
		delay(100);
		HPM_cmd(PmSensorCmd::ContinuousMode);
		delay(100);
		debug_outln_info(F("Stopping HPM..."));
		is_HPM_running = HPM_cmd(PmSensorCmd::Stop);
	}

	if (cfg::sps30_read) {
		debug_outln_info(F("Read SPS30..."));
		initSPS30();
	}

	if (cfg::dht_read) {
		dht.begin();										// Start DHT
		debug_outln_info(F("Read DHT..."));
	}

	if (cfg::htu21d_read) {
		debug_outln_info(F("Read HTU21D..."));
		if (!htu21d.begin()) {
			debug_outln_error(F("Check HTU21D wiring"));
			htu21d_init_failed = true;
		}
	}

	if (cfg::bmp_read) {
		debug_outln_info(F("Read BMP..."));
		if (!bmp.begin()) {
			debug_outln_error(F("No valid BMP085 sensor, check wiring!"));
			bmp_init_failed = 1;
		}
	}

	if (cfg::bmx280_read) {
		debug_outln_info(F("Read BMP280/BME280..."));
		if (!initBMX280(0x76) && !initBMX280(0x77)) {
			debug_outln_error(F("Check BMP280/BME280 wiring"));
			bmx280_init_failed = 1;
		}
	}

	if (cfg::ds18b20_read) {
		ds18b20.begin();									// Start DS18B20
		debug_outln_info(F("Read DS18B20..."));
	}

	if (cfg::dnms_read) {
		debug_outln_info(F("Read DNMS..."));
		initDNMS();
	}

}

static void logEnabledAPIs() {
	debug_outln_info(F("Send to :"));
	if (cfg::send2dusti) {
		debug_outln_info(F("luftdaten.info"));
	}

	if (cfg::send2madavi) {
		debug_outln_info(F("Madavi.de"));
	}

	if (cfg::send2csv) {
		debug_outln_info(F("Serial as CSV"));
	}

	if (cfg::send2custom) {
		debug_outln_info(F("custom API"));
	}

	if (cfg::send2aircms) {
		debug_outln_info(F("aircms API"));
	}

	if (cfg::send2influx) {
		debug_outln_info(F("custom influx DB"));
	}
	debug_outln_info(F("----"));
	if (cfg::auto_update) {
		debug_outln_info(F("Auto-Update active..."));
	}
}

static void logEnabledDisplays() {
	if (cfg::has_display || cfg::has_sh1106) {
		debug_outln_info(F("Show on OLED..."));
	}
	if (cfg::has_lcd1602 || cfg::has_lcd1602_27) {
		debug_outln_info(F("Show on LCD 1602 ..."));
	}
	if (cfg::has_lcd2004_27) {
		debug_outln_info(F("Show on LCD 2004 ..."));
	}
}

static void time_is_set (void) {
	sntp_time_is_set = true;
}

static bool acquireNetworkTime() {
	// server name ptrs must be persisted after the call to configTime because internally
	// the pointers are stored see implementation of lwip sntp_setservername()
	static char ntpServer1[16], ntpServer2[16];
	debug_outln_info(F("Setting time using SNTP"));
	time_t now = time(nullptr);
	debug_outln_info(ctime(&now));
#if defined(ESP8266)
	settimeofday_cb(time_is_set);
#endif
	WiFi.gatewayIP().toString().toCharArray(ntpServer1, sizeof(ntpServer1));
	String(String(INTL_LANG) + ".pool.ntp.org").toCharArray(ntpServer2, sizeof(ntpServer2));
	configTime(0, 0, ntpServer1, ntpServer2);
	for (int retryCount = 0; retryCount++ < 20; ++retryCount) {
		if (sntp_time_is_set) {
			now = time(nullptr);
			debug_outln_info(ctime(&now));
			return true;
		}
		delay(500);
		debug_out(".", DEBUG_MIN_INFO);
	}
	return false;
}

static unsigned long sendDataToOptionalApis(const String &data) {
	unsigned long sum_send_time = 0;

	if (cfg::send2madavi) {
		debug_outln_info(FPSTR(DBG_TXT_SENDING_TO), F("madavi.de: "));
		sum_send_time += sendData(data, 0, HOST_MADAVI, (cfg::ssl_madavi ? 443 : 80), URL_MADAVI, cfg::ssl_madavi, "", FPSTR(TXT_CONTENT_TYPE_JSON));
	}

	if (cfg::send2sensemap && (cfg::senseboxid[0] != '\0')) {
		debug_outln_info(FPSTR(DBG_TXT_SENDING_TO), F("opensensemap: "));
		String sensemap_path(tmpl(FPSTR(URL_SENSEMAP), cfg::senseboxid));
		sum_send_time += sendData(data, 0, HOST_SENSEMAP, PORT_SENSEMAP, sensemap_path.c_str(), true, "", FPSTR(TXT_CONTENT_TYPE_JSON));
	}

	if (cfg::send2fsapp) {
		debug_outln_info(FPSTR(DBG_TXT_SENDING_TO), F("Server FS App: "));
		sum_send_time += sendData(data, 0, HOST_FSAPP, PORT_FSAPP, URL_FSAPP, false, "", FPSTR(TXT_CONTENT_TYPE_JSON));
	}

	if (cfg::send2aircms) {
		debug_outln_info(FPSTR(DBG_TXT_SENDING_TO), F(" aircms.online: "));
		unsigned long ts = millis() / 1000;
		String token = WiFi.macAddress();
		String aircms_data = "L=" + esp_chipid + "&t=" + String(ts, DEC) + "&airrohr=" + data;
		String aircms_url(FPSTR(URL_AIRCMS));
		aircms_url += hmac1(sha1Hex(token), aircms_data + token);

		sum_send_time += sendData(aircms_data, 0, HOST_AIRCMS, PORT_AIRCMS, aircms_url.c_str(), true, "", FPSTR(TXT_CONTENT_TYPE_TEXT_PLAIN));
	}

	if (cfg::send2influx) {
		debug_outln_info(FPSTR(DBG_TXT_SENDING_TO), F("custom influx db: "));
		const String data_4_influxdb = create_influxdb_string(data);
		sum_send_time += sendData(data_4_influxdb, 0, cfg::host_influx, cfg::port_influx, cfg::url_influx, cfg::ssl_influx, basic_auth_influx.c_str(), FPSTR(TXT_CONTENT_TYPE_INFLUXDB));
	}

	if (cfg::send2csv) {
		debug_outln_info(F("## Sending as csv: "));
		send_csv(data);
	}

	if (cfg::send2custom) {
		String data_to_send = data;
		data_to_send.remove(0, 1);
		String data_4_custom("{\"esp8266id\": \"");
		data_4_custom += esp_chipid;
		data_4_custom += "\", ";
		data_4_custom += data_to_send;
		debug_outln_info(FPSTR(DBG_TXT_SENDING_TO), F("custom api: "));
		sum_send_time += sendData(data_4_custom, 0, cfg::host_custom, cfg::port_custom, cfg::url_custom, cfg::ssl_custom || (cfg::port_custom == 443), basic_auth_custom.c_str(), FPSTR(TXT_CONTENT_TYPE_JSON));
	}
	return sum_send_time;
}

/*****************************************************************
 * The Setup                                                     *
 *****************************************************************/

void setup(void) {
	Serial.begin(9600);					// Output to Serial at 9600 baud
#if defined(ESP8266)
	serialSDS.begin(9600);
#endif
#if defined(ESP32)
	serialSDS.begin(9600, SERIAL_8N1, PM_SERIAL_RX, PM_SERIAL_TX);
#endif

#if defined(WIFI_LoRa_32_V2)
	// reset the OLED display, e.g. of the heltec_wifi_lora_32 board
	pinMode(RST_OLED, OUTPUT);
	digitalWrite(RST_OLED, LOW);
	delay(50);
	digitalWrite(RST_OLED, HIGH);
#endif
	Wire.begin(I2C_PIN_SDA, I2C_PIN_SCL);

#if defined(ESP8266)
	esp_chipid = std::move(String(ESP.getChipId()));
#endif
#if defined(ESP32)
	uint64_t chipid_num;
	chipid_num = ESP.getEfuseMac();
	esp_chipid = String((uint16_t)(chipid_num >> 32), HEX);
	esp_chipid += String((uint32_t)chipid_num, HEX);
#endif
	cfg::initNonTrivials(esp_chipid.c_str());
	WiFi.persistent(false);

	readConfig();
	init_display();
	init_lcd();
	display_debug(F("Connecting to"), String(cfg::wlanssid));
	connectWifi();
	bool got_ntp = acquireNetworkTime();
	debug_out(F("\nNTP time "), DEBUG_MIN_INFO);
	debug_outln_info(got_ntp ? FPSTR(DBG_TXT_FOUND) : FPSTR(DBG_TXT_NOT_FOUND));
	twoStageAutoUpdate();
	setup_webserver();
	create_basic_auth_strings();
	debug_outln_info(F("\nChipId: "), esp_chipid);


	if (cfg::gps_read) {
		serialGPS = new SoftwareSerial(GPS_SERIAL_RX, GPS_SERIAL_TX, false, 512);
#if defined(ESP8266)
		serialGPS->begin(9600);
#endif
#if defined(ESP32)
		serialGPS->begin(9600, SERIAL_8N1, GPS_SERIAL_RX, GPS_SERIAL_TX);
#endif
		debug_outln_info(F("Read GPS..."));
		disable_unneeded_nmea();
	}

	powerOnTestSensors();
	logEnabledAPIs();
	logEnabledDisplays();

	delay(50);

	// sometimes parallel sending data and web page will stop nodemcu, watchdogtimer set to 30 seconds
#if defined(ESP8266)
	wdt_disable();
#if defined(NDEBUG)
	wdt_enable(30000);
#endif
#endif

	starttime = millis();									// store the start time
	time_point_device_start_ms = starttime;
	starttime_SDS = starttime;
	next_display_millis = starttime + DISPLAY_UPDATE_INTERVAL_MS;
}

/*****************************************************************
 * And action                                                    *
 *****************************************************************/
void loop(void) {
	String result_PPD, result_SDS, result_PMS, result_HPM;
	String result_GPS, result_DNMS;

	unsigned sum_send_time = 0;

	act_micro = micros();
	act_milli = millis();
	send_now = msSince(starttime) > cfg::sending_intervall_ms;

	sample_count++;

#if defined(ESP8266)
	wdt_reset(); // nodemcu is alive
#endif

	if (last_micro != 0) {
		unsigned long diff_micro = act_micro - last_micro;
		if (max_micro < diff_micro) {
			max_micro = diff_micro;
		}
		if (min_micro > diff_micro) {
			min_micro = diff_micro;
		}
	}
	last_micro = act_micro;

	if (msSince(time_point_device_start_ms) > DURATION_BEFORE_FORCED_RESTART_MS) {
		ESP.restart();
	}

	if (msSince(last_update_attempt) > PAUSE_BETWEEN_UPDATE_ATTEMPTS_MS) {
		twoStageAutoUpdate();
	}

	if (cfg::sps30_read && ( !sps30_init_failed)) {
		if ((msSince(starttime) - SPS30_read_timer) > SPS30_WAITING_AFTER_LAST_READ) {
			struct sps30_measurement sps30_values;
			int16_t ret_SPS30;

			SPS30_read_timer = msSince(starttime);

			ret_SPS30 = sps30_read_measurement(&sps30_values);
			++SPS30_read_counter;
			if (ret_SPS30 < 0) {
				debug_outln_info(F("SPS30 error reading measurement"));
				SPS30_read_error_counter++;
			} else {
				if (SPS_IS_ERR_STATE(ret_SPS30)) {
					debug_outln_info(F("SPS30 measurements may not be accurate"));
					SPS30_read_error_counter++;
				}
				value_SPS30_P0 += sps30_values.mc_1p0;
				value_SPS30_P1 += sps30_values.mc_2p5;
				value_SPS30_P2 += sps30_values.mc_4p0;
				value_SPS30_P3 += sps30_values.mc_10p0;
				value_SPS30_N0 += sps30_values.nc_0p5;
				value_SPS30_N1 += sps30_values.nc_1p0;
				value_SPS30_N2 += sps30_values.nc_2p5;
				value_SPS30_N3 += sps30_values.nc_4p0;
				value_SPS30_N4 += sps30_values.nc_10p0;
				value_SPS30_TS += sps30_values.tps;
				++SPS30_measurement_count;
			}
		}
	}

	if (cfg::ppd_read) {
		fetchSensorPPD(result_PPD);
	}

	if ((msSince(starttime_SDS) > SAMPLETIME_SDS_MS) || send_now) {
		starttime_SDS = act_milli;
		if (cfg::sds_read) {
			fetchSensorSDS(result_SDS);
		}

		if (cfg::pms_read) {
			fetchSensorPMS(result_PMS);
		}

		if (cfg::hpm_read) {
			fetchSensorHPM(result_HPM);
		}
	}

	if (cfg::gps_read && !gps_init_failed) {
		// process serial GPS data..
		while (serialGPS->available() > 0) {
			gps.encode(serialGPS->read());
		}

		if ((msSince(starttime_GPS) > SAMPLETIME_GPS_MS) || send_now) {
			// getting GPS coordinates
			fetchSensorGPS(result_GPS);
			starttime_GPS = act_milli;
		}
	}

	if ((cfg::has_display || cfg::has_sh1106 || cfg::has_lcd2004_27 || cfg::has_lcd1602 ||
			cfg::has_lcd1602_27) && (act_milli > next_display_millis)) {
		display_values();
	}

	server.handleClient();
	yield();

	if (send_now) {
		debug_outln_info(F("Creating data string:"));
		String signal_strength(WiFi.RSSI());
		RESERVE_STRING(data, LARGE_STR);
		data = FPSTR(data_first_part);
		RESERVE_STRING(result, MED_STR);

		debug_outln_info(F("WLAN signal strength (dBm): "), signal_strength);
		debug_outln_info(F("----"));

		if (cfg::ppd_read) {
			data += result_PPD;
			sum_send_time += sendLuftdaten(result_PPD, PPD_API_PIN, FPSTR(SENSORS_PPD42NS), "PPD_");
		}
		if (cfg::sds_read) {
			data += result_SDS;
			sum_send_time += sendLuftdaten(result_SDS, SDS_API_PIN, FPSTR(SENSORS_SDS011), "SDS_");
		}
		if (cfg::pms_read) {
			data += result_PMS;
			sum_send_time += sendLuftdaten(result_PMS, PMS_API_PIN, FPSTR(SENSORS_PMSx003), "PMS_");
		}
		if (cfg::hpm_read) {
			data += result_HPM;
			sum_send_time += sendLuftdaten(result_HPM, HPM_API_PIN, FPSTR(SENSORS_HPM), "HPM_");
		}
		if (cfg::sps30_read && (! sps30_init_failed)) {
			fetchSensorSPS30(result);
			data += result;
			sum_send_time += sendLuftdaten(result, SPS30_API_PIN, FPSTR(SENSORS_SPS30), "SPS30_");
		}
		if (cfg::dht_read) {
			// getting temperature and humidity (optional)
			fetchSensorDHT(result);
			data += result;
			sum_send_time += sendLuftdaten(result, DHT_API_PIN, FPSTR(SENSORS_DHT22), "DHT_");
		}
		if (cfg::htu21d_read && (! htu21d_init_failed)) {
			// getting temperature and humidity (optional)
			fetchSensorHTU21D(result);
			data += result;
			sum_send_time += sendLuftdaten(result, HTU21D_API_PIN, FPSTR(SENSORS_HTU21D), "HTU21D_");
		}
		if (cfg::bmp_read && (! bmp_init_failed)) {
			// getting temperature and pressure (optional)
			fetchSensorBMP(result);
			data += result;
			sum_send_time += sendLuftdaten(result, BMP_API_PIN, FPSTR(SENSORS_BMP180), "BMP_");
		}
		if (cfg::bmx280_read && (! bmx280_init_failed)) {
			// getting temperature, humidity and pressure (optional)
			fetchSensorBMX280(result);
			data += result;
			if (bmx280.sensorID() == BME280_SENSOR_ID) {
				sum_send_time += sendLuftdaten(result, BME280_API_PIN, FPSTR(SENSORS_BMX280), "BME280_");
			} else {
				sum_send_time += sendLuftdaten(result, BMP280_API_PIN, FPSTR(SENSORS_BMX280), "BMP280_");
			}
		}
		if (cfg::ds18b20_read) {
			// getting temperature (optional)
			fetchSensorDS18B20(result);
			data += result;
			sum_send_time += sendLuftdaten(result, DS18B20_API_PIN, FPSTR(SENSORS_DS18B20), "DS18B20_");
		}
		if (cfg::dnms_read && (! dnms_init_failed)) {
			// getting noise measurement values from dnms (optional)
			fetchSensorDNMS(result);
			data += result;
			sum_send_time += sendLuftdaten(result, DNMS_API_PIN, FPSTR(SENSORS_DNMS), "DNMS_");
		}
		if (cfg::gps_read) {
			data += result_GPS;
			sum_send_time += sendLuftdaten(result_GPS, GPS_API_PIN, F("GPS"), "GPS_");
		}
		add_Value2Json(data, F("samples"), String(sample_count));
		add_Value2Json(data, F("min_micro"), String(min_micro));
		add_Value2Json(data, F("max_micro"), String(max_micro));
		add_Value2Json(data, F("signal"), signal_strength);

		if ((unsigned)(data.lastIndexOf(',') + 1) == data.length()) {
			data.remove(data.length() - 1);
		}
		data += "]}";

		sum_send_time += sendDataToOptionalApis(data);

		sending_time = (4 * sending_time + sum_send_time) / 5;
		debug_outln_info(F("Time for sending data (ms): "), String(sending_time));

		// reconnect to WiFi if disconnected
		if (WiFi.status() != WL_CONNECTED) {
			debug_outln_info(F("Connection lost, reconnecting "));
			WiFi.reconnect();
			waitForWifiToConnect(20);
		}

		// Resetting for next sampling
		last_data_string = std::move(data);
		lowpulseoccupancyP1 = 0;
		lowpulseoccupancyP2 = 0;
		sample_count = 0;
		last_micro = 0;
		min_micro = 1000000000;
		max_micro = 0;
		sum_send_time = 0;
		starttime = millis();								// store the start time
		first_cycle = false;
		count_sends += 1;
	}
	yield();
#if defined(ESP8266)
	MDNS.update();
#endif

	if (sample_count % 500 == 0) {
//		Serial.println(ESP.getFreeHeap(),DEC);
	}
}
