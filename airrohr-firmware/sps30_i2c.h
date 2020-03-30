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

#include <Arduino.h>
#include <Wire.h>

#define SPS_I2C_ADDRESS 0x69
#define SPS_MAX_SERIAL_LEN 32
#define SENSIRION_WORD_SIZE         2
#define SENSIRION_NUM_WORDS(x) (sizeof(x) / SENSIRION_WORD_SIZE)
#define STATUS_OK 0
#define STATUS_FAIL (-1)
#define SENSIRION_COMMAND_SIZE      2
#define CRC8_POLYNOMIAL             0x31
#define CRC8_INIT                   0xFF
#define CRC8_LEN                    1
#define SENSIRION_MAX_BUFFER_WORDS  32
#define SPS_IS_ERR_STATE(err_code) (((err_code) | 0xff) == 0x1ff)

#define SPS_CMD_START_MEASUREMENT       0x0010
#define SPS_CMD_START_MEASUREMENT_ARG   0x0300
#define SPS_CMD_STOP_MEASUREMENT        0x0104
#define SPS_CMD_READ_MEASUREMENT        0x0300
#define SPS_CMD_GET_DATA_READY          0x0202
#define SPS_CMD_AUTOCLEAN_INTERVAL      0x8004
#define SPS_CMD_GET_SERIAL              0xd033
#define SPS_CMD_RESET                   0xd304
#define SPS_WRITE_DELAY_US              20000


#define be16_to_cpu(s) (((uint16_t)(s) << 8) | (0xff & ((uint16_t)(s)) >> 8))
#define be32_to_cpu(s) (((uint32_t)be16_to_cpu(s) << 16) | \
                        (0xffff & (be16_to_cpu((s) >> 16))))

/**
   Convert a word-array to a bytes-array, effectively reverting the
   host-endianness to big-endian
   @a:  word array to change (must be (uint16_t *) castable)
   @w:  number of word-sized elements in the array (SENSIRION_NUM_WORDS(a)).
*/
#define SENSIRION_WORDS_TO_BYTES(a, w) \
  for (uint16_t *__a = (uint16_t *)(a), __e = (w), __w = 0; __w < __e; ++__w) { \
    __a[__w] = be16_to_cpu(__a[__w]); \
  }


struct sps30_measurement {
  float mc_1p0;
  float mc_2p5;
  float mc_4p0;
  float mc_10p0;
  float nc_0p5;
  float nc_1p0;
  float nc_2p5;
  float nc_4p0;
  float nc_10p0;
  float tps;
};

int16_t sps30_reset();


/**
   sps30_probe() - check if SPS sensor is available and initialize it

   Note that Pin 4 must be pulled to ground for the sensor to operate in i2c
   mode (this driver). When left floating, the sensor operates in UART mode
   which is not compatible with this i2c driver.

   Return:  0 on success, an error code otherwise
*/
/*
int16_t sps30_probe();
*/

/**
   sps30_get_serial() - retrieve the serial number

   Note that serial must be discarded when the return code is non-zero.

   @serial: Memory where the serial number is written into as hex string (zero
            terminated). Must be at least SPS_MAX_SERIAL_LEN long.
   Return:  0 on success, an error code otherwise
*/
int16_t sps30_get_serial(char *serial);

int16_t sps30_start_measurement();

/*
int16_t sps30_stop_measurement();
*/

int16_t sps30_read_data_ready(uint16_t *data_ready);

int16_t sps30_read_measurement(struct sps30_measurement *measurement);

/*
int16_t sps30_get_fan_auto_cleaning_interval(uint32_t *interval_seconds);
*/

int16_t sps30_set_fan_auto_cleaning_interval(uint32_t interval_seconds);

/*
int16_t sps30_get_fan_auto_cleaning_interval_days(uint8_t *interval_days);

int16_t sps30_set_fan_auto_cleaning_interval_days(uint8_t interval_days);
*/

int16_t sensirion_i2c_read_cmd(uint8_t address, uint16_t cmd, uint16_t *data_words, uint16_t num_words);

/*
int16_t sensirion_i2c_delayed_read_cmd(uint8_t address, uint16_t cmd, uint32_t delay_us, uint16_t *data_words, uint16_t num_words);
*/

int8_t sensirion_i2c_read(uint8_t address, uint8_t* data, uint16_t count);

int8_t sensirion_i2c_write(uint8_t address, const uint8_t* data, uint16_t count);

/*
void sensirion_sleep_usec(uint32_t useconds);
*/

uint8_t sensirion_common_generate_crc(uint8_t *data, uint16_t count);

int8_t sensirion_common_check_crc(uint8_t *data, uint16_t count, uint8_t checksum);

uint16_t sensirion_fill_cmd_send_buf(uint8_t *buf, uint16_t cmd, const uint16_t *args, uint8_t num_args);

int16_t sensirion_i2c_read_bytes(uint8_t address, uint8_t *data, uint16_t num_words);

int16_t sensirion_i2c_read_words(uint8_t address, uint16_t *data_words, uint16_t num_words);

int16_t sensirion_i2c_write_cmd(uint8_t address, uint16_t command);

int16_t sensirion_i2c_write_cmd_with_args(uint8_t address, uint16_t command, const uint16_t *data_words, uint16_t num_words);
