/*
 *  airRohr firmware
 *  Copyright (C) 2016-2021  Code for Stuttgart a.o.
 *  Copyright (C) 2021-2024  Sensor.Community a.o.
 * 
 *  Finnish translation
 * 
 *	Texts should be as short as possible
 */

#define INTL_LANG "FI"
#define INTL_PM_SENSOR "Hiukkasanturi"
const char INTL_CONFIGURATION[] PROGMEM = "Konfigurointi";
#define INTL_WIFI_SETTINGS "WiFi-asetukset"
#define INTL_WIFI_NETWORKS "Wlan-verkkojen lataaminen ..."
#define INTL_LANGUAGE "Kieli"
const char INTL_NO_NETWORKS[] PROGMEM =  "WiFi-verkkoa ei löydy";
const char INTL_NETWORKS_FOUND[] PROGMEM = "Löydetyt verkostot:";
const char INTL_AB_HIER_NUR_ANDERN[] PROGMEM = "Lisäasetukset (vain jos tiedät, mitä teet)";
const char INTL_SAVE[] PROGMEM = "Tallenna";
const char INTL_SENSORS[] PROGMEM = "Anturit";
const char INTL_MORE_SENSORS[] PROGMEM = "Lisää antureita";
const char INTL_SDS011[] PROGMEM = "SDS011 ({pm})";
const char INTL_PMS[] PROGMEM = "Plantower PMS(1,3,5,6,7)003 ({pm})";
const char INTL_HPM[] PROGMEM = "Honeywell PM ({pm})";
const char INTL_NPM[] PROGMEM = "Tera Sensor Seuraava PM ({pm})";
const char INTL_NPM_FULLTIME[] PROGMEM = "Next PM fulltime";
const char INTL_IPS[] PROGMEM = "Piera Systems IPS-7100 ({pm})";
const char INTL_SPS30[] PROGMEM = "Sensirion SPS30 ({pm})";
const char INTL_PPD42NS[] PROGMEM = "PPD42NS ({pm})";
const char INTL_DHT22[] PROGMEM = "DHT22 ({t}, {h})";
const char INTL_HTU21D[] PROGMEM = "HTU21D ({t}, {h})";
const char INTL_BMP180[] PROGMEM = "BMP180 ({t}, {p})";
const char INTL_BMX280[] PROGMEM = "BME280 ({t}, {h}, {p}), BMP280 ({t}, {p}).";
const char INTL_SHT3X[] PROGMEM = "SHT3X ({t}, {h})";
const char INTL_SCD30[] PROGMEM = "SCD30 ({t}, {h}, CO₂)";
const char INTL_DS18B20[] PROGMEM = "DS18B20 ({t})";
const char INTL_DNMS[] PROGMEM = "DNMS ({l_a})";
const char INTL_DNMS_CORRECTION[] PROGMEM = "korjaus dB(A)";
const char INTL_TEMP_CORRECTION[] PROGMEM = "Korjaus °C:ssa";
const char INTL_HEIGHT_ABOVE_SEALEVEL[] PROGMEM = "[[height_above_sealevel]]";
const char INTL_PRESSURE_AT_SEALEVEL[] PROGMEM = "[[pressure_at_sealevel]]";
const char INTL_NEO6M[] PROGMEM = "GPS (NEO 6M)";
const char INTL_BASICAUTH[] PROGMEM = "Tunnistus";
#define INTL_REPORT_ISSUE "Ilmoita asiasta"

const char INTL_FS_WIFI_DESCRIPTION[] PROGMEM = "WiFi Sensor konfigurointitilassa";
const char INTL_FS_WIFI_NAME[] PROGMEM = "Verkon nimi";
const char INTL_MORE_SETTINGS[] PROGMEM = "Lisää asetuksia";
const char INTL_AUTO_UPDATE[] PROGMEM = "Automaattinen laiteohjelmiston päivitys";
const char INTL_USE_BETA[] PROGMEM = "Lataa beta-firmware";
const char INTL_DISPLAY[] PROGMEM = "OLED SSD1306";
const char INTL_SH1106[] PROGMEM = "OLED SH1106";
const char INTL_FLIP_DISPLAY[] PROGMEM = "OLED-näytön kääntäminen";
const char INTL_LCD1602_27[] PROGMEM = "LCD 1602 (I2C: 0x27)";
const char INTL_LCD1602_3F[] PROGMEM = "LCD 1602 (I2C: 0x3F)";
const char INTL_LCD2004_27[] PROGMEM = "LCD 2004 (I2C: 0x27)";
const char INTL_LCD2004_3F[] PROGMEM = "LCD 2004 (I2C: 0x3F)";
const char INTL_DISPLAY_WIFI_INFO[] PROGMEM = "Näytä Wifi tiedot";
const char INTL_DISPLAY_DEVICE_INFO[] PROGMEM = "Näytä laitteen tiedot";

#define INTL_STATIC_IP_TEXT "[[static_ip_text]]"
const char INTL_STATIC_IP[] PROGMEM = "[[static_ip]]";
const char INTL_STATIC_SUBNET[] PROGMEM = "[[static_subnet]]";
const char INTL_STATIC_GATEWAY[] PROGMEM = "[[static_gateway]]";
const char INTL_STATIC_DNS[] PROGMEM = "[[static_dns]]";

const char INTL_DEBUG_LEVEL[] PROGMEM = "Debug&nbsp;taso";
const char INTL_MEASUREMENT_INTERVAL[] PROGMEM = "Mittausväli (sek)";
const char INTL_DURATION_ROUTER_MODE[] PROGMEM = "Reititintilan kesto";
const char INTL_POWERSAVE[] PROGMEM = "[[powersave]]";
const char INTL_MORE_APIS[] PROGMEM = "Lisää sovellusrajapintoja";
const char INTL_SEND_TO_OWN_API[] PROGMEM = "Tietojen lähettäminen mukautettuun API:han";
const char INTL_SERVER[] PROGMEM = "Palvelin";
const char INTL_PATH[] PROGMEM = "Polku";
const char INTL_PORT[] PROGMEM = "Satama";
const char INTL_USER[] PROGMEM = "Käyttäjä";
const char INTL_PASSWORD[] PROGMEM = "Salasana";
const char INTL_MEASUREMENT[] PROGMEM = "Mittaus";
const char INTL_SEND_TO[] PROGMEM = "Lähetä osoitteeseen {v}";
const char INTL_READ_FROM[] PROGMEM = "Lue {v}";
const char INTL_SENSOR_IS_REBOOTING[] PROGMEM = "Anturi käynnistyy uudelleen.";
const char INTL_RESTART_DEVICE[] PROGMEM = "Käynnistä laite uudelleen";
const char INTL_DELETE_CONFIG[] PROGMEM = "poista tallennettu konfiguraatio";
const char INTL_RESTART_SENSOR[] PROGMEM = "Käynnistä anturi uudelleen";
#define INTL_HOME "Etusivu"
#define INTL_BACK_TO_HOME "Takaisin etusivulle"
const char INTL_CURRENT_DATA[] PROGMEM = "Nykyiset tiedot";
const char INTL_DEVICE_STATUS[] PROGMEM = "Laitteen tila";
#define INTL_ACTIVE_SENSORS_MAP "Aktiivisten antureiden kartta (ulkoinen linkki)"
#define INTL_CONFIGURATION_DELETE "Poista kokoonpano"
#define INTL_CONFIGURATION_REALLY_DELETE "Oletko varma, että haluat poistaa kokoonpanon?"
#define INTL_DELETE "Poista"
#define INTL_CANCEL "Peruuta"
#define INTL_REALLY_RESTART_SENSOR "Oletko varma, että haluat käynnistää anturin uudelleen?"
#define INTL_RESTART "Käynnistä uudelleen"
const char INTL_SAVE_AND_RESTART[] PROGMEM = "Tallenna kokoonpano ja käynnistä uudelleen";
#define INTL_FIRMWARE "Firmware-versio"
const char INTL_DEBUG_SETTING_TO[] PROGMEM = "Aseta debug-tasoksi";
#define INTL_NONE "off"
#define INTL_ERROR "vain virheet"
#define INTL_WARNING "varoitukset"
#define INTL_MIN_INFO "min. info"
#define INTL_MED_INFO "mid. info"
#define INTL_MAX_INFO "max. info"
#define INTL_CONFIG_DELETED "Konfiguraatio poistettiin"
#define INTL_CONFIG_CAN_NOT_BE_DELETED "Konfiguraatiota ei voi poistaa"
#define INTL_CONFIG_NOT_FOUND "Konfiguraatiota ei löydy"
const char INTL_TIME_TO_FIRST_MEASUREMENT[] PROGMEM = "Vielä {v} sekuntia ensimmäiseen mittaukseen.";
const char INTL_TIME_SINCE_LAST_MEASUREMENT[] PROGMEM = " sekuntia edellisestä mittauksesta.";
const char INTL_PARTICLES_PER_LITER[] PROGMEM = "hiukkaslitra";
const char INTL_PARTICULATE_MATTER[] PROGMEM = "hiukkaset";
const char INTL_TEMPERATURE[] PROGMEM = "lämpötila";
const char INTL_HUMIDITY[] PROGMEM = "kosteus";
const char INTL_PRESSURE[] PROGMEM = "ilmanpaine";
const char INTL_DEW_POINT[] PROGMEM = "[[dew_point]]";
const char INTL_CO2_PPM[] PROGMEM = "ppm CO₂";
const char INTL_LEQ_A[] PROGMEM = "LAeq";
const char INTL_LA_MIN[] PROGMEM = "LA min";
const char INTL_LA_MAX[] PROGMEM = "LA max";
const char INTL_LATITUDE[] PROGMEM = "Leveysaste";
const char INTL_LONGITUDE[] PROGMEM = "Pituusaste";
const char INTL_ALTITUDE[] PROGMEM = "Korkeus";
const char INTL_TIME_UTC[] PROGMEM = "Aika (UTC)";
const char INTL_SIGNAL_STRENGTH[] PROGMEM = "signaalin voimakkuus";
const char INTL_SIGNAL_QUALITY[] PROGMEM = "signaalin laatu";
#define INTL_NUMBER_OF_MEASUREMENTS "Mittausten lukumäärä"
#define INTL_TIME_SENDING_MS "Lataamiseen käytetty aika"
#define INTL_SENSOR "Anturi"
#define INTL_PARAMETER "Parametri"
#define INTL_VALUE "Arvo"

#include "./airrohr-logo-common.h"
