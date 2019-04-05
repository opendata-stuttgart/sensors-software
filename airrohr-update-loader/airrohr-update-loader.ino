#include <Arduino.h>

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
 *                                                                      *
 * Loader for two step update                                           *
 *                                                                      *
 *                                                                      *
 ************************************************************************
 *                                                                      *
 *
 * 06.07.2018
 * Der Sketch verwendet 459607 Bytes (44%) des Programmspeicherplatzes. Das Maximum sind 1044464 Bytes.
 * Globale Variablen verwenden 48736 Bytes (59%) des dynamischen Speichers, 33184 Bytes für lokale Variablen verbleiben. Das Maximum sind 81920 Bytes.
 *
 * first version with esp8266 lib 2.4.2
 * Der Sketch verwendet 491364 Bytes (47%) des Programmspeicherplatzes. Das Maximum sind 1044464 Bytes.
 * Globale Variablen verwenden 37172 Bytes (45%) des dynamischen Speichers, 44748 Bytes für lokale Variablen verbleiben. Das Maximum sind 81920 Bytes.
 *
 * Der Sketch verwendet 489152 Bytes (46%) des Programmspeicherplatzes. Das Maximum sind 1044464 Bytes.
 * Globale Variablen verwenden 37160 Bytes (45%) des dynamischen Speichers, 44760 Bytes für lokale Variablen verbleiben. Das Maximum sind 81920 Bytes.
 *
 ************************************************************************/
// increment on change
#define SOFTWARE_VERSION "LOADER-001"

/*****************************************************************
 * Includes                                                      *
 *****************************************************************/
#include <FS.h>                     // must be first
#include <ESP8266WiFi.h>
#include <ESP8266httpUpdate.h>
#include <ArduinoJson.h>
#include <time.h>
#include <coredecls.h>
#include <assert.h>

// define debug levels
#define DEBUG_ERROR 1
#define DEBUG_WARNING 2
#define DEBUG_MIN_INFO 3
#define DEBUG_MED_INFO 4
#define DEBUG_MAX_INFO 5

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
	char wlanssid[35];
	char wlanpwd[65];

	char current_lang[3] = "DE";
	char www_username[65];
	char www_password[65];
	bool www_basicauth_enabled;

	char fs_ssid[33];
	char fs_pwd[65];

	char version_from_local_config[20] = "";

	bool dht_read;
	bool htu21d_read;
	bool ppd_read;
	bool sds_read;
	bool pms_read;
	bool hpm_read;
	bool bmp_read;
	bool bmp280_read;
	bool bme280_read;
	bool ds18b20_read;
	bool gps_read;
	bool send2dusti;
	bool send2madavi;
	bool send2sensemap;
	bool send2fsapp;
	bool send2custom;
	bool send2lora;
	bool send2influx;
	bool send2csv;
	bool auto_update;
	bool use_beta;
	bool has_display;
	bool has_sh1106;
	bool has_lcd1602;
	bool has_lcd1602_27;
	bool has_lcd2004_27;
	int  debug;

	bool ssl_madavi;
	bool ssl_dusti;
	char senseboxid[30];

	char host_influx[100];
	char url_influx[100];
	int port_influx;
	char user_influx[65];
	char pwd_influx[65];
	char measurement_name_influx[100];
	bool ssl_influx;

	char host_custom[100];
	char url_custom[100];
	int port_custom;
	char user_custom[65];
	char pwd_custom[65];

	unsigned long time_for_wifi_config = 600000;
	unsigned long sending_intervall_ms = 145000;

	void initNonTrivials(const char* id) {
		strcpy(cfg::current_lang, "DE");
		if (fs_ssid[0] == '\0') {
			strcpy(fs_ssid, "Feinstaubsensor-");
			strcat(fs_ssid, id);
		}
	}
}

#define UPDATE_HOST "www.madavi.de"
#define UPDATE_URL "/sensor/update/firmware.php"
#define UPDATE_PORT 80

#define JSON_BUFFER_SIZE 2000

int TimeZone = 1;

String esp_chipid;

bool sntp_time_is_set = false;

bool got_ntp = false;

struct struct_wifiInfo {
	char ssid[35];
	uint8_t encryptionType;
	int32_t RSSI;
	int32_t channel;
	bool isHidden;
};

struct struct_wifiInfo *wifiInfo;
uint8_t count_wifiInfo;

template<typename T, std::size_t N> constexpr std::size_t array_num_elements(const T(&)[N]) {
	return N;
}

template<typename T, std::size_t N> constexpr std::size_t capacity_null_terminated_char_array(const T(&)[N]) {
	return N - 1;
}

/*****************************************************************
 * Debug output                                                  *
 *****************************************************************/
void debug_out(const String& text, const int level, const bool linebreak) {
	if (level <= cfg::debug) {
		if (linebreak) {
			Serial.println(text);
		} else {
			Serial.print(text);
		}
	}
}

/*****************************************************************
 * read config from spiffs                                       *
 *****************************************************************/
void readConfig() {
	using namespace cfg;
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
				const size_t size = configFile.size();
				// Allocate a buffer to store contents of the file.
				std::unique_ptr<char[]> buf(new char[size]);

				configFile.readBytes(buf.get(), size);
				StaticJsonBuffer<JSON_BUFFER_SIZE> jsonBuffer;
				JsonObject& json = jsonBuffer.parseObject(buf.get());
				json.printTo(json_string);
				debug_out(F("File content: "), DEBUG_MAX_INFO, 0);
				debug_out(String(buf.get()), DEBUG_MAX_INFO, 1);
				debug_out(F("JSON Buffer content: "), DEBUG_MAX_INFO, 0);
				debug_out(json_string, DEBUG_MAX_INFO, 1);
				if (json.success()) {
					debug_out(F("parsed json..."), DEBUG_MIN_INFO, 1);
					if (json.containsKey("SOFTWARE_VERSION")) {
						strcpy(version_from_local_config, json["SOFTWARE_VERSION"]);
					}

#define setFromJSON(key)    if (json.containsKey(#key)) key = json[#key];
#define strcpyFromJSON(key) if (json.containsKey(#key)) strcpy(key, json[#key]);
					strcpyFromJSON(current_lang);
					strcpyFromJSON(wlanssid);
					strcpyFromJSON(wlanpwd);

					setFromJSON(auto_update);
					setFromJSON(use_beta);
					setFromJSON(debug);
					configFile.close();
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
}

static void waitForWifiToConnect(int maxRetries) {
	int retryCount = 0;
	while ((WiFi.status() != WL_CONNECTED) && (retryCount <  maxRetries)) {
		delay(500);
		debug_out(".", DEBUG_MIN_INFO, 0);
		++retryCount;
	}
}

/*****************************************************************
 * WiFi auto connecting script                                   *
 *****************************************************************/
void connectWifi() {
	debug_out(String(WiFi.status()), DEBUG_MIN_INFO, 1);
	WiFi.disconnect();
	WiFi.setOutputPower(20.5);
	WiFi.setPhyMode(WIFI_PHY_MODE_11N);
	WiFi.mode(WIFI_STA);
	WiFi.begin(cfg::wlanssid, cfg::wlanpwd); // Start WiFI

	debug_out(F("Connecting to "), DEBUG_MIN_INFO, 0);
	debug_out(cfg::wlanssid, DEBUG_MIN_INFO, 1);

	waitForWifiToConnect(40);
	debug_out("", DEBUG_MIN_INFO, 1);
	debug_out(F("WiFi connected\nIP address: "), DEBUG_MIN_INFO, 0);
	debug_out(WiFi.localIP().toString(), DEBUG_MIN_INFO, 1);
}

/*****************************************************************
 * AutoUpdate                                                    *
 *****************************************************************/
static void autoUpdate() {
	if (cfg::auto_update) {
		debug_out(F("Starting OTA update ..."), DEBUG_MIN_INFO, 1);
		debug_out(F("NodeMCU firmware : "), DEBUG_MIN_INFO, 0);
		debug_out(SOFTWARE_VERSION, DEBUG_MIN_INFO, 1);
		debug_out(UPDATE_HOST, DEBUG_MED_INFO, 1);
		debug_out(UPDATE_URL, DEBUG_MED_INFO, 1);

		t_httpUpdate_return ret = ESPhttpUpdate.update(UPDATE_HOST, UPDATE_PORT, UPDATE_URL,
									 SOFTWARE_VERSION + String(" ") + esp_chipid + String(" ") + String("update_loader") + String(" ") +
									 String(cfg::current_lang) + String(" ") + String(cfg::current_lang) + String(" ") +
									 String(cfg::use_beta ? "BETA" : ""));
		switch(ret) {
		case HTTP_UPDATE_FAILED:
			debug_out(F("Update failed ..."), DEBUG_ERROR, 0);
			debug_out(ESPhttpUpdate.getLastErrorString().c_str(), DEBUG_ERROR, 1);
			break;
		case HTTP_UPDATE_NO_UPDATES:
			debug_out(F("No update found ..."), DEBUG_MIN_INFO, 1);
			break;
		case HTTP_UPDATE_OK:
			debug_out(F("Update ok..."), DEBUG_MIN_INFO, 1); // may not called we reboot the ESP
			break;
		}
	}
}

void time_is_set (void) {
	sntp_time_is_set = true;
}

static bool acquireNetworkTime() {
	int retryCount = 0;
	debug_out(F("Setting time using SNTP"), DEBUG_MIN_INFO, 1);
	time_t now = time(nullptr);
	debug_out(ctime(&now), DEBUG_MIN_INFO, 1);
	debug_out(F("NTP.org:"),DEBUG_MIN_INFO,1);
	settimeofday_cb(time_is_set);
	configTime(8 * 3600, 0, "pool.ntp.org");
	while (retryCount++ < 20) {
		// later than 2000/01/01:00:00:00
		if (sntp_time_is_set) {
			now = time(nullptr);
			debug_out(ctime(&now), DEBUG_MIN_INFO, 1);
			return true;
		}
		delay(500);
		debug_out(".",DEBUG_MIN_INFO,0);
	}
	debug_out(F("\nrouter/gateway:"),DEBUG_MIN_INFO,1);
	retryCount = 0;
	configTime(0, 0, WiFi.gatewayIP().toString().c_str());
	while (retryCount++ < 20) {
		// later than 2000/01/01:00:00:00
		if (sntp_time_is_set) {
			now = time(nullptr);
			debug_out(ctime(&now), DEBUG_MIN_INFO, 1);
			return true;
		}
		delay(500);
		debug_out(".",DEBUG_MIN_INFO,0);
	}
	return false;
}

/*****************************************************************
 * The Setup                                                     *
 *****************************************************************/
void setup() {
	Serial.begin(9600);					// Output to Serial at 9600 baud

	esp_chipid = String(ESP.getChipId());
	cfg::initNonTrivials(esp_chipid.c_str());
	readConfig();

	connectWifi();
	got_ntp = acquireNetworkTime();
	debug_out(F("\nNTP time "), DEBUG_MIN_INFO, 0);
	debug_out(String(got_ntp?"":"not ")+F("received"), DEBUG_MIN_INFO, 1);
	autoUpdate();
}

/*****************************************************************
 * And action                                                    *
 *****************************************************************/
void loop() {
	yield();
//	if (sample_count % 500 == 0) { Serial.println(ESP.getFreeHeap(),DEC); }
}
