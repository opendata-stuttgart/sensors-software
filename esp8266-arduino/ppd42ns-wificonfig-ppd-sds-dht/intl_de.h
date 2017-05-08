const char INTL_LANG[] = "DE";
const char INTL_FEINSTAUBSENSOR[] PROGMEM = "Feinstaubsensor";
const char INTL_KONFIGURATION[] PROGMEM = "Konfiguration";
const char INTL_WLAN_DATEN[] PROGMEM = "WLAN Daten";
const char INTL_SPRACHE[] PROGMEM = "Sprache";
const char INTL_KEINE_NETZWERKE[] PROGMEM =  "Keine Netzwerke gefunden";
const char INTL_NETZWERKE_GEFUNDEN[] = "Netzwerke gefunden: ";
const char INTL_AB_HIER_NUR_ANDERN[] PROGMEM = "Ab hier nur ändern, wenn Sie wirklich wissen, was Sie tun";
const char INTL_SPEICHERN[] PROGMEM = "Speichern";
const char INTL_SENSOREN[] PROGMEM = "Sensoren";
const char INTL_BASICAUTH[] PROGMEM = "BasicAuth aktivieren";
const char INTL_WEITERE_EINSTELLUNGEN[] PROGMEM ="Weitere Einstellungen";
const char INTL_AUTO_UPDATE[] PROGMEM = "Auto Update";
const char INTL_DISPLAY[] PROGMEM = "Display";
const char INTL_DEBUG_LEVEL[] PROGMEM = "Debug&nbsp;Level";
const char INTL_WEITERE_APIS[] PROGMEM = "Weitere APIs";
const char INTL_AN_EIGENE_API_SENDEN[] PROGMEM = "An eigene API senden";
const char INTL_SERVER[] PROGMEM = "Server"; 
const char INTL_PFAD[] PROGMEM = "Pfad"; 
const char INTL_PORT[] PROGMEM = "Port"; 
const char INTL_BENUTZER[] PROGMEM = "Benutzer"; 
const char INTL_PASSWORT[] PROGMEM = "Passwort"; 
const char INTL_SENDEN_AN[] PROGMEM = "Senden an {v}"; 
const char INTL_LESE[] PROGMEM = "Lese";
const char INTL_GERAT_NEU_STARTEN[] PROGMEM = "Gerät neu starten";
const char INTL_CONFIG_LOSCHEN[] PROGMEM = "Config.json löschen";
const char INTL_SENSOR_NEU_STARTEN[] PROGMEM = "Sensor neu starten";
const char INTL_UBERSICHT[] PROGMEM = "Übersicht";
const char INTL_ZURUCK_ZUR_STARTSEITE[] PROGMEM = "Zurück zur Startseite";
const char INTL_AKTUELLE_WERTE[] PROGMEM = "Aktuelle Werte";
const char INTL_KARTE_DER_AKTIVEN_SENSOREN[] PROGMEM = "Karte der aktiven Sensoren (externer Link)";
const char INTL_KONFIGURATION_LOSCHEN[] PROGMEM = "Konfiguration löschen";
const char INTL_KONFIGURATION_WIRKLICH_LOSCHEN[] PROGMEM = "Konfiguration wirklich löschen?";
const char INTL_LOSCHEN[] PROGMEM = "Löschen";
const char INTL_ABBRECHEN[] PROGMEM = "Abbrechen";
const char INTL_SENSOR_WIRKLICH_NEU_STARTEN[] PROGMEM = "Sensor wirklich neu starten";
const char INTL_NEU_STARTEN[] PROGMEM = "Neu starten";
const char INTL_FIRMWARE[] PROGMEM = "Firmware";
const char INTL_SETZE_DEBUG_AUF[] PROGMEM = "Setze Debug auf";
const char INTL_NONE[] PROGMEM = "none";
const char INTL_ERROR[] PROGMEM = "error";
const char INTL_WARNING[] PROGMEM = "warning";
const char INTL_MIN_INFO[] PROGMEM = "min. info";
const char INTL_MED_INFO[] PROGMEM = "med. info";
const char INTL_MAX_INFO[] PROGMEM = "max. info";
const char INTL_CONFIG_GELOSCHT[] PROGMEM = "Config.json gelöscht";
const char INTL_CONFIG_KONNTE_NICHT_GELOSCHT_WERDEN[] PROGMEM = "Config.json konnte nicht gelöscht werden";
const char INTL_CONFIG_NICHT_GEFUNDEN[] PROGMEM = "Config.json nicht gefunden";
const char INTL_PARTIKEL_LITER[] PROGMEM = "Partikel/Liter";
const char INTL_TEMPERATUR[] PROGMEM = "Temperatur";
const char INTL_LUFTFEUCHTE[] PROGMEM = "rel. Luftfeuchte";
const char INTL_LUFTDRUCK[] PROGMEM = "Luftdruck";
const char INTL_SIGNAL[] PROGMEM = "Signal";
const char INTL_QUALITAT[] PROGMEM = "Qualität";
const char INTL_SENSOR[] PROGMEM = "Sensor";
const char INTL_PARAMETER[] PROGMEM = "Parameter";
const char INTL_WERT[] PROGMEM = "Wert";

const char LUFTDATEN_INFO_LOGO_SVG[] PROGMEM = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
<!-- Generator: Adobe Illustrator 15.1.0, SVG Export Plug-In . SVG Version: 6.00 Build 0)  -->\
<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\
<svg version=\"1.1\" id=\"Layer_1\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" x=\"0px\" y=\"0px\" width=\"100px\" height=\"88.891px\" viewBox=\"0 0 100 88.891\" enable-background=\"new 0 0 100 88.891\" xml:space=\"preserve\">\
<path fill=\"#ffffff\" d=\"M90.277,66.571v0.094h-1.388h-5.556c-2.046,0-3.705-1.656-3.705-3.704c0-2.044,1.659-3.7,3.705-3.7h5.556  c2.046,0,3.702-1.661,3.702-3.704c0-2.046-1.656-3.704-3.702-3.704s-3.704-1.659-3.704-3.705c0-2.045,1.658-3.704,3.704-3.704 c0.255,0,0.505,0.025,0.743,0.076C95.417,44.91,100,49.675,100,55.557C100,61.219,95.757,65.884,90.277,66.571z\"/>\
<path fill=\"#ffffff\" d=\"M70.371,44.444c-2.044,0-3.704-1.659-3.704-3.704c0-2.044,1.66-3.705,3.704-3.705  c0.257,0,0.503,0.025,0.745,0.076c5.78,0.391,10.365,5.155,10.365,11.036c0,5.667-4.243,10.33-9.722,11.016v0.098h-1.389H55.583  c-7.432,0-21.038,0-25.953,0c-2.045,0-3.704,1.658-3.704,3.7c0,2.048,1.659,3.704,3.704,3.704h40.741h1.389v0.098  c5.479,0.684,9.722,5.352,9.722,11.015c0,5.882-4.585,10.645-10.365,11.037c-0.242,0.047-0.492,0.076-0.745,0.076  c-2.044,0-3.704-1.661-3.704-3.705c0-2.045,1.66-3.704,3.704-3.704c2.043,0,3.704-1.658,3.704-3.704  c0-2.045-1.661-3.704-3.704-3.704H29.63h-1.389v-0.096c-5.48-0.686-9.724-5.352-9.724-11.017c0-1.953,0.544-3.762,1.432-5.352  C8.345,53.594,0,42.599,0,29.63C0,13.267,13.265,0,29.63,0c11.12,0,20.798,6.134,25.864,15.195c1.23-0.212,2.475-0.38,3.766-0.38  c10.919,0,19.98,7.882,21.851,18.265c-2.582-1.843-5.648-3.048-8.979-3.361c-2.553-4.475-7.356-7.495-12.871-7.495  c-2.964,0-5.712,0.889-8.026,2.389C48.952,14.767,40.17,7.407,29.63,7.407c-12.274,0-22.223,9.949-22.223,22.223  c0,12.271,9.949,22.223,22.223,22.223c4.812,0,15.097,0,22.594,0h18.146c2.043,0,3.704-1.659,3.704-3.705  C74.075,46.101,72.417,44.444,70.371,44.444z\"/>\
</svg>";
