/*
 *	airRohr firmware
 *	Copyright (C) 2016-2018  Code for Stuttgart a.o.
 * 
 *  Translation template
 * 
 *	Texts should be as short as possible
 *	We only have 512 kB for the entire firmware
 */

const char INTL_LANG[] = "";
const char INTL_PM_SENSOR[] PROGMEM = "";
const char INTL_CONFIGURATION[] PROGMEM = "";
const char INTL_WIFI_SETTINGS[] PROGMEM = "";
const char INTL_WIFI_NETWORKS[] PROGMEM = "";
const char INTL_LANGUAGE[] PROGMEM = "";
const char INTL_NO_NETWORKS[] PROGMEM =  "";
const char INTL_NETWORKS_FOUND[] PROGMEM = "";
const char INTL_AB_HIER_NUR_ANDERN[] PROGMEM = "";
const char INTL_SAVE[] PROGMEM = "";
const char INTL_SENSORS[] PROGMEM = "";
const char INTL_SDS011[] PROGMEM = "SDS011 ({pm})";
const char INTL_PMS[] PROGMEM = "Plantower PMS(1,3,5,6,7)003 ({pm})";
const char INTL_HPM[] PROGMEM = "Honeywell PMS";
const char INTL_SPS30[] PROGMEM = "Sensirion SPS30 ({pm})";
const char INTL_PPD42NS[] PROGMEM = "PPD42NS";
const char INTL_DHT22[] PROGMEM = "DHT22 ({t}, {h})";
const char INTL_HTU21D[] PROGMEM = "HTU21D ({t}, {h})";
const char INTL_BMP180[] PROGMEM = "BMP180 ({t}, {p})";
const char INTL_BMX280[] PROGMEM = "BMP/BME280 ({t}, {h}, {p})";
const char INTL_DS18B20[] PROGMEM = "DS18B20 ({t})";
const char INTL_DNMS[] PROGMEM = "DNMS ({l_a})";
const char INTL_DNMS_CORRECTION[] PROGMEM ="";
const char INTL_NEO6M[] PROGMEM = "GPS (NEO 6M)";
const char INTL_BASICAUTH[] PROGMEM = "";
const char INTL_FS_WIFI[] PROGMEM = "";
const char INTL_FS_WIFI_DESCRIPTION[] PROGMEM = "";
const char INTL_FS_WIFI_NAME[] PROGMEM = "";
const char INTL_MORE_SETTINGS[] PROGMEM ="";
const char INTL_AUTO_UPDATE[] PROGMEM = "";
const char INTL_USE_BETA[] PROGMEM = "";
const char INTL_DISPLAY[] PROGMEM = "OLED SSD1306";
const char INTL_SH1106[] PROGMEM = "OLED SH1106";
const char INTL_FLIP_DISPLAY[] PROGMEM = "OLED Display Flip";
const char INTL_LCD1602_27[] PROGMEM = "LCD 1602 (I2C: 0x27)";
const char INTL_LCD1602_3F[] PROGMEM = "LCD 1602 (I2C: 0x3F)";
const char INTL_LCD2004_27[] PROGMEM = "LCD 2004 (I2C: 0x27)";
const char INTL_DISPLAY_WIFI_INFO[] PROGMEM = "";
const char INTL_DISPLAY_DEVICE_INFO[] PROGMEM = "";
const char INTL_DEBUG_LEVEL[] PROGMEM = "";
const char INTL_MEASUREMENT_INTERVAL[] PROGMEM = "";
const char INTL_DURATION_ROUTER_MODE[] PROGMEM = "";
const char INTL_MORE_APIS[] PROGMEM = "";
const char INTL_SEND_TO_OWN_API[] PROGMEM = "";
const char INTL_SERVER[] PROGMEM = ""; 
const char INTL_PATH[] PROGMEM = ""; 
const char INTL_PORT[] PROGMEM = ""; 
const char INTL_USER[] PROGMEM = ""; 
const char INTL_PASSWORD[] PROGMEM = ""; 
const char INTL_SEND_TO[] PROGMEM = ""; 
const char INTL_READ_FROM[] PROGMEM = "";
const char INTL_SENSOR_IS_REBOOTING[] PROGMEM = "";
const char INTL_RESTART_DEVICE[] PROGMEM = "";
const char INTL_DELETE_CONFIG[] PROGMEM = "";
const char INTL_RESTART_SENSOR[] PROGMEM = "";
const char INTL_HOME[] PROGMEM = "";
const char INTL_BACK_TO_HOME[] PROGMEM = "";
const char INTL_CURRENT_DATA[] PROGMEM = "";
const char INTL_ACTIVE_SENSORS_MAP[] PROGMEM = "";
const char INTL_CONFIGURATION_DELETE[] PROGMEM = "";
const char INTL_CONFIGURATION_REALLY_DELETE[] PROGMEM = "";
const char INTL_DELETE[] PROGMEM = "";
const char INTL_CANCEL[] PROGMEM = "";
const char INTL_REALLY_RESTART_SENSOR[] PROGMEM = "";
const char INTL_RESTART[] PROGMEM = "";
const char INTL_SAVE_AND_RESTART[] PROGMEM = "";
const char INTL_FIRMWARE[] PROGMEM = "";
const char INTL_DEBUG_SETTING_TO[] PROGMEM = "";
const char INTL_NONE[] PROGMEM = "";
const char INTL_ERROR[] PROGMEM = "";
const char INTL_WARNING[] PROGMEM = "";
const char INTL_MIN_INFO[] PROGMEM = "";
const char INTL_MED_INFO[] PROGMEM = "";
const char INTL_MAX_INFO[] PROGMEM = "";
const char INTL_CONFIG_DELETED[] PROGMEM = "";
const char INTL_CONFIG_CAN_NOT_BE_DELETED[] PROGMEM = "";
const char INTL_CONFIG_NOT_FOUND[] PROGMEM = "";
const char INTL_TIME_TO_FIRST_MEASUREMENT[] PROGMEM = "";
const char INTL_TIME_SINCE_LAST_MEASUREMENT[] PROGMEM = "";
const char INTL_PARTICLES_PER_LITER[] PROGMEM = "";
const char INTL_PARTICULATE_MATTER[] PROGMEM = "";
const char INTL_TEMPERATURE[] PROGMEM = "";
const char INTL_HUMIDITY[] PROGMEM = "";
const char INTL_PRESSURE[] PROGMEM = "";
const char INTL_LEQ_A[] PROGMEM = "LAeq";
const char INTL_LA_MIN[] PROGMEM = "LA min";
const char INTL_LA_MAX[] PROGMEM = "LA max";
const char INTL_LATITUDE[] PROGMEM = "";
const char INTL_LONGITUDE[] PROGMEM = "";
const char INTL_ALTITUDE[] PROGMEM = "";
const char INTL_DATE[] PROGMEM = "";
const char INTL_TIME[] PROGMEM = "";
const char INTL_SIGNAL_STRENGTH[] PROGMEM = "";
const char INTL_SIGNAL_QUALITY[] PROGMEM = "";
const char INTL_NUMBER_OF_MEASUREMENTS[] PROGMEM = "";
const char INTL_SENSOR[] PROGMEM = "";
const char INTL_PARAMETER[] PROGMEM = "";
const char INTL_VALUE[] PROGMEM = "";

#include "./airrohr-logo-common.h"
