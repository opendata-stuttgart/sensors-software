/**
 * \file PlantowerPmsa003M5AirKit.cpp
 * \author greenairalsace.vercel.app (m.alognikou, d.kalumvuati, r.nguemo and a.azzoug)
 * \brief The main purpose of this component is to implement a set of function to
 *        command the PMSA003M5 air quality Sensor build by PLATOWER company
 * \date 11 may 2023
 * \copyright all rigth reserved to greenairalsace.vercel.app
 */


/**********************************************************************************************************************/
/* INCLUSIONS                                                                                                         */
/**********************************************************************************************************************/

#include "PlantowerPmsa003M5AirKit.h"

/**********************************************************************************************************************/
/* PRIVATE VARIABLES                                                                                                  */
/**********************************************************************************************************************/

static uint8_t Air_val[32] = {0};
static int16_t p_val[16]   = {0};
static uint8_t i           = 0;

/**********************************************************************************************************************/
/* PRIVATE METHODS CODE                                                                                               */
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/* PUBLIC METHODS CODE                                                                                                */
/**********************************************************************************************************************/

extern "C" int m5_esp32_pmsa003_read_data() {
    while (i != 32)
    {
        if (m5_esp32_uart_checkdata_byte())
        {
           Air_val[i] = m5_esp32_uart_read();
           m5_esp32_uart_write(Air_val[i]);
           i++;
        } else {
            i = 0;
        }
    }

    if (i == 32)
    {
        i = 0;
        return 1;
    } else {
        return 0;
    }
    
}

extern "C" int m5_esp32_pmsa003_set_data() {
     for (int i = 0, j = 0; i < 32; i++) {
        if (i % 2 == 0) {
            p_val[j] = Air_val[i];
            p_val[j] = p_val[j] << 8;
        } else {
            p_val[j] |= Air_val[i];
            j++;
        }
     }

    if (p_val[2] != 0 && p_val[3] != 0 && p_val[4] != 0)
    {
        return 1;
    } else {
        return 0;
    }
    
}


extern "C" int16_t m5_esp32_pmsa003_get_PM1_data() {
    return p_val[2];
}


extern "C" int16_t m5_esp32_pmsa003_get_PM25_data() {
    return p_val[2];
}


extern "C" int16_t m5_esp32_pmsa003_get_PM10_data() {
    return p_val[4];
}

/**********************************************************************************************************************/
/* END OF FILE                                                                                                        */
/**********************************************************************************************************************/