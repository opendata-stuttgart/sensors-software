/*
 *	airRohr firmware
 *	Copyright (C) 2016-2018  Code for Stuttgart a.o.
 * 
 *  Italian translations
 * 
 *	Texts should be as short as possible
 *	We only have 512 kB for the entire firmware
 */

const char INTL_LANG[] = "IT";
const char INTL_PM_SENSOR[] PROGMEM = "Sensore polveri sottili";
const char INTL_CONFIGURATION[] PROGMEM = "Configurazione";
const char INTL_WIFI_SETTINGS[] PROGMEM = "Impostazioni Wifi";
const char INTL_WIFI_NETWORKS[] PROGMEM = "Ricarica reti wifi ...";
const char INTL_LANGUAGE[] PROGMEM = "Lingua";
const char INTL_NO_NETWORKS[] PROGMEM =  "Nessuna rete WiFi trovata";
const char INTL_NETWORKS_FOUND[] PROGMEM = "Reti trovate: ";
const char INTL_AB_HIER_NUR_ANDERN[] PROGMEM = "Impostazioni avanzate (solo se sai quello che stai facendo)";
const char INTL_SAVE[] PROGMEM = "Salvare";
const char INTL_SENSORS[] PROGMEM = "Sensori";
const char INTL_SDS011[] PROGMEM = "SDS011 ({pm})";
const char INTL_PMS[] PROGMEM = "Plantower PMS(1,3,5,6,7)003 ({pm})";
const char INTL_HPM[] PROGMEM = "Honeywell sensore polveri sottili";
const char INTL_SPS30[] PROGMEM = "Sensirion SPS30 ({pm})";
const char INTL_PPD42NS[] PROGMEM = "PPD42NS";
const char INTL_DHT22[] PROGMEM = "DHT22 ({t}, {h})";
const char INTL_HTU21D[] PROGMEM = "HTU21D ({t}, {h})";
const char INTL_BMP180[] PROGMEM = "BMP180 ({t}, {p})";
const char INTL_BMX280[] PROGMEM = "BMP280/BME280 ({t}, {h}, {p})";
const char INTL_DS18B20[] PROGMEM = "DS18B20 ({t})";
const char INTL_DNMS[] PROGMEM = "DNMS ({l_a})";
const char INTL_DNMS_CORRECTION[] PROGMEM ="";
const char INTL_NEO6M[] PROGMEM = "GPS (NEO 6M)";
const char INTL_BASICAUTH[] PROGMEM = "Autorizzazione";
const char INTL_FS_WIFI[] PROGMEM = "";
const char INTL_FS_WIFI_DESCRIPTION[] PROGMEM = "";
const char INTL_FS_WIFI_NAME[] PROGMEM = "";
const char INTL_MORE_SETTINGS[] PROGMEM ="Altre configurazioni";
const char INTL_AUTO_UPDATE[] PROGMEM = "Aggiornamento automatico firmware";
const char INTL_USE_BETA[] PROGMEM = "";
const char INTL_DISPLAY[] PROGMEM = "OLED SSD1306";
const char INTL_SH1106[] PROGMEM = "OLED SH1106";
const char INTL_FLIP_DISPLAY[] PROGMEM = "";
const char INTL_LCD1602_27[] PROGMEM = "LCD 1602 (I2C: 0x27)";
const char INTL_LCD1602_3F[] PROGMEM = "LCD 1602 (I2C: 0x3F)";
const char INTL_LCD2004_27[] PROGMEM = "LCD 2004 (I2C: 0x27)";
const char INTL_DISPLAY_WIFI_INFO[] PROGMEM = "";
const char INTL_DISPLAY_DEVICE_INFO[] PROGMEM = "";
const char INTL_DEBUG_LEVEL[] PROGMEM = "Debug&nbsp;Level";
const char INTL_MEASUREMENT_INTERVAL[] PROGMEM = "intervallo di misura";
const char INTL_DURATION_ROUTER_MODE[] PROGMEM = "Durata della modalità router";
const char INTL_MORE_APIS[] PROGMEM = "Altre API";
const char INTL_SEND_TO_OWN_API[] PROGMEM = "Invia i dati alla propria API";
const char INTL_SERVER[] PROGMEM = "Server"; 
const char INTL_PATH[] PROGMEM = "Percorso"; 
const char INTL_PORT[] PROGMEM = "Porta"; 
const char INTL_USER[] PROGMEM = "Utente"; 
const char INTL_PASSWORD[] PROGMEM = "Password"; 
const char INTL_SEND_TO[] PROGMEM = "Spedire a {v}"; 
const char INTL_READ_FROM[] PROGMEM = "Leggi da {v}";
const char INTL_SENSOR_IS_REBOOTING[] PROGMEM = "Riavvio dispositivo.";
const char INTL_RESTART_DEVICE[] PROGMEM = "Riavvia dispositivo";
const char INTL_DELETE_CONFIG[] PROGMEM = "Cancella configurazione";
const char INTL_RESTART_SENSOR[] PROGMEM = "Riavvio sensore";
const char INTL_HOME[] PROGMEM = "Home";
const char INTL_BACK_TO_HOME[] PROGMEM = "Torna alla home page";
const char INTL_CURRENT_DATA[] PROGMEM = "Dati attuali";
const char INTL_ACTIVE_SENSORS_MAP[] PROGMEM = "Mappa dei sensori attivi (link esterno)";
const char INTL_CONFIGURATION_DELETE[] PROGMEM = "Elimina configurazione";
const char INTL_CONFIGURATION_REALLY_DELETE[] PROGMEM = "Sei sicuro di voler eliminare la configurazione?";
const char INTL_DELETE[] PROGMEM = "Elimina";
const char INTL_CANCEL[] PROGMEM = "Annulla";
const char INTL_REALLY_RESTART_SENSOR[] PROGMEM = "Sei sicuro di voler riavviare il sensore?";
const char INTL_RESTART[] PROGMEM = "Riavvio";
const char INTL_SAVE_AND_RESTART[] PROGMEM = "Salva e riavvia";
const char INTL_FIRMWARE[] PROGMEM = "Versione firmware";
const char INTL_DEBUG_SETTING_TO[] PROGMEM = "Imposta debug su";
const char INTL_NONE[] PROGMEM = "Nessuno";
const char INTL_ERROR[] PROGMEM = "Errore";
const char INTL_WARNING[] PROGMEM = "Warning";
const char INTL_MIN_INFO[] PROGMEM = "min. info";
const char INTL_MED_INFO[] PROGMEM = "med. info";
const char INTL_MAX_INFO[] PROGMEM = "max. info";
const char INTL_CONFIG_DELETED[] PROGMEM = "Configurazione cancellata";
const char INTL_CONFIG_CAN_NOT_BE_DELETED[] PROGMEM = "Impossibile cancellare la configurazione";
const char INTL_CONFIG_NOT_FOUND[] PROGMEM = "Configurazione non trovata";
const char INTL_TIME_TO_FIRST_MEASUREMENT[] PROGMEM = "Altri {v} secondi per la prima misurazione.";
const char INTL_TIME_SINCE_LAST_MEASUREMENT[] PROGMEM = "";
const char INTL_PARTICLES_PER_LITER[] PROGMEM = "Particelle / litro";
const char INTL_PARTICULATE_MATTER[] PROGMEM = "polveri sottili";
const char INTL_TEMPERATURE[] PROGMEM = "Temperatura";
const char INTL_HUMIDITY[] PROGMEM = "Umidità";
const char INTL_PRESSURE[] PROGMEM = "Pressione dell'aria";
const char INTL_LEQ_A[] PROGMEM = "LAeq";
const char INTL_LA_MIN[] PROGMEM = "LA min";
const char INTL_LA_MAX[] PROGMEM = "LA max";
const char INTL_LATITUDE[] PROGMEM = "";
const char INTL_LONGITUDE[] PROGMEM = "";
const char INTL_ALTITUDE[] PROGMEM = "";
const char INTL_DATE[] PROGMEM = "";
const char INTL_TIME[] PROGMEM = "";
const char INTL_SIGNAL_STRENGTH[] PROGMEM = "Potenza del segnale";
const char INTL_SIGNAL_QUALITY[] PROGMEM = "Qualità del segnale";
const char INTL_NUMBER_OF_MEASUREMENTS[] PROGMEM = "";
const char INTL_SENSOR[] PROGMEM = "Sensore";
const char INTL_PARAMETER[] PROGMEM = "Parametro";
const char INTL_VALUE[] PROGMEM = "Valore";

#include "./airrohr-logo-common.h"
