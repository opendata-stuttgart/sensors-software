/*
 *  airRohr firmware 
 *  Copyright (C) 2016-2018 Code for Stuttgart a.o. 
 * 
 *  Greek translation
 * 
 *	Texts should be as short as possible
 */

#define INTL_LANG "GR"
#define INTL_PM_SENSOR "Αισθητήρας σωματιδίων"
const char INTL_CONFIGURATION[] PROGMEM = "Διαμόρφωση";
#define INTL_WIFI_SETTINGS "Ρυθμίσεις WiFi"
#define INTL_WIFI_NETWORKS "Φόρτωση δικτύων wifi ..."
#define INTL_LANGUAGE "Γλώσσα"
const char INTL_NO_NETWORKS[] PROGMEM =  "Δεν βρέθηκε δίκτυο WiFi";
const char INTL_NETWORKS_FOUND[] PROGMEM = "Βρέθηκαν δίκτυα:";
const char INTL_AB_HIER_NUR_ANDERN[] PROGMEM = "Ρυθμίσεις για προχωρημένους (μόνο αν ξέρετε τι κάνετε)";
const char INTL_SAVE[] PROGMEM = "Αποθήκευση";
const char INTL_SENSORS[] PROGMEM = "Αισθητήρες";
const char INTL_MORE_SENSORS[] PROGMEM = "Περισσότεροι αισθητήρες";
const char INTL_SDS011[] PROGMEM = "SDS011 ({pm})";
const char INTL_PMS[] PROGMEM = "Plantower PMS(1,3,5,6,7)003 ({pm})";
const char INTL_HPM[] PROGMEM = "Honeywell PM ({pm})";
const char INTL_NPM[] PROGMEM = "Αισθητήρας Tera Next PM ({pm})";
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
const char INTL_DNMS_CORRECTION[] PROGMEM = "διόρθωση σε dB(A)";
const char INTL_TEMP_CORRECTION[] PROGMEM = "Διόρθωση σε °C";
const char INTL_HEIGHT_ABOVE_SEALEVEL[] PROGMEM = "";
const char INTL_PRESSURE_AT_SEALEVEL[] PROGMEM = "";
const char INTL_NEO6M[] PROGMEM = "GPS (NEO 6M)";
const char INTL_BASICAUTH[] PROGMEM = "Αυθεντικοποίηση";
#define INTL_REPORT_ISSUE "Αναφέρετε ένα θέμα"

const char INTL_FS_WIFI_DESCRIPTION[] PROGMEM = "Αισθητήρας WiFi σε λειτουργία διαμόρφωσης";
const char INTL_FS_WIFI_NAME[] PROGMEM = "Όνομα δικτύου";
const char INTL_MORE_SETTINGS[] PROGMEM = "Περισσότερες ρυθμίσεις";
const char INTL_AUTO_UPDATE[] PROGMEM = "Αυτόματη ενημέρωση υλικολογισμικού";
const char INTL_USE_BETA[] PROGMEM = "Φόρτωση firmware beta";
const char INTL_DISPLAY[] PROGMEM = "OLED SSD1306";
const char INTL_SH1106[] PROGMEM = "OLED SH1106";
const char INTL_FLIP_DISPLAY[] PROGMEM = "Αναδίπλωση οθόνης OLED";
const char INTL_LCD1602_27[] PROGMEM = "LCD 1602 (I2C: 0x27)";
const char INTL_LCD1602_3F[] PROGMEM = "LCD 1602 (I2C: 0x3F)";
const char INTL_LCD2004_27[] PROGMEM = "LCD 2004 (I2C: 0x27)";
const char INTL_LCD2004_3F[] PROGMEM = "LCD 2004 (I2C: 0x3F)";
const char INTL_DISPLAY_WIFI_INFO[] PROGMEM = "Εμφάνιση πληροφοριών Wifi";
const char INTL_DISPLAY_DEVICE_INFO[] PROGMEM = "Εμφάνιση πληροφοριών συσκευής";

#define INTL_STATIC_IP_TEXT ""
const char INTL_STATIC_IP[] PROGMEM = "";
const char INTL_STATIC_SUBNET[] PROGMEM = "";
const char INTL_STATIC_GATEWAY[] PROGMEM = "";
const char INTL_STATIC_DNS[] PROGMEM = "";

const char INTL_DEBUG_LEVEL[] PROGMEM = "Αποσφαλμάτωση&nbsp;επίπεδο";
const char INTL_MEASUREMENT_INTERVAL[] PROGMEM = "Διάστημα μέτρησης (sec)";
const char INTL_DURATION_ROUTER_MODE[] PROGMEM = "Διάρκεια λειτουργίας δρομολογητή";
const char INTL_POWERSAVE[] PROGMEM = "";
const char INTL_MORE_APIS[] PROGMEM = "Περισσότερα APIs";
const char INTL_SEND_TO_OWN_API[] PROGMEM = "Αποστολή δεδομένων σε προσαρμοσμένο API";
const char INTL_SERVER[] PROGMEM = "Διακομιστής";
const char INTL_PATH[] PROGMEM = "Διαδρομή";
const char INTL_PORT[] PROGMEM = "Λιμάνι";
const char INTL_USER[] PROGMEM = "Χρήστης";
const char INTL_PASSWORD[] PROGMEM = "Κωδικός πρόσβασης";
const char INTL_MEASUREMENT[] PROGMEM = "Μέτρηση";
const char INTL_SEND_TO[] PROGMEM = "Στείλτε στο {v}";
const char INTL_READ_FROM[] PROGMEM = "Διαβάστε από {v}";
const char INTL_SENSOR_IS_REBOOTING[] PROGMEM = "Ο αισθητήρας κάνει επανεκκίνηση.";
const char INTL_RESTART_DEVICE[] PROGMEM = "Επανεκκίνηση της συσκευής";
const char INTL_DELETE_CONFIG[] PROGMEM = "διαγραφή αποθηκευμένων ρυθμίσεων";
const char INTL_RESTART_SENSOR[] PROGMEM = "Επανεκκίνηση αισθητήρα";
#define INTL_HOME "Αρχική σελίδα"
#define INTL_BACK_TO_HOME "Επιστροφή στην αρχική σελίδα"
const char INTL_CURRENT_DATA[] PROGMEM = "Τρέχοντα δεδομένα";
const char INTL_DEVICE_STATUS[] PROGMEM = "Κατάσταση συσκευής";
#define INTL_ACTIVE_SENSORS_MAP "Χάρτης ενεργών αισθητήρων (εξωτερικός σύνδεσμος)"
#define INTL_CONFIGURATION_DELETE "Διαγραφή ρυθμίσεων"
#define INTL_CONFIGURATION_REALLY_DELETE "Είστε σίγουροι ότι θέλετε να διαγράψετε τη διαμόρφωση;"
#define INTL_DELETE "Διαγραφή"
#define INTL_CANCEL "Ακύρωση"
#define INTL_REALLY_RESTART_SENSOR "Είστε σίγουροι ότι θέλετε να επανεκκινήσετε τον αισθητήρα;"
#define INTL_RESTART "Επανεκκίνηση"
const char INTL_SAVE_AND_RESTART[] PROGMEM = "Αποθήκευση ρυθμίσεων και επανεκκίνηση";
#define INTL_FIRMWARE "Έκδοση υλικολογισμικού"
const char INTL_DEBUG_SETTING_TO[] PROGMEM = "Ορίστε το επίπεδο εντοπισμού σφαλμάτων σε";
#define INTL_NONE "off"
#define INTL_ERROR "μόνο σφάλματα"
#define INTL_WARNING "προειδοποιήσεις"
#define INTL_MIN_INFO "ελάχιστη πληροφορία"
#define INTL_MED_INFO "mid. info"
#define INTL_MAX_INFO "max. πληροφορίες"
#define INTL_CONFIG_DELETED "Η διαμόρφωση διαγράφηκε"
#define INTL_CONFIG_CAN_NOT_BE_DELETED "Η διαμόρφωση δεν μπορεί να διαγραφεί"
#define INTL_CONFIG_NOT_FOUND "Η διαμόρφωση δεν βρέθηκε"
const char INTL_TIME_TO_FIRST_MEASUREMENT[] PROGMEM = "Ακόμα {v} δευτερόλεπτα μέχρι την πρώτη μέτρηση.";
const char INTL_TIME_SINCE_LAST_MEASUREMENT[] PROGMEM = " δευτερόλεπτα από την τελευταία μέτρηση.";
const char INTL_PARTICLES_PER_LITER[] PROGMEM = "particlesliter";
const char INTL_PARTICULATE_MATTER[] PROGMEM = "σωματιδιακή ύλη";
const char INTL_TEMPERATURE[] PROGMEM = "θερμοκρασία";
const char INTL_HUMIDITY[] PROGMEM = "υγρασία";
const char INTL_PRESSURE[] PROGMEM = "πίεση του αέρα";
const char INTL_DEW_POINT[] PROGMEM = "";
const char INTL_CO2_PPM[] PROGMEM = "ppm CO₂";
const char INTL_LEQ_A[] PROGMEM = "LAeq";
const char INTL_LA_MIN[] PROGMEM = "LA min";
const char INTL_LA_MAX[] PROGMEM = "LA max";
const char INTL_LATITUDE[] PROGMEM = "Γεωγραφικό πλάτος";
const char INTL_LONGITUDE[] PROGMEM = "Γεωγραφικό μήκος";
const char INTL_ALTITUDE[] PROGMEM = "Υψόμετρο";
const char INTL_TIME_UTC[] PROGMEM = "Ώρα (UTC)";
const char INTL_SIGNAL_STRENGTH[] PROGMEM = "ισχύς του σήματος";
const char INTL_SIGNAL_QUALITY[] PROGMEM = "ποιότητα σήματος";
#define INTL_NUMBER_OF_MEASUREMENTS "Αριθμός μετρήσεων"
#define INTL_TIME_SENDING_MS "Χρόνος μεταφόρτωσης"
#define INTL_SENSOR "Αισθητήρας"
#define INTL_PARAMETER "Παράμετρος"
#define INTL_VALUE "Αξία"
const char INTL_ENABLE_BATTERY_MONITOR[] PROGMEM = "Ενεργοποίηση οθόνης μπαταρίας";
const char INTL_BATTERY_CHARGE[] PROGMEM = "Φόρτιση μπαταρίας";
const char INTL_BATTERY_U_MIN[] PROGMEM = "Μπαταρία U min (mV)";
const char INTL_BATTERY_U_MAX[] PROGMEM = "Μπαταρία U max (mV)";
const char INTL_ADC_DIVIDER_U_MAX[] PROGMEM = "Διαχωριστικό ADC U max (mV)";

#include "./airrohr-logo-common.h"
