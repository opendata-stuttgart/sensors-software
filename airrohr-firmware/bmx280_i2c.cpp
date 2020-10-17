/*!
 * @file BMX280_i2c.h
 *
 *  Copied from Adafruits BME280 Library. SPI removed, BMP280 added
 * 
 *  Driver for the BMX280 humidity, temperature & pressure sensor
 *
 * These sensors use I2C or SPI to communicate, 2 or 4 pins are required
 * to interface.
 *
 * Designed specifically to work with the Adafruit BME280 Breakout
 * ----> http://www.adafruit.com/products/2652
 *
 *  Adafruit invests time and resources providing this open source code,
 *  please support Adafruit and open-source hardware by purchasing
 *  products from Adafruit!
 *
 * @section author Author
 *
 * Written by Kevin "KTOWN" Townsend for Adafruit Industries.
 *
 * @section license License
 *
 * BSD license, all text here must be included in any redistribution.
 * See the LICENSE file for details.
 *
 */

#include "bmx280_i2c.h"
#include "Arduino.h"
#include <Wire.h>

/*!
 *  @brief Register addresses
 */
enum {
  BMX280_REGISTER_DIG_T1 = 0x88,
  BMX280_REGISTER_DIG_T2 = 0x8A,
  BMX280_REGISTER_DIG_T3 = 0x8C,

  BMX280_REGISTER_DIG_P1 = 0x8E,
  BMX280_REGISTER_DIG_P2 = 0x90,
  BMX280_REGISTER_DIG_P3 = 0x92,
  BMX280_REGISTER_DIG_P4 = 0x94,
  BMX280_REGISTER_DIG_P5 = 0x96,
  BMX280_REGISTER_DIG_P6 = 0x98,
  BMX280_REGISTER_DIG_P7 = 0x9A,
  BMX280_REGISTER_DIG_P8 = 0x9C,
  BMX280_REGISTER_DIG_P9 = 0x9E,

  BME280_REGISTER_DIG_H1 = 0xA1,
  BME280_REGISTER_DIG_H2 = 0xE1,
  BME280_REGISTER_DIG_H3 = 0xE3,
  BME280_REGISTER_DIG_H4 = 0xE4,
  BME280_REGISTER_DIG_H5 = 0xE5,
  BME280_REGISTER_DIG_H6 = 0xE7,

  BMX280_REGISTER_CHIPID = 0xD0,
  BMX280_REGISTER_VERSION = 0xD1,
  BMX280_REGISTER_SOFTRESET = 0xE0,

  BMX280_REGISTER_CAL26 = 0xE1, // R calibration stored in 0xE1-0xF0

  BMX280_REGISTER_CONTROLHUMID = 0xF2,
  BMX280_REGISTER_STATUS = 0XF3,
  BMX280_REGISTER_CONTROL = 0xF4,
  BMX280_REGISTER_CONFIG = 0xF5,
  BMX280_REGISTER_PRESSUREDATA = 0xF7,
  BMX280_REGISTER_TEMPDATA = 0xFA,
  BMX280_REGISTER_HUMIDDATA = 0xFD,

};

/*!
 *   @brief  Initialise sensor with given parameters / settings
 *   @param addr the I2C address the device can be found on
 *   @returns true on success, false otherwise
 */
bool BMX280::begin(uint8_t addr) {
  _i2caddr = addr;
  _wire = &Wire;
  return init();
}

/*!
 *   @brief  Initialise sensor with given parameters / settings
 *   @returns true on success, false otherwise
 */
bool BMX280::init() {
  // I2C
  _wire->begin();

  // check if sensor, i.e. the chip ID is correct
  _sensorID = read8(BMX280_REGISTER_CHIPID);
  if (_sensorID != BMP280_SENSOR_ID && _sensorID != BME280_SENSOR_ID)
    return false;

  // reset the device using soft-reset
  // this makes sure the IIR is off, etc.
  write8(BMX280_REGISTER_SOFTRESET, 0xB6);

  // wait for chip to wake up.
  delay(30);

  // if chip is still reading calibration, delay
  unsigned attempts = 50;
  while (--attempts && isReadingCalibration())
    delay(10);

  readCoefficients(); // read trimming parameters, see DS 4.2.2

  setSampling(); // use defaults

  return true;
}

/*!
 *   @brief  setup sensor with given parameters / settings
 *
 *   This is simply a overload to the normal begin()-function, so SPI users
 *   don't get confused about the library requiring an address.
 *   @param mode the power mode to use for the sensor
 *   @param tempSampling the temp samping rate to use
 *   @param pressSampling the pressure sampling rate to use
 *   @param humSampling the humidity sampling rate to use
 *   @param duration the standby duration to use
 */
void BMX280::setSampling(sensor_mode mode,
                                  sensor_sampling tempSampling,
                                  sensor_sampling pressSampling,
                                  sensor_sampling humSampling,
                                  standby_duration duration) {

  _measReg.mode = mode;
  _measReg.osrs_t = tempSampling;
  _measReg.osrs_p = pressSampling;

  ctrl_hum _humReg;
  _humReg.osrs_h = humSampling;

  config _configReg;
  _configReg.t_sb = duration;

  // making sure sensor is in sleep mode before setting configuration
  // as it otherwise may be ignored
  write8(BMX280_REGISTER_CONTROL, MODE_SLEEP);
 
  if (_sensorID == BME280_SENSOR_ID) {
    // you must make sure to also set REGISTER_CONTROL after setting the
    // CONTROLHUMID register, otherwise the values won't be applied (see
    // DS 5.4.3)
    write8(BMX280_REGISTER_CONTROLHUMID, _humReg.get());
  }
  write8(BMX280_REGISTER_CONFIG, _configReg.get());
  write8(BMX280_REGISTER_CONTROL, _measReg.get());
}

/*!
 *   @brief  Writes an 8 bit value over I2C
 *   @param reg the register address to write to
 *   @param value the value to write to the register
 */
void BMX280::write8(uint8_t reg, uint8_t value) {
  _wire->beginTransmission((uint8_t)_i2caddr);
  _wire->write((uint8_t)reg);
  _wire->write((uint8_t)value);
  _wire->endTransmission();
}

/*!
 *   @brief  Reads an 8 bit value over I2C
 *   @param reg the register address to read from
 *   @returns the data byte read from the device
 */
uint8_t BMX280::read8(uint8_t reg) {
  _wire->beginTransmission((uint8_t)_i2caddr);
  _wire->write((uint8_t)reg);
  _wire->endTransmission();
  _wire->requestFrom((uint8_t)_i2caddr, (uint8_t)1);
  return _wire->read();
}

uint16_t BMX280::read16_LE(uint8_t reg) {
  uint16_t value;

  _wire->beginTransmission((uint8_t)_i2caddr);
  _wire->write((uint8_t)reg);
  _wire->endTransmission();
  _wire->requestFrom((uint8_t)_i2caddr, (uint8_t)2);
  value = _wire->read();
  value |= (uint16_t) _wire->read() << 8;
  return value;
}

/*!
 *   @brief  Reads a signed little endian 16 bit value over I2C or SPI
 *   @param reg the register address to read from
 *   @returns the 16 bit data value read from the device
 */
int16_t BMX280::readS16_LE(uint8_t reg) {
  return (int16_t)read16_LE(reg);
}

/*!
 *   @brief  Reads a 24 bit value over I2C
 *   @param reg the register address to read from
 *   @returns the 24 bit data value read from the device
 */
uint32_t BMX280::read24(uint8_t reg) {
  uint32_t value;

  _wire->beginTransmission((uint8_t)_i2caddr);
  _wire->write((uint8_t)reg);
  _wire->endTransmission();
  _wire->requestFrom((uint8_t)_i2caddr, (uint8_t)3);

  value = _wire->read();
  value <<= 8;
  value |= _wire->read();
  value <<= 8;
  value |= _wire->read();

  return value;
}

/*!
 *  @brief  Take a new measurement (only possible in forced mode)
 */
void BMX280::takeForcedMeasurement() {
  // set to forced mode, i.e. "take next measurement"
  write8(BMX280_REGISTER_CONTROL, _measReg.get());
  // wait until measurement has been completed, otherwise we would read
  // the values from the last measurement
  unsigned attempts = 15;
  while (--attempts && (read8(BMX280_REGISTER_STATUS) & 0x08))
    delay(1);
}

/*!
 *   @brief  Reads the factory-set coefficients
 */
void BMX280::readCoefficients(void) {
  dig_T1 = read16_LE(BMX280_REGISTER_DIG_T1);
  dig_T2 = readS16_LE(BMX280_REGISTER_DIG_T2);
  dig_T3 = readS16_LE(BMX280_REGISTER_DIG_T3);

  dig_P1 = read16_LE(BMX280_REGISTER_DIG_P1);
  dig_P2 = readS16_LE(BMX280_REGISTER_DIG_P2);
  dig_P3 = readS16_LE(BMX280_REGISTER_DIG_P3);
  dig_P4 = readS16_LE(BMX280_REGISTER_DIG_P4);
  dig_P5 = readS16_LE(BMX280_REGISTER_DIG_P5);
  dig_P6 = readS16_LE(BMX280_REGISTER_DIG_P6);
  dig_P7 = readS16_LE(BMX280_REGISTER_DIG_P7);
  dig_P8 = readS16_LE(BMX280_REGISTER_DIG_P8);
  dig_P9 = readS16_LE(BMX280_REGISTER_DIG_P9);

  if (_sensorID == BME280_SENSOR_ID) {
    dig_H1 = read8(BME280_REGISTER_DIG_H1);
    dig_H2 = readS16_LE(BME280_REGISTER_DIG_H2);
    dig_H3 = read8(BME280_REGISTER_DIG_H3);
    dig_H4 = (read8(BME280_REGISTER_DIG_H4) << 4) |
                           (read8(BME280_REGISTER_DIG_H4 + 1) & 0xF);
    dig_H5 = readS16_LE(BME280_REGISTER_DIG_H5) >> 4;
    dig_H6 = (int8_t)read8(BME280_REGISTER_DIG_H6);
  }
}

/*!
 *   @brief return true if chip is busy reading cal data
 *   @returns true if reading calibration, false otherwise
 */
bool BMX280::isReadingCalibration(void) {
  uint8_t const rStatus = read8(BMX280_REGISTER_STATUS);

  return (rStatus & (1 << 0)) != 0;
}

/*!
 *   @brief  Returns the temperature from the sensor
 *   @returns the temperature read from the device
 */
float BMX280::readTemperature(void) {
  int32_t var1, var2;

  int32_t adc_T = read24(BMX280_REGISTER_TEMPDATA);
  if (adc_T == 0x800000) // value in case temp measurement was disabled
    return NAN;
  adc_T >>= 4;

  var1 = ((((adc_T >> 3) - ((int32_t)dig_T1 << 1))) *
          ((int32_t)dig_T2)) >>
         11;

  var2 = (((((adc_T >> 4) - ((int32_t)dig_T1)) *
            ((adc_T >> 4) - ((int32_t)dig_T1))) >>
           12) *
          ((int32_t)dig_T3)) >>
         14;

  t_fine = var1 + var2;

  return float(t_fine) / 5120.0f;
}

/*!
 *   @brief  Returns the pressure from the sensor
 *   @returns the pressure value (in Pascal) read from the device
 */
float BMX280::readPressure(void) {

  readTemperature(); // must be done first to get t_fine

  uint32_t adc_P = read24(BMX280_REGISTER_PRESSUREDATA);
  if (adc_P == 0x800000) // value in case pressure measurement was disabled
    return NAN;

  adc_P >>= 4;

  int64_t var1, var2, p;
  var1 = ((int64_t)t_fine) - 128000;
  var2 = var1 * var1 * (int64_t)dig_P6;
  var2 = var2 + ((var1 * (int64_t)dig_P5) << 17);
  var2 = var2 + (((int64_t)dig_P4) << 35);
  var1 = ((var1 * var1 * (int64_t)dig_P3) >> 8) +
         ((var1 * (int64_t)dig_P2) << 12);
  var1 =
      (((((int64_t)1) << 47) + var1)) * ((int64_t)dig_P1) >> 33;

  // avoid exception caused by division by zero
  if (var1 == 0) {
    return 30000.0f;
  }
  p = 1048576 - adc_P;
  p = (((p << 31) - var2) * 3125) / var1;
  var1 = (((int64_t)dig_P9) * (p >> 13) * (p >> 13)) >> 25;
  var2 = (((int64_t)dig_P8) * p) >> 19;

  int32_t ps = int32_t((p + var1 + var2) >> 8) + (((int32_t)dig_P7) << 4);
  return float(ps >> 3) / 32.0f;
}

/*!
 *  @brief  Returns the humidity from the sensor
 *  @returns the humidity value read from the device
 */
float BMX280::readHumidity(void) {
  if (_sensorID != BME280_SENSOR_ID)
    return NAN;

  readTemperature(); // must be done first to get t_fine

  uint16_t raw_h = read16_LE(BMX280_REGISTER_HUMIDDATA);
  int32_t adc_H = (uint16_t) ((raw_h >> 8) | (raw_h << 8));
  if (adc_H == 0x8000) // value in case humidity measurement was disabled
    return NAN;

  int32_t v_x1_u32r;

  v_x1_u32r = (t_fine - ((int32_t)76800));

  v_x1_u32r = (((((adc_H << 14) - (((int32_t)dig_H4) << 20) -
                  (((int32_t)dig_H5) * v_x1_u32r)) +
                 ((int32_t)16384)) >>
                15) *
               (((((((v_x1_u32r * ((int32_t)dig_H6)) >> 10) *
                    (((v_x1_u32r * ((int32_t)dig_H3)) >> 11) +
                     ((int32_t)32768))) >>
                   10) +
                  ((int32_t)2097152)) *
                     ((int32_t)dig_H2) +
                 8192) >>
                14));

  v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) *
                             ((int32_t)dig_H1)) >>
                            4));

  v_x1_u32r = (v_x1_u32r < 0) ? 0 : v_x1_u32r;
  v_x1_u32r = (v_x1_u32r > 419430400) ? 419430400 : v_x1_u32r;
  return float(v_x1_u32r >> 12) / 1024.0f;
}
