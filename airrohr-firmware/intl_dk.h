/*
 *	airRohr firmware
 *	Copyright (C) 2016-2018  Code for Stuttgart a.o.
 *
 *  Danish translations
 *
 *	Texts should be as short as possible
 *	We only have 512 kB for the entire firmware
 */

const char INTL_LANG[] = "DK";
#define INTL_PM_SENSOR "Partikelsensor"
const char INTL_CONFIGURATION[] PROGMEM = "Opsætning";
#define INTL_WIFI_SETTINGS "Wi-Fi indstillinger"
#define INTL_WIFI_NETWORKS "Leder efter Wi-Fi netværk..."
#define INTL_LANGUAGE "Sprog"
const char INTL_NO_NETWORKS[] PROGMEM =  "Ingen netværk fundet";
const char INTL_NETWORKS_FOUND[] PROGMEM = "Netværker fundet: ";
const char INTL_AB_HIER_NUR_ANDERN[] PROGMEM = "Ændr følgende kun hvis du ved hvad du laver";
const char INTL_SAVE[] PROGMEM = "Gem";
const char INTL_SENSORS[] PROGMEM = "Sensorer";
const char INTL_MORE_SENSORS[] PROGMEM = "More Sensorer";
const char INTL_SDS011[] PROGMEM = "SDS011 ({pm})";
const char INTL_PMS[] PROGMEM = "Plantower PMS(1,3,5,6,7)003 ({pm})";
const char INTL_HPM[] PROGMEM = "Honeywell PM ({pm})";
const char INTL_SPS30[] PROGMEM = "Sensirion SPS30 ({pm})";
const char INTL_PPD42NS[] PROGMEM = "PPD42NS ({pm})";
const char INTL_DHT22[] PROGMEM = "DHT22 ({t}, {h})";
const char INTL_HTU21D[] PROGMEM = "HTU21D ({t}, {h})";
const char INTL_BMP180[] PROGMEM = "BMP180 ({t}, {p})";
const char INTL_BMX280[] PROGMEM = "BMP280/BME280 ({t}, {h}, {p})";
const char INTL_SHT3X[] PROGMEM = "SHT3X ({t}, {h})";
const char INTL_DS18B20[] PROGMEM = "DS18B20 ({t})";
const char INTL_DNMS[] PROGMEM = "DNMS ({l_a})";
const char INTL_DNMS_CORRECTION[] PROGMEM ="korrektion i dB (A)";
const char INTL_NEO6M[] PROGMEM = "GPS (NEO 6M)";
const char INTL_BASICAUTH[] PROGMEM = "Aktiver BasicAuth";

const char INTL_FS_WIFI_DESCRIPTION[] PROGMEM = "Wi-Fi sensor i opsætningsmode";
const char INTL_FS_WIFI_NAME[] PROGMEM = "Sensorens Wi-Fi navn";
const char INTL_MORE_SETTINGS[] PROGMEM ="Avancerede indstillinger";
const char INTL_AUTO_UPDATE[] PROGMEM = "Automatisk opdatering";
const char INTL_USE_BETA[] PROGMEM = "Brug beta-versioner";
const char INTL_DISPLAY[] PROGMEM = "OLED SSD1306";
const char INTL_SH1106[] PROGMEM = "OLED SH1106";
const char INTL_FLIP_DISPLAY[] PROGMEM = "OLED display flip";
const char INTL_LCD1602_27[] PROGMEM = "LCD 1602 (I2C: 0x27)";
const char INTL_LCD1602_3F[] PROGMEM = "LCD 1602 (I2C: 0x3F)";
const char INTL_LCD2004_27[] PROGMEM = "LCD 2004 (I2C: 0x27)";
const char INTL_LCD2004_3F[] PROGMEM = "LCD 2004 (I2C: 0x3F)";
const char INTL_DISPLAY_WIFI_INFO[] PROGMEM = "Vis WiFi-info";
const char INTL_DISPLAY_DEVICE_INFO[] PROGMEM = "Vis enhedsinfo";
const char INTL_DEBUG_LEVEL[] PROGMEM = "Debug&nbsp;level";
const char INTL_MEASUREMENT_INTERVAL[] PROGMEM = "Målinterval";
const char INTL_DURATION_ROUTER_MODE[] PROGMEM = "Permanent&nbsp;router-mode";
const char INTL_MORE_APIS[] PROGMEM = "Yderligere APIer";
const char INTL_SEND_TO_OWN_API[] PROGMEM = "Send til eget API";
const char INTL_SERVER[] PROGMEM = "Server";
const char INTL_PATH[] PROGMEM = "Sti (path)";
const char INTL_PORT[] PROGMEM = "Port";
const char INTL_USER[] PROGMEM = "Brugernavn";
const char INTL_PASSWORD[] PROGMEM = "Kodeord";
const char INTL_SEND_TO[] PROGMEM = "Send til {v}";
const char INTL_READ_FROM[] PROGMEM = "Hent fra {v}";
const char INTL_SENSOR_IS_REBOOTING[] PROGMEM = "Sensor genstartes.";
const char INTL_RESTART_DEVICE[] PROGMEM = "Genstart enhed";
const char INTL_DELETE_CONFIG[] PROGMEM = "Slet Config.json";
const char INTL_RESTART_SENSOR[] PROGMEM = "Genstart sensor";
#define INTL_HOME "Oversigt"
#define INTL_BACK_TO_HOME "Tilbage til oversigten"
const char INTL_CURRENT_DATA[] PROGMEM = "Aktuelle målværdier";
const char INTL_DEVICE_STATUS[] PROGMEM = "Enhedsstatus";
#define INTL_ACTIVE_SENSORS_MAP "Kort over aktive sensorer (ekstern link)"
#define INTL_CONFIGURATION_DELETE "Slet opsætningen"
#define INTL_CONFIGURATION_REALLY_DELETE "Skal opsætningen virkelig slettes?"
#define INTL_DELETE "Slet"
#define INTL_CANCEL "Afbryd"
#define INTL_REALLY_RESTART_SENSOR "Config.json kunne ikke findes"
#define INTL_RESTART "Genstart"
const char INTL_SAVE_AND_RESTART[] PROGMEM = "Gem og genstart";
#define INTL_FIRMWARE "Firmware"
const char INTL_DEBUG_SETTING_TO[] PROGMEM = "Debug-indstillinger sat til";
#define INTL_NONE "none"
#define INTL_ERROR "error"
#define INTL_WARNING "warning"
#define INTL_MIN_INFO "min. info"
#define INTL_MED_INFO "med. info"
#define INTL_MAX_INFO "max. info"
#define INTL_CONFIG_DELETED "Config.json slettet"
#define INTL_CONFIG_CAN_NOT_BE_DELETED "Config.json kunne ikke slettes"
#define INTL_CONFIG_NOT_FOUND "Config.json kunne ikke findes"
const char INTL_TIME_TO_FIRST_MEASUREMENT[] PROGMEM = "Der går {v} sekunder før den første måling.";
const char INTL_TIME_SINCE_LAST_MEASUREMENT[] PROGMEM = " sekunder siden den seneste måling.";
const char INTL_PARTICLES_PER_LITER[] PROGMEM = "Partikler/liter";
const char INTL_PARTICULATE_MATTER[] PROGMEM = "Partikelsensor";
const char INTL_TEMPERATURE[] PROGMEM = "Temperatur";
const char INTL_HUMIDITY[] PROGMEM = "Rel. Fugtighed";
const char INTL_PRESSURE[] PROGMEM = "Lufttryk";
const char INTL_LEQ_A[] PROGMEM = "LAeq";
const char INTL_LA_MIN[] PROGMEM = "LA min";
const char INTL_LA_MAX[] PROGMEM = "LA max";
const char INTL_LATITUDE[] PROGMEM = "Breddegrad";
const char INTL_LONGITUDE[] PROGMEM = "Længdegrad";
const char INTL_ALTITUDE[] PROGMEM = "Højde";
const char INTL_DATE[] PROGMEM = "Dato";
const char INTL_TIME[] PROGMEM = "Tid";
const char INTL_SIGNAL_STRENGTH[] PROGMEM = "Signal";
const char INTL_SIGNAL_QUALITY[] PROGMEM = "Kvalitet";
#define INTL_NUMBER_OF_MEASUREMENTS "Antal målinger"
#define INTL_TIME_SENDING_MS "Tid brugt på afsendelse"
#define INTL_SENSOR "Sensor"
#define INTL_PARAMETER "Parameter"
#define INTL_VALUE "Værdi"

#include "./airrohr-logo-common.h"
