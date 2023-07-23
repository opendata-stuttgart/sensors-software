/**
 * \file m5_esp32_spi_bus_lora.h
 * \author greenairalsace.vercel.app (m.alognikou, d.kalumvuati, r.nguemo and a.azzoug)
 * \brief Main header of the component that re-adapt the SPI protocol for for working with M5Lora 868 (SEMTECH sx1276)
 * \date 11 may 2023
 * \copyright all rigth reserved to greenairalsace.vercel.app
 */


/**********************************************************************************************************************/
/* MACROS                                                                                                             */
/**********************************************************************************************************************/

#ifndef M5_ESP32_SPI_BUS_LORA_H
#define M5_ESP32_SPI_BUS_LORA_H


/**********************************************************************************************************************/
/* INCLUSIONS                                                                                                         */
/**********************************************************************************************************************/

#include "base.h"
#include "SPI.h"

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
 * @brief SPI read operation
 * 
 * The first byte is the address byte. It is comprises:
 * A wnr bit, which is 1 for write access and 0 for read access.
 * Then 7 bits of address, MSB first.
 * 
 * @param reg_addr register address
 * @param chip_select_pin chip select pin number
 * @param m5_esp32_spi_settings the SPI settings which consist of :
 * 1- the maximum speed of communication (eg 1MHZ = 1E6)
 * 2- the bit which is first transmit MSB or LSB
 * 3- releative to the CPOL(clk state in resting state) & CPHA (clk fronts)
 * 
 * @retval response from m5_esp32_spi_operation method
*/
uint8_t m5_esp32_spi_read(uint8_t reg_addr, uint8_t chip_select_pin, SPISettings m5_esp32_spi_settings);

/**
 * @brief SPI write operation
 * 
 * The first byte is the address byte. It is comprises:
 * A wnr bit, which is 1 for write access and 0 for read access.
 * Then 7 bits of address, MSB first.
 * 
 * @param reg_addr register address
 * @param write_byte byte to be write
 * @param chip_select_pin chip select pin number
 * @param m5_esp32_spi_settings the SPI settings which consist of :
 * 1- the maximum speed of communication (eg 1MHZ = 1E6)
 * 2- the bit which is first transmit MSB or LSB
 * 3- releative to the CPOL(clk state in resting state) & CPHA (clk fronts)
 * 
 * @retval null (void)
*/
void m5_esp32_spi_write(uint8_t reg_addr, uint8_t write_byte, uint8_t chip_select_pin, SPISettings m5_esp32_spi_settings);

/**
 * @brief  start the SPI communication
 * 
 * @retval null (void)
*/
void m5_esp32_spi_start(void);

/**
 * @brief  stop the SPI communication
 * 
 * @retval null (void)
*/
void m5_esp32_spi_stop(void);



#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif


/**********************************************************************************************************************/
/* END OF FILE                                                                                                        */
/**********************************************************************************************************************/