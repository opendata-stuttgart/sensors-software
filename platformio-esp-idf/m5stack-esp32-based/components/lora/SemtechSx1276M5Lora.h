/**
 * \file SemtechSx1276M5Lora.h
 * \author greenairalsace.vercel.app (m.alognikou, d.kalumvuati, r.nguemo and a.azzoug)
 * \brief Main header of the lora protocol based on semtech sx1276 sensor for M5 series board
 * \date 11 may 2023
 * \copyright all rigth reserved to greenairalsace.vercel.app
 */


/**********************************************************************************************************************/
/* MACROS                                                                                                             */
/**********************************************************************************************************************/

#ifndef SMTECHSX1276M5LORA_H
#define SMTECHSX1276M5LORA_H

/* sensor pin definition */
/* pin definition source : http://docs.m5stack.com/en/module/lora */
#define M5_SX1276_LORA_CHIP_SELECT_PIN 5
#define M5_SX1276_LORA_RESET_PIN 26
#define M5_SX1276_LORA_INTERRUPT_REQUEST 36

/* Sensor Register definition */
/* source : SEMTECH sx1276 datasheet */
#define REG_VERSION 0x42 // semtech ID relating the silicon revision
#define REG_OP_MODE 0x01 // registers that set  lora mode
#define REG_FRF_MSB 0x06 // carrier freq MSB byte (23-16)
#define REG_FRF_MID 0x07 // carrier freq MID byte (15-8)
#define REG_FRF_LSB 0x08 // carrier freq LSB byte (7-0)

#define REG_FIFO 0x00 // FIFO register address
#define REG_IRQ_FLAGS 0x12 // register for interuption reading
#define REG_RX_NB_BYTES 0x13 // register that contain receiver bit
#define REG_FIFO_RX_CURRENT_ADDR 0x10 // start address of the FIFO

#define REG_PKT_RSSI_VALUE 0x1a
#define REG_PKT_SNR_VALUE  0x1b

#define REG_LNA 0x0c // LNA gain register (boost high freq)
#define REG_PA_CONFIG 0x09 // register that set the transmitter output power
#define REG_FIFO_ADDR_PTR 0x0d // SPI interface address pointer in FIFO data buffer
#define REG_PAYLOAD_LENGTH 0x22 // Payload length in bytes

#define REG_MODEM_CONFIG_1 0x1d // register that set the modem physical layer
#define REG_MODEM_CONFIG_3 0x26 // ACG for low data rate optimization

#define REG_FIFO_TX_BASE_ADDR 0x0e // the transmitter FIFO base address
#define REG_FIFO_RX_BASE_ADDR 0x0f // the receiver FIFO base address


/**********************************************************************************************************************/
/* INCLUSIONS                                                                                                         */
/**********************************************************************************************************************/

#include "base.h"
#include "m5_esp32_spi_bus_lora.h"
#include "M5LoRa.h"

/* *INDENT-OFF* */
#ifdef __cplusplus
    extern "C" {
#endif
/* *INDENT-ON* */

/**********************************************************************************************************************/
/* PRIVATE ENUM AND VARIABLE                                                                                          */
/**********************************************************************************************************************/


/**********************************************************************************************************************/
/* MACROS                                                                                                             */
/**********************************************************************************************************************/

#define m5_sx1276_lora LoRa

/**********************************************************************************************************************/
/* PUBLIC METHODS PROTOTYPES                                                                                          */
/**********************************************************************************************************************/

/**
 * @brief sx1276 sensor for M5 series board tun on lora protocol (initialization)
 * 
 * @param dev_freq device work frequency
 * 
 * @retval boolean (true or false)
*/
bool m5_sx1276_lora_turn_on(long dev_freq);

/**
 * @brief sx1276 sensor for M5 series board turn off lora protocol (disabling)
 * 
 * @retval null (void)
*/
void m5_sx1276_lora_turn_off();

/**
 * @brief open a data session for data transfer on sx1276 sensor for M5 series board
 * 
 * @retval boolean (true or false)
*/
bool m5_sx1276_lora_data_session_open();

/**
 * @brief close a data session recently opened for data transfer on sx1276 sensor for M5 series board
 * 
 * @retval boolean (true of false)
*/
bool m5_sx1276_lora_data_session_close();

/**
 * @brief analize data packet and collect packet size 
 * 
 * @retval packetsize <=> payload length
*/
int m5_sx1276_lora_analyze_packet_get_size();

/**
 * @brief transfer data packet via lora protocol
 * 
 * @param data_buff data to be send
 * @param data_size data size
 * 
 * @retval data_size
*/
size_t m5_sx1276_lora_data_transfer(const uint8_t* data_buff, size_t data_size);

/**
 * @brief check for received data by the transmitter
 * 
 * @retval 1 if data is found
*/
int m5_sx1276_lora_data_process();

/**
 * @brief get data received by the transmitter
 * 
 * @retval data byte
*/
int m5_sx1276_lora_get_data();

#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif


/**********************************************************************************************************************/
/* END OF FILE                                                                                                        */
/**********************************************************************************************************************/