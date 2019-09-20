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

#include "mhz19.h"

CMHZ19Sensor::CMHZ19Sensor(Stream& serialPort) :
#if defined(MHZ19_SUPPORT_RANGE)
	ppmMaxValue(0xffff),
#endif
	m_pSerialPort(&serialPort)
{
}

#if defined(MHZ19_SUPPORT_RANGE)
/*
set the measuring range to 1000, 2000, 3000 or 5000
ppm range for sensor MH-Z19 is set to 2000 when sensor is delivered
*/
bool CMHZ19Sensor::setRange(uint16_t range)
{
  if((range % 1000) == 0
    && range >= 1000
    && range <= 5000
  )
  {
    uint8_t cmd[packetLen] = {0xFF, 0x01, 0x99, 0x00, 0x00, 0x00, (uint8_t)((range >> 8) & 0xff), (uint8_t)(range & 0xff), 0x00}; // 2nd uint8_t is the sensor number
    cmd[packetLen - 1] = calcCheckSum(cmd);
    m_pSerialPort->write(cmd, sizeof(cmd));
    // TODO: check return value if any
    // consume any response in the receive buffer
    delay(200);
    while(m_pSerialPort->available())
      m_pSerialPort->read();

    return true;
  }
  else
  {
    return false;
  }
}

uint16_t CMHZ19Sensor::getRange()
{
  return ppmMaxValue;
}
#endif

// returns 0xffff when reading fails
uint16_t CMHZ19Sensor::readCO2Sensor(){
  uint16_t ppm = 0xffff;
  uint8_t response[packetLen];
  static const uint8_t cmd[packetLen] = {0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79}; // 2nd uint8_t is the sensor number
  m_pSerialPort->write(cmd, sizeof(cmd));
  if(!synchronizeStream())
  {
#if defined(MHZ19_DEBUG_OUTPUT)
      Serial.print(F("Stream not synchronized "));
#endif
  }
  else
  {
    uint8_t recvCnt = m_pSerialPort->readBytes((char*)response, sizeof(response));

#if defined(MHZ19_DEBUG_OUTPUT)
    for(int8_t i = 0; i < min(recvCnt, packetLen); i++)
    {
      Serial.print(response[i], HEX);
      Serial.write(' ');
    }
#endif

    if(recvCnt == sizeof(response)
      && response[0] == 0xff
      && response[1] == 0x86
      && calcCheckSum(response) == response[packetLen - 1]
    )
    {
      uint16_t ppmRaw = (response[2] << 8) | response[3];
      if(response[6] == 0x3A) // this marks the startup value (first ppm value will be 128 and then the max limit). After the startup phase this status goes to 0x35 and some time later to 0x34
      {
#if defined(MHZ19_SUPPORT_RANGE)
        // there will be values of 128, <maxValue>, 5, 301 and 400 on startup => ensure to ignore the non-relevant values!
        // note: 397 was the smallest measured value, when using a range of 5000 ppm. This might me pure coincidence, but the values might also have a meaning
        if(((ppmRaw % 1000) == 0) //&& (ppmRaw != 128) && (ppmRaw != 5) && (ppmRaw != 301) && (ppmRaw != 400)
          && (ppmMaxValue != ppmRaw)
         )
        {
          ppmMaxValue = ppmRaw;
#if defined(MHZ19_DEBUG_OUTPUT)
          Serial.print(F("ppmMaxValue="));
          Serial.println(ppmMaxValue);
#endif
        }
#endif
      }
      else
      {
        ppm = ppmRaw;
      }
    }
  }
  return ppm;
}

uint8_t CMHZ19Sensor::calcCheckSum(uint8_t *packet)
{
  uint8_t checksum = 0;
  for(int8_t i = 1; i < (packetLen - 1); i++) //without the first uint8_t
  {
    checksum += packet[i];
  }
  return -checksum;
}

// synchronize with receive stream: first uint8_t must be 0xff
// actually this consumes the rest of any dangling uint8_ts from the previous packet (will mainly happen on startup)
bool CMHZ19Sensor::synchronizeStream()
{
  const uint16_t millisecondsPerChar = 1.0/(mh_z19_baudrate / 10.0) * 1000.0 + 1.1; // 9600 Baud, 8N1
  const uint16_t millisecondsPerPacket = packetLen * 1.0/(mh_z19_baudrate / 10.0) * 1000.0 + 10.1;// 9600 Baud, 8N1
  delay(millisecondsPerPacket); // allow buffer to fill up
  for(int8_t i = 0; i < (4*packetLen); i++)
  {
    int16_t c = m_pSerialPort->peek();
    if(c == 0xff)
    {
      return true; // now we are 'probably' synchronized
    }
    else if(c != -1)
    {
      m_pSerialPort->read(); // remove the trash from the input stream
    }
    if(!m_pSerialPort->available())
      delay(millisecondsPerChar); // give sender a chance to transmit some more
  }

  return false; // not synchronized
}

