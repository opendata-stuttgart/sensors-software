/************************************************************************
 *                                                                      *
 *  Driver for DNMS - Digital Noise Measurement Sensor                  *
 *                                                                      *
 *  This source code is for the board NodeMCU based on ESP8266          *
 *                                                                      *
 *                                                                      *
 ************************************************************************
 *                                                                      *
 *    DNMS - Digital Noise Measurement Sensor                           *
 *    Copyright (C) 2019  Helmut Bitter                                 *
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

#include "./dnms_i2c.h"


int16_t dnms_reset() {
  return dnms_i2c_write_cmd(DNMS_I2C_ADDRESS, DNMS_CMD_RESET);
}


int16_t dnms_read_version(char *dnms_version) {
  uint16_t i;
  int16_t ret;
  union {
    char dnms_version[DNMS_MAX_VERSION_LEN];
    uint16_t __enforce_alignment;
  } buffer;

  ret = dnms_i2c_read_cmd(DNMS_I2C_ADDRESS, DNMS_CMD_READ_VERSION, (uint16_t *)buffer.dnms_version, DNMS_NUM_WORDS(buffer.dnms_version));
  if (ret != STATUS_OK) {
    return ret;
  }
  DNMS_WORDS_TO_BYTES(buffer.dnms_version, DNMS_NUM_WORDS(buffer.dnms_version));
  for (i = 0; i < DNMS_MAX_VERSION_LEN; ++i) {
    dnms_version[i] = buffer.dnms_version[i];
  }
  if ((dnms_version[0] == 'D') && (dnms_version[1] == 'N') && (dnms_version[2] == 'M') && (dnms_version[3] == 'S')) {
    return 0;
  }
  return 1;  // error 
}


int16_t dnms_calculate_leq() {

  return dnms_i2c_write_cmd(DNMS_I2C_ADDRESS, DNMS_CMD_CALCULATE_LEQ);
}


int16_t dnms_read_data_ready(uint16_t *data_ready) {
  return dnms_i2c_read_cmd(DNMS_I2C_ADDRESS, DNMS_CMD_READ_DATA_READY, data_ready, DNMS_NUM_WORDS(*data_ready));
}


int16_t dnms_read_leq(struct dnms_measurements *leq) {
  int16_t ret;
  uint16_t idx;
  union {
    uint16_t uu[2];
    uint32_t u;
    float f;
  } val, data[3];

  ret = dnms_i2c_read_cmd(DNMS_I2C_ADDRESS, DNMS_CMD_READ_LEQ, data->uu, DNMS_NUM_WORDS(data));
  if (ret != STATUS_OK)
    return ret;

  DNMS_WORDS_TO_BYTES(data->uu, DNMS_NUM_WORDS(data));

  idx = 0;
  val.u = be32_to_cpu(data[idx].u);
  leq->leq_a = val.f;
  ++idx;
  val.u = be32_to_cpu(data[idx].u);
  leq->leq_a_min = val.f;
  ++idx;
  val.u = be32_to_cpu(data[idx].u);
  leq->leq_a_max = val.f;

  return 0;
}


int16_t dnms_i2c_read_cmd(uint8_t address, uint16_t cmd, uint16_t *data_words, uint16_t num_words) {
  int16_t ret;
  uint8_t buf[DNMS_COMMAND_SIZE];

  dnms_fill_cmd_send_buf(buf, cmd, NULL, 0);
  ret = dnms_i2c_write(address, buf, DNMS_COMMAND_SIZE);
  if (ret != STATUS_OK) {
    return ret;
  }
  return dnms_i2c_read_words(address, data_words, num_words);
}


int8_t dnms_i2c_read(uint8_t address, uint8_t* data, uint16_t count) {
  uint8_t rxByteCount = 0;

  // 2 bytes RH, 1 CRC, 2 bytes T, 1 CRC
  Wire.requestFrom(address, (uint8_t)count);
  while (Wire.available()) { // wait till all arrive
    data[rxByteCount++] = Wire.read();
    if (rxByteCount >= count) {
      break;
    }
  }
  return 0;
}

int8_t dnms_i2c_write(uint8_t address, const uint8_t* data, uint16_t count) {
  Wire.beginTransmission(address);
  Wire.write(data, count);
  Wire.endTransmission();
  return 0;
}


uint8_t dnms_common_generate_crc(uint8_t *data, uint16_t count) {
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


int8_t dnms_common_check_crc(uint8_t *data, uint16_t count, uint8_t checksum) {
  uint8_t crc;
  crc = dnms_common_generate_crc(data, count);
  if (crc != checksum) {
    return STATUS_FAIL;
   }
  return STATUS_OK;
}


uint16_t dnms_fill_cmd_send_buf(uint8_t *buf, uint16_t cmd, const uint16_t *args, uint8_t num_args) {
  uint8_t crc;
  uint8_t i;
  uint16_t idx = 0;

  buf[idx++] = (uint8_t)((cmd & 0xFF00) >> 8);
  buf[idx++] = (uint8_t)((cmd & 0x00FF) >> 0);

  for (i = 0; i < num_args; ++i) {
    buf[idx++] = (uint8_t)((args[i] & 0xFF00) >> 8);
    buf[idx++] = (uint8_t)((args[i] & 0x00FF) >> 0);

    crc = dnms_common_generate_crc((uint8_t *)&buf[idx - 2], DNMS_WORD_SIZE);
    buf[idx++] = crc;
  }
  return idx;
}


int16_t dnms_i2c_read_bytes(uint8_t address, uint8_t *data, uint16_t num_words) {
  int16_t ret;
  uint16_t i, j;
  uint16_t size = num_words * (DNMS_WORD_SIZE + CRC8_LEN);
  uint16_t word_buf[DNMS_MAX_BUFFER_WORDS];
  uint8_t * const buf8 = (uint8_t *)word_buf;
  
  ret = dnms_i2c_read(address, buf8, size);
  if (ret != STATUS_OK) {
    return ret;
  }
  /* check the CRC for each word */
  for (i = 0, j = 0; i < size; i += DNMS_WORD_SIZE + CRC8_LEN) {
    ret = dnms_common_check_crc(&buf8[i], DNMS_WORD_SIZE, buf8[i + DNMS_WORD_SIZE]);
    if (ret != STATUS_OK) {
      return ret;
    }
    data[j++] = buf8[i];
    data[j++] = buf8[i + 1];
  }

  return STATUS_OK;
}


int16_t dnms_i2c_read_words(uint8_t address, uint16_t *data_words, uint16_t num_words) {
  int16_t ret;
  uint8_t i;

  ret = dnms_i2c_read_bytes(address, (uint8_t *)data_words, num_words);
  if (ret != STATUS_OK) {
    return ret;
  }
  for (i = 0; i < num_words; ++i) {
    data_words[i] = be16_to_cpu(data_words[i]);
  }
  return STATUS_OK;
}


int16_t dnms_i2c_write_cmd(uint8_t address, uint16_t command) {
  uint8_t buf[DNMS_COMMAND_SIZE];

  dnms_fill_cmd_send_buf(buf, command, NULL, 0);
  return dnms_i2c_write(address, buf, DNMS_COMMAND_SIZE);
}


int16_t dnms_i2c_write_cmd_with_args(uint8_t address, uint16_t command, const uint16_t *data_words, uint16_t num_words) {
  uint8_t buf[DNMS_MAX_BUFFER_WORDS];
  uint16_t buf_size;

  buf_size = dnms_fill_cmd_send_buf(buf, command, data_words, num_words);
  return dnms_i2c_write(address, buf, buf_size);
}
