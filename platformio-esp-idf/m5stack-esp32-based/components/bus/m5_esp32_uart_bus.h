/**
 * \file m5_esp32_uart_bus.h
 * \author greenairalsace.vercel.app (m.alognikou, d.kalumvuati, r.nguemo and a.azzoug)
 * \brief Main header of the component that re-adapt the UART protocol for for working
 *        with PMSA003 sensor embedded in M5stack PM2.5 Air Kit
 * \date 11 may 2023
 * \copyright all rigth reserved to greenairalsace.vercel.app
 */


/**********************************************************************************************************************/
/* MACROS                                                                                                             */
/**********************************************************************************************************************/

#ifndef M5_ESP32_UART_BUS_H
#define M5_ESP32_UART_BUS_H


/**********************************************************************************************************************/
/* INCLUSIONS                                                                                                         */
/**********************************************************************************************************************/

#include "base.h"

/* *INDENT-OFF* */
#ifdef __cplusplus
    extern "C" {
#endif
/* *INDENT-ON* */

/**********************************************************************************************************************/
/* PRIVATE ENUM AND VARIABLE                                                                                          */
/**********************************************************************************************************************/


/**********************************************************************************************************************/
/* PRIVATE METHODS PROTOTYPES                                                                                         */
/**********************************************************************************************************************/


/**********************************************************************************************************************/
/* PUBLIC METHODS PROTOTYPES                                                                                          */
/**********************************************************************************************************************/

/**
 * @brief start UART communication with setting config parameters
 * 
 * @param u_speed the UART speed
 * @param u_config sets data, parity, and stop bits
 * @param rx_pin the UART receiver pin
 * @param tx_pin the UART transmitter pin
 * 
 * @retval null (void) 
*/
void m5_esp32_uart_start(unsigned long u_speed, uint32_t u_config, int8_t rx_pin, int8_t tx_pin);


/**
 * @brief start UART communication
 * 
 * @retval null (void)
*/
void m5_esp32_uart_stop(void);

/**
 * @brief check byte data on bus
 * 
 * @retval integer | return 0 = data non available | 1 = non data available
*/
int m5_esp32_uart_checkdata_byte();

/**
 * @brief read data from UART tx
 * 
 * @retval integer | return the byte read on the UART line
*/
int m5_esp32_uart_read();


/**
 * @brief wrtie data on UART rx
 * 
 * @retval size_t the size of the data to be write
*/
void m5_esp32_uart_write(uint8_t data_byte);


#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif


/**********************************************************************************************************************/
/* END OF FILE                                                                                                        */
/**********************************************************************************************************************/