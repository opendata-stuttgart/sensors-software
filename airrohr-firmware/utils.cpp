/************************************************************************
 *                                                                      *
 *    airRohr firmware                                                  *
 *    Copyright (C) 2016-2020  Code for Stuttgart a.o.                  *
 *    Copyright (C) 2019-2020  Dirk Mueller                             *
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
 */

#include <WString.h>
#include <Hash.h>
#include <coredecls.h>
#include <ESP8266WiFi.h>

#include "./intl.h"
#include "./utils.h"
#include "./defines.h"

#include "ca-root.h"


/*****************************************************************
 * aircms.online helper functions                                *
 *****************************************************************/
String sha1Hex(const String& s) {
	char sha1sum_output[20];

#if defined(ESP8266)
	br_sha1_context sc;

	br_sha1_init(&sc);
	br_sha1_update(&sc, s.c_str(), s.length());
	br_sha1_out(&sc, sha1sum_output);
#endif
#if defined(ESP32)
	esp_sha(SHA1, (const unsigned char*) s.c_str(), s.length(), (unsigned char*)sha1sum_output);
#endif
	String r;
	for (uint16_t i = 0; i < 20; i++) {
		char hex[3];
		snprintf(hex, sizeof(hex), "%02x", sha1sum_output[i]);
		r += hex;
	}
	return r;
}

String hmac1(const String& secret, const String& s) {
	String str = sha1Hex(s);
	str = secret + str;
	return sha1Hex(str);
}

String tmpl(const __FlashStringHelper* patt, const String& value) {
	String s = patt;
	s.replace("{v}", value);
	return s;
}

void add_line_value(String& s, const __FlashStringHelper* name, const String& value) {
	s += F("<br/>");
	s += name;
	s += ": ";
	s += value;
}

void add_line_value_bool(String& s, const __FlashStringHelper* name, const bool value) {
	add_line_value(s, name, String(value));
}

void add_line_value_bool(String&s, const __FlashStringHelper* patt, const __FlashStringHelper* name, const bool value) {
	s += F("<br/>");
	s += tmpl(patt, name);
	s += ": ";
	s += String(value);
}

void add_table_row_from_value(String& page_content, const __FlashStringHelper* sensor, const __FlashStringHelper* param, const String& value, const String& unit) {
	RESERVE_STRING(s, MED_STR);
	s = F("<tr><td>{s}</td><td>{p}</td><td class='r'>{v}&nbsp;{u}</td></tr>");
	s.replace("{s}", sensor);
	s.replace("{p}", param);
	s.replace("{v}", value);
	s.replace("{u}", unit);
	page_content += s;
}

void add_table_row_from_value(String& page_content, const __FlashStringHelper* param, const String& value, const char* unit) {
	RESERVE_STRING(s, MED_STR);
	s = F("<tr><td>{p}</td><td class='r'>{v}&nbsp;{u}</td></tr>");
	s.replace("{p}", param);
	s.replace("{v}", value);
	s.replace("{u}", String(unit));
	page_content += s;
}

int32_t calcWiFiSignalQuality(int32_t rssi) {
	// Treat 0 or positive values as 0%
	if (rssi >= 0 || rssi < -100) {
		rssi = -100;
	}
	if (rssi > -50) {
		rssi = -50;
	}
	return (rssi + 100) * 2;
}

String add_sensor_type(const String& sensor_text) {
	RESERVE_STRING(s, SMALL_STR);
	s = sensor_text;
	s.replace("{pm}", FPSTR(INTL_PARTICULATE_MATTER));
	s.replace("{t}", FPSTR(INTL_TEMPERATURE));
	s.replace("{h}", FPSTR(INTL_HUMIDITY));
	s.replace("{p}", FPSTR(INTL_PRESSURE));
	s.replace("{l_a}", FPSTR(INTL_LEQ_A));
	return s;
}

String wlan_ssid_to_table_row(const String& ssid, const String& encryption, int32_t rssi) {
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

String delayToString(unsigned time_ms) {

	char buf[64];
	String s;

	if (time_ms > 2 * 1000 * 60 * 60 * 24) {
		sprintf_P(buf, PSTR("%d days, "), time_ms / (1000 * 60 * 60 * 24));
		s += buf;
		time_ms %= 1000 * 60 * 60 * 24;
	}

	if (time_ms > 2 * 1000 * 60 * 60) {
		sprintf_P(buf, PSTR("%d hours, "), time_ms / (1000 * 60 * 60));
		s += buf;
		time_ms %= 1000 * 60 * 60;
	}

	if (time_ms > 2 * 1000 * 60) {
		sprintf_P(buf, PSTR("%d min, "), time_ms / (1000 * 60));
		s += buf;
		time_ms %= 1000 * 60;
	}

	if (time_ms > 2 * 1000) {
		sprintf_P(buf, PSTR("%ds, "), time_ms / 1000);
		s += buf;
	}

	if (s.length() > 2) {
		s = s.substring(0, s.length() - 2);
	}

	return s;
}

#if defined(ESP8266)
BearSSL::X509List x509_dst_root_ca(dst_root_ca_x3);

void configureCACertTrustAnchor(WiFiClientSecure* client) {
	constexpr time_t fw_built_year = (__DATE__[ 7] - '0') * 1000 + \
							  (__DATE__[ 8] - '0') *  100 + \
							  (__DATE__[ 9] - '0') *   10 + \
							  (__DATE__[10] - '0');
	if (time(nullptr) < (fw_built_year - 1970) * 365 * 24 * 3600) {
		debug_outln_info(F("Time incorrect; Disabling CA verification."));
		client->setInsecure();
	}
	else {
		client->setTrustAnchors(&x509_dst_root_ca);
	}
}

bool launchUpdateLoader(const String& md5) {

	File loaderFile = SPIFFS.open(F("/loader.bin"), "r");
	if (!loaderFile) {
		return false;
	}

	if (!Update.begin(loaderFile.size(), U_FLASH)) {
		return false;
	}

	if (md5.length() && !Update.setMD5(md5.c_str())) {
		return false;
	}

	if (Update.writeStream(loaderFile) != loaderFile.size()) {
		return false;
	}
	loaderFile.close();

	if (!Update.end()) {
		return false;
	}

	debug_outln_info(F("Erasing SDK config."));
	ESP.eraseConfig();
	return true;
}

#endif


/*****************************************************************
 * check display values, return '-' if undefined                 *
 *****************************************************************/
String check_display_value(double value, double undef, uint8_t len, uint8_t str_len) {
	RESERVE_STRING(s, 15);
	s = (value != undef ? String(value, len) : String("-"));
	while (s.length() < str_len) {
		s = " " + s;
	}
	return s;
}

/*****************************************************************
 * add value to json string                                  *
 *****************************************************************/
void add_Value2Json(String& res, const __FlashStringHelper* type, const String& value) {
	RESERVE_STRING(s, SMALL_STR);

	s = F("{\"value_type\":\"{t}\",\"value\":\"{v}\"},");
	s.replace("{t}", String(type));
	s.replace("{v}", value);
	res += s;
}

void add_Value2Json(String& res, const __FlashStringHelper* type, const __FlashStringHelper* debug_type, const float& value) {
	debug_outln_info(FPSTR(debug_type), value);
	add_Value2Json(res, type, String(value));
}

float readCorrectionOffset(const char* correction) {
	char* pEnd = nullptr;
	// Avoiding atof() here as this adds a lot (~ 9kb) of code size
	float r = float(strtol(correction, &pEnd, 10));
	if (pEnd && pEnd[0] == '.' && pEnd[1] >= '0' && pEnd[1] <= '9') {
		r += (r >= 0 ? 1.0 : -1.0) * ((pEnd[1] - '0') / 10.0);
	}
	return r;
}

/*****************************************************************
 * Debug output                                                  *
 *****************************************************************/

#define debug_level_check(level) { if (level > cfg::debug) return; }

void debug_out(const String& text, unsigned int level) {
	debug_level_check(level); Serial.print(text);
}

void debug_out(const __FlashStringHelper* text, unsigned int level) {
	debug_level_check(level); Serial.print(text);
}

void debug_outln(const String& text, unsigned int level) {
	debug_level_check(level); Serial.println(text);
}

void debug_outln_info(const String& text) {
	debug_level_check(DEBUG_MIN_INFO); Serial.println(text);
}

void debug_outln_verbose(const String& text) {
	debug_level_check(DEBUG_MED_INFO); Serial.println(text);
}

void debug_outln_error(const __FlashStringHelper* text) {
	debug_level_check(DEBUG_ERROR); Serial.println(text);
}

void debug_outln_info(const __FlashStringHelper* text) {
	debug_level_check(DEBUG_MIN_INFO); Serial.println(text);
}

void debug_outln_verbose(const __FlashStringHelper* text) {
	debug_level_check(DEBUG_MED_INFO); Serial.println(text);
}

void debug_outln_info(const __FlashStringHelper* text, const String& option) {
	debug_level_check(DEBUG_MIN_INFO);
	Serial.print(text);
	Serial.println(option);
}

void debug_outln_info(const __FlashStringHelper* text, float value) {
	debug_outln_info(text, String(value));
}

void debug_outln_verbose(const __FlashStringHelper* text, const String& option) {
	debug_level_check(DEBUG_MED_INFO);
	Serial.print(text);
	Serial.println(option);
}

void debug_outln_info_bool(const __FlashStringHelper* text, const bool option) {
	debug_level_check(DEBUG_MIN_INFO);
	Serial.print(text);
	Serial.println(String(option));
}

#undef debug_level_check