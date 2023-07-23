
#include "base.h"

#include "SensirionSht30M5TempHum.h"
#include "SemtechSx1276M5Lora.h"
#include "PlantowerPmsa003M5AirKit.h"
/**
 * \file main.cpp
 * \author greenairalsace.vercel.app (m.alognikou, d.kalumvuati, r.nguemo, r.mers and a.azzoug)
 * \brief Main component that manage tasks
 * \date 11 may 2023
 * \copyright all rigth reserved to greenairalsace.vercel.app
 */

/**********************************************************************************************************************/
/* INCLUSIONS                                                                                                         */
/**********************************************************************************************************************/

#include "header.h"
#include "body.h"
#include "footer.h"

TaskHandle_t mainTaskHandle = NULL;
// WDT (Watchdog ) is timer that is used to detect and recover from MCU malfunctions
bool mainTaskWDTEnabled;

/* temperature & humidity data */
float temp = 0.0, hum = 0.0;
/* Air quality data */
uint16_t p_1 = 0, p_25 = 0, p_10 = 0;
double lat = 00.00000, lng = 00.00000;

const char* host = "esp32";


// A sample NMEA stream.
const char *gpsStream =
  "$GPRMC,045103.000,A,3014.1984,N,09749.2872,W,0.67,161.46,030913,,,A*7C\r\n"
  "$GPGGA,045104.000,3014.1985,N,09749.2873,W,1,09,1.2,211.6,M,-22.5,M,,0000*62\r\n"
  "$GPRMC,045200.000,A,3014.3820,N,09748.9514,W,36.88,65.02,030913,,,A*77\r\n"
  "$GPGGA,045201.000,3014.3864,N,09748.9411,W,1,10,1.2,200.8,M,-22.5,M,,0000*6C\r\n"
  "$GPRMC,045251.000,A,3014.4275,N,09749.0626,W,0.51,217.94,030913,,,A*7D\r\n"
  "$GPGGA,045252.000,3014.4273,N,09749.0628,W,1,09,1.3,206.9,M,-22.5,M,,0000*6F\r\n";

// The TinyGPSPlus object
TinyGPSPlus gps;


/**********************************************************************************************************************/
/* PRIVATE FUNCTION CODE                                                                                              */
/**********************************************************************************************************************/


void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    lat = gps.location.lat();
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
    lng = gps.location.lng();
  }
  else
  {
    Serial.print(F("INVALID"));
  }
}

static void set_temp_hum_data() {
    m5_esp32_sht30_start_measurement();
    m5_esp32_sht30_end_measurement();
    m5_esp32_sht30_reading_available_data();
    m5_esp32_sht30_ensure_data_is_available();

    temp = m5_esp32_sht30_get_temperature();
    hum = m5_esp32_sht30_get_humidity();
}

static void set_air_quality_val() {
    /*if (m5_esp32_pmsa003_read_data() == 1)
    {
        if (m5_esp32_pmsa003_set_data() == 1)
        {
            p_1 = (uint16_t)(m5_esp32_pmsa003_get_PM1_data() >> 10) + 3;
            p_25 = (uint16_t)(m5_esp32_pmsa003_get_PM25_data() >> 10) + 4;
            p_10 = (uint16_t)(m5_esp32_pmsa003_get_PM10_data() >> 10) + 2;
        }
    }*/
}

static void configTask() {
    m5_esp32_board_init();

    /* Initialize UART peripheral for air quality sensor */
    //m5_esp32_uart_start(9600, SERIAL_8N1, 16, 17);
   
    /* Initialize I2C peripheral for temperature and humidity sensor */
    m5_esp32_i2c_stop();
    m5_esp32_i2c_start();

    /* Lora intialization */
    if (!m5_sx1276_lora_turn_on(866E6)) {
        Serial.println("Starting LoRa failed!");
        while (1)
            ;
    }

    Serial.println(F("BasicExample.ino"));
    Serial.println(F("Basic demonstration of TinyGPSPlus (no device needed)"));
    Serial.print(F("Testing TinyGPSPlus library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
    Serial.println(F("by Mikal Hart"));
    Serial.println();

    while (*gpsStream)
        if (gps.encode(*gpsStream++))
        displayInfo();

    Serial.println();
    Serial.println(F("Done."));

    m5_esp_32_set_modem_sleep();
}

static void loopTask() {
    // setting temp and hum 
    set_temp_hum_data();

    // setting air quality data
    set_air_quality_val();

    delay(5000);

    // updating screen
    M5BOARD.update();

    m5_esp32_screen_header();

    m5_esp32_screen_body(temp, hum, p_1, p_25, p_10, lat, lng);

    m5_esp32_screen_footer();
}

void mainTask(void *pvParameters)
{
    configTask();

    for(;;) {

        // if WDT is enable reset it before strating the loop task
        if(mainTaskWDTEnabled){
            esp_task_wdt_reset();
        }
        
        loopTask();
    }
}

extern "C" void app_main()
{
    mainTaskWDTEnabled = true;

    ard_esp32_cpt_init();

    xTaskCreateUniversal(mainTask, "mainTask", 8192, NULL, 1, &mainTaskHandle, CONFIG_ARDUINO_RUNNING_CORE);
}

/**********************************************************************************************************************/
/* END OF FILE                                                                                                        */
/**********************************************************************************************************************/