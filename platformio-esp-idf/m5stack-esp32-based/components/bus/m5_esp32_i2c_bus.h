/**
 * \file m5_esp32_uart_bus.h
 * \author greenairalsace.vercel.app (m.alognikou, d.kalumvuati, r.nguemo and a.azzoug)
 * \brief Main header of the component that re-adapt the I2C protocol for for working
 *        with SHT30 sensor embedded in M5stack PM2.5 Air Kit
 * \date 11 may 2023
 * \copyright all rigth reserved to greenairalsace.vercel.app
 */


/**********************************************************************************************************************/
/* MACROS                                                                                                             */
/**********************************************************************************************************************/

#ifndef M5_ESP32_I2C_BUS_H
#define M5_ESP32_I2C_BUS_H


/**********************************************************************************************************************/
/* INCLUSIONS                                                                                                         */
/**********************************************************************************************************************/

#include "base.h"
#include "Wire.h"

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
 * @brief start I2C communication with setting config parameters
 * 
 * @retval null (void) 
*/
void m5_esp32_i2c_start();


/**
 * @brief start I2C communication
 * 
 * @retval null (void)
*/
void m5_esp32_i2c_stop(void);

/**
 * @brief check byte data on the I2C bus
 * 
 * @retval integer | return 0 = data non available | 1 = non data available
*/
int m5_esp32_i2c_checkdata_byte();

/**
 * @brief read data from register
 * 
 * @param reg_byte register to be read
 * 
 * @retval integer | return the byte read on the UART line
*/
void m5_esp32_i2c_read(uint8_t reg_byte);


/**
 * @brief write data on on register
 * 
 * @param register to be write
 * 
 * @retval size_t the size of the data to be write
*/
void m5_esp32_i2c_write(uint8_t reg_byte);

/**
 * @brief open a data exchange session on the i2c bus
 * 
 * @details this function refers to the start condition in data exchange context
 * 
 * @retval null (void)
*/
void m5_esp32_i2c_data_session_open(uint8_t slave_addr);

/**
 * @brief close a data exchange session on the i2c bus
 * 
 * @details this function refers to the stop condition in data exchange context
 * 
 * @retval null (void)
*/
bool m5_esp32_i2c_data_session_close();

/**
 * @brief get data return by a read command
 * 
 * @retval the value return by the sensor
*/
int m5_esp32_i2c_get_read_data();


#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif


/**********************************************************************************************************************/
/* END OF FILE                                                                                                        */
/**********************************************************************************************************************/