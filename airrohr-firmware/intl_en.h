/*
 *	airRohr firmware
 *	Copyright (C) 2016-2018  Code for Stuttgart a.o.
 * 
 *  English translations
 * 
 *	Texts should be as short as possible
 *	We only have 512 kB for the entire firmware
 */

const char INTL_LANG[] = "EN";
const char INTL_FEINSTAUBSENSOR[] PROGMEM = "Particulate matter sensor";
const char INTL_KONFIGURATION[] PROGMEM = "Configuration";
const char INTL_WLAN_DATEN[] PROGMEM = "WiFi Settings";
const char INTL_WLAN_LISTE[] PROGMEM = "Loading wifi networks ...";
const char INTL_SPRACHE[] PROGMEM = "Language";
const char INTL_KEINE_NETZWERKE[] PROGMEM =  "No WiFi Network Found";
const char INTL_NETZWERKE_GEFUNDEN[] PROGMEM = "Found Networks: ";
const char INTL_AB_HIER_NUR_ANDERN[] PROGMEM = "Advanced settings (оnly if you know what you are doing)";
const char INTL_SPEICHERN[] PROGMEM = "Save";
const char INTL_SENSOREN[] PROGMEM = "Sensors";
const char INTL_SDS011[] PROGMEM = "SDS011 (particulate matter)";
const char INTL_PMS24[] PROGMEM = "PMS3003";
const char INTL_PMS32[] PROGMEM = "PMS1003, PMS5003, PMS6003, PMS7003";
const char INTL_HPM[] PROGMEM = "Honeywell PM sensor";
const char INTL_PPD42NS[] PROGMEM = "PPD42NS";
const char INTL_DHT22[] PROGMEM = "DHT22 ({t}, {h})";
const char INTL_HTU21D[] PROGMEM = "HTU21D ({t}, {h})";
const char INTL_BMP180[] PROGMEM = "BMP180 ({t}, {p})";
const char INTL_BMP280[] PROGMEM = "BMP280 ({t}, {p})";
const char INTL_BME280[] PROGMEM = "BME280 ({t}, {h}, {p})";
const char INTL_DS18B20[] PROGMEM = "DS18B20 ({t})";
const char INTL_NEO6M[] PROGMEM = "GPS (NEO 6M)";
const char INTL_BASICAUTH[] PROGMEM = "Authorization";
const char INTL_FS_WIFI[] PROGMEM = "WiFi Sensor";
const char INTL_FS_WIFI_BESCHREIBUNG[] PROGMEM = "WiFi Sensor in configuration mode";
const char INTL_FS_WIFI_NAME[] PROGMEM = "Name";
const char INTL_WEITERE_EINSTELLUNGEN[] PROGMEM ="More settings";
const char INTL_AUTO_UPDATE[] PROGMEM = "Auto update firmware";
const char INTL_USE_BETA[] PROGMEM = "Load beta firmware";
const char INTL_DISPLAY[] PROGMEM = "OLED SSD1306";
const char INTL_SH1106[] PROGMEM = "OLED SH1106";
const char INTL_LCD1602_27[] PROGMEM = "LCD 1602 (I2C: 0x27)";
const char INTL_LCD1602_3F[] PROGMEM = "LCD 1602 (I2C: 0x3F)";
const char INTL_LCD2004_27[] PROGMEM = "LCD 2004 (I2C: 0x27)";
const char INTL_DEBUG_LEVEL[] PROGMEM = "Debug&nbsp;Level";
const char INTL_MESSINTERVALL[] PROGMEM = "Measuring interval";
const char INTL_DAUER_ROUTERMODUS[] PROGMEM = "Duration router mode";
const char INTL_WEITERE_APIS[] PROGMEM = "More API";
const char INTL_AN_EIGENE_API_SENDEN[] PROGMEM = "Send data to own API";
const char INTL_SERVER[] PROGMEM = "Server"; 
const char INTL_PFAD[] PROGMEM = "Path"; 
const char INTL_PORT[] PROGMEM = "Port"; 
const char INTL_BENUTZER[] PROGMEM = "User"; 
const char INTL_PASSWORT[] PROGMEM = "Password"; 
const char INTL_SENDEN_AN[] PROGMEM = "Send to {v}"; 
const char INTL_LESE[] PROGMEM = "Read from {v}";
const char INTL_GERAT_WIRD_NEU_GESTARTET[] PROGMEM = "Sensor is rebooting.";
const char INTL_GERAT_NEU_STARTEN[] PROGMEM = "Restart device";
const char INTL_CONFIG_LOSCHEN[] PROGMEM = "delete saved configuration";
const char INTL_SENSOR_NEU_STARTEN[] PROGMEM = "Restart sensor";
const char INTL_UBERSICHT[] PROGMEM = "Home";
const char INTL_ZURUCK_ZUR_STARTSEITE[] PROGMEM = "Back to home page";
const char INTL_AKTUELLE_WERTE[] PROGMEM = "Current data";
const char INTL_KARTE_DER_AKTIVEN_SENSOREN[] PROGMEM = "Active sensors map(external link)";
const char INTL_KONFIGURATION_LOSCHEN[] PROGMEM = "Configuration delete";
const char INTL_KONFIGURATION_WIRKLICH_LOSCHEN[] PROGMEM = "Are you sure you want to delete the configuration?";
const char INTL_LOSCHEN[] PROGMEM = "Delete";
const char INTL_ABBRECHEN[] PROGMEM = "Cancel";
const char INTL_SENSOR_WIRKLICH_NEU_STARTEN[] PROGMEM = "Are you sure you want to restart the sensor?";
const char INTL_NEU_STARTEN[] PROGMEM = "Restart";
const char INTL_FIRMWARE[] PROGMEM = "Firmware version";
const char INTL_SETZE_DEBUG_AUF[] PROGMEM = "Debug setting to ";
const char INTL_NONE[] PROGMEM = "off";
const char INTL_ERROR[] PROGMEM = "only errors";
const char INTL_WARNING[] PROGMEM = "warnings";
const char INTL_MIN_INFO[] PROGMEM = "min. info";
const char INTL_MED_INFO[] PROGMEM = "mid. info";
const char INTL_MAX_INFO[] PROGMEM = "max. info";
const char INTL_CONFIG_GELOSCHT[] PROGMEM = "Configuration is deleted";
const char INTL_CONFIG_KONNTE_NICHT_GELOSCHT_WERDEN[] PROGMEM = "Configuration can not be deleted";
const char INTL_CONFIG_NICHT_GEFUNDEN[] PROGMEM = "Configuration not found";
const char INTL_ERSTER_MESSZYKLUS[] PROGMEM = "Still {v} seconds until first measurement.";
const char INTL_ZEIT_SEIT_LETZTER_MESSUNG[] PROGMEM = " seconds since last measurement.";
const char INTL_PARTIKEL_LITER[] PROGMEM = "particles/liter";
const char INTL_TEMPERATUR[] PROGMEM = "temperature";
const char INTL_LUFTFEUCHTE[] PROGMEM = "humidity";
const char INTL_LUFTDRUCK[] PROGMEM = "air pressure";
const char INTL_LATITUDE[] PROGMEM = "Latitude";
const char INTL_LONGITUDE[] PROGMEM = "Longitude";
const char INTL_ALTITUDE[] PROGMEM = "Altitude";
const char INTL_DATE[] PROGMEM = "Date";
const char INTL_TIME[] PROGMEM = "Time";
const char INTL_SIGNAL[] PROGMEM = "signal strength";
const char INTL_QUALITAT[] PROGMEM = "signal quality";
const char INTL_ANZAHL_MESSUNGEN[] PROGMEM = "Number of measurements:";
const char INTL_SENSOR[] PROGMEM = "Sensor";
const char INTL_PARAMETER[] PROGMEM = "Parameter";
const char INTL_WERT[] PROGMEM = "Value";

const char LUFTDATEN_INFO_LOGO_SVG[] PROGMEM = "<svg id=\"Layer_1\" xmlns=\"http://www.w3.org/2000/svg\" x=\"0px\" y=\"0px\" width=\"100px\" height=\"88.891px\" viewBox=\"0 0 100 88.891\" enable-background=\"new 0 0 100 88.891\"><path fill=\"#fff\" d=\"M90.28 66.57v.1H83.33c-2.04 0-3.7-1.66-3.7-3.7 0-2.05 1.66-3.7 3.7-3.7h5.56c2.03 0 3.7-1.67 3.7-3.7 0-2.06-1.67-3.72-3.7-3.72s-3.72-1.66-3.72-3.7c0-2.05 1.66-3.7 3.7-3.7.26 0 .5.02.75.07 5.8.4 10.37 5.15 10.37 11.04 0 5.66-4.24 10.32-9.72 11z\"/><path fill=\"#fff\" d=\"M70.37 44.44c-2.04 0-3.7-1.65-3.7-3.7 0-2.04 1.66-3.7 3.7-3.7.26 0 .5.02.75.07 5.78.4 10.36 5.17 10.36 11.05 0 5.66-4.24 10.33-9.72 11v.1H29.63c-2.04 0-3.7 1.67-3.7 3.7 0 2.06 1.65 3.72 3.7 3.72h42.14v.1c5.47.68 9.7 5.35 9.7 11 0 5.9-4.57 10.65-10.35 11.05-.25.04-.5.07-.75.07-2.04 0-3.7-1.67-3.7-3.7 0-2.06 1.66-3.72 3.7-3.72s3.7-1.66 3.7-3.7c0-2.05-1.66-3.7-3.7-3.7H28.23v-.1c-5.47-.7-9.7-5.35-9.7-11.02 0-1.95.53-3.76 1.42-5.35C8.35 53.6 0 42.6 0 29.64 0 13.27 13.27 0 29.63 0c11.12 0 20.8 6.13 25.86 15.2 1.22-.22 2.47-.38 3.76-.38 10.92 0 19.98 7.88 21.85 18.26-2.57-1.84-5.64-3.05-8.97-3.36-2.55-4.48-7.35-7.5-12.87-7.5-2.96 0-5.7.9-8.03 2.4-2.28-9.85-11.06-17.2-21.6-17.2C17.36 7.4 7.4 17.35 7.4 29.6c0 12.28 9.96 22.23 22.23 22.23h40.74c2.04 0 3.7-1.66 3.7-3.7 0-2.05-1.65-3.7-3.7-3.7z\"/></svg>";
