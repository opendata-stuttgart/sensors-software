/*
 *	airRohr firmware
 *	Copyright (C) 2016-2018  Code for Stuttgart a.o.
 * 
 *  German translations
 * 
 *	Texts should be as short as possible
 *	We only have 512 kB for the entire firmware
 */

const char INTL_LANG[] = "DE";
const char INTL_PM_SENSOR[] PROGMEM = "Feinstaubsensor";
const char INTL_CONFIGURATION[] PROGMEM = "Konfiguration";
const char INTL_WIFI_SETTINGS[] PROGMEM = "WLAN Daten";
const char INTL_WIFI_NETWORKS[] PROGMEM = "Lade WLAN Netzwerke ...";
const char INTL_LANGUAGE[] PROGMEM = "Sprache";
const char INTL_NO_NETWORKS[] PROGMEM =  "Keine Netzwerke gefunden";
const char INTL_NETWORKS_FOUND[] PROGMEM = "Netzwerke gefunden: ";
const char INTL_AB_HIER_NUR_ANDERN[] PROGMEM = "Ab hier nur ändern, wenn Sie wirklich wissen, was Sie tun";
const char INTL_SAVE[] PROGMEM = "Speichern";
const char INTL_SENSORS[] PROGMEM = "Sensoren";
const char INTL_SDS011[] PROGMEM = "SDS011 ({pm})";
const char INTL_PMS[] PROGMEM = "Plantower PMS(1,3,5,6,7)003 ({pm})";
const char INTL_HPM[] PROGMEM = "Honeywell PM sensor";
const char INTL_SPS30[] PROGMEM = "Sensirion SPS30 ({pm})";
const char INTL_PPD42NS[] PROGMEM = "PPD42NS";
const char INTL_DHT22[] PROGMEM = "DHT22 ({t}, {h})";
const char INTL_HTU21D[] PROGMEM = "HTU21D ({t}, {h})";
const char INTL_BMP180[] PROGMEM = "BMP180 ({t}, {p})";
const char INTL_BMX280[] PROGMEM = "BMP280/BME280 ({t}, {h}, {p})";
const char INTL_DS18B20[] PROGMEM = "DS18B20 ({t})";
const char INTL_DNMS[] PROGMEM = "DNMS ({l_a})";
const char INTL_DNMS_CORRECTION[] PROGMEM ="Korrekturwert in dB(A)";
const char INTL_NEO6M[] PROGMEM = "GPS (NEO 6M)";
const char INTL_BASICAUTH[] PROGMEM = "BasicAuth aktivieren";
const char INTL_FS_WIFI[] PROGMEM = "Sensor WLAN";
const char INTL_FS_WIFI_DESCRIPTION[] PROGMEM = "Sensor WLAN Name im Konfigurationsmodus";
const char INTL_FS_WIFI_NAME[] PROGMEM = "Name";
const char INTL_MORE_SETTINGS[] PROGMEM ="Weitere Einstellungen";
const char INTL_AUTO_UPDATE[] PROGMEM = "Auto Update";
const char INTL_USE_BETA[] PROGMEM = "Lade Beta Versionen";
const char INTL_DISPLAY[] PROGMEM = "OLED SSD1306";
const char INTL_SH1106[] PROGMEM = "OLED SH1106";
const char INTL_FLIP_DISPLAY[] PROGMEM = "OLED Display um 180° drehen";
const char INTL_LCD1602_27[] PROGMEM = "LCD 1602 (I2C: 0x27)";
const char INTL_LCD1602_3F[] PROGMEM = "LCD 1602 (I2C: 0x3F)";
const char INTL_LCD2004_27[] PROGMEM = "LCD 2004 (I2C: 0x27)";
const char INTL_DISPLAY_WIFI_INFO[] PROGMEM = "Zeige WiFi Info";
const char INTL_DISPLAY_DEVICE_INFO[] PROGMEM = "Zeige Geräteinfo";
const char INTL_DEBUG_LEVEL[] PROGMEM = "Debug&nbsp;Level";
const char INTL_MEASUREMENT_INTERVAL[] PROGMEM = "Messintervall";
const char INTL_DURATION_ROUTER_MODE[] PROGMEM = "Dauer&nbsp;Routermodus";
const char INTL_MORE_APIS[] PROGMEM = "Weitere APIs";
const char INTL_SEND_TO_OWN_API[] PROGMEM = "An eigene API senden";
const char INTL_SERVER[] PROGMEM = "Server"; 
const char INTL_PATH[] PROGMEM = "Pfad"; 
const char INTL_PORT[] PROGMEM = "Port"; 
const char INTL_USER[] PROGMEM = "Benutzer"; 
const char INTL_PASSWORD[] PROGMEM = "Passwort"; 
const char INTL_SEND_TO[] PROGMEM = "Senden an {v}"; 
const char INTL_READ_FROM[] PROGMEM = "Lese {v}";
const char INTL_SENSOR_IS_REBOOTING[] PROGMEM = "Sensor wird neu gestartet.";
const char INTL_RESTART_DEVICE[] PROGMEM = "Gerät neu starten";
const char INTL_DELETE_CONFIG[] PROGMEM = "Config.json löschen";
const char INTL_RESTART_SENSOR[] PROGMEM = "Sensor neu starten";
const char INTL_HOME[] PROGMEM = "Übersicht";
const char INTL_BACK_TO_HOME[] PROGMEM = "Zurück zur Startseite";
const char INTL_CURRENT_DATA[] PROGMEM = "Aktuelle Werte";
const char INTL_ACTIVE_SENSORS_MAP[] PROGMEM = "Karte der aktiven Sensoren (externer Link)";
const char INTL_CONFIGURATION_DELETE[] PROGMEM = "Konfiguration löschen";
const char INTL_CONFIGURATION_REALLY_DELETE[] PROGMEM = "Konfiguration wirklich löschen?";
const char INTL_DELETE[] PROGMEM = "Löschen";
const char INTL_CANCEL[] PROGMEM = "Abbrechen";
const char INTL_REALLY_RESTART_SENSOR[] PROGMEM = "Sensor wirklich neu starten?";
const char INTL_RESTART[] PROGMEM = "Neu starten";
const char INTL_SAVE_AND_RESTART[] PROGMEM = "Speichern und neu starten";
const char INTL_FIRMWARE[] PROGMEM = "Firmware";
const char INTL_DEBUG_SETTING_TO[] PROGMEM = "Setze Debug auf";
const char INTL_NONE[] PROGMEM = "none";
const char INTL_ERROR[] PROGMEM = "error";
const char INTL_WARNING[] PROGMEM = "warning";
const char INTL_MIN_INFO[] PROGMEM = "min. info";
const char INTL_MED_INFO[] PROGMEM = "med. info";
const char INTL_MAX_INFO[] PROGMEM = "max. info";
const char INTL_CONFIG_DELETED[] PROGMEM = "Config.json gelöscht";
const char INTL_CONFIG_CAN_NOT_BE_DELETED[] PROGMEM = "Config.json konnte nicht gelöscht werden";
const char INTL_CONFIG_NOT_FOUND[] PROGMEM = "Config.json nicht gefunden";
const char INTL_TIME_TO_FIRST_MEASUREMENT[] PROGMEM = "Noch {v} Sekunden bis zur ersten Messung.";
const char INTL_TIME_SINCE_LAST_MEASUREMENT[] PROGMEM = " Sekunden seit der letzten Messung.";
const char INTL_PARTICLES_PER_LITER[] PROGMEM = "Partikel/Liter";
const char INTL_PARTICULATE_MATTER[] PROGMEM = "Feinstaub";
const char INTL_TEMPERATURE[] PROGMEM = "Temperatur";
const char INTL_HUMIDITY[] PROGMEM = "rel. Luftfeuchte";
const char INTL_PRESSURE[] PROGMEM = "Luftdruck";
const char INTL_LEQ_A[] PROGMEM = "LAeq";
const char INTL_LA_MIN[] PROGMEM = "LA min";
const char INTL_LA_MAX[] PROGMEM = "LA max";
const char INTL_LATITUDE[] PROGMEM = "Breite";
const char INTL_LONGITUDE[] PROGMEM = "Länge";
const char INTL_ALTITUDE[] PROGMEM = "Höhe";
const char INTL_DATE[] PROGMEM = "Datum";
const char INTL_TIME[] PROGMEM = "Zeit";
const char INTL_SIGNAL_STRENGTH[] PROGMEM = "Signal";
const char INTL_SIGNAL_QUALITY[] PROGMEM = "Qualität";
const char INTL_NUMBER_OF_MEASUREMENTS[] PROGMEM = "Anzahl Messungen:";
const char INTL_SENSOR[] PROGMEM = "Sensor";
const char INTL_PARAMETER[] PROGMEM = "Parameter";
const char INTL_VALUE[] PROGMEM = "Wert";

#include "./airrohr-logo-common.h"
