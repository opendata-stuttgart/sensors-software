/*
 *	airRohr firmware
 *	Copyright (C) 2016-2018  Code for Stuttgart a.o.
 *
 *  Dutch translations
 *
 *	Texts should be as short as possible
 *	We only have 512 kB for the entire firmware
 */

const char INTL_LANG[] = "NL";
#define INTL_PM_SENSOR "Fijnstofsensor"
const char INTL_CONFIGURATION[] PROGMEM = "Configuratie";
#define INTL_WIFI_SETTINGS "WiFi-instellingen"
#define INTL_WIFI_NETWORKS "Zoeken naar WiFi-netwerken ..."
#define INTL_LANGUAGE "Taal"
const char INTL_NO_NETWORKS[] PROGMEM =  "Geen WiFi-netwerk gevonden";
const char INTL_NETWORKS_FOUND[] PROGMEM = "Netwerk gevonden: ";
const char INTL_AB_HIER_NUR_ANDERN[] PROGMEM = "Geavanceerde instellingen (enkel als je weet wat je doet)";
const char INTL_SAVE[] PROGMEM = "Opslaan";
const char INTL_SENSORS[] PROGMEM = "Sensors";
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
const char INTL_DNMS_CORRECTION[] PROGMEM ="correctie in dB(A)";
const char INTL_NEO6M[] PROGMEM = "GPS (NEO 6M)";
const char INTL_BASICAUTH[] PROGMEM = "Beperk toegang";

const char INTL_FS_WIFI_DESCRIPTION[] PROGMEM = "Netwerknaam en -wachtwoord van de fijnstofsensor";
const char INTL_FS_WIFI_NAME[] PROGMEM = "Naam (SSID)";
const char INTL_MORE_SETTINGS[] PROGMEM ="Meer instellingen";
const char INTL_AUTO_UPDATE[] PROGMEM = "Firmware automatisch bijwerken";
const char INTL_USE_BETA[] PROGMEM = "Installeer beta-firmwares";
const char INTL_DISPLAY[] PROGMEM = "OLED SSD1306";
const char INTL_SH1106[] PROGMEM = "OLED SH1106";
const char INTL_FLIP_DISPLAY[] PROGMEM = "OLED display omdraaien";
const char INTL_LCD1602_27[] PROGMEM = "LCD 1602 (I2C: 0x27)";
const char INTL_LCD1602_3F[] PROGMEM = "LCD 1602 (I2C: 0x3F)";
const char INTL_LCD2004_27[] PROGMEM = "LCD 2004 (I2C: 0x27)";
const char INTL_LCD2004_3F[] PROGMEM = "LCD 2004 (I2C: 0x3F)";
const char INTL_DISPLAY_WIFI_INFO[] PROGMEM = "Toon WiFi info";
const char INTL_DISPLAY_DEVICE_INFO[] PROGMEM = "Toon apparaatinfo";
const char INTL_DEBUG_LEVEL[] PROGMEM = "Debugniveau";
const char INTL_MEASUREMENT_INTERVAL[] PROGMEM = "Meetinterval";
const char INTL_DURATION_ROUTER_MODE[] PROGMEM = "Tijdsduur routermodus";
const char INTL_MORE_APIS[] PROGMEM = "Meer API's";
const char INTL_SEND_TO_OWN_API[] PROGMEM = "Verzend data naar eigen API";
const char INTL_SERVER[] PROGMEM = "Serveradres";
const char INTL_PATH[] PROGMEM = "Pad";
const char INTL_PORT[] PROGMEM = "Poort";
const char INTL_USER[] PROGMEM = "Gebruiker";
const char INTL_PASSWORD[] PROGMEM = "Wachtwoord";
const char INTL_SEND_TO[] PROGMEM = "Verzend naar {v}";
const char INTL_READ_FROM[] PROGMEM = "Lees uit {v}";
const char INTL_SENSOR_IS_REBOOTING[] PROGMEM = "Toestel wordt opnieuw opgestart";
const char INTL_RESTART_DEVICE[] PROGMEM = "Herstart toestel";
const char INTL_DELETE_CONFIG[] PROGMEM = "Verwijder opgeslagen configuratie";
const char INTL_RESTART_SENSOR[] PROGMEM = "Herstart sensor";
#define INTL_HOME "Home"
#define INTL_BACK_TO_HOME "Terug naar homepagina"
const char INTL_CURRENT_DATA[] PROGMEM = "Huidige data";
const char INTL_DEVICE_STATUS[] PROGMEM = "Apparaatstatus";
#define INTL_ACTIVE_SENSORS_MAP "Actieve sensors kaart (externe link)"
#define INTL_CONFIGURATION_DELETE "Configuratie verwijderen"
#define INTL_CONFIGURATION_REALLY_DELETE "Bent u zeker dat u de configuratie wilt verwijderen?"
#define INTL_DELETE "Verwijderen"
#define INTL_CANCEL "Annuleren"
#define INTL_REALLY_RESTART_SENSOR "Bent u zeker dat u de sensor wilt herstarten?"
#define INTL_RESTART "Herstart"
const char INTL_SAVE_AND_RESTART[] PROGMEM = "Opslaan en herstarten";
#define INTL_FIRMWARE "Firmware-versie"
const char INTL_DEBUG_SETTING_TO[] PROGMEM = "Debugniveau naar ";
#define INTL_NONE "Uit"
#define INTL_ERROR "enkel foutmeldingen"
#define INTL_WARNING "waarschuwingen"
#define INTL_MIN_INFO "min. info"
#define INTL_MED_INFO "mid. info"
#define INTL_MAX_INFO "max. info"
#define INTL_CONFIG_DELETED "Configuratie is verwijderd"
#define INTL_CONFIG_CAN_NOT_BE_DELETED "Configuratie kan niet worden verwijderd"
#define INTL_CONFIG_NOT_FOUND "Configuratie is niet gevonden"
const char INTL_TIME_TO_FIRST_MEASUREMENT[] PROGMEM = "Nog {v} seconden voor de eerste meting.";
const char INTL_TIME_SINCE_LAST_MEASUREMENT[] PROGMEM = " seconden sinds laatste meting.";
const char INTL_PARTICLES_PER_LITER[] PROGMEM = "deeltjes/liter";
const char INTL_PARTICULATE_MATTER[] PROGMEM = "fijnstof";
const char INTL_TEMPERATURE[] PROGMEM = "Temperatuur";
const char INTL_HUMIDITY[] PROGMEM = "Rel. luchtvochtigheid";
const char INTL_PRESSURE[] PROGMEM = "Luchtdruk";
const char INTL_LEQ_A[] PROGMEM = "LAeq";
const char INTL_LA_MIN[] PROGMEM = "LA min";
const char INTL_LA_MAX[] PROGMEM = "LA max";
const char INTL_LATITUDE[] PROGMEM = "Breedtegraad";
const char INTL_LONGITUDE[] PROGMEM = "Lengtegraad";
const char INTL_ALTITUDE[] PROGMEM = "Hoogte";
const char INTL_DATE[] PROGMEM = "Datum";
const char INTL_TIME[] PROGMEM = "Tijd";
const char INTL_SIGNAL_STRENGTH[] PROGMEM = "Signaalsterkte";
const char INTL_SIGNAL_QUALITY[] PROGMEM = "Signaalkwaliteit";
#define INTL_NUMBER_OF_MEASUREMENTS "Aantal metingen"
#define INTL_TIME_SENDING_MS "Tijdsduur opsturen metingen"
#define INTL_SENSOR "Sensor"
#define INTL_PARAMETER "Parameter"
#define INTL_VALUE "Waarde"

#include "./airrohr-logo-common.h"
