/**
 * \file m5_esp32_spi_bus_lora.cpp
 * \author greenairalsace.vercel.app (m.alognikou, d.kalumvuati, r.nguemo and a.azzoug)
 * \brief The main purpose of this component is to re-implement SPI protocol as esp-idf component
 *         for working with M5Lora 868 (SEMTECH sx1276)
 * \date 11 may 2023
 * \copyright all rigth reserved to greenairalsace.vercel.app
 */


/**********************************************************************************************************************/
/* INCLUSIONS                                                                                                         */
/**********************************************************************************************************************/

#include "m5_esp32_spi_bus_lora.h"

/**********************************************************************************************************************/
/* PRIVATE METHODS CODE                                                                                               */
/**********************************************************************************************************************/

/**
 * @brief handle SPI operations with setting communication parameters (read and write from registers)
 * 
 * @param reg_addr register address
 * @param opt_byte byte to be write
 * @param chip_select_pin chip select pin number
 * @param m5_esp32_spi_settings the SPI settings which consist of :
 * 1- the maximum speed of communication (eg 1MHZ = 1E6)
 * 2- the bit which is first transmit MSB or LSB
 * 3- releative to the CPOL(clk state in resting state) & CPHA (clk fronts)
 * 
 * @retval response the outcome value from an operation successful process
*/
extern "C" uint8_t m5_esp32_spi_operation(uint8_t reg_addr, uint8_t opt_byte, uint8_t chip_select_pin, SPISettings m5_esp32_spi_settings) {
    uint8_t response;

    // lowring cs pin to start bit transmission
    digitalWrite(chip_select_pin, LOW);

    // begin SPI transaction with core settings
    SPI.beginTransaction(m5_esp32_spi_settings);

    // r|w the register
    SPI.transfer(reg_addr);

    // getting the response
    response = SPI.transfer(opt_byte);
    
    // end SPI transaction
    SPI.endTransaction();

    // releasing cs pin to stop bit transmission
    digitalWrite(chip_select_pin, HIGH);

    return response;
}

/**********************************************************************************************************************/
/* PUBLIC METHODS CODE                                                                                                */
/**********************************************************************************************************************/

extern "C" uint8_t m5_esp32_spi_read(uint8_t reg_addr, uint8_t chip_select_pin, SPISettings m5_esp32_spi_settings) {
    return m5_esp32_spi_operation(reg_addr & 0x7f, 0x00, chip_select_pin, m5_esp32_spi_settings);
}

extern "C" void m5_esp32_spi_write(uint8_t reg_addr, uint8_t write_byte, uint8_t chip_select_pin, SPISettings m5_esp32_spi_settings) {
    m5_esp32_spi_operation(reg_addr | 0x80, write_byte, chip_select_pin, m5_esp32_spi_settings);
}

extern "C" void m5_esp32_spi_start(void) {
    SPI.begin();
}

extern "C" void m5_esp32_spi_stop(void) {
    SPI.end();
}

/**********************************************************************************************************************/
/* END OF FILE                                                                                                        */
/**********************************************************************************************************************/