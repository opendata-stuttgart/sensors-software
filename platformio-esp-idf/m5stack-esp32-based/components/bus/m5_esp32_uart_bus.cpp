/**
 * \file m5_esp32_uart_bus.cpp
 * \author greenairalsace.vercel.app (m.alognikou, d.kalumvuati, r.nguemo and a.azzoug)
 * \brief The main purpose of this component is to re-implement UART protocol as esp-idf component
 *         for working with PMSA003 sensor embedded in M5stack PM2.5 Air Kit
 * \date 11 may 2023
 * \copyright all rigth reserved to greenairalsace.vercel.app
 */


/**********************************************************************************************************************/
/* INCLUSIONS                                                                                                         */
/**********************************************************************************************************************/

#include "m5_esp32_uart_bus.h"

/**********************************************************************************************************************/
/* PRIVATE METHODS CODE                                                                                               */
/**********************************************************************************************************************/


extern "C" void m5_esp32_uart_start(unsigned long u_speed, uint32_t u_config, int8_t rx_pin, int8_t tx_pin) {
    Serial1.begin(u_speed);
    Serial2.begin(u_speed, u_config, rx_pin, tx_pin);
    
    // to be clarified
    pinMode(13, OUTPUT);
    digitalWrite(13, 1);
}


extern "C" void m5_esp32_uart_stop(void) {
    Serial1.end();
    Serial2.end();
    digitalWrite(13, 0);
}


extern "C" int m5_esp32_uart_checkdata_byte() {
    return Serial2.available();
}


extern "C" int m5_esp32_uart_read() {
    return Serial2.read();
}


extern "C" void m5_esp32_uart_write(uint8_t data_byte) {
    Serial1.write(data_byte);
}

/**********************************************************************************************************************/
/* PUBLIC METHODS CODE                                                                                                */
/**********************************************************************************************************************/



/**********************************************************************************************************************/
/* END OF FILE                                                                                                        */
/**********************************************************************************************************************/