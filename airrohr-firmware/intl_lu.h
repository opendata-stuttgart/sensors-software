/*
 *	airRohr firmware
 *	Copyright (C) 2016-2018  Code for Stuttgart a.o.
 * 
 *  Luxembourgish translations
 * 
 *	Texts should be as short as possible
 *	We only have 512 kB for the entire firmware
 */

const char INTL_LANG[] = "LU";
const char INTL_PM_SENSOR[] PROGMEM = "Reng Stëbspartikelensensor";
const char INTL_CONFIGURATION[] PROGMEM = "Konfiguratioun";
const char INTL_WIFI_SETTINGS[] PROGMEM = "WiFi Daten";
const char INTL_WIFI_NETWORKS[] PROGMEM = "WiFi Netzwierker lueden ...";
const char INTL_LANGUAGE[] PROGMEM = "Sprooch";
const char INTL_NO_NETWORKS[] PROGMEM =  "Keng Netzwierker fonnt";
const char INTL_NETWORKS_FOUND[] PROGMEM = "Netzwierker fonnt: ";
const char INTL_AB_HIER_NUR_ANDERN[] PROGMEM = "Ab hei nëmmen änneren, wann der wësst wat dir maacht";
const char INTL_SAVE[] PROGMEM = "Späicheren";
const char INTL_SENSORS[] PROGMEM = "Sensoren";
const char INTL_SDS011[] PROGMEM = "SDS011 ({pm})";
const char INTL_PMS[] PROGMEM = "Plantower PMS(1,3,5,6,7)003 ({pm})";
const char INTL_HPM[] PROGMEM = "Honeywell PM sensor";
const char INTL_SPS30[] PROGMEM = "Sensirion SPS30 ({pm})";
const char INTL_PPD42NS[] PROGMEM = "PPD42NS";
const char INTL_DHT22[] PROGMEM = "DHT22 ({t}, {h})";
const char INTL_HTU21D[] PROGMEM = "HTU21D ({t}, {h})";
const char INTL_BMP180[] PROGMEM = "BMP180 ({t}, {p})";
const char INTL_BMP280[] PROGMEM = "BMP280 ({t}, {p})";
const char INTL_BME280[] PROGMEM = "BME280 ({t}, {h}, {p})";
const char INTL_DS18B20[] PROGMEM = "DS18B20 ({t})";
const char INTL_DNMS[] PROGMEM = "DNMS ({l_a})";
const char INTL_DNMS_CORRECTION[] PROGMEM ="";
const char INTL_NEO6M[] PROGMEM = "GPS (NEO 6M)";
const char INTL_MHZ19[] PROGMEM = "MH-Z19 (CO₂)";
const char INTL_BASICAUTH[] PROGMEM = "BasicAuth aktivéieren";
const char INTL_FS_WIFI[] PROGMEM = "WiFi Sensor";
const char INTL_FS_WIFI_DESCRIPTION[] PROGMEM = "WiFi Sensor Numm am Konfiguratiounsmodus";
const char INTL_FS_WIFI_NAME[] PROGMEM = "Numm";
const char INTL_MORE_SETTINGS[] PROGMEM ="Méi Astellungen";
const char INTL_AUTO_UPDATE[] PROGMEM = "Automateschen Update";
const char INTL_USE_BETA[] PROGMEM = "Beta Versiounen eroflueden";
const char INTL_DISPLAY[] PROGMEM = "OLED SSD1306";
const char INTL_SH1106[] PROGMEM = "OLED SH1106";
const char INTL_FLIP_DISPLAY[] PROGMEM = "";
const char INTL_LCD1602_27[] PROGMEM = "LCD 1602 (I2C: 0x27)";
const char INTL_LCD1602_3F[] PROGMEM = "LCD 1602 (I2C: 0x3F)";
const char INTL_LCD2004_27[] PROGMEM = "LCD 2004 (I2C: 0x27)";
const char INTL_DISPLAY_WIFI_INFO[] PROGMEM = "";
const char INTL_DISPLAY_DEVICE_INFO[] PROGMEM = "";
const char INTL_DEBUG_LEVEL[] PROGMEM = "Debug Niveau";
const char INTL_MEASUREMENT_INTERVAL[] PROGMEM = "Mooss-intervall";
const char INTL_DURATION_ROUTER_MODE[] PROGMEM = "Zait&nbsp;Routermodus";
const char INTL_MORE_APIS[] PROGMEM = "Aner APIs";
const char INTL_SEND_TO_OWN_API[] PROGMEM = "Un eegen API schécken";
const char INTL_SERVER[] PROGMEM = "Server"; 
const char INTL_PATH[] PROGMEM = "Wee"; 
const char INTL_PORT[] PROGMEM = "Port"; 
const char INTL_USER[] PROGMEM = "Benotzer"; 
const char INTL_PASSWORD[] PROGMEM = "Passwuert"; 
const char INTL_SEND_TO[] PROGMEM = "Schécken op {v}"; 
const char INTL_READ_FROM[] PROGMEM = "Liesen {v}";
const char INTL_SENSOR_IS_REBOOTING[] PROGMEM = "De Sensor gëtt neigestart.";
const char INTL_RESTART_DEVICE[] PROGMEM = "Apparat nei starten";
const char INTL_DELETE_CONFIG[] PROGMEM = "Config.json läschen";
const char INTL_RESTART_SENSOR[] PROGMEM = "Sensor nei starten";
const char INTL_HOME[] PROGMEM = "Iwwersiicht";
const char INTL_BACK_TO_HOME[] PROGMEM = "Zréck op d'Haaptsäit";
const char INTL_CURRENT_DATA[] PROGMEM = "Aktuell Wäerter";
const char INTL_ACTIVE_SENSORS_MAP[] PROGMEM = "Kaart vun den aktive Sensoren (externen Link)";
const char INTL_CONFIGURATION_DELETE[] PROGMEM = "Konfiguratioun läschen";
const char INTL_CONFIGURATION_REALLY_DELETE[] PROGMEM = "Konfiguratioun wierklech läschen?";
const char INTL_DELETE[] PROGMEM = "Läschen";
const char INTL_CANCEL[] PROGMEM = "Ofbriechen";
const char INTL_REALLY_RESTART_SENSOR[] PROGMEM = "Sensor wierklech nei starten?";
const char INTL_RESTART[] PROGMEM = "Nei starten";
const char INTL_SAVE_AND_RESTART[] PROGMEM = "Späicheren a nei starten";
const char INTL_FIRMWARE[] PROGMEM = "Firmware";
const char INTL_DEBUG_SETTING_TO[] PROGMEM = "Debug setzen op";
const char INTL_NONE[] PROGMEM = "keng";
const char INTL_ERROR[] PROGMEM = "fehler";
const char INTL_WARNING[] PROGMEM = "warnung";
const char INTL_MIN_INFO[] PROGMEM = "min. info";
const char INTL_MED_INFO[] PROGMEM = "med. info";
const char INTL_MAX_INFO[] PROGMEM = "max. info";
const char INTL_CONFIG_DELETED[] PROGMEM = "Config.json geläscht";
const char INTL_CONFIG_CAN_NOT_BE_DELETED[] PROGMEM = "Config.json konnt net geläscht ginn";
const char INTL_CONFIG_NOT_FOUND[] PROGMEM = "Config.json net fonnt";
const char INTL_TIME_TO_FIRST_MEASUREMENT[] PROGMEM = "Nach {v} Sekonnen bis zur éischter Miessung.";
const char INTL_TIME_SINCE_LAST_MEASUREMENT[] PROGMEM = " Sekonnen zanter der leschter Miessung.";
const char INTL_PARTICLES_PER_LITER[] PROGMEM = "Partikel/Liter";
const char INTL_PARTICULATE_MATTER[] PROGMEM = "Reng Stëbspartikelen";
const char INTL_TEMPERATURE[] PROGMEM = "Temperatur";
const char INTL_HUMIDITY[] PROGMEM = "rel. Loftfiichtegkeet";
const char INTL_PRESSURE[] PROGMEM = "Loftdrock";
const char INTL_LEQ_A[] PROGMEM = "LAeq";
const char INTL_LA_MIN[] PROGMEM = "LA min";
const char INTL_LA_MAX[] PROGMEM = "LA max";
const char INTL_LATITUDE[] PROGMEM = "Breedegrad";
const char INTL_LONGITUDE[] PROGMEM = "Längtegrad";
const char INTL_ALTITUDE[] PROGMEM = "Héicht";
const char INTL_CO2[] PROGMEM = "Kuelendioxid";
const char INTL_DATE[] PROGMEM = "Datum";
const char INTL_TIME[] PROGMEM = "Zäit";
const char INTL_SIGNAL_STRENGTH[] PROGMEM = "Signal";
const char INTL_SIGNAL_QUALITY[] PROGMEM = "Qualitéit";
const char INTL_NUMBER_OF_MEASUREMENTS[] PROGMEM = "Zuel vu Mesuren:";
const char INTL_SENSOR[] PROGMEM = "Sensor";
const char INTL_PARAMETER[] PROGMEM = "Parameter";
const char INTL_VALUE[] PROGMEM = "Wäert";

const char LUFTDATEN_INFO_LOGO_SVG[] PROGMEM = "<svg id=\"Layer_1\" xmlns=\"http://www.w3.org/2000/svg\" x=\"0px\" y=\"0px\" width=\"100px\" height=\"88.891px\" viewBox=\"0 0 100 88.891\" enable-background=\"new 0 0 100 88.891\"><path fill=\"#fff\" d=\"M90.28 66.57v.1H83.33c-2.04 0-3.7-1.66-3.7-3.7 0-2.05 1.66-3.7 3.7-3.7h5.56c2.03 0 3.7-1.67 3.7-3.7 0-2.06-1.67-3.72-3.7-3.72s-3.72-1.66-3.72-3.7c0-2.05 1.66-3.7 3.7-3.7.26 0 .5.02.75.07 5.8.4 10.37 5.15 10.37 11.04 0 5.66-4.24 10.32-9.72 11z\"/><path fill=\"#fff\" d=\"M70.37 44.44c-2.04 0-3.7-1.65-3.7-3.7 0-2.04 1.66-3.7 3.7-3.7.26 0 .5.02.75.07 5.78.4 10.36 5.17 10.36 11.05 0 5.66-4.24 10.33-9.72 11v.1H29.63c-2.04 0-3.7 1.67-3.7 3.7 0 2.06 1.65 3.72 3.7 3.72h42.14v.1c5.47.68 9.7 5.35 9.7 11 0 5.9-4.57 10.65-10.35 11.05-.25.04-.5.07-.75.07-2.04 0-3.7-1.67-3.7-3.7 0-2.06 1.66-3.72 3.7-3.72s3.7-1.66 3.7-3.7c0-2.05-1.66-3.7-3.7-3.7H28.23v-.1c-5.47-.7-9.7-5.35-9.7-11.02 0-1.95.53-3.76 1.42-5.35C8.35 53.6 0 42.6 0 29.64 0 13.27 13.27 0 29.63 0c11.12 0 20.8 6.13 25.86 15.2 1.22-.22 2.47-.38 3.76-.38 10.92 0 19.98 7.88 21.85 18.26-2.57-1.84-5.64-3.05-8.97-3.36-2.55-4.48-7.35-7.5-12.87-7.5-2.96 0-5.7.9-8.03 2.4-2.28-9.85-11.06-17.2-21.6-17.2C17.36 7.4 7.4 17.35 7.4 29.6c0 12.28 9.96 22.23 22.23 22.23h40.74c2.04 0 3.7-1.66 3.7-3.7 0-2.05-1.65-3.7-3.7-3.7z\"/></svg>";

/* const char LUFTDATEN_INFO_LOGO_SVG[] PROGMEM = "<svg viewBox=\"0 0 350 350\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\
<defs><path id=\"d\" d=\"m284.38 273.35v-62.5c-1.77-23.65-9.32-42.14-22.65-55.48-13.33-13.33-30.76-20.88-52.27-22.64h-34.46-29.37c-24.67 2.77-43.66 10.82-57 24.16-13.33 13.33-21 31.32-23 53.96v62.5\"/><path id=\"c\" d=\"m177.6 188.56v-112 112z\"/><path id=\"a\" d=\"m171.92 76.73c5.82 0 10.53 4.71 10.53 10.52v90.95c0 5.82-4.71 10.53-10.53 10.53h-17.2c-5.82 0-10.53-4.71-10.53-10.53v-90.95c0-5.81 4.71-10.52 10.53-10.52h17.2z\"/><path id=\"e\" d=\"m228.81 248.48h112-112z\"/><path id=\"b\" d=\"m340.81 243.19c0 5.82-4.71 10.53-10.52 10.53h-90.95c-5.81 0-10.53-4.71-10.53-10.53v-17.21c0-5.81 4.72-10.52 10.53-10.52h90.95c5.81 0 10.52 4.71 10.52 10.52v17.21z\"/></defs>\
<use fill-opacity=\"0\" stroke=\"#c0c0c0\" stroke-width=\"100\" xlink:href=\"#d\"/><use fill-opacity=\"0\" stroke=\"#c0c0c0\" stroke-width=\"50\" xlink:href=\"#c\"/><use fill=\"#c0c0c0\" xlink:href=\"#a\"/><use fill-opacity=\"0\" stroke=\"#c0c0c0\" stroke-width=\"50\" xlink:href=\"#e\"/><use fill=\"#c0c0c0\" xlink:href=\"#b\"/>\
</svg>";
*/
