/**
 * \file m5_esp32_uart_bus.cpp
 * \author greenairalsace.vercel.app (m.alognikou, d.kalumvuati, r.nguemo and a.azzoug)
 * \brief The main purpose of this component is to re-implement I2C protocol as esp-idf component
 *         for working with SHT30 sensor embedded in M5stack PM2.5 Air Kit
 * \date 11 may 2023
 * \copyright all rigth reserved to greenairalsace.vercel.app
 */


/**********************************************************************************************************************/
/* INCLUSIONS                                                                                                         */
/**********************************************************************************************************************/

#include "m5_esp32_i2c_bus.h"

/**********************************************************************************************************************/
/* PRIVATE METHODS CODE                                                                                               */
/**********************************************************************************************************************/

extern "C" void m5_esp32_i2c_start() {
    Wire.begin();
}


extern "C" void m5_esp32_i2c_stop(void) {
    Wire.end();
}


extern "C" int m5_esp32_i2c_checkdata_byte() {
    return Wire.available();
}


extern "C" void m5_esp32_i2c_read(uint8_t reg_byte) {
    Wire.requestFrom(reg_byte, (uint8_t)6);
}


extern "C" void m5_esp32_i2c_write(uint8_t reg_byte) {
    Wire.write(reg_byte);
}


extern "C" void m5_esp32_i2c_data_session_open(uint8_t slave_addr) {
    Wire.beginTransmission(slave_addr);
}


extern "C" bool m5_esp32_i2c_data_session_close() {
    if (Wire.endTransmission() != 0) {
        //Serial.printf("Transmission ended successfully with ACK bit sent by the slave!\n");
        return true;
    } else {
        //Serial.printf("Error while ending transmission!\n");
        return false;
    }
}

extern "C" int m5_esp32_i2c_get_read_data() {
    return Wire.read();
}

/**********************************************************************************************************************/
/* PUBLIC METHODS CODE                                                                                                */
/**********************************************************************************************************************/



/**********************************************************************************************************************/
/* END OF FILE                                                                                                        */
/**********************************************************************************************************************/