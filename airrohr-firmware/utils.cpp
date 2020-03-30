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

#include "./intl.h"
#include "./utils.h"
#include "./defines.h"
#include "./ext_def.h"

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

LoggingSerial Debug;

#if defined(ESP8266)
LoggingSerial::LoggingSerial()
    : HardwareSerial(UART0)
    , m_buffer(new circular_queue<uint8_t>(LARGE_STR))
{
}
#endif

#if defined(ESP32)
LoggingSerial::LoggingSerial()
    : HardwareSerial(0)
{
	m_buffer = xQueueCreate(LARGE_STR, sizeof(uint8_t));
}
#endif

size_t LoggingSerial::write(uint8_t c)
{
#if defined(ESP32)
	xQueueSendToBack(m_buffer, ( void * ) &c, ( TickType_t ) 1);
#endif
#if defined(ESP8266)
	m_buffer->push(c);
#endif
	return HardwareSerial::write(c);
}

size_t LoggingSerial::write(const uint8_t *buffer, size_t size)
{
#if defined(ESP32)
	for(int i = 0; i < size; i++) {
		xQueueSendToBack(m_buffer, ( void * ) &buffer[i], ( TickType_t ) 1);
	}
#endif
#if defined(ESP8266)
	m_buffer->push_n(buffer, size);
#endif
	return HardwareSerial::write(buffer, size);
}

String LoggingSerial::popLines()
{
	String r;
#if defined(ESP8266)
	while (m_buffer->available() > 0) {
		uint8_t c = m_buffer->pop();
		r += (char) c;

		if (c == '\n' && r.length() > m_buffer->available())
			break;
	}
#endif
#if defined(ESP32)
	uint8_t c;
	while (xQueueReceive(m_buffer, &(c ), (TickType_t) 1 )) {
		r += (char) c;

		if (c == '\n' && r.length() > 10)
			break;
	}
#endif
	return r;
}

#define debug_level_check(level) { if (level > cfg::debug) return; }

void debug_out(const String& text, unsigned int level) {
	debug_level_check(level); Debug.print(text);
}

void debug_out(const __FlashStringHelper* text, unsigned int level) {
	debug_level_check(level); Debug.print(text);
}

void debug_outln(const String& text, unsigned int level) {
	debug_level_check(level); Debug.println(text);
}

void debug_outln_info(const String& text) {
	debug_level_check(DEBUG_MIN_INFO); Debug.println(text);
}

void debug_outln_verbose(const String& text) {
	debug_level_check(DEBUG_MED_INFO); Debug.println(text);
}

void debug_outln_error(const __FlashStringHelper* text) {
	debug_level_check(DEBUG_ERROR); Debug.println(text);
}

void debug_outln_info(const __FlashStringHelper* text) {
	debug_level_check(DEBUG_MIN_INFO); Debug.println(text);
}

void debug_outln_verbose(const __FlashStringHelper* text) {
	debug_level_check(DEBUG_MED_INFO); Debug.println(text);
}

void debug_outln_info(const __FlashStringHelper* text, const String& option) {
	debug_level_check(DEBUG_MIN_INFO);
	Debug.print(text);
	Debug.println(option);
}

void debug_outln_info(const __FlashStringHelper* text, float value) {
	debug_outln_info(text, String(value));
}

void debug_outln_verbose(const __FlashStringHelper* text, const String& option) {
	debug_level_check(DEBUG_MED_INFO);
	Debug.print(text);
	Debug.println(option);
}

void debug_outln_info_bool(const __FlashStringHelper* text, const bool option) {
	debug_level_check(DEBUG_MIN_INFO);
	Debug.print(text);
	Debug.println(String(option));
}

#undef debug_level_check


/*****************************************************************
 * send SDS011 command (start, stop, continuous mode, version    *
 *****************************************************************/

template<typename T, std::size_t N> constexpr std::size_t array_num_elements(const T(&)[N]) {
	return N;
}

bool SDS_checksum_valid(const uint8_t (&data)[8]) {
    uint8_t checksum_is = 0;
    for (unsigned i = 0; i < 6; ++i) {
        checksum_is += data[i];
    }
    return (data[7] == 0xAB && checksum_is == data[6]);
}

void SDS_rawcmd(const uint8_t cmd_head1, const uint8_t cmd_head2, const uint8_t cmd_head3) {
	constexpr uint8_t cmd_len = 19;

	uint8_t buf[cmd_len];
	buf[0] = 0xAA;
	buf[1] = 0xB4;
	buf[2] = cmd_head1;
	buf[3] = cmd_head2;
	buf[4] = cmd_head3;
	for (unsigned i = 5; i < 15; ++i) {
		buf[i] = 0x00;
	}
	buf[15] = 0xFF;
	buf[16] = 0xFF;
	buf[17] = cmd_head1 + cmd_head2 + cmd_head3 - 2;
	buf[18] = 0xAB;
	serialSDS.write(buf, cmd_len);
}

bool SDS_cmd(PmSensorCmd cmd) {
	switch (cmd) {
	case PmSensorCmd::Start:
		SDS_rawcmd(0x06, 0x01, 0x01);
		break;
	case PmSensorCmd::Stop:
		SDS_rawcmd(0x06, 0x01, 0x00);
		break;
	case PmSensorCmd::ContinuousMode:
		// TODO: Check mode first before (re-)setting it
		SDS_rawcmd(0x08, 0x01, 0x00);
		SDS_rawcmd(0x02, 0x01, 0x00);
		break;
	}

	return cmd != PmSensorCmd::Stop;
}

/*****************************************************************
 * send Plantower PMS sensor command start, stop, cont. mode     *
 *****************************************************************/
bool PMS_cmd(PmSensorCmd cmd) {
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
	}
	serialSDS.write(buf, cmd_len);
	return cmd != PmSensorCmd::Stop;
}

/*****************************************************************
 * send Honeywell PMS sensor command start, stop, cont. mode     *
 *****************************************************************/
bool HPM_cmd(PmSensorCmd cmd) {
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
	}
	serialSDS.write(buf, cmd_len);
	return cmd != PmSensorCmd::Stop;
}


/*****************************************************************
 * send Tera Sensor Next PM sensor command start, stop, cont. mode     *
 *****************************************************************/
//REVOIR LES DEFINITIONS ICI


bool NPM_checksum_valid_4(const uint8_t (&data)[4]) {
//Works only like that...
  uint8_t checksum = data[3] + (data[0] + data[1] + data[2]);
  return (checksum == 0);
}

bool NPM_checksum_valid_16(const uint8_t (&data)[16]) {
  //Works only like that...
    uint8_t sum = data[0] + data[1] + data[2] + data[3] + data[4] + data[5] + data[6] + data[7] + data[8] + data[9] + data[10] + data[11] + data[12] + data[13] + data[14] + data[15];
    uint8_t checksum = sum % 0x100;
    return (checksum == 0);
}


void NPM_cmd(PmSensorCmd2 cmd) { 
  
  static constexpr uint8_t state_cmd[] PROGMEM = { //read the current state
    0x81,0x16,0x69
  };
  static constexpr uint8_t change_cmd[] PROGMEM = { //change the sate alternatively start/stop
    0x81,0x15,0x6A
  };
  static constexpr uint8_t concentration_cmd[] PROGMEM = { //No continous mode => repeat call
    0x81,0x11,0x6E      //Concentrations reading’s averaged over 10 seconds and updated every 1 second
  };
  
  constexpr uint8_t cmd_len = array_num_elements(change_cmd);
  uint8_t buf[cmd_len];
    
  switch (cmd) {
  case PmSensorCmd2::State:
    memcpy_P(buf, state_cmd, cmd_len);
    break;
  case PmSensorCmd2::Change:
    memcpy_P(buf, change_cmd, cmd_len);
    break;
  case PmSensorCmd2::Concentration:
    memcpy_P(buf, concentration_cmd, cmd_len);
    break;
  }
  serialSDS.write(buf, cmd_len);
}


// workaround for https://github.com/plerup/espsoftwareserial/issues/127
void yield_for_serial_buffer(size_t length) {
	unsigned long startMillis = millis();
	unsigned long yield_timeout = length * 9 * 1000 / 9600;

	while (serialSDS.available() < (int) length &&
				millis() - startMillis < yield_timeout) {
		yield();
#if defined(ESP8266)
		serialSDS.perform_work();
#endif
	}
}

const __FlashStringHelper* loggerDescription(unsigned i) {
    const __FlashStringHelper* logger = nullptr;
    switch (i) {
        case LoggerSensorCommunity:
            logger = F("Sensor.Community");
            break;
        case LoggerMadavi:
            logger = F("Madavi.de");
            break;
        case LoggerSensemap:
            logger = F("OpenSenseMap.org");
            break;
        case LoggerFSapp:
            logger = F("Feinstaub-App");
            break;
        case Loggeraircms:
            logger = F("aircms.online");
            break;
        case LoggerInflux:
            logger = F("InfluxDB");
            break;
        case LoggerCustom:
            logger = F("Custom");
            break;
    }
    return logger;
}
