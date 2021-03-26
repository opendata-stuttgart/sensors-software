/* 
*AirRohr programinė įranga 
*Copyright (C) 2016-2018 Code for Stuttgart a.o. 
* 
* 
*Tekstai turi būti kuo trumpesni 
*/

#define INTL_LANG "LT"
#define INTL_PM_SENSOR "Kietųjų dalelių jutiklis"
const char INTL_CONFIGURATION[] PROGMEM = "Konfigūracija";
#define INTL_WIFI_SETTINGS ""WiFi" nustatymai"
#define INTL_WIFI_NETWORKS "Wi-Fi tinklų įkėlimas ..."
#define INTL_LANGUAGE "Kalba"
const char INTL_NO_NETWORKS[] PROGMEM =  "Nerastas "Wi-Fi" tinklas";
const char INTL_NETWORKS_FOUND[] PROGMEM = "Rasti tinklai:";
const char INTL_AB_HIER_NUR_ANDERN[] PROGMEM = "Išplėstiniai nustatymai (tik jei žinote, ką darote)";
const char INTL_SAVE[] PROGMEM = "Išsaugoti";
const char INTL_SENSORS[] PROGMEM = "Jutikliai";
const char INTL_MORE_SENSORS[] PROGMEM = "Daugiau jutiklių";
const char INTL_SDS011[] PROGMEM = "SDS011 ({pm})";
const char INTL_PMS[] PROGMEM = ""Plantower" PMS(1,3,5,6,7)003 ({pm})";
const char INTL_HPM[] PROGMEM = ""Honeywell PM" ({pm})";
const char INTL_NPM[] PROGMEM = ""Tera Sensor Next PM" ({pm})";
const char INTL_SPS30[] PROGMEM = ""Sensirion SPS30" ({pm})";
const char INTL_PPD42NS[] PROGMEM = "PPD42NS ({pm})";
const char INTL_DHT22[] PROGMEM = "DHT22 ({t}, {h})";
const char INTL_HTU21D[] PROGMEM = "HTU21D ({t}, {h})";
const char INTL_BMP180[] PROGMEM = "BMP180 ({t}, {p})";
const char INTL_BMX280[] PROGMEM = "BME280 ({t}, {h}, {p}), BMP280 ({t}, {p})";
const char INTL_SHT3X[] PROGMEM = "SHT3X ({t}, {h})";
const char INTL_DS18B20[] PROGMEM = "DS18B20 ({t})";
const char INTL_DNMS[] PROGMEM = "DNMS ({l_a})";
const char INTL_DNMS_CORRECTION[] PROGMEM = "korekcija dB(A)";
const char INTL_TEMP_CORRECTION[] PROGMEM = "Korekcija °C";
const char INTL_NEO6M[] PROGMEM = "GPS (NEO 6M)";
const char INTL_BASICAUTH[] PROGMEM = "Autentiškumo nustatymas";
#define INTL_REPORT_ISSUE "Pranešti apie problemą"

const char INTL_FS_WIFI_DESCRIPTION[] PROGMEM = ""WiFi" jutiklio konfigūravimo režimas";
const char INTL_FS_WIFI_NAME[] PROGMEM = "Tinklo pavadinimas";
const char INTL_MORE_SETTINGS[] PROGMEM = "Daugiau nustatymų";
const char INTL_AUTO_UPDATE[] PROGMEM = "Automatinis programinės įrangos atnaujinimas";
const char INTL_USE_BETA[] PROGMEM = "Įkelti beta programinę įrangą";
const char INTL_DISPLAY[] PROGMEM = "OLED SSD1306";
const char INTL_SH1106[] PROGMEM = "OLED SH1106";
const char INTL_FLIP_DISPLAY[] PROGMEM = "OLED ekrano apvertimas";
const char INTL_LCD1602_27[] PROGMEM = "LCD 1602 (I2C: 0x27)";
const char INTL_LCD1602_3F[] PROGMEM = "LCD 1602 (I2C: 0x3F)";
const char INTL_LCD2004_27[] PROGMEM = "LCD 2004 (I2C: 0x27)";
const char INTL_LCD2004_3F[] PROGMEM = "LCD 2004 (I2C: 0x3F)";
const char INTL_DISPLAY_WIFI_INFO[] PROGMEM = "Rodyti "Wifi" informaciją";
const char INTL_DISPLAY_DEVICE_INFO[] PROGMEM = "Rodyti informaciją apie įrenginį";
const char INTL_DEBUG_LEVEL[] PROGMEM = "Derinimo&amp;nbsp;lygis";
const char INTL_MEASUREMENT_INTERVAL[] PROGMEM = "Matavimo intervalas (sek.)";
const char INTL_DURATION_ROUTER_MODE[] PROGMEM = "Trukmė maršrutizatoriaus režimas";
const char INTL_MORE_APIS[] PROGMEM = "Daugiau API";
const char INTL_SEND_TO_OWN_API[] PROGMEM = "Duomenų siuntimas į pasirinktinę API";
const char INTL_SERVER[] PROGMEM = "Serveris";
const char INTL_PATH[] PROGMEM = "Kelias";
const char INTL_PORT[] PROGMEM = "Uostas";
const char INTL_USER[] PROGMEM = "Vartotojas";
const char INTL_PASSWORD[] PROGMEM = "Slaptažodis";
const char INTL_MEASUREMENT[] PROGMEM = "Matavimas";
const char INTL_SEND_TO[] PROGMEM = "Siųsti į {v}";
const char INTL_READ_FROM[] PROGMEM = "Skaityti iš {v}";
const char INTL_SENSOR_IS_REBOOTING[] PROGMEM = "Jutiklis paleidžiamas iš naujo.";
const char INTL_RESTART_DEVICE[] PROGMEM = "Iš naujo paleiskite įrenginį";
const char INTL_DELETE_CONFIG[] PROGMEM = "ištrinti išsaugotą konfigūraciją";
const char INTL_RESTART_SENSOR[] PROGMEM = "Iš naujo paleiskite jutiklį";
#define INTL_HOME "Pagrindinis"
#define INTL_BACK_TO_HOME "Grįžti į pagrindinį puslapį"
const char INTL_CURRENT_DATA[] PROGMEM = "Dabartiniai duomenys";
const char INTL_DEVICE_STATUS[] PROGMEM = "Įrenginio būsena";
#define INTL_ACTIVE_SENSORS_MAP "Aktyvių jutiklių žemėlapis (išorinė nuoroda)"
#define INTL_CONFIGURATION_DELETE "Ištrinti konfigūraciją"
#define INTL_CONFIGURATION_REALLY_DELETE "Ar tikrai norite ištrinti konfigūraciją?"
#define INTL_DELETE "Ištrinti"
#define INTL_CANCEL "Atšaukti"
#define INTL_REALLY_RESTART_SENSOR "Ar tikrai norite iš naujo paleisti jutiklį?"
#define INTL_RESTART "Iš naujo paleiskite"
const char INTL_SAVE_AND_RESTART[] PROGMEM = "Išsaugoti konfigūraciją ir paleisti iš naujo";
#define INTL_FIRMWARE "Programinės įrangos versija"
const char INTL_DEBUG_SETTING_TO[] PROGMEM = "Nustatykite derinimo lygį į";
#define INTL_NONE "iš"
#define INTL_ERROR "tik klaidos"
#define INTL_WARNING "įspėjimai"
#define INTL_MIN_INFO "min. informacija"
#define INTL_MED_INFO "vidurio informacija"
#define INTL_MAX_INFO "maksimali informacija"
#define INTL_CONFIG_DELETED "Konfigūracija buvo ištrinta"
#define INTL_CONFIG_CAN_NOT_BE_DELETED "Konfigūracijos negalima ištrinti"
#define INTL_CONFIG_NOT_FOUND "Konfigūracija nerasta"
const char INTL_TIME_TO_FIRST_MEASUREMENT[] PROGMEM = "Dar {v} sekundžių iki pirmojo matavimo.";
const char INTL_TIME_SINCE_LAST_MEASUREMENT[] PROGMEM = " sekundžių nuo paskutinio matavimo.";
const char INTL_PARTICLES_PER_LITER[] PROGMEM = "daleliųlitras";
const char INTL_PARTICULATE_MATTER[] PROGMEM = "kietosios dalelės";
const char INTL_TEMPERATURE[] PROGMEM = "temperatūra";
const char INTL_HUMIDITY[] PROGMEM = "drėgmė";
const char INTL_PRESSURE[] PROGMEM = "oro slėgis";
const char INTL_LEQ_A[] PROGMEM = "LAeq";
const char INTL_LA_MIN[] PROGMEM = "LA min.";
const char INTL_LA_MAX[] PROGMEM = "LA max";
const char INTL_LATITUDE[] PROGMEM = "Platuma";
const char INTL_LONGITUDE[] PROGMEM = "Ilguma";
const char INTL_ALTITUDE[] PROGMEM = "Aukštis";
const char INTL_TIME_UTC[] PROGMEM = "Laikas (UTC)";
const char INTL_SIGNAL_STRENGTH[] PROGMEM = "signalo stiprumas";
const char INTL_SIGNAL_QUALITY[] PROGMEM = "signalo kokybė";
#define INTL_NUMBER_OF_MEASUREMENTS "Matavimų skaičius"
#define INTL_TIME_SENDING_MS "Įkėlimo laikas"
#define INTL_SENSOR "Jutiklis"
#define INTL_PARAMETER "Parametras"
#define INTL_VALUE "Vertė"

#include ".airrohr-logo-common.h"
