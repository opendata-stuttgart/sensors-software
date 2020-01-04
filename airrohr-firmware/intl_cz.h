/*
 *	airRohr firmware
 *	Copyright (C) 2016-2018  Code for Stuttgart a.o.
 *
 *  Czech translations
 *
 *	Texts should be as short as possible
 *	We only have 512 kB for the entire firmware
 */

const char INTL_LANG[] = "CZ";
#define INTL_PM_SENSOR "Senzor prachových èástic"
const char INTL_CONFIGURATION[] PROGMEM = "Konfigurace";
#define INTL_WIFI_SETTINGS "Nastavení Wi-Fi"
#define INTL_WIFI_NETWORKS "Vyhledávání Wi-Fi sítí ..."
#define INTL_LANGUAGE "Jazyk"
const char INTL_NO_NETWORKS[] PROGMEM = "Žádné Wi-Fi sítì v dosahu.";
const char INTL_NETWORKS_FOUND[] PROGMEM = "Dostupné sítì: ";
const char INTL_AB_HIER_NUR_ANDERN[] PROGMEM = "Rozšíøené nastavení (jen pokud víte jistì, co dìláte)";
const char INTL_SAVE[] PROGMEM = "Uložit";
const char INTL_SENSORS[] PROGMEM = "Moduly (èidla)";
const char INTL_MORE_SENSORS[] PROGMEM = "More Moduly (èidla)";
const char INTL_SDS011[] PROGMEM = "SDS011 (modul {pm})";
const char INTL_PMS[] PROGMEM = "Plantower PMS(1,3,5,6,7)003 (modul {pm})";
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
const char INTL_DNMS_CORRECTION[] PROGMEM ="korekce v dB (A)";
const char INTL_NEO6M[] PROGMEM = "GPS (NEO 6M)";
const char INTL_BASICAUTH[] PROGMEM = "Pøihlášení (heslem)";

const char INTL_FS_WIFI_DESCRIPTION[] PROGMEM = "Wi-Fi modul v konfiguraèním módu";
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
const char INTL_DEBUG_LEVEL[] PROGMEM = "Ladìní&nbsp;Úroveò";
const char INTL_MEASUREMENT_INTERVAL[] PROGMEM = "Interval mìøení";
const char INTL_DURATION_ROUTER_MODE[] PROGMEM = "Trvání&nbsp;Mód routeru";
const char INTL_MORE_APIS[] PROGMEM = "Další API";
const char INTL_SEND_TO_OWN_API[] PROGMEM = "Poslat data na vlastní API";
const char INTL_SERVER[] PROGMEM = "Server";
const char INTL_PATH[] PROGMEM = "Cesta";
const char INTL_PORT[] PROGMEM = "Port";
const char INTL_USER[] PROGMEM = "Uživatel";
const char INTL_PASSWORD[] PROGMEM = "Heslo";
const char INTL_SEND_TO[] PROGMEM = "Odeslat na {v}";
const char INTL_READ_FROM[] PROGMEM = "Èti z {v}";
const char INTL_SENSOR_IS_REBOOTING[] PROGMEM = "Zaøízení bude restartováno";
const char INTL_RESTART_DEVICE[] PROGMEM = "Restartovat zaøízení";
const char INTL_DELETE_CONFIG[] PROGMEM = "Smazat Config.json";
const char INTL_RESTART_SENSOR[] PROGMEM = "Restart senzoru";
#define INTL_HOME "Hlavní stránka"
#define INTL_BACK_TO_HOME "Zpìt na hlavní stránku"
const char INTL_CURRENT_DATA[] PROGMEM = "Aktuální hodnoty";
const char INTL_DEVICE_STATUS[] PROGMEM = "stav pohonu";
#define INTL_ACTIVE_SENSORS_MAP "Mapa aktivních senzorù (externí odkaz)"
#define INTL_CONFIGURATION_DELETE "Smazat konfiguraci"
#define INTL_CONFIGURATION_REALLY_DELETE "Opravdu smazat konfiguraci?"
#define INTL_DELETE "Smazat"
#define INTL_CANCEL "Zrušit"
#define INTL_REALLY_RESTART_SENSOR "Opravdu restartovat senzor"
#define INTL_RESTART "Restartovat"
const char INTL_SAVE_AND_RESTART[] PROGMEM = "Uložit a restartovat";
#define INTL_FIRMWARE "Firmware verze"
const char INTL_DEBUG_SETTING_TO[] PROGMEM = "Ladìní nastaveno na";
#define INTL_NONE "žádný"
#define INTL_ERROR "chyba"
#define INTL_WARNING "varování"
#define INTL_MIN_INFO "min. info"
#define INTL_MED_INFO "stø. info"
#define INTL_MAX_INFO "max. info"
#define INTL_CONFIG_DELETED "Config.json smazán"
#define INTL_CONFIG_CAN_NOT_BE_DELETED "Config.json nemohl být smazán"
#define INTL_CONFIG_NOT_FOUND "Config.json nenalezen"
const char INTL_TIME_TO_FIRST_MEASUREMENT[] PROGMEM = "Zbývá {v} sekund do prvního mìøení.";
const char INTL_TIME_SINCE_LAST_MEASUREMENT[] PROGMEM = " sekund od posledního mìøení.";
const char INTL_PARTICLES_PER_LITER[] PROGMEM = "èástice/litr";
const char INTL_PARTICULATE_MATTER[] PROGMEM = "prachových èástic";
const char INTL_TEMPERATURE[] PROGMEM = "teplota";
const char INTL_HUMIDITY[] PROGMEM = "rel. vlhkost";
const char INTL_PRESSURE[] PROGMEM = "tlak vzduchu";
const char INTL_LEQ_A[] PROGMEM = "LAeq";
const char INTL_LA_MIN[] PROGMEM = "LA min";
const char INTL_LA_MAX[] PROGMEM = "LA max";
const char INTL_LATITUDE[] PROGMEM = "Zem. šíøka";
const char INTL_LONGITUDE[] PROGMEM = "Zem. délka";
const char INTL_ALTITUDE[] PROGMEM = "Nadm. výška";
const char INTL_DATE[] PROGMEM = "Datum";
const char INTL_TIME[] PROGMEM = "Èas";
const char INTL_SIGNAL_STRENGTH[] PROGMEM = "Síla signálu";
const char INTL_SIGNAL_QUALITY[] PROGMEM = "Kvalita signálu";
#define INTL_NUMBER_OF_MEASUREMENTS "Počet měření"
#define INTL_TIME_SENDING_MS "Poèet mìøení"
#define INTL_SENSOR "Modul"
#define INTL_PARAMETER "Parametr"
#define INTL_VALUE "Hodnota"

#include "./airrohr-logo-common.h"
