/**
 * \file PlantowerPmsa003M5AirKit.h
 * \author greenairalsace.vercel.app (m.alognikou, d.kalumvuati, r.nguemo and a.azzoug)
 * \brief Main header the component that command the PMSA003M5 air quality
 *        Sensor build by PLANTOWER company
 * \date 11 may 2023
 * \copyright all rigth reserved to greenairalsace.vercel.app
 */


/**********************************************************************************************************************/
/* MACROS                                                                                                             */
/**********************************************************************************************************************/

#ifndef PLANTOWERPMSA003M5AIRKIT_H
#define PLANTOWERPMSA003M5AIRKIT_H

/**********************************************************************************************************************/
/* INCLUSIONS                                                                                                         */
/**********************************************************************************************************************/

#include "base.h"
#include "m5_esp32_uart_bus.h"

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
 * @brief read data from uart line
 * 
 * @retval null (void)
*/
int m5_esp32_pmsa003_read_data();

/**
 * @brief read data from uart line
 * 
 * @retval data int[] | PM1, PM2.5 and PM10
*/
int m5_esp32_pmsa003_set_data();

/**
 * @brief get PM1 data
 * 
 * @retval data int | PM1
*/
int16_t m5_esp32_pmsa003_get_PM1_data();

/**
 * @brief get PM1 data
 * 
 * @retval data int | PM25
*/
int16_t m5_esp32_pmsa003_get_PM25_data();

/**
 * @brief get PM1 data
 * 
 * @retval data int | PM10
*/
int16_t m5_esp32_pmsa003_get_PM10_data();

#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif


/**********************************************************************************************************************/
/* END OF FILE                                                                                                        */
/**********************************************************************************************************************/