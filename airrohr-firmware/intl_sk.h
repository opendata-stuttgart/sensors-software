/*
 *	airRohr firmware
 *	Copyright (C) 2016-2018 Code for Stuttgart a.o.
 *
 *  Slovak translations
 *
 *	Texts should be as short as possible
 */

#define INTL_LANG "SK"
#define INTL_PM_SENSOR "Senzor prachových častíc"
const char INTL_CONFIGURATION[] PROGMEM = "Konfigurácia";
#define INTL_WIFI_SETTINGS "Nastavenie WiFi"
#define INTL_WIFI_NETWORKS "Vyhľadávanie WiFi sieti..."
#define INTL_LANGUAGE "Jazyk"
const char INTL_NO_NETWORKS[] PROGMEM = "Žiadne WiFi siete v dosahu.";
const char INTL_NETWORKS_FOUND[] PROGMEM = "Dostupné siete: ";
const char INTL_AB_HIER_NUR_ANDERN[] PROGMEM = "Pokročilé nastavenia (iba ak viete, čo robíte)";
const char INTL_SAVE[] PROGMEM = "Uložiť";
const char INTL_SENSORS[] PROGMEM = "Senzory (čidlá)";
const char INTL_MORE_SENSORS[] PROGMEM = "Ďalšie senzory (čidlá)";
const char INTL_SDS011[] PROGMEM = "SDS011 (modul {pm})";
const char INTL_PMS[] PROGMEM = "Plantower PMS(1,3,5,6,7)003 (modul {pm})";
const char INTL_HPM[] PROGMEM = "Honeywell PM ({pm})";
const char INTL_SPS30[] PROGMEM = "Sensirion SPS30 ({pm})";
const char INTL_PPD42NS[] PROGMEM = "PPD42NS ({pm})";
const char INTL_DHT22[] PROGMEM = "DHT22 ({t}, {h})";
const char INTL_HTU21D[] PROGMEM = "HTU21D ({t}, {h})";
const char INTL_BMP180[] PROGMEM = "BMP180 ({t}, {p})";
const char INTL_BMX280[] PROGMEM = "BME280 ({t}, {h}, {p}), BMP280 ({t}, {p})";
const char INTL_SHT3X[] PROGMEM = "SHT3X ({t}, {h})";
const char INTL_DS18B20[] PROGMEM = "DS18B20 ({t})";
const char INTL_DNMS[] PROGMEM = "DNMS ({l_a})";
const char INTL_DNMS_CORRECTION[] PROGMEM ="korekcia v dB(A)";
const char INTL_TEMP_CORRECTION[] PROGMEM = "korekcia v °C";
const char INTL_NEO6M[] PROGMEM = "GPS (NEO 6M)";
const char INTL_BASICAUTH[] PROGMEM = "Prihlásenie (heslom)";
#define INTL_REPORT_ISSUE "Report an issue"

const char INTL_FS_WIFI_DESCRIPTION[] PROGMEM = "WiFi modul v konfiguračnom móde";
const char INTL_FS_WIFI_NAME[] PROGMEM = "Názov siete";
const char INTL_MORE_SETTINGS[] PROGMEM = "Ďalšie nastavenia";
const char INTL_AUTO_UPDATE[] PROGMEM = "Auto. aktualizácia";
const char INTL_USE_BETA[] PROGMEM = "Nahrať betaverziu";
const char INTL_DISPLAY[] PROGMEM = "OLED SSD1306";
const char INTL_SH1106[] PROGMEM = "OLED SH1106";
const char INTL_FLIP_DISPLAY[] PROGMEM = "OLED displej flip";
const char INTL_LCD1602_27[] PROGMEM = "LCD 1602 (I2C: 0x27)";
const char INTL_LCD1602_3F[] PROGMEM = "LCD 1602 (I2C: 0x3F)";
const char INTL_LCD2004_27[] PROGMEM = "LCD 2004 (I2C: 0x27)";
const char INTL_LCD2004_3F[] PROGMEM = "LCD 2004 (I2C: 0x3F)";
const char INTL_DISPLAY_WIFI_INFO[] PROGMEM = "Zobraziť info o WiFi";
const char INTL_DISPLAY_DEVICE_INFO[] PROGMEM = "Zobraziť info o zariadení";
const char INTL_DEBUG_LEVEL[] PROGMEM = "Ladenide&nbsp;úroveň";
const char INTL_MEASUREMENT_INTERVAL[] PROGMEM = "Interval meraní (sec)";
const char INTL_DURATION_ROUTER_MODE[] PROGMEM = "Trvanie router mod";
const char INTL_MORE_APIS[] PROGMEM = "Dalšie API";
const char INTL_SEND_TO_OWN_API[] PROGMEM = "Poslať data na vlastné API";
const char INTL_SERVER[] PROGMEM = "Server";
const char INTL_PATH[] PROGMEM = "Cesta";
const char INTL_PORT[] PROGMEM = "Port";
const char INTL_USER[] PROGMEM = "Uživateľ";
const char INTL_PASSWORD[] PROGMEM = "Heslo";
const char INTL_MEASUREMENT[] PROGMEM = "Measurement";
const char INTL_SEND_TO[] PROGMEM = "Odoslať na {v}";
const char INTL_READ_FROM[] PROGMEM = "Čítaj z {v}";
const char INTL_SENSOR_IS_REBOOTING[] PROGMEM = "Senzor sa reštartuje";
const char INTL_RESTART_DEVICE[] PROGMEM = "Reštartovať zariadenie";
const char INTL_DELETE_CONFIG[] PROGMEM = "Zmazať uloženú konfiguráciu";
const char INTL_RESTART_SENSOR[] PROGMEM = "Reštart senzoru";
#define INTL_HOME "Úvod"
#define INTL_BACK_TO_HOME "Späť na úvodnú stránku"
const char INTL_CURRENT_DATA[] PROGMEM = "Aktuálne hodnoty";
const char INTL_DEVICE_STATUS[] PROGMEM = "Stav zariadenia";
#define INTL_ACTIVE_SENSORS_MAP "Mapa aktívnych senzorov (externý odkaz)"
#define INTL_CONFIGURATION_DELETE "Zmazať konfiguráciu?"
#define INTL_CONFIGURATION_REALLY_DELETE "Naozaj zmazať konfiguráciu?"
#define INTL_DELETE "Zmazať"
#define INTL_CANCEL "Zrušiť"
#define INTL_REALLY_RESTART_SENSOR "Naozaj reštartovať senzor?"
#define INTL_RESTART "Reštartovať"
const char INTL_SAVE_AND_RESTART[] PROGMEM = "Uložiť a reštartovať";
#define INTL_FIRMWARE "Firmware verzia"
const char INTL_DEBUG_SETTING_TO[] PROGMEM = "Ladenie nastavené na";
#define INTL_NONE "žiadny"
#define INTL_ERROR "chyba"
#define INTL_WARNING "varovanie"
#define INTL_MIN_INFO "min. info"
#define INTL_MED_INFO "str. info"
#define INTL_MAX_INFO "max. info"
#define INTL_CONFIG_DELETED "Konfigurácia zmazaná"
#define INTL_CONFIG_CAN_NOT_BE_DELETED "Konfigurácia nemohla byť zmazaná"
#define INTL_CONFIG_NOT_FOUND "Konfigurácia nenájdená"
const char INTL_TIME_TO_FIRST_MEASUREMENT[] PROGMEM = "Zostáva {v} sekúnd do prvého merania.";
const char INTL_TIME_SINCE_LAST_MEASUREMENT[] PROGMEM = " sekúnd od posledného merania.";
const char INTL_PARTICLES_PER_LITER[] PROGMEM = "častíc/liter";
const char INTL_PARTICULATE_MATTER[] PROGMEM = "prachových častíc";
const char INTL_TEMPERATURE[] PROGMEM = "teplota";
const char INTL_HUMIDITY[] PROGMEM = "rel. vlhkosť";
const char INTL_PRESSURE[] PROGMEM = "tlak vzduchu";
const char INTL_LEQ_A[] PROGMEM = "LAeq";
const char INTL_LA_MIN[] PROGMEM = "LA min";
const char INTL_LA_MAX[] PROGMEM = "LA max";
const char INTL_LATITUDE[] PROGMEM = "Zem. šírka";
const char INTL_LONGITUDE[] PROGMEM = "Zem. dĺžka";
const char INTL_ALTITUDE[] PROGMEM = "Nadm. výška";
const char INTL_TIME_UTC[] PROGMEM = "Čas (UTC)";
const char INTL_SIGNAL_STRENGTH[] PROGMEM = "sila signálu";
const char INTL_SIGNAL_QUALITY[] PROGMEM = "kvalita signálu";
#define INTL_NUMBER_OF_MEASUREMENTS "Počet meraní"
#define INTL_TIME_SENDING_MS "Trvanie odosielania dát"
#define INTL_SENSOR "Senzor"
#define INTL_PARAMETER "Parameter"
#define INTL_VALUE "Hodnota"

#include "./airrohr-logo-common.h"
