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

#include <Arduino.h>
#include <Wire.h>
#define DNMS_I2C_ADDRESS                0x55
#define DNMS_MAX_VERSION_LEN            18
#define DNMS_WORD_SIZE                  2
#define DNMS_NUM_WORDS(x)               (sizeof(x) / DNMS_WORD_SIZE)
#define STATUS_OK                       0
#define STATUS_FAIL                     (-1)
#define DNMS_COMMAND_SIZE               2
#define CRC8_POLYNOMIAL                 0x31
#define CRC8_INIT                       0xFF
#define CRC8_LEN                        1
#define DNMS_MAX_BUFFER_WORDS           32
#define DNMS_IS_ERR_STATE(err_code)     (((err_code) | 0xff) == 0x1ff)

#define DNMS_CMD_RESET                  0x0001
#define DNMS_CMD_READ_VERSION           0x0002
#define DNMS_CMD_CALCULATE_LEQ          0x0003
#define DNMS_CMD_READ_DATA_READY        0x0004
#define DNMS_CMD_READ_LEQ               0x0005


#define be16_to_cpu(s) (((uint16_t)(s) << 8) | (0xff & ((uint16_t)(s)) >> 8))
#define be32_to_cpu(s) (((uint32_t)be16_to_cpu(s) << 16) | \
                        (0xffff & (be16_to_cpu((s) >> 16))))
#define be64_to_cpu(s) (((uint64_t)be32_to_cpu(s) << 32) | \
                        (0xffffffff & ((uint64_t)be32_to_cpu((s) >> 32))))
/**
   Convert a word-array to a bytes-array, effectively reverting the
   host-endianness to big-endian
   @a:  word array to change (must be (uint16_t *) castable)
   @w:  number of word-sized elements in the array (DNMS_NUM_WORDS(a)).
*/
#define DNMS_WORDS_TO_BYTES(a, w) \
  for (uint16_t *__a = (uint16_t *)(a), __e = (w), __w = 0; __w < __e; ++__w) { \
    __a[__w] = be16_to_cpu(__a[__w]); \
  }


struct dnms_measurements {
  float leq_a;
  float leq_a_min;
  float leq_a_max;
};


/**
   dnms_reset() - reset the dnms system
   
   Return:  0 on success, an error code otherwise
*/
int16_t dnms_reset();


/**
   dnms_get_version() - retrieve the version of the dnms

   Note that version must be discarded when the return code is non-zero.

   @dnms_version: Memory where the serial number is written into as hex string (zero
            terminated). Must be at least DNMS_MAX_VERSION_LEN long.
   Return:  0 on success, an error code otherwise
*/
int16_t dnms_read_version(char *dnms_version);



int16_t dnms_calculate_leq();



int16_t dnms_read_data_ready(uint16_t *data_ready);



int16_t dnms_read_leq(struct dnms_measurements *leq);






int16_t dnms_i2c_read_cmd(uint8_t address, uint16_t cmd, uint16_t *data_words, uint16_t num_words);

//int16_t dnms_i2c_delayed_read_cmd(uint8_t address, uint16_t cmd, uint32_t delay_us, uint16_t *data_words, uint16_t num_words);

int8_t dnms_i2c_read(uint8_t address, uint8_t* data, uint16_t count);

int8_t dnms_i2c_write(uint8_t address, const uint8_t* data, uint16_t count);

//void dnms_sleep_usec(uint32_t useconds);

uint8_t dnms_common_generate_crc(uint8_t *data, uint16_t count);

int8_t dnms_common_check_crc(uint8_t *data, uint16_t count, uint8_t checksum);

uint16_t dnms_fill_cmd_send_buf(uint8_t *buf, uint16_t cmd, const uint16_t *args, uint8_t num_args);

int16_t dnms_i2c_read_bytes(uint8_t address, uint8_t *data, uint16_t num_words);

int16_t dnms_i2c_read_words(uint8_t address, uint16_t *data_words, uint16_t num_words);

int16_t dnms_i2c_write_cmd(uint8_t address, uint16_t command);

int16_t dnms_i2c_write_cmd_with_args(uint8_t address, uint16_t command, const uint16_t *data_words, uint16_t num_words);
