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
const char INTL_PPD42NS[] PROGMEM = "PPD42NS";
const char INTL_DHT22[] PROGMEM = "DHT22 ({t}, {h})";
const char INTL_HTU21D[] PROGMEM = "HTU21D ({t}, {h})";
const char INTL_BMP180[] PROGMEM = "BMP180 ({t}, {p})";
const char INTL_BMP280[] PROGMEM = "BMP280 ({t}, {p})";
const char INTL_BME280[] PROGMEM = "BME280 ({t}, {h}, {p})";
const char INTL_DS18B20[] PROGMEM = "DS18B20 ({t})";
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
const char INTL_LCD1602_27[] PROGMEM = "LCD 1602 (I2C: 0x27)";
const char INTL_LCD1602_3F[] PROGMEM = "LCD 1602 (I2C: 0x3F)";
const char INTL_LCD2004_27[] PROGMEM = "LCD 2004 (I2C: 0x27)";
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

const char LUFTDATEN_INFO_LOGO_SVG[] PROGMEM = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
<svg viewBox=\"0 0 350 350\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\
<defs>\
<path id=\"d\" d=\"m284.38 273.35v-62.5c-1.77-23.65-9.32-42.14-22.65-55.48-13.33-13.33-30.76-20.88-52.27-22.64h-34.46-29.37c-24.67 2.77-43.66 10.82-57 24.16-13.33 13.33-21 31.32-23 53.96v62.5\"/>\
<path id=\"c\" d=\"m177.6 188.56v-112 112z\"/>\
<path id=\"a\" d=\"m171.92 76.73c5.82 0 10.53 4.71 10.53 10.52v90.95c0 5.82-4.71 10.53-10.53 10.53h-17.2c-5.82 0-10.53-4.71-10.53-10.53v-90.95c0-5.81 4.71-10.52 10.53-10.52h17.2z\"/>\
<path id=\"e\" d=\"m228.81 248.48h112-112z\"/>\
<path id=\"b\" d=\"m340.81 243.19c0 5.82-4.71 10.53-10.52 10.53h-90.95c-5.81 0-10.53-4.71-10.53-10.53v-17.21c0-5.81 4.72-10.52 10.53-10.52h90.95c5.81 0 10.52 4.71 10.52 10.52v17.21z\"/>\
</defs>\
<use fill-opacity=\"0\" stroke=\"#e0e0e0\" stroke-width=\"100\" xlink:href=\"#d\"/>\
<use fill-opacity=\"0\" stroke=\"#e0e0e0\" stroke-width=\"50\" xlink:href=\"#c\"/>\
<use fill=\"#e0e0e0\" xlink:href=\"#a\"/>\
<use fill-opacity=\"0\" stroke=\"#e0e0e0\" stroke-width=\"50\" xlink:href=\"#e\"/>\
<use fill=\"#e0e0e0\" xlink:href=\"#b\"/>\
</svg>";
