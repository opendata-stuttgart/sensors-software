/**
 * \file SensirionSht30M5TempHum.h
 * \author greenairalsace.vercel.app (m.alognikou, d.kalumvuati, r.nguemo and a.azzoug)
 * \brief Main header the component that command the SHT30 temperature and humidity
 *        Sensor build by Sensirion company
 * \date 11 may 2023
 * \copyright all rigth reserved to greenairalsace.vercel.app
 */


/**********************************************************************************************************************/
/* MACROS                                                                                                             */
/**********************************************************************************************************************/

#ifndef SENSIRIONSHT30M5TEMPHUM_H
#define SENSIRIONSHT30M5TEMPHUM_H

/* general definitions */
#define M5_SHT30_SLAVE_ADDRESS 0x44 // (SAO link to the GND)


/* Sensor Register definition */
#define REG_START_MESEARMENT_MSB 0x2C // MSB of the register to send measurement begin command
#define REG_START_MESEARMENT_LSB 0x10 // LSB of the register to send measurement begin command



/**********************************************************************************************************************/
/* INCLUSIONS                                                                                                         */
/**********************************************************************************************************************/

#include "base.h"
#include "m5_esp32_i2c_bus.h"

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


/**********************************************************************************************************************/
/* PUBLIC METHODS PROTOTYPES                                                                                          */
/**********************************************************************************************************************/

/**
 * @brief ask the sensor to start measuring humidity and temparature
 * 
 * @details There are two slave unique adresses for the SHT30 sensor consider
 *          a slave in our case of I2C communication :
 *          1- 0x44 is used when the ADDR which is relative to the LSB of the
 *             slave unique address is link to the ground (GND)
 *          2- 0x45 is used when !1- (1-) is the case of the M5tack (in our case: Core Controller M5GO)
 * 
 * @retval integer | 0 => the process of the command is unsuccessfull
 *                   1 => the process of the command is successfull
*/
int m5_esp32_sht30_start_measurement();

/**
 * @brief end the measurement command to start the reading process
 * 
 * @details After sending a command to the sensor a minimal waiting time of 1ms is needed
 *          before another command can be received by the sensor.
 *          Here we decided to send 200ms just for efficiency purpose
 * 
 * @retval null (void)
*/
void m5_esp32_sht30_end_measurement();

/**
 * @brief reading available data from sensor
 * 
 * @details Sending reading sensor data command. This function get the 6 bytes to be read for temperature and Humidity
 * temp MSB, temp LSB, temp CKS, hum MSB, hum LSB, hum CKS
 * 
 * @retval null (void)
*/
void m5_esp32_sht30_reading_available_data();

/**
 * @brief ensure data in interest are available
 * 
 * @retval bool (true or false)
*/
bool m5_esp32_sht30_ensure_data_is_available();

/**
 * @brief get humidity data from sensor and convert it to decimal
 * 
 * @retval float | return humditiy
*/
float m5_esp32_sht30_get_humidity();

/**
 * @brief get temparature data from sensor and convert it to decimal
 * 
 * @retval float | return temparature
*/
float m5_esp32_sht30_get_temperature();

#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif


/**********************************************************************************************************************/
/* END OF FILE                                                                                                        */
/**********************************************************************************************************************/