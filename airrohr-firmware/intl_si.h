/*
 *  airRohr firmware
 *  Copyright (C) 2016-2018 Code for Stuttgart a.o. 
 *
 *  Slovenian translation
 *
 *	Texts should be as short as possible
 */

#define INTL_LANG "SI"
#define INTL_PM_SENSOR "Senzor za trdne delce"
const char INTL_CONFIGURATION[] PROGMEM = "Konfiguracija";
#define INTL_WIFI_SETTINGS "Nastavitve WiFi"
#define INTL_WIFI_NETWORKS "Nalaganje omrežij wifi ..."
#define INTL_LANGUAGE "Jezik"
const char INTL_NO_NETWORKS[] PROGMEM =  "Omrežje WiFi ni bilo najdeno";
const char INTL_NETWORKS_FOUND[] PROGMEM = "Najdena omrežja:";
const char INTL_AB_HIER_NUR_ANDERN[] PROGMEM = "Napredne nastavitve (samo če veste, kaj počnete)";
const char INTL_SAVE[] PROGMEM = "Shrani";
const char INTL_SENSORS[] PROGMEM = "Senzorji";
const char INTL_MORE_SENSORS[] PROGMEM = "Več senzorjev";
const char INTL_SDS011[] PROGMEM = "SDS011 ({pm})";
const char INTL_PMS[] PROGMEM = "Rastlinjak PMS(1,3,5,6,7)003 ({pm})";
const char INTL_HPM[] PROGMEM = "Honeywell PM ({pm})";
const char INTL_NPM[] PROGMEM = "Senzor Tera Naslednji PM ({pm})";
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
const char INTL_DNMS_CORRECTION[] PROGMEM = "popravek v dB(A)";
const char INTL_TEMP_CORRECTION[] PROGMEM = "Popravek v °C";
const char INTL_HEIGHT_ABOVE_SEALEVEL[] PROGMEM = "";
const char INTL_PRESSURE_AT_SEALEVEL[] PROGMEM = "";
const char INTL_NEO6M[] PROGMEM = "GPS (NEO 6M)";
const char INTL_BASICAUTH[] PROGMEM = "Preverjanje pristnosti";
#define INTL_REPORT_ISSUE "Prijavite težavo"

const char INTL_FS_WIFI_DESCRIPTION[] PROGMEM = "Senzor WiFi v načinu konfiguracije";
const char INTL_FS_WIFI_NAME[] PROGMEM = "Ime omrežja";
const char INTL_MORE_SETTINGS[] PROGMEM = "Več nastavitev";
const char INTL_AUTO_UPDATE[] PROGMEM = "Samodejno posodabljanje vdelane programske opreme";
const char INTL_USE_BETA[] PROGMEM = "Nalaganje vdelane programske opreme beta";
const char INTL_DISPLAY[] PROGMEM = "OLED SSD1306";
const char INTL_SH1106[] PROGMEM = "OLED SH1106";
const char INTL_FLIP_DISPLAY[] PROGMEM = "Obračanje zaslona OLED";
const char INTL_LCD1602_27[] PROGMEM = "LCD 1602 (I2C: 0x27)";
const char INTL_LCD1602_3F[] PROGMEM = "LCD 1602 (I2C: 0x3F)";
const char INTL_LCD2004_27[] PROGMEM = "LCD 2004 (I2C: 0x27)";
const char INTL_LCD2004_3F[] PROGMEM = "LCD 2004 (I2C: 0x3F)";
const char INTL_DISPLAY_WIFI_INFO[] PROGMEM = "Prikaz informacij o Wifi";
const char INTL_DISPLAY_DEVICE_INFO[] PROGMEM = "Prikaz informacij o napravi";

#define INTL_STATIC_IP_TEXT ""
const char INTL_STATIC_IP[] PROGMEM = "";
const char INTL_STATIC_SUBNET[] PROGMEM = "";
const char INTL_STATIC_GATEWAY[] PROGMEM = "";
const char INTL_STATIC_DNS[] PROGMEM = "";

const char INTL_DEBUG_LEVEL[] PROGMEM = "Debug&nbsp;raven";
const char INTL_MEASUREMENT_INTERVAL[] PROGMEM = "Interval merjenja (s)";
const char INTL_DURATION_ROUTER_MODE[] PROGMEM = "Trajanje načina usmerjevalnika";
const char INTL_POWERSAVE[] PROGMEM = "";
const char INTL_MORE_APIS[] PROGMEM = "Več API-jev";
const char INTL_SEND_TO_OWN_API[] PROGMEM = "Pošiljanje podatkov v API po meri";
const char INTL_SERVER[] PROGMEM = "Strežnik";
const char INTL_PATH[] PROGMEM = "Pot";
const char INTL_PORT[] PROGMEM = "Pristanišče";
const char INTL_USER[] PROGMEM = "Uporabnik";
const char INTL_PASSWORD[] PROGMEM = "Geslo";
const char INTL_MEASUREMENT[] PROGMEM = "Merjenje";
const char INTL_SEND_TO[] PROGMEM = "Pošlji na {v}";
const char INTL_READ_FROM[] PROGMEM = "Preberi od {v}";
const char INTL_SENSOR_IS_REBOOTING[] PROGMEM = "Senzor se ponovno zažene.";
const char INTL_RESTART_DEVICE[] PROGMEM = "Ponovni zagon naprave";
const char INTL_DELETE_CONFIG[] PROGMEM = "brisanje shranjene konfiguracije";
const char INTL_RESTART_SENSOR[] PROGMEM = "Ponovni zagon senzorja";
#define INTL_HOME "Domov"
#define INTL_BACK_TO_HOME "Nazaj na domačo stran"
const char INTL_CURRENT_DATA[] PROGMEM = "Trenutni podatki";
const char INTL_DEVICE_STATUS[] PROGMEM = "Stanje naprave";
#define INTL_ACTIVE_SENSORS_MAP "Zemljevid aktivnih senzorjev (zunanja povezava)"
#define INTL_CONFIGURATION_DELETE "Brisanje konfiguracije"
#define INTL_CONFIGURATION_REALLY_DELETE "Ali ste prepričani, da želite izbrisati konfiguracijo?"
#define INTL_DELETE "Izbriši"
#define INTL_CANCEL "Prekliči"
#define INTL_REALLY_RESTART_SENSOR "Ste prepričani, da želite znova zagnati senzor?"
#define INTL_RESTART "Ponovni zagon"
const char INTL_SAVE_AND_RESTART[] PROGMEM = "Shranite konfiguracijo in znova zaženite";
#define INTL_FIRMWARE "Različica strojne programske opreme"
const char INTL_DEBUG_SETTING_TO[] PROGMEM = "Nastavite raven razhroščevanja na";
#define INTL_NONE "izklop"
#define INTL_ERROR "samo napake"
#define INTL_WARNING "opozorila"
#define INTL_MIN_INFO "min. informacije"
#define INTL_MED_INFO "sredina. info"
#define INTL_MAX_INFO "največje informacije"
#define INTL_CONFIG_DELETED "Konfiguracija je bila izbrisana"
#define INTL_CONFIG_CAN_NOT_BE_DELETED "Konfiguracije ni mogoče izbrisati"
#define INTL_CONFIG_NOT_FOUND "Konfiguracija ni bila najdena"
const char INTL_TIME_TO_FIRST_MEASUREMENT[] PROGMEM = "Še vedno {v} sekund do prve meritve.";
const char INTL_TIME_SINCE_LAST_MEASUREMENT[] PROGMEM = " sekund od zadnje meritve.";
const char INTL_PARTICLES_PER_LITER[] PROGMEM = "delciliter";
const char INTL_PARTICULATE_MATTER[] PROGMEM = "trdni delci";
const char INTL_TEMPERATURE[] PROGMEM = "temperatura";
const char INTL_HUMIDITY[] PROGMEM = "vlažnost";
const char INTL_PRESSURE[] PROGMEM = "zračni tlak";
const char INTL_DEW_POINT[] PROGMEM = "";
const char INTL_CO2_PPM[] PROGMEM = "ppm CO₂";
const char INTL_LEQ_A[] PROGMEM = "LAeq";
const char INTL_LA_MIN[] PROGMEM = "LA min";
const char INTL_LA_MAX[] PROGMEM = "LA max";
const char INTL_LATITUDE[] PROGMEM = "Zemljepisna širina";
const char INTL_LONGITUDE[] PROGMEM = "Zemljepisna dolžina";
const char INTL_ALTITUDE[] PROGMEM = "Nadmorska višina";
const char INTL_TIME_UTC[] PROGMEM = "Čas (UTC)";
const char INTL_SIGNAL_STRENGTH[] PROGMEM = "moč signala";
const char INTL_SIGNAL_QUALITY[] PROGMEM = "kakovost signala";
#define INTL_NUMBER_OF_MEASUREMENTS "Število meritev"
#define INTL_TIME_SENDING_MS "Čas, porabljen za nalaganje"
#define INTL_SENSOR "Senzor"
#define INTL_PARAMETER "Parameter"
#define INTL_VALUE "Vrednost"
const char INTL_ENABLE_BATTERY_MONITOR[] PROGMEM = "Omogoči nadzor baterije";
const char INTL_BATTERY_CHARGE[] PROGMEM = "Polnjenje baterije";
const char INTL_BATTERY_U_MIN[] PROGMEM = "Baterija U min (mV)";
const char INTL_BATTERY_U_MAX[] PROGMEM = "Baterija U max (mV)";
const char INTL_ADC_DIVIDER_U_MAX[] PROGMEM = "ADC delilnik U max (mV)";

#include "./airrohr-logo-common.h"
