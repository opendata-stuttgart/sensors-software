/*
   Driver for Sensirion SPS30 PM Sensor for Arduino

   it's streamlined für Arduino and not generic as the Sensirion driver

   but it's based on Sensirion Software

   changed by Helmut Bitter, 25.01.2019

*/
/*
   Copyright (c) 2018, Sensirion AG
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

 * * Redistributions of source code must retain the above copyright notice, this
     list of conditions and the following disclaimer.

 * * Redistributions in binary form must reproduce the above copyright notice,
     this list of conditions and the following disclaimer in the documentation
     and/or other materials provided with the distribution.

 * * Neither the name of Sensirion AG nor the names of its
     contributors may be used to endorse or promote products derived from
     this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
*/

#include "./sps30_i2c.h"

/*
  void sps30_reset() {
  set_pointer(SPS_CMD_RESET);
  delay(1000);
  }
*/

int16_t sps30_reset() {
  return sensirion_i2c_write_cmd(SPS_I2C_ADDRESS, SPS_CMD_RESET);
}


/*
int16_t sps30_probe() {
  char serial[SPS_MAX_SERIAL_LEN];

  // i2c init is done by Wire.begin(.,.) within setup of Arduino sketch

  return sps30_get_serial(serial);
}
*/


int16_t sps30_get_serial(char *serial) {
  uint16_t i;
  int16_t ret;
  union {
    char serial[SPS_MAX_SERIAL_LEN];
    uint16_t __enforce_alignment;
  } buffer;

  ret = sensirion_i2c_read_cmd(SPS_I2C_ADDRESS, SPS_CMD_GET_SERIAL, (uint16_t *)buffer.serial, SENSIRION_NUM_WORDS(buffer.serial));
  if (ret != STATUS_OK) {
    return ret;
  }
  SENSIRION_WORDS_TO_BYTES(buffer.serial, SENSIRION_NUM_WORDS(buffer.serial));
  for (i = 0; i < SPS_MAX_SERIAL_LEN; ++i) {
    serial[i] = buffer.serial[i];
    if (serial[i] == '\0')
      return 0;
  }
  return 0;
}

int16_t sps30_start_measurement() {
  const uint16_t arg = SPS_CMD_START_MEASUREMENT_ARG;

  return sensirion_i2c_write_cmd_with_args(SPS_I2C_ADDRESS, SPS_CMD_START_MEASUREMENT, &arg, SENSIRION_NUM_WORDS(arg));
}


/*
int16_t sps30_stop_measurement() {
  return sensirion_i2c_write_cmd(SPS_I2C_ADDRESS, SPS_CMD_STOP_MEASUREMENT);
}
*/


int16_t sps30_read_data_ready(uint16_t *data_ready) {
  return sensirion_i2c_read_cmd(SPS_I2C_ADDRESS, SPS_CMD_GET_DATA_READY, data_ready, SENSIRION_NUM_WORDS(*data_ready));
}


int16_t sps30_read_measurement(struct sps30_measurement *measurement) {
  int16_t ret;
  uint16_t idx;
  union {
    uint16_t uu[2];
    uint32_t u;
    float f;
  } val, data[10];

  ret = sensirion_i2c_read_cmd(SPS_I2C_ADDRESS, SPS_CMD_READ_MEASUREMENT, data->uu, SENSIRION_NUM_WORDS(data));
  if (ret != STATUS_OK) {
//    Serial.println("Fehler beim I²C read command");
    return ret;
  }
  SENSIRION_WORDS_TO_BYTES(data->uu, SENSIRION_NUM_WORDS(data));

  idx = 0;
  val.u = be32_to_cpu(data[idx].u);
  measurement->mc_1p0 = val.f;
  ++idx;
  val.u = be32_to_cpu(data[idx].u);
  measurement->mc_2p5 = val.f;
  ++idx;
  val.u = be32_to_cpu(data[idx].u);
  measurement->mc_4p0 = val.f;
  ++idx;
  val.u = be32_to_cpu(data[idx].u);
  measurement->mc_10p0 = val.f;
  ++idx;
  val.u = be32_to_cpu(data[idx].u);
  measurement->nc_0p5 = val.f;
  ++idx;
  val.u = be32_to_cpu(data[idx].u);
  measurement->nc_1p0 = val.f;
  ++idx;
  val.u = be32_to_cpu(data[idx].u);
  measurement->nc_2p5 = val.f;
  ++idx;
  val.u = be32_to_cpu(data[idx].u);
  measurement->nc_4p0 = val.f;
  ++idx;
  val.u = be32_to_cpu(data[idx].u);
  measurement->nc_10p0 = val.f;
  ++idx;
  val.u = be32_to_cpu(data[idx].u);
  measurement->tps = val.f;
  ++idx;

  return 0;
}

/*
int16_t sps30_get_fan_auto_cleaning_interval(uint32_t *interval_seconds) {
  union {
    uint16_t u[2];
    uint32_t uu;
  } data;
  int16_t ret = sensirion_i2c_read_cmd(SPS_I2C_ADDRESS, SPS_CMD_AUTOCLEAN_INTERVAL, data.u, SENSIRION_NUM_WORDS(data.u));
  if (ret != STATUS_OK)
    return ret;

  SENSIRION_WORDS_TO_BYTES(data.u, SENSIRION_NUM_WORDS(data.u));
  *interval_seconds = be32_to_cpu(data.uu);

  return 0;
}
*/


int16_t sps30_set_fan_auto_cleaning_interval(uint32_t interval_seconds) {
  int16_t ret;
  const uint16_t data[] = {(uint16_t)((interval_seconds & 0xFFFF0000) >> 16),
                           (uint16_t)((interval_seconds & 0x0000FFFF) >> 0)};

  ret = sensirion_i2c_write_cmd_with_args(SPS_I2C_ADDRESS,  SPS_CMD_AUTOCLEAN_INTERVAL, data, SENSIRION_NUM_WORDS(data));
//  sensirion_sleep_usec(SPS_WRITE_DELAY_US);
  delay(SPS_WRITE_DELAY_US / 1000);
  return ret;
}


/*
int16_t sps30_get_fan_auto_cleaning_interval_days(uint8_t *interval_days) {
  int16_t ret;
  uint32_t interval_seconds;

  ret = sps30_get_fan_auto_cleaning_interval(&interval_seconds);
  if (ret < 0)
    return ret;

  *interval_days = interval_seconds / (24 * 60 * 60);
  return ret;
}


int16_t sps30_set_fan_auto_cleaning_interval_days(uint8_t interval_days) {
  return sps30_set_fan_auto_cleaning_interval((uint32_t)interval_days * 24 * 60 * 60);
}
*/

/*
int16_t sensirion_i2c_delayed_read_cmd(uint8_t address, uint16_t cmd, uint32_t delay_us, uint16_t *data_words, uint16_t num_words) {
  int16_t ret;
  uint8_t buf[SENSIRION_COMMAND_SIZE];

  sensirion_fill_cmd_send_buf(buf, cmd, NULL, 0);
  ret = sensirion_i2c_write(address, buf, SENSIRION_COMMAND_SIZE);
  if (ret != STATUS_OK) {
    return ret;
  }
  if (delay_us) {
    sensirion_sleep_usec(delay_us);
  }
  return sensirion_i2c_read_words(address, data_words, num_words);
}


int16_t sensirion_i2c_read_cmd(uint8_t address, uint16_t cmd, uint16_t *data_words, uint16_t num_words) {
  return sensirion_i2c_delayed_read_cmd(address, cmd, 0, data_words, num_words);
}
*/

int16_t sensirion_i2c_read_cmd(uint8_t address, uint16_t cmd, uint16_t *data_words, uint16_t num_words) {
  int16_t ret;
  uint8_t buf[SENSIRION_COMMAND_SIZE];

  sensirion_fill_cmd_send_buf(buf, cmd, NULL, 0);
  ret = sensirion_i2c_write(address, buf, SENSIRION_COMMAND_SIZE);
  if (ret != STATUS_OK) {
    return ret;
  }
  return sensirion_i2c_read_words(address, data_words, num_words);
}


int8_t sensirion_i2c_read(uint8_t address, uint8_t* data, uint16_t count) {
  uint8_t rxByteCount = 0;

  // 2 bytes RH, 1 CRC, 2 bytes T, 1 CRC
  Wire.requestFrom(address, (uint8_t)count);

  while (Wire.available()) { // wait till all arrive
    data[rxByteCount++] = Wire.read();
    if (rxByteCount >= count) {
      break;
    }
  }
  return STATUS_OK;
}

int8_t sensirion_i2c_write(uint8_t address, const uint8_t* data, uint16_t count) {

  Wire.beginTransmission(address);
  Wire.write(data, count);
  Wire.endTransmission();
  return STATUS_OK;
}


/**
   Sleep for a given number of microseconds. The function should delay the
   execution for at least the given time, but may also sleep longer.

   @param useconds the sleep time in microseconds
*/
/*
void sensirion_sleep_usec(uint32_t useconds) {
  delay((useconds / 1000) + 1);
}
*/


uint8_t sensirion_common_generate_crc(uint8_t *data, uint16_t count) {
  uint16_t current_byte;
  uint8_t crc = CRC8_INIT;
  uint8_t crc_bit;

  /* calculates 8-Bit checksum with given polynomial */
  for (current_byte = 0; current_byte < count; ++current_byte) {
    crc ^= (data[current_byte]);
    for (crc_bit = 8; crc_bit > 0; --crc_bit) {
      if (crc & 0x80)
        crc = (crc << 1) ^ CRC8_POLYNOMIAL;
      else
        crc = (crc << 1);
    }
  }
  return crc;
}

int8_t sensirion_common_check_crc(uint8_t *data, uint16_t count, uint8_t checksum) {

  if (sensirion_common_generate_crc(data, count) != checksum)
    return STATUS_FAIL;
  return STATUS_OK;
}

uint16_t sensirion_fill_cmd_send_buf(uint8_t *buf, uint16_t cmd, const uint16_t *args, uint8_t num_args) {
  uint8_t crc;
  uint8_t i;
  uint16_t idx = 0;

  buf[idx++] = (uint8_t)((cmd & 0xFF00) >> 8);
  buf[idx++] = (uint8_t)((cmd & 0x00FF) >> 0);

  for (i = 0; i < num_args; ++i) {
    buf[idx++] = (uint8_t)((args[i] & 0xFF00) >> 8);
    buf[idx++] = (uint8_t)((args[i] & 0x00FF) >> 0);

    crc = sensirion_common_generate_crc((uint8_t *)&buf[idx - 2],
                                        SENSIRION_WORD_SIZE);
    buf[idx++] = crc;
  }
  return idx;
}

int16_t sensirion_i2c_read_bytes(uint8_t address, uint8_t *data, uint16_t num_words) {
  int16_t ret;
  uint16_t i, j;
  uint16_t size = num_words * (SENSIRION_WORD_SIZE + CRC8_LEN);
  uint16_t word_buf[SENSIRION_MAX_BUFFER_WORDS];
  uint8_t * const buf8 = (uint8_t *)word_buf;

  ret = sensirion_i2c_read(address, buf8, size);
  if (ret != STATUS_OK) {
    return ret;
  }
  /* check the CRC for each word */
  for (i = 0, j = 0; i < size; i += SENSIRION_WORD_SIZE + CRC8_LEN) {

    ret = sensirion_common_check_crc(&buf8[i], SENSIRION_WORD_SIZE, buf8[i + SENSIRION_WORD_SIZE]);
    if (ret != STATUS_OK) {
      return ret;
    }
    data[j++] = buf8[i];
    data[j++] = buf8[i + 1];
  }

  return STATUS_OK;
}

int16_t sensirion_i2c_read_words(uint8_t address, uint16_t *data_words, uint16_t num_words) {
  int16_t ret;
  uint8_t i;

  ret = sensirion_i2c_read_bytes(address, (uint8_t *)data_words, num_words);
  if (ret != STATUS_OK) {
    return ret;
  }
  for (i = 0; i < num_words; ++i) {
    data_words[i] = be16_to_cpu(data_words[i]);
  }
  return STATUS_OK;
}

int16_t sensirion_i2c_write_cmd(uint8_t address, uint16_t command) {
  uint8_t buf[SENSIRION_COMMAND_SIZE];

  sensirion_fill_cmd_send_buf(buf, command, NULL, 0);
  return sensirion_i2c_write(address, buf, SENSIRION_COMMAND_SIZE);
}

int16_t sensirion_i2c_write_cmd_with_args(uint8_t address, uint16_t command, const uint16_t *data_words, uint16_t num_words) {
  uint8_t buf[SENSIRION_MAX_BUFFER_WORDS];
  uint16_t buf_size;

  buf_size = sensirion_fill_cmd_send_buf(buf, command, data_words, num_words);
  return sensirion_i2c_write(address, buf, buf_size);
}
