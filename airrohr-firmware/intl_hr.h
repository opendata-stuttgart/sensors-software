/*
 *	airRohr firmware
 *  Copyright (C) 2016-2021  Code for Stuttgart a.o.
 *  Copyright (C) 2021-2024  Sensor.Community a.o.
 *
 *  English translations
 *
 *	Texts should be as short as possible
 */

#define INTL_LANG "HR"
#define INTL_PM_SENSOR "Senzor čestica"
const char INTL_CONFIGURATION[] PROGMEM = "Konfiguracija";
#define INTL_WIFI_SETTINGS "WiFi postavke"
#define INTL_WIFI_NETWORKS "Učitavanje wifi mreža ..."
#define INTL_LANGUAGE "Jezik"
const char INTL_NO_NETWORKS[] PROGMEM =  "WiFi mreža nije pronađena";
const char INTL_NETWORKS_FOUND[] PROGMEM = "Pronađene mreže: ";
const char INTL_AB_HIER_NUR_ANDERN[] PROGMEM = "Napredne postavke";
const char INTL_SAVE[] PROGMEM = "Spremi";
const char INTL_SENSORS[] PROGMEM = "Senzori";
const char INTL_MORE_SENSORS[] PROGMEM = "Više senzora";
const char INTL_SDS011[] PROGMEM = "SDS011 ({pm})";
const char INTL_PMS[] PROGMEM = "Plantower PMS(1,3,5,6,7)003 ({pm})";
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
const char INTL_DNMS_CORRECTION[] PROGMEM = "ispravak u dB(A)";
const char INTL_TEMP_CORRECTION[] PROGMEM = "ispravak u °C";
const char INTL_HEIGHT_ABOVE_SEALEVEL[] PROGMEM = "Iznad razine mora (m)";
const char INTL_PRESSURE_AT_SEALEVEL[] PROGMEM = "tlak na razini mora";
const char INTL_NEO6M[] PROGMEM = "GPS (NEO 6M)";
const char INTL_BASICAUTH[] PROGMEM = "Pristupni podaci";
#define INTL_REPORT_ISSUE "Prijavite problem"

const char INTL_FS_WIFI_DESCRIPTION[] PROGMEM = "WiFi mreža kod instalacije";
const char INTL_FS_WIFI_NAME[] PROGMEM = "Naziv mreže";
const char INTL_MORE_SETTINGS[] PROGMEM = "Dodatne postavke";
const char INTL_AUTO_UPDATE[] PROGMEM = "Automatsko ažuriranje firmvera";
const char INTL_USE_BETA[] PROGMEM = "Učitaj beta verziju firmvera";
const char INTL_DISPLAY[] PROGMEM = "OLED SSD1306";
const char INTL_SH1106[] PROGMEM = "OLED SH1106";
const char INTL_FLIP_DISPLAY[] PROGMEM = "OLED display flip";
const char INTL_LCD1602_27[] PROGMEM = "LCD 1602 (I2C: 0x27)";
const char INTL_LCD1602_3F[] PROGMEM = "LCD 1602 (I2C: 0x3F)";
const char INTL_LCD2004_27[] PROGMEM = "LCD 2004 (I2C: 0x27)";
const char INTL_LCD2004_3F[] PROGMEM = "LCD 2004 (I2C: 0x3F)";
const char INTL_DISPLAY_WIFI_INFO[] PROGMEM = "Prikaz WiFi informacija";
const char INTL_DISPLAY_DEVICE_INFO[] PROGMEM = "Prikaz informacija o uređaju";

#define INTL_STATIC_IP_TEXT "Konfiguracija statičke IP adrese (sva polja moraju biti ispunjena)"
const char INTL_STATIC_IP[] PROGMEM = "IP adresa";
const char INTL_STATIC_SUBNET[] PROGMEM = "Subnet";
const char INTL_STATIC_GATEWAY[] PROGMEM = "Gateway";
const char INTL_STATIC_DNS[] PROGMEM = "DNS server";

const char INTL_DEBUG_LEVEL[] PROGMEM = "Debug&nbsp;level";
const char INTL_MEASUREMENT_INTERVAL[] PROGMEM = "Interval mjerenja (s)";
const char INTL_DURATION_ROUTER_MODE[] PROGMEM = "Trajanje router načina rada";
const char INTL_POWERSAVE[] PROGMEM = "Ušteda energije";
const char INTL_MORE_APIS[] PROGMEM = "Dodatna programskih sučelja (API)";
const char INTL_SEND_TO_OWN_API[] PROGMEM = "Pošalji na API";
const char INTL_SERVER[] PROGMEM = "Server";
const char INTL_PATH[] PROGMEM = "Path";
const char INTL_PORT[] PROGMEM = "Port";
const char INTL_USER[] PROGMEM = "Korisnik";
const char INTL_PASSWORD[] PROGMEM = "Lozinka";
const char INTL_MEASUREMENT[] PROGMEM = "Mjerenje";
const char INTL_SEND_TO[] PROGMEM = "Pošalji na {v}";
const char INTL_READ_FROM[] PROGMEM = "Čitaj iz {v}";
const char INTL_SENSOR_IS_REBOOTING[] PROGMEM = "Senzor se ponovno pokreće.";
const char INTL_RESTART_DEVICE[] PROGMEM = "Ponovno pokretanje uređaja";
const char INTL_DELETE_CONFIG[] PROGMEM = "Izbriši konfiguraciju";
const char INTL_RESTART_SENSOR[] PROGMEM = "Ponovno pokretanje senzora";
#define INTL_HOME "Početna"
#define INTL_BACK_TO_HOME "Povratak na početnu stranicu"
const char INTL_CURRENT_DATA[] PROGMEM = "Aktualni podaci";
const char INTL_DEVICE_STATUS[] PROGMEM = "Status uređaja";
#define INTL_ACTIVE_SENSORS_MAP "Karta aktivnih senzora (vanjska poveznica)"
#define INTL_CONFIGURATION_DELETE "Izbriši konfiguraciju"
#define INTL_CONFIGURATION_REALLY_DELETE "Jeste li sigurni da želite izbrisati konfiguraciju?"
#define INTL_DELETE "Izbriši"
#define INTL_CANCEL "Odustani"
#define INTL_REALLY_RESTART_SENSOR "Jeste li sigurni da želite ponovno pokrenuti senzor?"
#define INTL_RESTART "Ponovno pokretanje"
const char INTL_SAVE_AND_RESTART[] PROGMEM = "Spremi izmjene i ponovno pokreni";
#define INTL_FIRMWARE "Firmver"
const char INTL_DEBUG_SETTING_TO[] PROGMEM = "Postavite razinu analize grešaka na";
#define INTL_NONE "isključeno"
#define INTL_ERROR "greške"
#define INTL_WARNING "upozorenja"
#define INTL_MIN_INFO "minimalne informacije"
#define INTL_MED_INFO "srednje informacije"
#define INTL_MAX_INFO "maximalne informacije"
#define INTL_CONFIG_DELETED "Konfiguracija je izbrisana"
#define INTL_CONFIG_CAN_NOT_BE_DELETED "Konfiguracija se ne može izbrisati"
#define INTL_CONFIG_NOT_FOUND "Konfiguracija nije pronađena"
const char INTL_TIME_TO_FIRST_MEASUREMENT[] PROGMEM = "Još {v} sekundi do prvog mjerenja.";
const char INTL_TIME_SINCE_LAST_MEASUREMENT[] PROGMEM = " sekundi od zadnjeg mjerenja.";
const char INTL_PARTICLES_PER_LITER[] PROGMEM = "čestica po litri";
const char INTL_PARTICULATE_MATTER[] PROGMEM = "čestice";
const char INTL_TEMPERATURE[] PROGMEM = "temperatura";
const char INTL_HUMIDITY[] PROGMEM = "vlažnost";
const char INTL_PRESSURE[] PROGMEM = "tlak zraka";
const char INTL_DEW_POINT[] PROGMEM = "točka rosišta";
const char INTL_CO2_PPM[] PROGMEM = "ppm CO₂";
const char INTL_LEQ_A[] PROGMEM = "LAeq";
const char INTL_LA_MIN[] PROGMEM = "LA min";
const char INTL_LA_MAX[] PROGMEM = "LA max";
const char INTL_LATITUDE[] PROGMEM = "Zemljopisna širina";
const char INTL_LONGITUDE[] PROGMEM = "Zemljopisna dužina";
const char INTL_ALTITUDE[] PROGMEM = "Nadmorska visina";
const char INTL_TIME_UTC[] PROGMEM = "Vrijeme (UTC)";
const char INTL_SIGNAL_STRENGTH[] PROGMEM = "jačina signala";
const char INTL_SIGNAL_QUALITY[] PROGMEM = "kvaliteta signala";
#define INTL_NUMBER_OF_MEASUREMENTS "Broj mjerenja"
#define INTL_TIME_SENDING_MS "Vrijeme utrošeno na slanje podataka"
#define INTL_SENSOR "Senzor"
#define INTL_PARAMETER "Parametar"
#define INTL_VALUE "Vrijednost"

#include "./airrohr-logo-common.h"
