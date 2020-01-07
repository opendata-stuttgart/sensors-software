/*
 *	airRohr firmware
 *	Copyright (C) 2016-2018  Code for Stuttgart a.o.
 *
 *  Polish translations
 *
 *	Texts should be as short as possible
 *	We only have 512 kB for the entire firmware
 */

const char INTL_LANG[] = "PL";
#define INTL_PM_SENSOR "Czujnik pyłu zawieszonego"
const char INTL_CONFIGURATION[] PROGMEM = "Konfiguracja";
#define INTL_WIFI_SETTINGS "Ustawienia WiFi"
#define INTL_WIFI_NETWORKS "Ładowanie sieci WiFi..."
#define INTL_LANGUAGE "Język"
const char INTL_NO_NETWORKS[] PROGMEM =  "Nie znaleziono sieci WiFi";
const char INTL_NETWORKS_FOUND[] PROGMEM = "Znalezione sieci: ";
const char INTL_AB_HIER_NUR_ANDERN[] PROGMEM = "Ustawienia zaawansowane (tylko gdy wiesz co robisz)";
const char INTL_SAVE[] PROGMEM = "Zapisz";
const char INTL_SENSORS[] PROGMEM = "Sensory";
const char INTL_MORE_SENSORS[] PROGMEM = "More Sensory";
const char INTL_SDS011[] PROGMEM = "SDS011 ({pm})";
const char INTL_PMS[] PROGMEM = "Plantower PMS(1,3,5,6,7)003 ({pm})";
const char INTL_HPM[] PROGMEM = "Honeywell ({pm})";
const char INTL_SPS30[] PROGMEM = "Sensirion SPS30 ({pm})";
const char INTL_PPD42NS[] PROGMEM = "PPD42NS ({pm})";
const char INTL_DHT22[] PROGMEM = "DHT22 ({t}, {h})";
const char INTL_HTU21D[] PROGMEM = "HTU21D ({t}, {h})";
const char INTL_BMP180[] PROGMEM = "BMP180 ({t}, {p})";
const char INTL_BMX280[] PROGMEM = "BMP280/BME280 ({t}, {h}, {p})";
const char INTL_SHT3X[] PROGMEM = "SHT3X ({t}, {h})";
const char INTL_DS18B20[] PROGMEM = "DS18B20 ({t})";
const char INTL_DNMS[] PROGMEM = "DNMS ({l_a})";
const char INTL_DNMS_CORRECTION[] PROGMEM ="poprawka w dB(A)";
const char INTL_NEO6M[] PROGMEM = "GPS (NEO 6M)";
const char INTL_BASICAUTH[] PROGMEM = "Autoryzacja";

const char INTL_FS_WIFI_DESCRIPTION[] PROGMEM = "Parametry WiFi w trybie konfiguracji czujnika";
const char INTL_FS_WIFI_NAME[] PROGMEM = "Nazwa sieci";
const char INTL_MORE_SETTINGS[] PROGMEM ="Więcej ustawień";
const char INTL_AUTO_UPDATE[] PROGMEM = "Aktualizuj firmware automatycznie";
const char INTL_USE_BETA[] PROGMEM = "Załaduj firmware beta";
const char INTL_DISPLAY[] PROGMEM = "OLED SSD1306";
const char INTL_SH1106[] PROGMEM = "OLED SH1106";
const char INTL_FLIP_DISPLAY[] PROGMEM = "Obrót ekranu OLED";
const char INTL_LCD1602_27[] PROGMEM = "LCD 1602 (I2C: 0x27)";
const char INTL_LCD1602_3F[] PROGMEM = "LCD 1602 (I2C: 0x3F)";
const char INTL_LCD2004_27[] PROGMEM = "LCD 2004 (I2C: 0x27)";
const char INTL_LCD2004_3F[] PROGMEM = "LCD 2004 (I2C: 0x3F)";
const char INTL_DISPLAY_WIFI_INFO[] PROGMEM = "Wyświetl info o WiFi";
const char INTL_DISPLAY_DEVICE_INFO[] PROGMEM = "Wyświetl info o urządzeniu";
const char INTL_DEBUG_LEVEL[] PROGMEM = "Poziom&nbsp;debugowania";
const char INTL_MEASUREMENT_INTERVAL[] PROGMEM = "Czas między pomiarami (sek.)";
const char INTL_DURATION_ROUTER_MODE[] PROGMEM = "Czas trwania w trybie routera (sek.)";
const char INTL_MORE_APIS[] PROGMEM = "Kolejne API";
const char INTL_SEND_TO_OWN_API[] PROGMEM = "Wysyłaj dane do własnego API";
const char INTL_SERVER[] PROGMEM = "Adres serwera";
const char INTL_PATH[] PROGMEM = "Ścieżka";
const char INTL_PORT[] PROGMEM = "Port";
const char INTL_USER[] PROGMEM = "Nazwa użytkownika";
const char INTL_PASSWORD[] PROGMEM = "Hasło";
const char INTL_SEND_TO[] PROGMEM = "Wysyłaj dane do {v}";
const char INTL_READ_FROM[] PROGMEM = "Czytaj z {v}";
const char INTL_SENSOR_IS_REBOOTING[] PROGMEM = "Ponowne uruchamianie czujnika.";
const char INTL_RESTART_DEVICE[] PROGMEM = "Uruchom ponownie urządzenie";
const char INTL_DELETE_CONFIG[] PROGMEM = "Usuń zapisaną konfigurację";
const char INTL_RESTART_SENSOR[] PROGMEM = "Uruchom ponownie czujnik";
#define INTL_HOME "Strona startowa"
#define INTL_BACK_TO_HOME "Powrót do strony startowej"
const char INTL_CURRENT_DATA[] PROGMEM = "Obecne wskazania";
const char INTL_DEVICE_STATUS[] PROGMEM = "Stan urządzenia";
#define INTL_ACTIVE_SENSORS_MAP "Mapa aktywnych czujników (link zewnętrzny)"
#define INTL_CONFIGURATION_DELETE "Usunięcie konfiguracji"
#define INTL_CONFIGURATION_REALLY_DELETE "Czy na pewno chcesz usunąć konfigurację?"
#define INTL_DELETE "Usuń"
#define INTL_CANCEL "Anuluj"
#define INTL_REALLY_RESTART_SENSOR "Czy na pewno chcesz uruchomić czujnik ponownie?"
#define INTL_RESTART "Uruchom ponownie"
const char INTL_SAVE_AND_RESTART[] PROGMEM = "Zapisz i zrestartuj";
#define INTL_FIRMWARE "Wersja firmware"
const char INTL_DEBUG_SETTING_TO[] PROGMEM = "Ustawiono poziom debugowania na ";
#define INTL_NONE "wyłączony"
#define INTL_ERROR "tylko błędy"
#define INTL_WARNING "ostrzeżenia"
#define INTL_MIN_INFO "min. info"
#define INTL_MED_INFO "śr. info"
#define INTL_MAX_INFO "maks. info"
#define INTL_CONFIG_DELETED "Usunięto konfigurację"
#define INTL_CONFIG_CAN_NOT_BE_DELETED "Konfiguracja nie może zostać usunięta"
#define INTL_CONFIG_NOT_FOUND "Nie znaleziono konfiguracji"
const char INTL_TIME_TO_FIRST_MEASUREMENT[] = "Pozostało {v} sekund do pierwszego pomiaru.";
const char INTL_TIME_SINCE_LAST_MEASUREMENT[] = " sekund od ostatniego pomiaru.";
const char INTL_PARTICLES_PER_LITER[] PROGMEM = "cząsteczek/litr";
const char INTL_PARTICULATE_MATTER[] PROGMEM = "Pył zawieszony";
const char INTL_TEMPERATURE[] PROGMEM = "Temperatura";
const char INTL_HUMIDITY[] PROGMEM = "Wilgotność";
const char INTL_PRESSURE[] PROGMEM = "Ciśnienie";
const char INTL_LEQ_A[] PROGMEM = "LAeq";
const char INTL_LA_MIN[] PROGMEM = "LA min";
const char INTL_LA_MAX[] PROGMEM = "LA max";
const char INTL_LATITUDE[] PROGMEM = "Szerokość geo.";
const char INTL_LONGITUDE[] PROGMEM = "Długość geo.";
const char INTL_ALTITUDE[] PROGMEM = "Wysokość";
const char INTL_DATE[] PROGMEM = "Data";
const char INTL_TIME[] PROGMEM = "Czas";
const char INTL_SIGNAL_STRENGTH[] PROGMEM = "Siła sygnału";
const char INTL_SIGNAL_QUALITY[] PROGMEM = "Jakość sygnału";
#define INTL_NUMBER_OF_MEASUREMENTS "Liczba pomiarów"
#define INTL_TIME_SENDING_MS "Czas spędzony na wysyłce"
#define INTL_SENSOR "Czujnik"
#define INTL_PARAMETER "Parametr"
#define INTL_VALUE "Wartość"

#include "./airrohr-logo-common.h"
