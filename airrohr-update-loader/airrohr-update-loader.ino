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

 * 8.10.2019 (Arduino Core 2.4.2):
 * DATA:    [===       ]  34.0% (used 27876 bytes from 81920 bytes)
 * PROGRAM: [===       ]  25.6% (used 267072 bytes from 1044464 bytes)

 * 28.10.2019 (Arduino Core 2.5.2):
 * DATA:    [===       ]  32.9% (used 26964 bytes from 81920 bytes)
 * PROGRAM: [===       ]  26.9% (used 280588 bytes from 1044464 bytes)

 ************************************************************************/
// increment on change
#define SOFTWARE_VERSION "LOADER-002"

/*****************************************************************
 * Includes                                                      *
 *****************************************************************/
#include <Arduino.h>
#include <FS.h>                     // must be first
#include <StreamString.h>

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
	int debug = DEBUG_MIN_INFO;
}

/*****************************************************************
 * Debug output                                                  *
 *****************************************************************/

#define debug_level_check(level) if (level > cfg::debug) return;

static void debug_outln_info(const __FlashStringHelper* text) {
	debug_level_check(DEBUG_MIN_INFO); Serial.println(text);
}

static void debug_outln_info(const __FlashStringHelper* text, const String& option) {
        debug_level_check(DEBUG_MIN_INFO);
        Serial.print(text);
        Serial.println(option);
}

static void debug_outln_error(const __FlashStringHelper* text) {
        debug_level_check(DEBUG_ERROR); Serial.println(text);
}

#undef debug_level_check

bool use_old_firmware = false;

static bool SPIFFSAutoUpdate() {
	const char firmware_filename[] = "/firmware.bin";
	const char firmware_md5_filename[] = "/firmware.bin.md5";
	const char prev_firmware_filename[] = "/firmware.old";

	String firmware = use_old_firmware ? prev_firmware_filename : firmware_filename;

	if (!SPIFFS.exists(firmware)) {
		debug_outln_info(F("No Firmware file found, looking for: "), firmware);
		return false;
	}
	File updateFile = SPIFFS.open(firmware, "r");
	if (!updateFile) {
		debug_outln_info(F("Failed to open : "), firmware);
		return false;
	}
	if (updateFile.size() >= ESP.getFreeSketchSpace()) {
		debug_outln_error(F("Cannot update, Firmware too large"));
		return false;
	}
	if (!Update.begin(updateFile.size(), U_FLASH)) {
		StreamString error;
		Update.printError(error);

		debug_outln_info(F("Update.begin returned: "), error);
		return false;
	}
	if (!use_old_firmware) {
		File md5File = SPIFFS.open(firmware_md5_filename, "r");
		if (md5File) {
			String md5sum_firmware = md5File.readString();
			debug_outln_info(F("Found firmware MD5: "), md5sum_firmware);
			Update.setMD5(md5sum_firmware.c_str());
			md5File.close();
		}
	}
	if (Update.writeStream(updateFile) != updateFile.size()) {
		StreamString error;
		Update.printError(error);

		debug_outln_info(F("Update.writeStream returned: "), error);
		return false;
	}
	updateFile.close();

	if (!Update.end()) {
		StreamString error;
		Update.printError(error);

		debug_outln_info(F("Update.end() returned: "), error);
		return false;
	}

	debug_outln_info(F("Moving Firmware image to old."));

	SPIFFS.remove(prev_firmware_filename);
	SPIFFS.remove(firmware_md5_filename);
	SPIFFS.rename(firmware_filename, prev_firmware_filename);
	SPIFFS.end();
	debug_outln_info(F("Finished successfully.. Rebooting!"));
	delay(500);
	ESP.restart();
	return true;
}

/*****************************************************************
 * The Setup                                                     *
 *****************************************************************/
void setup() {
	Serial.begin(9600);					// Output to Serial at 9600 baud
	pinMode(LED_BUILTIN, OUTPUT);

	if (!SPIFFS.begin()) {
		debug_outln_error(F("Failed to mount SPIFFS!"));
		return;
	}
}

/*****************************************************************
 * And action                                                    *
 *****************************************************************/
void loop() {

	if (!SPIFFSAutoUpdate()) {
		bool slow = false;

		debug_outln_error(F("Update Failed."));
		debug_outln_error(F("Please upload the latest firmware as '/firmware.bin' on SPIFSS to recover."));

		for (int j = 0; j < 3; ++j) {
			for (int i = 0; i < 3; ++i) {
				digitalWrite(LED_BUILTIN, HIGH);
				delay(60);
				digitalWrite(LED_BUILTIN, LOW);
				delay(slow ? 1000 : 400);
				yield();
			}
			digitalWrite(LED_BUILTIN, HIGH);
			delay(800);
			slow = !slow;
		}
	}

	use_old_firmware = !use_old_firmware;
}
