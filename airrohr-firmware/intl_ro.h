/*
 *  airRohr firmware
 *  Copyright (C) 2016-2018 Code for Stuttgart a.o. 
 *
 *  Romanian translation
 *
 *	Texts should be as short as possible
 */

#define INTL_LANG "RO"
#define INTL_PM_SENSOR "Senzor de particule în suspensie"
const char INTL_CONFIGURATION[] PROGMEM = "Configurație";
#define INTL_WIFI_SETTINGS "Setări WiFi"
#define INTL_WIFI_NETWORKS "Încărcare rețele wifi ..."
#define INTL_LANGUAGE "Limba"
const char INTL_NO_NETWORKS[] PROGMEM =  "Nu s-a găsit nicio rețea WiFi";
const char INTL_NETWORKS_FOUND[] PROGMEM = "Rețele găsite:";
const char INTL_AB_HIER_NUR_ANDERN[] PROGMEM = "Setări avansate (numai dacă știți ce faceți)";
const char INTL_SAVE[] PROGMEM = "Salvați";
const char INTL_SENSORS[] PROGMEM = "Senzori";
const char INTL_MORE_SENSORS[] PROGMEM = "Mai mulți senzori";
const char INTL_SDS011[] PROGMEM = "SDS011 ({pm})";
const char INTL_PMS[] PROGMEM = "Plantower PMS(1,3,5,5,6,7)003 ({pm})";
const char INTL_HPM[] PROGMEM = "Honeywell PM ({pm})";
const char INTL_NPM[] PROGMEM = "Tera Sensor Next PM ({pm})";
const char INTL_NPM_FULLTIME[] PROGMEM = "Next PM fulltime";
const char INTL_IPS[] PROGMEM = "Piera Systems IPS-7100 ({pm})";
const char INTL_SPS30[] PROGMEM = "Sensirion SPS30 ({pm})";
const char INTL_PPD42NS[] PROGMEM = "PPD42NS ({pm})";
const char INTL_DHT22[] PROGMEM = "DHT22 ({t}, {h})";
const char INTL_HTU21D[] PROGMEM = "HTU21D ({t}, {h})";
const char INTL_BMP180[] PROGMEM = "BMP180 ({t}, {p})";
const char INTL_BMX280[] PROGMEM = "BME280 ({t}, {h}, {p}), BMP280 ({t}, {p})";
const char INTL_SHT3X[] PROGMEM = "SHT3X ({t}, {h})";
const char INTL_SCD30[] PROGMEM = "SCD30 ({t}, {h}, CO₂)";
const char INTL_DS18B20[] PROGMEM = "DS18B20 ({t})";
const char INTL_DNMS[] PROGMEM = "DNMS ({l_a})";
const char INTL_DNMS_CORRECTION[] PROGMEM = "corecție în dB(A)";
const char INTL_TEMP_CORRECTION[] PROGMEM = "Corecție în °C";
const char INTL_HEIGHT_ABOVE_SEALEVEL[] PROGMEM = "";
const char INTL_PRESSURE_AT_SEALEVEL[] PROGMEM = "";
const char INTL_NEO6M[] PROGMEM = "GPS (NEO 6M)";
const char INTL_BASICAUTH[] PROGMEM = "Autentificare";
#define INTL_REPORT_ISSUE "Raportați o problemă"

const char INTL_FS_WIFI_DESCRIPTION[] PROGMEM = "Senzorul WiFi în modul de configurare";
const char INTL_FS_WIFI_NAME[] PROGMEM = "Numele rețelei";
const char INTL_MORE_SETTINGS[] PROGMEM = "Mai multe setări";
const char INTL_AUTO_UPDATE[] PROGMEM = "Actualizare automată a firmware-ului";
const char INTL_USE_BETA[] PROGMEM = "Încărcați firmware-ul beta";
const char INTL_DISPLAY[] PROGMEM = "OLED SSD1306";
const char INTL_SH1106[] PROGMEM = "OLED SH1106";
const char INTL_FLIP_DISPLAY[] PROGMEM = "Afișaj OLED flip";
const char INTL_LCD1602_27[] PROGMEM = "LCD 1602 (I2C: 0x27)";
const char INTL_LCD1602_3F[] PROGMEM = "LCD 1602 (I2C: 0x3F)";
const char INTL_LCD2004_27[] PROGMEM = "LCD 2004 (I2C: 0x27)";
const char INTL_LCD2004_3F[] PROGMEM = "LCD 2004 (I2C: 0x3F)";
const char INTL_DISPLAY_WIFI_INFO[] PROGMEM = "Afișarea informațiilor Wifi";
const char INTL_DISPLAY_DEVICE_INFO[] PROGMEM = "Afișarea informațiilor despre dispozitiv";

#define INTL_STATIC_IP_TEXT ""
const char INTL_STATIC_IP[] PROGMEM = "";
const char INTL_STATIC_SUBNET[] PROGMEM = "";
const char INTL_STATIC_GATEWAY[] PROGMEM = "";
const char INTL_STATIC_DNS[] PROGMEM = "";

const char INTL_DEBUG_LEVEL[] PROGMEM = "Debug&nbsp;level";
const char INTL_MEASUREMENT_INTERVAL[] PROGMEM = "Interval de măsurare (sec)";
const char INTL_DURATION_ROUTER_MODE[] PROGMEM = "Durata modului router";
const char INTL_POWERSAVE[] PROGMEM = "";
const char INTL_MORE_APIS[] PROGMEM = "Mai multe API-uri";
const char INTL_SEND_TO_OWN_API[] PROGMEM = "Trimiteți date către API personalizat";
const char INTL_SERVER[] PROGMEM = "Server";
const char INTL_PATH[] PROGMEM = "Calea";
const char INTL_PORT[] PROGMEM = "Port";
const char INTL_USER[] PROGMEM = "Utilizator";
const char INTL_PASSWORD[] PROGMEM = "Parola";
const char INTL_MEASUREMENT[] PROGMEM = "Măsurare";
const char INTL_SEND_TO[] PROGMEM = "Trimiteți la {v}";
const char INTL_READ_FROM[] PROGMEM = "Citiți de la {v}";
const char INTL_SENSOR_IS_REBOOTING[] PROGMEM = "Senzorul se repornește.";
const char INTL_RESTART_DEVICE[] PROGMEM = "Reporniți dispozitivul";
const char INTL_DELETE_CONFIG[] PROGMEM = "ștergerea configurației salvate";
const char INTL_RESTART_SENSOR[] PROGMEM = "Reporniți senzorul";
#define INTL_HOME "Acasă"
#define INTL_BACK_TO_HOME "Înapoi la pagina principală"
const char INTL_CURRENT_DATA[] PROGMEM = "Date curente";
const char INTL_DEVICE_STATUS[] PROGMEM = "Starea dispozitivului";
#define INTL_ACTIVE_SENSORS_MAP "Harta senzorilor activi (link extern)"
#define INTL_CONFIGURATION_DELETE "Ștergeți configurația"
#define INTL_CONFIGURATION_REALLY_DELETE "Sunteți sigur că doriți să ștergeți configurația?"
#define INTL_DELETE "Ștergeți"
#define INTL_CANCEL "Anulează"
#define INTL_REALLY_RESTART_SENSOR "Sunteți sigur că doriți să reporniți senzorul?"
#define INTL_RESTART "Reporniți"
const char INTL_SAVE_AND_RESTART[] PROGMEM = "Salvați configurația și reporniți";
#define INTL_FIRMWARE "Versiunea Firmware"
const char INTL_DEBUG_SETTING_TO[] PROGMEM = "Setați nivelul de depanare la";
#define INTL_NONE "off"
#define INTL_ERROR "numai erori"
#define INTL_WARNING "avertismente"
#define INTL_MIN_INFO "min. info"
#define INTL_MED_INFO "informații medii."
#define INTL_MAX_INFO "max. info"
#define INTL_CONFIG_DELETED "Configurația a fost ștearsă"
#define INTL_CONFIG_CAN_NOT_BE_DELETED "Configurația nu poate fi ștearsă"
#define INTL_CONFIG_NOT_FOUND "Configurația nu a fost găsită"
const char INTL_TIME_TO_FIRST_MEASUREMENT[] PROGMEM = "Încă {v} secunde până la prima măsurătoare.";
const char INTL_TIME_SINCE_LAST_MEASUREMENT[] PROGMEM = " secunde de la ultima măsurare.";
const char INTL_PARTICLES_PER_LITER[] PROGMEM = "particuleliter";
const char INTL_PARTICULATE_MATTER[] PROGMEM = "pulberi în suspensie";
const char INTL_TEMPERATURE[] PROGMEM = "temperatură";
const char INTL_HUMIDITY[] PROGMEM = "umiditate";
const char INTL_PRESSURE[] PROGMEM = "presiunea aerului";
const char INTL_DEW_POINT[] PROGMEM = "";
const char INTL_CO2_PPM[] PROGMEM = "ppm CO₂";
const char INTL_LEQ_A[] PROGMEM = "LAeq";
const char INTL_LA_MIN[] PROGMEM = "LA min";
const char INTL_LA_MAX[] PROGMEM = "LA max";
const char INTL_LATITUDE[] PROGMEM = "Latitudine";
const char INTL_LONGITUDE[] PROGMEM = "Longitudine";
const char INTL_ALTITUDE[] PROGMEM = "Altitudine";
const char INTL_TIME_UTC[] PROGMEM = "Ora (UTC)";
const char INTL_SIGNAL_STRENGTH[] PROGMEM = "puterea semnalului";
const char INTL_SIGNAL_QUALITY[] PROGMEM = "calitatea semnalului";
#define INTL_NUMBER_OF_MEASUREMENTS "Număr de măsurători"
#define INTL_TIME_SENDING_MS "Timp petrecut la încărcare"
#define INTL_SENSOR "Senzor"
#define INTL_PARAMETER "Parametru"
#define INTL_VALUE "Valoare"

#include "./airrohr-logo-common.h"
