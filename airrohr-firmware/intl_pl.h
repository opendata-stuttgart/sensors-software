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
const char INTL_PM_SENSOR[] PROGMEM = "Czujnik pyłu zawieszonego";
const char INTL_CONFIGURATION[] PROGMEM = "Konfiguracja";
const char INTL_WIFI_SETTINGS[] PROGMEM = "Ustawienia WiFi";
const char INTL_WIFI_NETWORKS[] PROGMEM = "Ładowanie sieci WiFi...";
const char INTL_LANGUAGE[] PROGMEM = "Język";
const char INTL_NO_NETWORKS[] PROGMEM =  "Nie znaleziono sieci WiFi";
const char INTL_NETWORKS_FOUND[] PROGMEM = "Znalezione sieci: ";
const char INTL_AB_HIER_NUR_ANDERN[] PROGMEM = "Ustawienia zaawansowane (tylko gdy wiesz co robisz)";
const char INTL_SAVE[] PROGMEM = "Zapisz";
const char INTL_SENSORS[] PROGMEM = "Sensory";
const char INTL_SDS011[] PROGMEM = "SDS011 ({pm})";
const char INTL_PMS[] PROGMEM = "Plantower PMS(1,3,5,6,7)003 ({pm})";
const char INTL_HPM[] PROGMEM = "Honeywell czujnik pyłu zawieszonego";
const char INTL_SPS30[] PROGMEM = "Sensirion SPS30 ({pm})";
const char INTL_PPD42NS[] PROGMEM = "PPD42NS";
const char INTL_DHT22[] PROGMEM = "DHT22 ({t}, {h})";
const char INTL_HTU21D[] PROGMEM = "HTU21D ({t}, {h})";
const char INTL_BMP180[] PROGMEM = "BMP180 ({t}, {p})";
const char INTL_BMX280[] PROGMEM = "BMP280/BME280 ({t}, {h}, {p})";
const char INTL_DS18B20[] PROGMEM = "DS18B20 ({t})";
const char INTL_DNMS[] PROGMEM = "DNMS ({l_a})";
const char INTL_DNMS_CORRECTION[] PROGMEM ="poprawka w dB(A)";
const char INTL_NEO6M[] PROGMEM = "GPS (NEO 6M)";
const char INTL_BASICAUTH[] PROGMEM = "Autoryzacja";
const char INTL_FS_WIFI[] PROGMEM = "WiFi czujnika";
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
const char INTL_HOME[] PROGMEM = "Strona startowa";
const char INTL_BACK_TO_HOME[] PROGMEM = "Powrót do strony startowej";
const char INTL_CURRENT_DATA[] PROGMEM = "Obecne wskazania";
const char INTL_ACTIVE_SENSORS_MAP[] PROGMEM = "Mapa aktywnych czujników (link zewnętrzny)";
const char INTL_CONFIGURATION_DELETE[] PROGMEM = "Usunięcie konfiguracji";
const char INTL_CONFIGURATION_REALLY_DELETE[] PROGMEM = "Czy na pewno chcesz usunąć konfigurację?";
const char INTL_DELETE[] PROGMEM = "Usuń";
const char INTL_CANCEL[] PROGMEM = "Anuluj";
const char INTL_REALLY_RESTART_SENSOR[] PROGMEM = "Czy na pewno chcesz uruchomić czujnik ponownie?";
const char INTL_RESTART[] PROGMEM = "Uruchom ponownie";
const char INTL_SAVE_AND_RESTART[] PROGMEM = "Zapisz i zrestartuj";
const char INTL_FIRMWARE[] PROGMEM = "Wersja firmware";
const char INTL_DEBUG_SETTING_TO[] PROGMEM = "Ustaw poziom debugowania na ";
const char INTL_NONE[] PROGMEM = "wyłączony";
const char INTL_ERROR[] PROGMEM = "tylko błędy";
const char INTL_WARNING[] PROGMEM = "ostrzeżenia";
const char INTL_MIN_INFO[] PROGMEM = "min. info";
const char INTL_MED_INFO[] PROGMEM = "śr. info";
const char INTL_MAX_INFO[] PROGMEM = "maks. info";
const char INTL_CONFIG_DELETED[] PROGMEM = "Usunięto konfigurację";
const char INTL_CONFIG_CAN_NOT_BE_DELETED[] PROGMEM = "Konfiguracja nie może zostać usunięta";
const char INTL_CONFIG_NOT_FOUND[] PROGMEM = "Nie znaleziono konfiguracji";
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
const char INTL_NUMBER_OF_MEASUREMENTS[] PROGMEM = "Liczba pomiarów:";
const char INTL_SENSOR[] PROGMEM = "Czujnik";
const char INTL_PARAMETER[] PROGMEM = "Parametr";
const char INTL_VALUE[] PROGMEM = "Wartość";

#include "./airrohr-logo-common.h"
