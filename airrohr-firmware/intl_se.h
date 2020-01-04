/*
 *	airRohr firmware
 *	Copyright (C) 2016-2018  Code for Stuttgart a.o.
 *
 *  Swedish translations
 *
 *	Texts should be as short as possible
 *	We only have 512 kB for the entire firmware
 */

const char INTL_LANG[] = "SE";
#define INTL_PM_SENSOR "Partikelsensor"
const char INTL_CONFIGURATION[] PROGMEM = "Inställningar";
#define INTL_WIFI_SETTINGS "WLAN konfiguration"
#define INTL_WIFI_NETWORKS "Laddar trådlösa nätverk..."
#define INTL_LANGUAGE "Språk"
const char INTL_NO_NETWORKS[] PROGMEM =  "Inga nätverk hittades";
const char INTL_NETWORKS_FOUND[] PROGMEM = "Nätverk hittades: ";
const char INTL_AB_HIER_NUR_ANDERN[] PROGMEM = "Ändra nedanför enbart om du verkligen vet vad du gör";
const char INTL_SAVE[] PROGMEM = "Spara";
const char INTL_SENSORS[] PROGMEM = "Sensorer";
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
const char INTL_DNMS_CORRECTION[] PROGMEM ="korrigering i dB (A)";
const char INTL_NEO6M[] PROGMEM = "GPS (NEO 6M)";
const char INTL_BASICAUTH[] PROGMEM = "Aktivera BasicAuth";

const char INTL_FS_WIFI_DESCRIPTION[] PROGMEM = "WiFi-sensor i konfigurationsläge";
const char INTL_FS_WIFI_NAME[] PROGMEM = "Sensorns WLAN namn";
const char INTL_MORE_SETTINGS[] PROGMEM ="Avancerade inställningar";
const char INTL_AUTO_UPDATE[] PROGMEM = "Automatisk uppdatering";
const char INTL_USE_BETA[] PROGMEM = "Använd beta-versioner";
const char INTL_DISPLAY[] PROGMEM = "OLED SSD1306";
const char INTL_SH1106[] PROGMEM = "OLED SH1106";
const char INTL_FLIP_DISPLAY[] PROGMEM = "Vänd OLED-display";
const char INTL_LCD1602_27[] PROGMEM = "LCD 1602 (I2C: 0x27)";
const char INTL_LCD1602_3F[] PROGMEM = "LCD 1602 (I2C: 0x3F)";
const char INTL_LCD2004_27[] PROGMEM = "LCD 2004 (I2C: 0x27)";
const char INTL_LCD2004_3F[] PROGMEM = "LCD 2004 (I2C: 0x3F)";
const char INTL_DISPLAY_WIFI_INFO[] PROGMEM = "Visa WiFi-information";
const char INTL_DISPLAY_DEVICE_INFO[] PROGMEM = "Visa enhetsinfo";
const char INTL_DEBUG_LEVEL[] PROGMEM = "Debug&nbsp;level";
const char INTL_MEASUREMENT_INTERVAL[] PROGMEM = "Mätintervall";
const char INTL_DURATION_ROUTER_MODE[] PROGMEM = "Permanent&nbsp;router-modus";
const char INTL_MORE_APIS[] PROGMEM = "Ytterligare APIer";
const char INTL_SEND_TO_OWN_API[] PROGMEM = "Skicka till eget API";
const char INTL_SERVER[] PROGMEM = "Server";
const char INTL_PATH[] PROGMEM = "Sökväg (path)";
const char INTL_PORT[] PROGMEM = "Port";
const char INTL_USER[] PROGMEM = "Användarnamn";
const char INTL_PASSWORD[] PROGMEM = "Lösenord";
const char INTL_SEND_TO[] PROGMEM = "Skicka till {v}";
const char INTL_READ_FROM[] PROGMEM = "Hämta {v}";
const char INTL_SENSOR_IS_REBOOTING[] PROGMEM = "Sensor startas om.";
const char INTL_RESTART_DEVICE[] PROGMEM = "Starta om enhet";
const char INTL_DELETE_CONFIG[] PROGMEM = "Ta bort Config.json";
const char INTL_RESTART_SENSOR[] PROGMEM = "Starta om sensor";
#define INTL_HOME "Översikt"
#define INTL_BACK_TO_HOME "Tillbaka till översikten"
const char INTL_CURRENT_DATA[] PROGMEM = "Aktuella mätvärden";
const char INTL_DEVICE_STATUS[] PROGMEM = "Enhetsstatus";
#define INTL_ACTIVE_SENSORS_MAP "Karta över aktiva sensorer (extern länk)"
#define INTL_CONFIGURATION_DELETE "Ta bort konfiguration"
#define INTL_CONFIGURATION_REALLY_DELETE "Ska konfigurationen tas bort?"
#define INTL_DELETE "Ta bort"
#define INTL_CANCEL "Avbryt"
#define INTL_REALLY_RESTART_SENSOR "Config.json kunde inte hittas"
#define INTL_RESTART "Starta om"
const char INTL_SAVE_AND_RESTART[] PROGMEM = "Spara och starta om";
#define INTL_FIRMWARE "Firmware"
const char INTL_DEBUG_SETTING_TO[] PROGMEM = "Ställa in debug-läge";
#define INTL_NONE "none"
#define INTL_ERROR "error"
#define INTL_WARNING "warning"
#define INTL_MIN_INFO "min. info"
#define INTL_MED_INFO "med. info"
#define INTL_MAX_INFO "max. info"
#define INTL_CONFIG_DELETED "Config.json borttagen"
#define INTL_CONFIG_CAN_NOT_BE_DELETED "Config.json kunde inte tas bort"
#define INTL_CONFIG_NOT_FOUND "Config.json kunde inte hittas"
const char INTL_TIME_TO_FIRST_MEASUREMENT[] PROGMEM = "Det är {v} sekunder kvar till första mätningen.";
const char INTL_TIME_SINCE_LAST_MEASUREMENT[] PROGMEM = " sekunder sedan den senaste mätningen.";
const char INTL_PARTICLES_PER_LITER[] PROGMEM = "Partiklar/liter";
const char INTL_PARTICULATE_MATTER[] PROGMEM = "partikelsensor";
const char INTL_TEMPERATURE[] PROGMEM = "Temperatur";
const char INTL_HUMIDITY[] PROGMEM = "rel. fuktighet";
const char INTL_PRESSURE[] PROGMEM = "Lufttryck";
const char INTL_LEQ_A[] PROGMEM = "LAeq";
const char INTL_LA_MIN[] PROGMEM = "LA min";
const char INTL_LA_MAX[] PROGMEM = "LA max";
const char INTL_LATITUDE[] PROGMEM = "Latitud";
const char INTL_LONGITUDE[] PROGMEM = "Longitud";
const char INTL_ALTITUDE[] PROGMEM = "Altitud";
const char INTL_DATE[] PROGMEM = "Datum";
const char INTL_TIME[] PROGMEM = "Tid";
const char INTL_SIGNAL_STRENGTH[] PROGMEM = "Signal";
const char INTL_SIGNAL_QUALITY[] PROGMEM = "Kvalitet";
#define INTL_NUMBER_OF_MEASUREMENTS "Antal mätningar"
#define INTL_TIME_SENDING_MS "Tid som skickas i att skicka"
#define INTL_SENSOR "Sensor"
#define INTL_PARAMETER "Parameter"
#define INTL_VALUE "Värde"

#include "./airrohr-logo-common.h"
