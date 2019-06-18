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
const char INTL_PM_SENSOR[] PROGMEM = "Fijnstofsensor";
const char INTL_CONFIGURATION[] PROGMEM = "Configuratie";
const char INTL_WIFI_SETTINGS[] PROGMEM = "WiFi-instellingen";
const char INTL_WIFI_NETWORKS[] PROGMEM = "Zoeken naar WiFi-netwerken ...";
const char INTL_LANGUAGE[] PROGMEM = "Taal";
const char INTL_NO_NETWORKS[] PROGMEM =  "Geen WiFi-netwerk gevonden";
const char INTL_NETWORKS_FOUND[] PROGMEM = "Netwerk gevonden: ";
const char INTL_AB_HIER_NUR_ANDERN[] PROGMEM = "Geavanceerde instellingen (enkel als je weet wat je doet)";
const char INTL_SAVE[] PROGMEM = "Opslaan";
const char INTL_SENSORS[] PROGMEM = "Sensors";
const char INTL_SDS011[] PROGMEM = "SDS011 ({pm})";
const char INTL_PMS[] PROGMEM = "Plantower PMS(1,3,5,6,7)003 ({pm})";
const char INTL_HPM[] PROGMEM = "Honeywell fijnstofsensor";
const char INTL_PPD42NS[] PROGMEM = "PPD42NS";
const char INTL_DHT22[] PROGMEM = "DHT22 ({t}, {h})";
const char INTL_HTU21D[] PROGMEM = "HTU21D ({t}, {h})";
const char INTL_BMP180[] PROGMEM = "BMP180 ({t}, {p})";
const char INTL_BMP280[] PROGMEM = "BMP280 ({t}, {p})";
const char INTL_BME280[] PROGMEM = "BME280 ({t}, {h}, {p})";
const char INTL_DS18B20[] PROGMEM = "DS18B20 ({t})";
const char INTL_NEO6M[] PROGMEM = "GPS (NEO 6M)";
const char INTL_BASICAUTH[] PROGMEM = "Beperk toegang";
const char INTL_FS_WIFI[] PROGMEM = "Instellingen voor rechtstreekse WiFi-verbinding";
const char INTL_FS_WIFI_DESCRIPTION[] PROGMEM = "Netwerknaam en -wachtwoord van de fijnstofsensor";
const char INTL_FS_WIFI_NAME[] PROGMEM = "Naam (SSID)";
const char INTL_MORE_SETTINGS[] PROGMEM ="Meer instellingen";
const char INTL_AUTO_UPDATE[] PROGMEM = "Firmware automatisch bijwerken";
const char INTL_USE_BETA[] PROGMEM = "Installeer beta-firmwares";
const char INTL_DISPLAY[] PROGMEM = "OLED SSD1306";
const char INTL_SH1106[] PROGMEM = "OLED SH1106";
const char INTL_LCD1602_27[] PROGMEM = "LCD 1602 (I2C: 0x27)";
const char INTL_LCD1602_3F[] PROGMEM = "LCD 1602 (I2C: 0x3F)";
const char INTL_LCD2004_27[] PROGMEM = "LCD 2004 (I2C: 0x27)";
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
const char INTL_HOME[] PROGMEM = "Home";
const char INTL_BACK_TO_HOME[] PROGMEM = "Terug naar homepagina";
const char INTL_CURRENT_DATA[] PROGMEM = "Huidige data";
const char INTL_ACTIVE_SENSORS_MAP[] PROGMEM = "Actieve sensors kaart (externe link)";
const char INTL_CONFIGURATION_DELETE[] PROGMEM = "Configuratie verwijderen";
const char INTL_CONFIGURATION_REALLY_DELETE[] PROGMEM = "Bent u zeker dat u de configuratie wilt verwijderen?";
const char INTL_DELETE[] PROGMEM = "Verwijderen";
const char INTL_CANCEL[] PROGMEM = "Annuleren";
const char INTL_REALLY_RESTART_SENSOR[] PROGMEM = "Bent u zeker dat u de sensor wilt herstarten?";
const char INTL_RESTART[] PROGMEM = "Herstart";
const char INTL_SAVE_AND_RESTART[] PROGMEM = "Opslaan en herstarten";
const char INTL_FIRMWARE[] PROGMEM = "Firmware-versie";
const char INTL_DEBUG_SETTING_TO[] PROGMEM = "Debugniveau naar ";
const char INTL_NONE[] PROGMEM = "Uit";
const char INTL_ERROR[] PROGMEM = "enkel foutmeldingen";
const char INTL_WARNING[] PROGMEM = "waarschuwingen";
const char INTL_MIN_INFO[] PROGMEM = "min. info";
const char INTL_MED_INFO[] PROGMEM = "mid. info";
const char INTL_MAX_INFO[] PROGMEM = "max. info";
const char INTL_CONFIG_DELETED[] PROGMEM = "Configuratie is verwijderd";
const char INTL_CONFIG_CAN_NOT_BE_DELETED[] PROGMEM = "Configuratie kan niet worden verwijderd";
const char INTL_CONFIG_NOT_FOUND[] PROGMEM = "Configuratie is niet gevonden";
const char INTL_TIME_TO_FIRST_MEASUREMENT[] PROGMEM = "Nog {v} seconden voor de eerste meting.";
const char INTL_TIME_SINCE_LAST_MEASUREMENT[] PROGMEM = " seconden sinds laatste meting.";
const char INTL_PARTICLES_PER_LITER[] PROGMEM = "deeltjes/liter";
const char INTL_PARTICULATE_MATTER[] PROGMEM = "fijnstof";
const char INTL_TEMPERATURE[] PROGMEM = "Temperatuur";
const char INTL_HUMIDITY[] PROGMEM = "Rel. luchtvochtigheid";
const char INTL_PRESSURE[] PROGMEM = "Luchtdruk";
const char INTL_LATITUDE[] PROGMEM = "Breedtegraad";
const char INTL_LONGITUDE[] PROGMEM = "Lengtegraad";
const char INTL_ALTITUDE[] PROGMEM = "Hoogte";
const char INTL_DATE[] PROGMEM = "Datum";
const char INTL_TIME[] PROGMEM = "Tijd";
const char INTL_SIGNAL_STRENGTH[] PROGMEM = "Signaalsterkte";
const char INTL_SIGNAL_QUALITY[] PROGMEM = "Signaalkwaliteit";
const char INTL_NUMBER_OF_MEASUREMENTS[] PROGMEM = "Aantal metingen:";
const char INTL_SENSOR[] PROGMEM = "Sensor";
const char INTL_PARAMETER[] PROGMEM = "Parameter";
const char INTL_VALUE[] PROGMEM = "Waarde";

const char LUFTDATEN_INFO_LOGO_SVG[] PROGMEM = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
<svg viewBox=\"0 0 350 350\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\
<defs>\
<path id=\"d\" d=\"m284.38 273.35v-62.5c-1.77-23.65-9.32-42.14-22.65-55.48-13.33-13.33-30.76-20.88-52.27-22.64h-34.46-29.37c-24.67 2.77-43.66 10.82-57 24.16-13.33 13.33-21 31.32-23 53.96v62.5\"/>\
<path id=\"c\" d=\"m177.6 188.56v-112 112z\"/>\
<path id=\"a\" d=\"m171.92 76.73c5.82 0 10.53 4.71 10.53 10.52v90.95c0 5.82-4.71 10.53-10.53 10.53h-17.2c-5.82 0-10.53-4.71-10.53-10.53v-90.95c0-5.81 4.71-10.52 10.53-10.52h17.2z\"/>\
<path id=\"e\" d=\"m228.81 248.48h112-112z\"/>\
<path id=\"b\" d=\"m340.81 243.19c0 5.82-4.71 10.53-10.52 10.53h-90.95c-5.81 0-10.53-4.71-10.53-10.53v-17.21c0-5.81 4.72-10.52 10.53-10.52h90.95c5.81 0 10.52 4.71 10.52 10.52v17.21z\"/>\
</defs>\
<use fill-opacity=\"0\" stroke=\"#e0e0e0\" stroke-width=\"100\" xlink:href=\"#d\"/>\
<use fill-opacity=\"0\" stroke=\"#e0e0e0\" stroke-width=\"50\" xlink:href=\"#c\"/>\
<use fill=\"#e0e0e0\" xlink:href=\"#a\"/>\
<use fill-opacity=\"0\" stroke=\"#e0e0e0\" stroke-width=\"50\" xlink:href=\"#e\"/>\
<use fill=\"#e0e0e0\" xlink:href=\"#b\"/>\
</svg>";
