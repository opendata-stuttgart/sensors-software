 /***********************************************************************
 *    MH-Z19 CO2 sensor driver                                          *
 *    Copyright (C) 2017-2019 Michael Dreher <michael (at) 5dot1.de>    *
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
 ***********************************************************************/

#include <Arduino.h>

class CMHZ19Sensor
{
public:
	CMHZ19Sensor(Stream& serialPort);

	// returns 0xffff when reading fails
	uint16_t readCO2Sensor();
	static const uint16_t mh_z19_baudrate = 9600;

	/*  set the measuring range to 1000, 2000, 3000 or 5000
	    ppm range for sensor MH-Z19 is set to 2000 when sensor is delivered
	    value is stored in EEPROM, so don't call this too often otherwise
	    EEPROM will be damaged
	*/
	bool setRange(uint16_t range);

	// this only contains a value of the sensor has been done a reset cycle
	// otherwise it will return 0xffff
	uint16_t getRange();

/* this can't be implemented, because of Arduino issue 570, see here: https://github.com/arduino/Arduino/issues/570
	void Setup() {
		serialPort.begin(mh_z19_baudrate);
	}
*/

private:
	static const uint8_t packetLen = 9;
	Stream* m_pSerialPort;
	uint16_t ppmMaxValue; // 1000, 2000, 3000 or 5000

	CMHZ19Sensor(); // default constructor not allowed to be used
	static uint8_t calcCheckSum(uint8_t *packet);

	// synchronize with receive stream: first uint8_t must be 0xff
	// actually this consumes the rest of any dangling uint8_ts from the previous packet (will mainly happen on startup)
	bool synchronizeStream();
};

