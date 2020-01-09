/*
 *	airRohr firmware
 *	Copyright (C) 2016-2018  Code for Stuttgart a.o.
 *
 *  Serbian translations
 *
 *	Texts should be as short as possible
 *	We only have 512 kB for the entire firmware
 */

const char INTL_LANG[] = "RS";
#define INTL_PM_SENSOR "Senzor suspendovanih čestica"
const char INTL_CONFIGURATION[] PROGMEM = "Konfiguracija";
#define INTL_WIFI_SETTINGS "WiFi podešavanja"
#define INTL_WIFI_NETWORKS "Učitavanje WiFi mreža ..."
#define INTL_LANGUAGE "Jezik"
const char INTL_NO_NETWORKS[] PROGMEM =  "Nije pronađena WiFi mreža";
const char INTL_NETWORKS_FOUND[] PROGMEM = "Pronađene mreže: ";
const char INTL_AB_HIER_NUR_ANDERN[] PROGMEM = "Napredna podešavanja (samo ako znate šta radite)";
const char INTL_SAVE[] PROGMEM = "Sačuvaj";
const char INTL_SENSORS[] PROGMEM = "Senzori";
const char INTL_MORE_SENSORS[] PROGMEM = "More Sensors";
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
const char INTL_DNMS_CORRECTION[] PROGMEM ="Korekcija u dB(A)";
const char INTL_NEO6M[] PROGMEM = "GPS (NEO 6M)";
const char INTL_BASICAUTH[] PROGMEM = "Autorizacija";

const char INTL_FS_WIFI_DESCRIPTION[] PROGMEM = "WiFi senzor u konfiguracionom režimu";
const char INTL_FS_WIFI_NAME[] PROGMEM = "Naziv";
const char INTL_MORE_SETTINGS[] PROGMEM ="Više podešavanja";
const char INTL_AUTO_UPDATE[] PROGMEM = "Automatski ažuriraj firmver";
const char INTL_USE_BETA[] PROGMEM = "Učitaj beta firmver";
const char INTL_DISPLAY[] PROGMEM = "OLED SSD1306";
const char INTL_SH1106[] PROGMEM = "OLED SH1106";
const char INTL_FLIP_DISPLAY[] PROGMEM = "Rotiraj OLED displej (180°)";
const char INTL_LCD1602_27[] PROGMEM = "LCD 1602 (I2C: 0x27)";
const char INTL_LCD1602_3F[] PROGMEM = "LCD 1602 (I2C: 0x3F)";
const char INTL_LCD2004_27[] PROGMEM = "LCD 2004 (I2C: 0x27)";
const char INTL_LCD2004_3F[] PROGMEM = "LCD 2004 (I2C: 0x3F)";
const char INTL_DISPLAY_WIFI_INFO[] PROGMEM = "Prikaži WiFi podatke";
const char INTL_DISPLAY_DEVICE_INFO[] PROGMEM = "Pokaži informacije o uređaju";
const char INTL_DEBUG_LEVEL[] PROGMEM = "Nivo&nbsp;korekcije";
const char INTL_MEASUREMENT_INTERVAL[] PROGMEM = "Merni interval";
const char INTL_DURATION_ROUTER_MODE[] PROGMEM = "Trajanje ruter režima";
const char INTL_MORE_APIS[] PROGMEM = "Više API-ja";
const char INTL_SEND_TO_OWN_API[] PROGMEM = "Pošalji podatke mom API-ju";
const char INTL_SERVER[] PROGMEM = "Server";
const char INTL_PATH[] PROGMEM = "Putanja";
const char INTL_PORT[] PROGMEM = "Port";
const char INTL_USER[] PROGMEM = "Korisnik";
const char INTL_PASSWORD[] PROGMEM = "Lozinka";
const char INTL_SEND_TO[] PROGMEM = "Pošalji na {v}";
const char INTL_READ_FROM[] PROGMEM = "Pročitaj iz {v}";
const char INTL_SENSOR_IS_REBOOTING[] PROGMEM = "Senzor se restartuje.";
const char INTL_RESTART_DEVICE[] PROGMEM = "Restartuj uređaj";
const char INTL_DELETE_CONFIG[] PROGMEM = "Obriši sačuvanu konfiguraciju";
const char INTL_RESTART_SENSOR[] PROGMEM = "Restartuj senzor";
#define INTL_HOME "Naslovna"
#define INTL_BACK_TO_HOME "Povratak na naslovnu stranicu"
const char INTL_CURRENT_DATA[] PROGMEM = "Trenutni podaci";
const char INTL_DEVICE_STATUS[] PROGMEM = "Status уређаја";
#define INTL_ACTIVE_SENSORS_MAP "Mapa aktivnih senzora (spoljni link)"
#define INTL_CONFIGURATION_DELETE "Izbriši konfiguraciju"
#define INTL_CONFIGURATION_REALLY_DELETE "Jeste li sigurni da želite da izbrišete konfiguraciju?"
#define INTL_DELETE "Izbriši"
#define INTL_CANCEL "Poništi"
#define INTL_REALLY_RESTART_SENSOR "Jeste li sigurni da hoćete da ponovo pokrenete senzor?"
#define INTL_RESTART "Restartuj"
const char INTL_SAVE_AND_RESTART[] PROGMEM = "Sačuvaj i restartuj";
#define INTL_FIRMWARE "Verzija firmvera"
const char INTL_DEBUG_SETTING_TO[] PROGMEM = "Podesi debagovanje na";
#define INTL_NONE "isključeno"
#define INTL_ERROR "greške"
#define INTL_WARNING "upozorenja"
#define INTL_MIN_INFO "min. info"
#define INTL_MED_INFO "mid. info"
#define INTL_MAX_INFO "max. info"
#define INTL_CONFIG_DELETED "Config.json je izbrisan"
#define INTL_CONFIG_CAN_NOT_BE_DELETED "Config.json se ne može izbrisati"
#define INTL_CONFIG_NOT_FOUND "Config.json nije pronađen"
const char INTL_TIME_TO_FIRST_MEASUREMENT[] PROGMEM = "Još {v} sekundi do prvog merenja.";
const char INTL_TIME_SINCE_LAST_MEASUREMENT[] PROGMEM = " sekundi od poslednjeg merenja.";
const char INTL_PARTICLES_PER_LITER[] PROGMEM = "čestica/litru";
const char INTL_PARTICULATE_MATTER[] PROGMEM = "suspendovane čestice";
const char INTL_TEMPERATURE[] PROGMEM = "temperatura";
const char INTL_HUMIDITY[] PROGMEM = "vlažnost";
const char INTL_PRESSURE[] PROGMEM = "vazdušni pritisak";
const char INTL_LEQ_A[] PROGMEM = "LAeq";
const char INTL_LA_MIN[] PROGMEM = "LA min";
const char INTL_LA_MAX[] PROGMEM = "LA max";
const char INTL_LATITUDE[] PROGMEM = "Geografska širina";
const char INTL_LONGITUDE[] PROGMEM = "Geografska dužina";
const char INTL_ALTITUDE[] PROGMEM = "Nadmorska visina";
const char INTL_DATE[] PROGMEM = "Datum";
const char INTL_TIME[] PROGMEM = "Vreme";
const char INTL_SIGNAL_STRENGTH[] PROGMEM = "jačina signala";
const char INTL_SIGNAL_QUALITY[] PROGMEM = "kvalitet signala";
#define INTL_NUMBER_OF_MEASUREMENTS "Broj merenja"
#define INTL_TIME_SENDING_MS "Vreme utrošeno za slanje"
#define INTL_SENSOR "Senzor"
#define INTL_PARAMETER "Parametar"
#define INTL_VALUE "Vrednost"

#include "./airrohr-logo-common.h"
