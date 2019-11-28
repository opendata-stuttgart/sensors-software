/*!
 * @file BMX280_i2c.h
 *
 * Copied from AdaFruit BME280 1.0.10 
 * 
 * These sensors use I2C communicate, 2 or 4 pins are required
 * to interface.
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 *
 * Written by Kevin "KTOWN" Townsend for Adafruit Industries.
 *
 * BSD license, all text here must be included in any redistribution.
 * See the LICENSE file for details.
 *
 */

#ifndef __BMX280_H__
#define __BMX280_H__

#include "Arduino.h"

#include <Wire.h>

enum {
  BMP280_SENSOR_ID = 0x58,
  BME280_SENSOR_ID = 0x60
};

/**************************************************************************/
/*!
    @brief  Class that stores state and functions for interacting with BMX280 IC
*/
/**************************************************************************/
class BMX280 {
public:
  /**************************************************************************/
  /*!
      @brief  sampling rates
  */
  /**************************************************************************/
  enum sensor_sampling {
    SAMPLING_NONE = 0b000,
    SAMPLING_X1 = 0b001,
    SAMPLING_X2 = 0b010,
    SAMPLING_X4 = 0b011,
    SAMPLING_X8 = 0b100,
    SAMPLING_X16 = 0b101
  };

  /**************************************************************************/
  /*!
      @brief  power modes
  */
  /**************************************************************************/
  enum sensor_mode {
    MODE_SLEEP = 0b00,
    MODE_FORCED = 0b01,
    MODE_NORMAL = 0b11
  };

  /**************************************************************************/
  /*!
      @brief  standby duration in ms
  */
  /**************************************************************************/
  enum standby_duration {
    STANDBY_MS_0_5 = 0b000,
    STANDBY_MS_62_5 = 0b001,
    STANDBY_MS_125 = 0b010,
    STANDBY_MS_250 = 0b011,
    STANDBY_MS_500 = 0b100,
    STANDBY_MS_1000 = 0b101
  };

  bool begin(uint8_t addr);
  bool init();

  void setSampling(sensor_mode mode = MODE_NORMAL,
                   sensor_sampling tempSampling = SAMPLING_X16,
                   sensor_sampling pressSampling = SAMPLING_X16,
                   sensor_sampling humSampling = SAMPLING_X16,
                   standby_duration duration = STANDBY_MS_0_5);

  void takeForcedMeasurement();
  float readTemperature(void);
  float readPressure(void);
  float readHumidity(void);

  uint32_t sensorID(void) { return _sensorID; }

protected:
  TwoWire *_wire; //!< pointer to a TwoWire object
  void readCoefficients(void);
  bool isReadingCalibration(void);

  void write8(uint8_t reg, uint8_t value);
  uint8_t read8(uint8_t reg);
  uint32_t read24(uint8_t reg);
  uint16_t read16_LE(uint8_t reg); // little endian
  int16_t readS16_LE(uint8_t reg); // little endian

  int32_t _sensorID; //!< ID of the BME Sensor
  int32_t t_fine; //!< temperature with high resolution, stored as an attribute
                  //!< as this is used for temperature compensation reading
                  //!< humidity and pressure

  uint16_t dig_T1; ///< temperature compensation value
  int16_t dig_T2;  ///< temperature compensation value
  int16_t dig_T3;  ///< temperature compensation value

  uint16_t dig_P1; ///< pressure compensation value
  int16_t dig_P2;  ///< pressure compensation value
  int16_t dig_P3;  ///< pressure compensation value
  int16_t dig_P4;  ///< pressure compensation value
  int16_t dig_P5;  ///< pressure compensation value
  int16_t dig_P6;  ///< pressure compensation value
  int16_t dig_P7;  ///< pressure compensation value
  int16_t dig_P8;  ///< pressure compensation value
  int16_t dig_P9;  ///< pressure compensation value

  int16_t dig_H2; ///< humidity compensation value
  int16_t dig_H4; ///< humidity compensation value
  int16_t dig_H5; ///< humidity compensation value
  uint8_t dig_H1; ///< humidity compensation value
  uint8_t dig_H3; ///< humidity compensation value
  int8_t dig_H6;  ///< humidity compensation value

  uint8_t _i2caddr;  //!< I2C addr for the TwoWire interface
  /**************************************************************************/
  /*!
      @brief  config register
  */
  /**************************************************************************/
  struct config {
    // inactive duration (standby time) in normal mode
    // 000 = 0.5 ms
    // 001 = 62.5 ms
    // 010 = 125 ms
    // 011 = 250 ms
    // 100 = 500 ms
    // 101 = 1000 ms
    // 110 = 10 ms
    // 111 = 20 ms
    uint8_t t_sb : 3; ///< inactive duration (standby time) in normal mode

    // unused - don't set
    uint8_t none : 1;     ///< unused - don't set
    uint8_t spi3w_en : 1; ///< unused - don't set

    uint8_t _unused : 3;

    /// @return combined config register
    uint8_t get() { return (t_sb << 5); }
  };

  /**************************************************************************/
  /*!
      @brief  ctrl_meas register
  */
  /**************************************************************************/
  struct ctrl_meas {
    // temperature oversampling
    // 000 = skipped
    // 001 = x1
    // 010 = x2
    // 011 = x4
    // 100 = x8
    // 101 and above = x16
    uint8_t osrs_t : 3; ///< temperature oversampling

    // pressure oversampling
    // 000 = skipped
    // 001 = x1
    // 010 = x2
    // 011 = x4
    // 100 = x8
    // 101 and above = x16
    uint8_t osrs_p : 3; ///< pressure oversampling

    // device mode
    // 00       = sleep
    // 01 or 10 = forced
    // 11       = normal
    uint8_t mode : 2; ///< device mode

    /// @return combined ctrl register
    uint8_t get() { return (osrs_t << 5) | (osrs_p << 2) | mode; }
  };
  ctrl_meas _measReg; //!< measurement register object

  /**************************************************************************/
  /*!
      @brief  ctrl_hum register
  */
  /**************************************************************************/
  struct ctrl_hum {
    /// unused - don't set
    uint8_t none : 5;

    // pressure oversampling
    // 000 = skipped
    // 001 = x1
    // 010 = x2
    // 011 = x4
    // 100 = x8
    // 101 and above = x16
    uint8_t osrs_h : 3; ///< pressure oversampling

    /// @return combined ctrl hum register
    uint8_t get() { return (osrs_h); }
  };
};

#endif
