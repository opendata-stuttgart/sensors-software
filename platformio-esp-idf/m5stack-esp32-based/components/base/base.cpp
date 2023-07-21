/**
 * \file base.c
 * \author greenairalsace.vercel.app (m.alognikou, d.kalumvuati, r.nguemo and a.azzoug)
 * \brief The main purpose of this component is to implement some base functions of the arduino as esp-idf component
 * \date 11 may 2023
 * \copyright all rigth reserved to greenairalsace.vercel.app
 */


/**********************************************************************************************************************/
/* INCLUSIONS                                                                                                         */
/**********************************************************************************************************************/

#include "base.h"

/**********************************************************************************************************************/
/* PRIVATE METHODS CODE                                                                                               */
/**********************************************************************************************************************/

extern "C" void disableWiFi(){
    adc_power_off();
    WiFi.disconnect(true);  // Disconnect from the network
    WiFi.mode(WIFI_OFF);    // Switch WiFi off
    Serial.println("");
    Serial.println("WiFi disconnected!");
}

extern "C" void disableBluetooth(){
    // Quite unusefully, no relevable power consumption
    btStop();
    Serial.println("");
    Serial.println("Bluetooth stop!");
}


/**********************************************************************************************************************/
/* PUBLIC METHODS CODE                                                                                                */
/**********************************************************************************************************************/

extern "C" void ard_esp32_cpt_init(void) {
    initArduino();
}

extern "C" void m5_esp32_board_init(void) {
    M5BOARD.begin();
    M5BOARD.Power.begin();
}
 
extern "C" void m5_esp_32_set_modem_sleep(void) {
    disableWiFi();
    disableBluetooth();
    setCpuFrequencyMhz(40);
    SCREEN.setBrightness(20);
}

/**********************************************************************************************************************/
/* END OF FILE                                                                                                        */
/**********************************************************************************************************************/