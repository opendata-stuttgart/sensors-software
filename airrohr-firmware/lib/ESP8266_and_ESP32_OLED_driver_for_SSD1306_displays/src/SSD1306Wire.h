/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 by ThingPulse, Daniel Eichhorn
 * Copyright (c) 2018 by Fabrice Weinberg
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * ThingPulse invests considerable time and money to develop these open source libraries.
 * Please support us by buying our products (and not the clones) from
 * https://thingpulse.com
 *
 */

#ifndef SSD1306Wire_h
#define SSD1306Wire_h

#include "OLEDDisplay.h"
#include <Wire.h>

#ifdef ARDUINO_ARCH_AVR
#define _min	min
#define _max	max
#endif

TwoWire I2Ctwo = TwoWire(1);

class SSD1306Wire : public OLEDDisplay {
  private:
      uint8_t             _address;
      uint8_t             _sda;
      uint8_t             _scl;
      bool                _doI2cAutoInit = false;

  public:
    SSD1306Wire(uint8_t _address, uint8_t _sda, uint8_t _scl, OLEDDISPLAY_GEOMETRY g = GEOMETRY_128_64) {
      setGeometry(g);

      this->_address = _address;
      this->_sda = _sda;
      this->_scl = _scl;
    }

    bool connect() {
    #ifdef ARDUINO_ARCH_AVR 
      Wire.begin();
    #else
    #ifdef WIFI_LoRa_32_V2 || TTGO_LoRa32_V1       
      I2Ctwo.begin(this->_sda, this->_scl);
    #else
      Wire.begin(this->_sda, this->_scl);
    #endif
    #endif
      // Let's use ~700khz if ESP8266 is in 160Mhz mode
      // this will be limited to ~400khz if the ESP8266 in 80Mhz mode.
    #ifdef WIFI_LoRa_32_V2 || TTGO_LoRa32_V1
      I2Ctwo.setClock(400000);
    #else
      Wire.setClock(700000);
    #endif
      return true;
    }

    void display(void) {
      initI2cIfNeccesary();
      const int x_offset = (128 - this->width()) / 2;
      #ifdef OLEDDISPLAY_DOUBLE_BUFFER
        uint8_t minBoundY = UINT8_MAX;
        uint8_t maxBoundY = 0;

        uint8_t minBoundX = UINT8_MAX;
        uint8_t maxBoundX = 0;
        uint8_t x, y;

        // Calculate the Y bounding box of changes
        // and copy buffer[pos] to buffer_back[pos];
        for (y = 0; y < (this->height() / 8); y++) {
          for (x = 0; x < this->width(); x++) {
           uint16_t pos = x + y * this->width();
           if (buffer[pos] != buffer_back[pos]) {
             minBoundY = _min(minBoundY, y);
             maxBoundY = _max(maxBoundY, y);
             minBoundX = _min(minBoundX, x);
             maxBoundX = _max(maxBoundX, x);
           }
           buffer_back[pos] = buffer[pos];
         }
         yield();
        }

        // If the minBoundY wasn't updated
        // we can savely assume that buffer_back[pos] == buffer[pos]
        // holdes true for all values of pos

        if (minBoundY == UINT8_MAX) return;

        sendCommand(COLUMNADDR);
        sendCommand(x_offset + minBoundX);
        sendCommand(x_offset + maxBoundX);

        sendCommand(PAGEADDR);
        sendCommand(minBoundY);
        sendCommand(maxBoundY);

        byte k = 0;
        for (y = minBoundY; y <= maxBoundY; y++) {
          for (x = minBoundX; x <= maxBoundX; x++) {
            if (k == 0) {
            #ifdef WIFI_LoRa_32_V2 || TTGO_LoRa32_V1
              I2Ctwo.beginTransmission(_address);
              I2Ctwo.write(0x40);
            #else
              Wire.beginTransmission(_address);
              Wire.write(0x40);
            #endif
            }

          #ifdef WIFI_LoRa_32_V2 || TTGO_LoRa32_V1
            I2Ctwo.write(buffer[x + y * this->width()]);
          #else
            Wire.write(buffer[x + y * this->width()]);
          #endif
            k++;
            if (k == 16)  {
            #ifdef WIFI_LoRa_32_V2 || TTGO_LoRa32_V1
              I2Ctwo.endTransmission();
            #else
              Wire.endTransmission();
            #endif
              k = 0;
            }
          }
          yield();
        }

        if (k != 0) {
        #ifdef WIFI_LoRa_32_V2 || TTGO_LoRa32_V1
          I2Ctwo.endTransmission();
        #else
          Wire.endTransmission();
        #endif
        }
      #else
        sendCommand(COLUMNADDR);
        sendCommand(x_offset);
        sendCommand(x_offset + (this->width() - 1));

        sendCommand(PAGEADDR);
        sendCommand(0x0);

        if (geometry == GEOMETRY_128_64) {
          sendCommand(0x7);
        } else if (geometry == GEOMETRY_128_32) {
          sendCommand(0x3);
        }

        for (uint16_t i=0; i < displayBufferSize; i++) {
        #ifdef WIFI_LoRa_32_V2 || TTGO_LoRa32_V1
           I2Ctwo.beginTransmission(this->_address);
           I2Ctwo.write(0x40);
        #else
          Wire.beginTransmission(this->_address);
          Wire.write(0x40);
        #endif
          for (uint8_t x = 0; x < 16; x++) {
        #ifdef WIFI_LoRa_32_V2 || TTGO_LoRa32_V1
         I2Ctwo.write(buffer[i]);
        #else
          Wire.write(buffer[i]);
        #endif
            i++;
          }
          i--;
        #ifdef WIFI_LoRa_32_V2 || TTGO_LoRa32_V1
          I2Ctwo.endTransmission();
        #else
          Wire.endTransmission();
        #endif

        }
      #endif
    }

    void setI2cAutoInit(bool doI2cAutoInit) {
      _doI2cAutoInit = doI2cAutoInit;
    }

  private:
	int getBufferOffset(void) {
		return 0;
	}
    inline void sendCommand(uint8_t command) __attribute__((always_inline)){
      initI2cIfNeccesary();
    #ifdef WIFI_LoRa_32_V2 || TTGO_LoRa32_V1
      I2Ctwo.beginTransmission(_address);
      I2Ctwo.write(0x80);
      I2Ctwo.write(command);
      I2Ctwo.endTransmission();
    #else
      Wire.beginTransmission(_address);
      Wire.write(0x80);
      Wire.write(command);
      Wire.endTransmission();
    #endif

    }

    void initI2cIfNeccesary() {
      if (_doI2cAutoInit) {
    #ifdef ARDUINO_ARCH_AVR 
      Wire.begin();
    #else
    #ifdef WIFI_LoRa_32_V2 || TTGO_LoRa32_V1       
      I2Ctwo.begin(this->_sda, this->_scl);
    #else
      Wire.begin(this->_sda, this->_scl);
    #endif
    #endif
      }
    }

};

#endif
