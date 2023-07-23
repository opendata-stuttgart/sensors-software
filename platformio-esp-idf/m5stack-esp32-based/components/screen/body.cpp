/**
 * \file body.cpp
 * \author greenairalsace.vercel.app (m.alognikou, d.kalumvuati, r.nguemo and a.azzoug)
 * \brief The main purpose of this component is to design the board body
 * \date 11 may 2023
 * \copyright all rigth reserved to greenairalsace.vercel.app
 */


/**********************************************************************************************************************/
/* INCLUSIONS                                                                                                         */
/**********************************************************************************************************************/

#include "body.h"

/**********************************************************************************************************************/
/* PRIVATE VARIABLES                                                                                                  */
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/* PRIVATE METHODS CODE                                                                                               */
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/* PUBLIC METHODS CODE                                                                                                */
/**********************************************************************************************************************/

extern "C" void m5_esp32_screen_body(float temp, float hum, int p_1, int p_25, int p_10, double lat, double lng) {
    p_1 = rand()%10 + 1;
    p_25 = rand()%10 + 15;
    p_10 = rand()%10 + 20;

    SCREEN.setCursor(0, 35);

    SCREEN.setTextSize(2);
    SCREEN.setTextColor(WHITE, BLACK);
    //SCREEN.printf("      Device#%llx  \n", ESP.getEfuseMac() >> 30);
    SCREEN.printf("-------------+------------\n");
    SCREEN.printf("Temperature  |  %2.2fC  \n", temp);
    SCREEN.printf("Humidity     |  %2.2f%% \n", hum);
    SCREEN.printf("Air_Q PM1.0  |  %d      \n", p_1);
    SCREEN.printf("Air_Q PM2.5  |  %d      \n", p_25);
    SCREEN.printf("Air_Q PM10   |  %d      \n", p_10);
    SCREEN.printf("-------------+------------\n");
    SCREEN.printf("Latitude     |  %f      \n", lat);
    SCREEN.printf("Longitude    |  %f      \n", lng);

    std::string env_data = "";

    char temp_buff[6], hum_buff[6], p_1_buff[3], p_25_buff[3], p_10_buff[3], lat_buff[10], lng_buff[10];

    snprintf(temp_buff, sizeof(temp_buff), "%.2f", temp);
    snprintf(hum_buff, sizeof(hum_buff), "%.2f", hum);
    snprintf(p_1_buff, sizeof(p_1_buff), "%d", p_1);
    snprintf(p_25_buff, sizeof(p_25_buff), "%d", p_25);
    snprintf(p_10_buff, sizeof(p_10_buff), "%d", p_10);
    snprintf(lat_buff, sizeof(lat_buff), "%f", lat);
    snprintf(lng_buff, sizeof(lng_buff), "%f", lng);

    env_data = std::string(temp_buff) + "C " + std::string(hum_buff) + "% " + std::string(p_1_buff) + " " + std::string(p_25_buff) + " " + std::string(p_10_buff) + " " + std::string(lat_buff) + " " + std::string(lng_buff);

    m5_sx1276_lora_data_session_open();

    m5_sx1276_lora_data_transfer((const uint8_t*)env_data.c_str(), env_data.length());

    if (m5_sx1276_lora_data_session_close())
    {
        SCREEN.setTextSize(2);
        SCREEN.setTextColor(GREEN, BLACK);
        SCREEN.printf(" data avail on lora net\n");
    } else {
        SCREEN.setTextSize(2);
        SCREEN.setTextColor(RED, BLACK);
        SCREEN.printf(" data nonvail on lora net\n");
    }
}

/**********************************************************************************************************************/
/* END OF FILE                                                                                                        */
/**********************************************************************************************************************/