/**
 * \file SensirionSht30M5TempHum.cpp
 * \author greenairalsace.vercel.app (m.alognikou, d.kalumvuati, r.nguemo and a.azzoug)
 * \brief The main purpose of this component is to implement a set of function to
 *        command the SHT30 temperature and humidity Sensor build by Sensirion company
 * \date 11 may 2023
 * \copyright all rigth reserved to greenairalsace.vercel.app
 */


/**********************************************************************************************************************/
/* INCLUSIONS                                                                                                         */
/**********************************************************************************************************************/

#include "SensirionSht30M5TempHum.h"

/**********************************************************************************************************************/
/* PRIVATE VARIABLES                                                                                                  */
/**********************************************************************************************************************/

static unsigned int sht30_data[6] = {0};

/**********************************************************************************************************************/
/* PRIVATE METHODS CODE                                                                                               */
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/* PUBLIC METHODS CODE                                                                                                */
/**********************************************************************************************************************/

extern "C" int m5_esp32_sht30_start_measurement() {
  /* start condition of I2C communication */
  m5_esp32_i2c_data_session_open(M5_SHT30_SLAVE_ADDRESS);

  /* 
    Sending mesearument command to the sensor
    Note: 0x0D 0x10 are used respectively for medium and low repeatability
  */
  m5_esp32_i2c_write(REG_START_MESEARMENT_MSB); // MSB of the command. This value is fixed
  m5_esp32_i2c_write(REG_START_MESEARMENT_LSB); // LSB of the command relative to the high repeatability (In french => Niveau de fidélité par rapport à la précision)

  /* stop condition of I2C communication */
  if (m5_esp32_i2c_data_session_close()) return 1;
  else return 0;

}

extern "C" void m5_esp32_sht30_end_measurement() {
    delay(200);
}

extern "C" void m5_esp32_sht30_reading_available_data() {
  m5_esp32_i2c_read(M5_SHT30_SLAVE_ADDRESS);

  /* saving raw data send by the slave for temperature and humidity */
  for (size_t i = 0; i < 6; i++)
  {
    sht30_data[i] = m5_esp32_i2c_get_read_data();
  }

  delay(50);
}

extern "C" bool m5_esp32_sht30_ensure_data_is_available() {
    if (m5_esp32_i2c_checkdata_byte() != 0) {
        //Serial.printf("All bytes were successfully read!\n");
        return true;
    } else {
        //Serial.printf("Error while reading data!\n");
        return false;
    }
}

extern "C" float m5_esp32_sht30_get_humidity() {
    unsigned int hum = sht30_data[3] << 8;
    hum |= sht30_data[4];
    return (float)((hum * 100) / 65535.0);
}

extern "C" float m5_esp32_sht30_get_temperature() {
    unsigned int temp = sht30_data[0] << 8;
    temp |= sht30_data[1];
    return (float)((temp * 175) / 65535.0) - 45;
}

/**********************************************************************************************************************/
/* END OF FILE                                                                                                        */
/**********************************************************************************************************************/