/*
 *  airRohr firmware
 *  Copyright (C) 2016-2021  Code for Stuttgart a.o.
 *  Copyright (C) 2021-2024  Sensor.Community a.o.
 *
 *  Latvian translation
 *
 *  tekstiem jābūt pēc iespējas īsākiem. 
 */

#define INTL_LANG "LV"
#define INTL_PM_SENSOR "Cieto daļiņu sensors"
const char INTL_CONFIGURATION[] PROGMEM = "Konfigurācija";
#define INTL_WIFI_SETTINGS "Wi-Fi iestatījumi"
#define INTL_WIFI_NETWORKS "Wifi tīklu ielāde ..."
#define INTL_LANGUAGE "Valoda"
const char INTL_NO_NETWORKS[] PROGMEM =  "Wi-Fi tīkls nav atrasts";
const char INTL_NETWORKS_FOUND[] PROGMEM = "Atrastie tīkli:";
const char INTL_AB_HIER_NUR_ANDERN[] PROGMEM = "Uzlabotie iestatījumi (tikai tad, ja zināt, ko darāt)";
const char INTL_SAVE[] PROGMEM = "Saglabāt";
const char INTL_SENSORS[] PROGMEM = "Sensori";
const char INTL_MORE_SENSORS[] PROGMEM = "Vairāk sensoru";
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
const char INTL_DNMS_CORRECTION[] PROGMEM = "korekcija dB(A)";
const char INTL_TEMP_CORRECTION[] PROGMEM = "Korekcija °C";
const char INTL_HEIGHT_ABOVE_SEALEVEL[] PROGMEM = "[[height_above_sealevel]]";
const char INTL_PRESSURE_AT_SEALEVEL[] PROGMEM = "[[pressure_at_sealevel]]";
const char INTL_NEO6M[] PROGMEM = "GPS (NEO 6M)";
const char INTL_BASICAUTH[] PROGMEM = "Autentifikācija";
const char INTL_NOPWD[] PROGMEM = "no WiFi password";
#define INTL_REPORT_ISSUE "Ziņot par problēmu"

const char INTL_FS_WIFI_DESCRIPTION[] PROGMEM = "WiFi sensors konfigurācijas režīmā";
const char INTL_FS_WIFI_NAME[] PROGMEM = "Tīkla nosaukums";
const char INTL_MORE_SETTINGS[] PROGMEM = "Vairāk iestatījumu";
const char INTL_AUTO_UPDATE[] PROGMEM = "Automātiska programmaparatūras atjaunināšana";
const char INTL_USE_BETA[] PROGMEM = "Ielādēt beta versijas programmaparatūru";
const char INTL_DISPLAY[] PROGMEM = "OLED SSD1306";
const char INTL_SH1106[] PROGMEM = "OLED SH1106";
const char INTL_FLIP_DISPLAY[] PROGMEM = "OLED displeja flip";
const char INTL_LCD1602_27[] PROGMEM = "LCD 1602 (I2C: 0x27)";
const char INTL_LCD1602_3F[] PROGMEM = "LCD 1602 (I2C: 0x3F)";
const char INTL_LCD2004_27[] PROGMEM = "LCD 2004 (I2C: 0x27)";
const char INTL_LCD2004_3F[] PROGMEM = "LCD 2004 (I2C: 0x3F)";
const char INTL_DISPLAY_WIFI_INFO[] PROGMEM = "Wifi informācijas rādīšana";
const char INTL_DISPLAY_DEVICE_INFO[] PROGMEM = "Parādīt informāciju par ierīci";

#define INTL_STATIC_IP_TEXT "[[static_ip_text]]"
const char INTL_STATIC_IP[] PROGMEM = "[[static_ip]]";
const char INTL_STATIC_SUBNET[] PROGMEM = "[[static_subnet]]";
const char INTL_STATIC_GATEWAY[] PROGMEM = "[[static_gateway]]";
const char INTL_STATIC_DNS[] PROGMEM = "[[static_dns]]";

const char INTL_DEBUG_LEVEL[] PROGMEM = "Debug&nbsp;līmenis";
const char INTL_MEASUREMENT_INTERVAL[] PROGMEM = "Mērīšanas intervāls (s)";
const char INTL_DURATION_ROUTER_MODE[] PROGMEM = "Ilgums maršrutētāja režīms";
const char INTL_POWERSAVE[] PROGMEM = "[[powersave]]";
const char INTL_MORE_APIS[] PROGMEM = "Vairāk API";
const char INTL_SEND_TO_OWN_API[] PROGMEM = "Datu nosūtīšana uz pielāgotu API";
const char INTL_SERVER[] PROGMEM = "Serveris";
const char INTL_PATH[] PROGMEM = "Ceļš";
const char INTL_PORT[] PROGMEM = "Osta";
const char INTL_USER[] PROGMEM = "Lietotājs";
const char INTL_PASSWORD[] PROGMEM = "Parole";
const char INTL_MEASUREMENT[] PROGMEM = "Mērījumi";
const char INTL_SEND_TO[] PROGMEM = "Nosūtīt uz {v}";
const char INTL_READ_FROM[] PROGMEM = "Lasīt no {v}";
const char INTL_SENSOR_IS_REBOOTING[] PROGMEM = "Sensors tiek restartēts.";
const char INTL_RESTART_DEVICE[] PROGMEM = "Ierīces restartēšana";
const char INTL_DELETE_CONFIG[] PROGMEM = "dzēst saglabāto konfigurāciju";
const char INTL_RESTART_SENSOR[] PROGMEM = "Sensora restartēšana";
#define INTL_HOME "Sākums"
#define INTL_BACK_TO_HOME "Atpakaļ uz sākumlapu"
const char INTL_CURRENT_DATA[] PROGMEM = "Pašreizējie dati";
const char INTL_DEVICE_STATUS[] PROGMEM = "Ierīces statuss";
#define INTL_ACTIVE_SENSORS_MAP "Aktīvo sensoru karte (ārējā saite)"
#define INTL_CONFIGURATION_DELETE "Konfigurācijas dzēšana"
#define INTL_CONFIGURATION_REALLY_DELETE "Vai esat pārliecināts, ka vēlaties izdzēst konfigurāciju?"
#define INTL_DELETE "Dzēst"
#define INTL_CANCEL "Atcelt"
#define INTL_REALLY_RESTART_SENSOR "Vai esat pārliecināts, ka vēlaties restartēt sensoru?"
#define INTL_RESTART "Restartējiet"
const char INTL_SAVE_AND_RESTART[] PROGMEM = "Konfigurācijas saglabāšana un restartēšana";
#define INTL_FIRMWARE "Programmatūras versija"
const char INTL_DEBUG_SETTING_TO[] PROGMEM = "Iestatiet atkļūdošanas līmeni uz";
#define INTL_NONE "izslēgts"
#define INTL_ERROR "tikai kļūdas"
#define INTL_WARNING "brīdinājumi"
#define INTL_MIN_INFO "min. informācija"
#define INTL_MED_INFO "vidējā informācija"
#define INTL_MAX_INFO "maksimālā informācija"
#define INTL_CONFIG_DELETED "Konfigurācija tika dzēsta"
#define INTL_CONFIG_CAN_NOT_BE_DELETED "Konfigurāciju nevar dzēst"
#define INTL_CONFIG_NOT_FOUND "Konfigurācija nav atrasta"
const char INTL_TIME_TO_FIRST_MEASUREMENT[] PROGMEM = "Vēl {v} sekundes līdz pirmajam mērījumam.";
const char INTL_TIME_SINCE_LAST_MEASUREMENT[] PROGMEM = " sekundes kopš pēdējā mērījuma.";
const char INTL_PARTICLES_PER_LITER[] PROGMEM = "daļiņu litrs";
const char INTL_PARTICULATE_MATTER[] PROGMEM = "cietās daļiņas";
const char INTL_TEMPERATURE[] PROGMEM = "temperatūra";
const char INTL_HUMIDITY[] PROGMEM = "mitrums";
const char INTL_PRESSURE[] PROGMEM = "gaisa spiediens";
const char INTL_DEW_POINT[] PROGMEM = "[[dew_point]]";
const char INTL_CO2_PPM[] PROGMEM = "ppm CO₂";
const char INTL_LEQ_A[] PROGMEM = "LAeq";
const char INTL_LA_MIN[] PROGMEM = "LA min";
const char INTL_LA_MAX[] PROGMEM = "LA max";
const char INTL_LATITUDE[] PROGMEM = "Platums";
const char INTL_LONGITUDE[] PROGMEM = "Ģeogrāfiskais garums";
const char INTL_ALTITUDE[] PROGMEM = "Augstums";
const char INTL_TIME_UTC[] PROGMEM = "Laiks (UTC)";
const char INTL_SIGNAL_STRENGTH[] PROGMEM = "signāla stiprums";
const char INTL_SIGNAL_QUALITY[] PROGMEM = "signāla kvalitāte";
#define INTL_NUMBER_OF_MEASUREMENTS "Mērījumu skaits"
#define INTL_TIME_SENDING_MS "Laiks, kas pavadīts, augšupielādējot"
#define INTL_SENSOR "Sensors"
#define INTL_PARAMETER "Parametrs"
#define INTL_VALUE "Vērtība"

#include "./airrohr-logo-common.h"
