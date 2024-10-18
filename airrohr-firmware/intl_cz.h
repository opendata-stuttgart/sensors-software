/*
 *	airRohr firmware
 *  Copyright (C) 2016-2021  Code for Stuttgart a.o.
 *  Copyright (C) 2021-2024  Sensor.Community a.o.
 *
 *  Czech translations
 *
 *	Texts should be as short as possible
 */

#define INTL_LANG "CZ"
#define INTL_PM_SENSOR "Senzor prachových částic"
const char INTL_CONFIGURATION[] PROGMEM = "Konfigurace";
#define INTL_WIFI_SETTINGS "Nastavení Wi-Fi"
#define INTL_WIFI_NETWORKS "Vyhledávání Wi-Fi sítí ..."
#define INTL_LANGUAGE "Jazyk"
const char INTL_NO_NETWORKS[] PROGMEM = "Žádné Wi-Fi sítě v dosahu.";
const char INTL_NETWORKS_FOUND[] PROGMEM = "Dostupné sítě: ";
const char INTL_AB_HIER_NUR_ANDERN[] PROGMEM = "Rozšířené nastavení (jen pokud víte, co děláte)";
const char INTL_SAVE[] PROGMEM = "Uložit";
const char INTL_SENSORS[] PROGMEM = "Moduly (čidla)";
const char INTL_MORE_SENSORS[] PROGMEM = "Více čidel";
const char INTL_SDS011[] PROGMEM = "SDS011 (modul {pm})";
const char INTL_PMS[] PROGMEM = "Plantower PMS(1,3,5,6,7)003 (modul {pm})";
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
const char INTL_DNMS_CORRECTION[] PROGMEM = "Korekce v dB (A)";
const char INTL_TEMP_CORRECTION[] PROGMEM = "Korekce ve °C";
const char INTL_HEIGHT_ABOVE_SEALEVEL[] PROGMEM = "[[height_above_sealevel]]";
const char INTL_PRESSURE_AT_SEALEVEL[] PROGMEM = "[[pressure_at_sealevel]]";
const char INTL_NEO6M[] PROGMEM = "GPS (NEO 6M)";
const char INTL_BASICAUTH[] PROGMEM = "Přihlášení";
const char INTL_NOPWD[] PROGMEM = "bez hesla WiFi";
#define INTL_REPORT_ISSUE "Nahlásit problém"

const char INTL_FS_WIFI_DESCRIPTION[] PROGMEM = "Wi-Fi modul v konfiguračním módu";
const char INTL_FS_WIFI_NAME[] PROGMEM = "Název";
const char INTL_MORE_SETTINGS[] PROGMEM = "Další nastavení";
const char INTL_AUTO_UPDATE[] PROGMEM = "Autom. aktualizace";
const char INTL_USE_BETA[] PROGMEM = "Nahrát betaverzi";
const char INTL_DISPLAY[] PROGMEM = "OLED SSD1306";
const char INTL_SH1106[] PROGMEM = "OLED SH1106";
const char INTL_FLIP_DISPLAY[] PROGMEM = "OLED displej flip";
const char INTL_LCD1602_27[] PROGMEM = "LCD 1602 (I2C: 0x27)";
const char INTL_LCD1602_3F[] PROGMEM = "LCD 1602 (I2C: 0x3F)";
const char INTL_LCD2004_27[] PROGMEM = "LCD 2004 (I2C: 0x27)";
const char INTL_LCD2004_3F[] PROGMEM = "LCD 2004 (I2C: 0x3F)";
const char INTL_DISPLAY_WIFI_INFO[] PROGMEM = "Zobrazit informace o WiFi";
const char INTL_DISPLAY_DEVICE_INFO[] PROGMEM = "Zobrazit informace o zařízení";

#define INTL_STATIC_IP_TEXT "[[static_ip_text]]"
const char INTL_STATIC_IP[] PROGMEM = "[[static_ip]]";
const char INTL_STATIC_SUBNET[] PROGMEM = "[[static_subnet]]";
const char INTL_STATIC_GATEWAY[] PROGMEM = "[[static_gateway]]";
const char INTL_STATIC_DNS[] PROGMEM = "[[static_dns]]";

const char INTL_DEBUG_LEVEL[] PROGMEM = "Úroveň ladění";
const char INTL_MEASUREMENT_INTERVAL[] PROGMEM = "Interval měření";
const char INTL_DURATION_ROUTER_MODE[] PROGMEM = "Trvání router módu";
const char INTL_POWERSAVE[] PROGMEM = "[[powersave]]";
const char INTL_MORE_APIS[] PROGMEM = "Další API";
const char INTL_SEND_TO_OWN_API[] PROGMEM = "Poslat data na vlastní API";
const char INTL_SERVER[] PROGMEM = "Server";
const char INTL_PATH[] PROGMEM = "Cesta";
const char INTL_PORT[] PROGMEM = "Port";
const char INTL_USER[] PROGMEM = "Uživatel";
const char INTL_PASSWORD[] PROGMEM = "Heslo";
const char INTL_MEASUREMENT[] PROGMEM = "Měření";
const char INTL_SEND_TO[] PROGMEM = "Odeslat na {v}";
const char INTL_READ_FROM[] PROGMEM = "Čti z {v}";
const char INTL_SENSOR_IS_REBOOTING[] PROGMEM = "Zařízení bude restartováno";
const char INTL_RESTART_DEVICE[] PROGMEM = "Restartovat zařízení";
const char INTL_DELETE_CONFIG[] PROGMEM = "smazat uložené nastavení";
const char INTL_RESTART_SENSOR[] PROGMEM = "Restart senzoru";
#define INTL_HOME "Hlavní stránka"
#define INTL_BACK_TO_HOME "Zpět na hlavní stránku"
const char INTL_CURRENT_DATA[] PROGMEM = "Aktuální hodnoty";
const char INTL_DEVICE_STATUS[] PROGMEM = "Stav zařízení";
#define INTL_ACTIVE_SENSORS_MAP "Mapa aktivních senzorů (externí odkaz)"
#define INTL_CONFIGURATION_DELETE "Smazat konfiguraci"
#define INTL_CONFIGURATION_REALLY_DELETE "Opravdu smazat konfiguraci?"
#define INTL_DELETE "Smazat"
#define INTL_CANCEL "Zrušit"
#define INTL_REALLY_RESTART_SENSOR "Opravdu restartovat senzor?"
#define INTL_RESTART "Restartovat"
const char INTL_SAVE_AND_RESTART[] PROGMEM = "Uložit a restartovat";
#define INTL_FIRMWARE "Verze firmware"
const char INTL_DEBUG_SETTING_TO[] PROGMEM = "Ladění nastaveno na";
#define INTL_NONE "žádný"
#define INTL_ERROR "chyba"
#define INTL_WARNING "varování"
#define INTL_MIN_INFO "min. info"
#define INTL_MED_INFO "stř. info"
#define INTL_MAX_INFO "max. info"
#define INTL_CONFIG_DELETED "Konfigurace smazána"
#define INTL_CONFIG_CAN_NOT_BE_DELETED "Konfigurace nemohla být smazána"
#define INTL_CONFIG_NOT_FOUND "Konfigurace nenalezena"
const char INTL_TIME_TO_FIRST_MEASUREMENT[] PROGMEM = "Zbývá {v} sekund do prvního měření.";
const char INTL_TIME_SINCE_LAST_MEASUREMENT[] PROGMEM = " sekund od posledního měření.";
const char INTL_PARTICLES_PER_LITER[] PROGMEM = "částice/litr";
const char INTL_PARTICULATE_MATTER[] PROGMEM = "prachových částic";
const char INTL_TEMPERATURE[] PROGMEM = "teplota";
const char INTL_HUMIDITY[] PROGMEM = "rel. vlhkost";
const char INTL_PRESSURE[] PROGMEM = "tlak vzduchu";
const char INTL_DEW_POINT[] PROGMEM = "rosný bod";
const char INTL_CO2_PPM[] PROGMEM = "ppm CO₂";
const char INTL_LEQ_A[] PROGMEM = "LAeq";
const char INTL_LA_MIN[] PROGMEM = "LA min";
const char INTL_LA_MAX[] PROGMEM = "LA max";
const char INTL_LATITUDE[] PROGMEM = "Zem. šířka";
const char INTL_LONGITUDE[] PROGMEM = "Zem. délka";
const char INTL_ALTITUDE[] PROGMEM = "Nadm. výška";
const char INTL_TIME_UTC[] PROGMEM = "Čas (UTC)";
const char INTL_SIGNAL_STRENGTH[] PROGMEM = "Síla signálu";
const char INTL_SIGNAL_QUALITY[] PROGMEM = "Kvalita signálu";
#define INTL_NUMBER_OF_MEASUREMENTS "Počet měření"
#define INTL_TIME_SENDING_MS "Doba nahrávání"
#define INTL_SENSOR "Senzor"
#define INTL_PARAMETER "Parametr"
#define INTL_VALUE "Hodnota"

#include "./airrohr-logo-common.h"
