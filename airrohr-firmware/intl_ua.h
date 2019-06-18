/*
 *	airRohr firmware
 *	Copyright (C) 2016-2018  Code for Stuttgart a.o.
 * 
 *  Ukrainian translations
 * 
 *	Texts should be as short as possible
 *	We only have 512 kB for the entire firmware
 */

const char INTL_LANG[] = "UA";
const char INTL_PM_SENSOR[] PROGMEM = "Вимірювач дрібних часток";
const char INTL_CONFIGURATION[] PROGMEM = "Налаштування";
const char INTL_WIFI_SETTINGS[] PROGMEM = "Параметри WiFi";
const char INTL_WIFI_NETWORKS[] PROGMEM = "Пошук WiFi мереж...";
const char INTL_LANGUAGE[] PROGMEM = "Мова";
const char INTL_NO_NETWORKS[] PROGMEM =  "Не знайдено жодної Wifi мережі";
const char INTL_NETWORKS_FOUND[] PROGMEM = "Знайдені мережі";
const char INTL_AB_HIER_NUR_ANDERN[] PROGMEM = "Експертні параметри (тільки якщо ви розумієте, що робите)";
const char INTL_SAVE[] PROGMEM = "Зберегти";
const char INTL_SENSORS[] PROGMEM = "Сенсори";
const char INTL_SDS011[] PROGMEM = "SDS011 ({pm})";
const char INTL_PMS[] PROGMEM = "Plantower PMS(1,3,5,6,7)003 ({pm})";
const char INTL_HPM[] PROGMEM = "Honeywell PMS";
const char INTL_PPD42NS[] PROGMEM = "PPD42NS";
const char INTL_DHT22[] PROGMEM = "DHT22 ({t}, {h})";
const char INTL_HTU21D[] PROGMEM = "HTU21D ({t}, {h})";
const char INTL_BMP180[] PROGMEM = "BMP180 ({t}, {p})";
const char INTL_BMP280[] PROGMEM = "BMP280 ({t}, {p})";
const char INTL_BME280[] PROGMEM = "BME280 ({t}, {h}, {p})";
const char INTL_DS18B20[] PROGMEM = "DS18B20 ({t})";
const char INTL_NEO6M[] PROGMEM = "GPS (NEO 6M)";
const char INTL_BASICAUTH[] PROGMEM = "Авторизація";
const char INTL_FS_WIFI[] PROGMEM = "WiFi сенсор";
const char INTL_FS_WIFI_DESCRIPTION[] PROGMEM = "WiFi сенсор в режимі конфігурації";
const char INTL_FS_WIFI_NAME[] PROGMEM = "Ім'я";
const char INTL_MORE_SETTINGS[] PROGMEM ="Додаткові параметри";
const char INTL_AUTO_UPDATE[] PROGMEM = "Автооновлення мікропрограми";
const char INTL_USE_BETA[] PROGMEM = "Встановлювати бета-версії мікропрограми";
const char INTL_DISPLAY[] PROGMEM = "OLED SSD1306";
const char INTL_SH1106[] PROGMEM = "OLED SH1106";
const char INTL_LCD1602_27[] PROGMEM = "LCD 1602 (I2C: 0x27)";
const char INTL_LCD1602_3F[] PROGMEM = "LCD 1602 (I2C: 0x3F)";
const char INTL_LCD2004_27[] PROGMEM = "LCD 2004 (I2C: 0x27)";
const char INTL_DEBUG_LEVEL[] PROGMEM = "Рівень&nbsp;Зневадження";
const char INTL_MEASUREMENT_INTERVAL[] PROGMEM = "Інтервал між вимірюваннями";
const char INTL_DURATION_ROUTER_MODE[] PROGMEM = "Тривалість режиму роутера";
const char INTL_MORE_APIS[] PROGMEM = "Додаткові API";
const char INTL_SEND_TO_OWN_API[] PROGMEM = "Відправляти дані на власний API";
const char INTL_SERVER[] PROGMEM = "Сервер"; 
const char INTL_PATH[] PROGMEM = "Шлях"; 
const char INTL_PORT[] PROGMEM = "Порт"; 
const char INTL_USER[] PROGMEM = "Користувач"; 
const char INTL_PASSWORD[] PROGMEM = "Пароль"; 
const char INTL_SEND_TO[] PROGMEM = "Відправляти до {v}"; 
const char INTL_READ_FROM[] PROGMEM = "Читати з {v}";
const char INTL_SENSOR_IS_REBOOTING[] PROGMEM = "Сенсор перезавантажується.";
const char INTL_RESTART_DEVICE[] PROGMEM = "Перезапустити пристрій";
const char INTL_DELETE_CONFIG[] PROGMEM = "видалити збережену конфігурацію";
const char INTL_RESTART_SENSOR[] PROGMEM = "Перезапустити сенсор";
const char INTL_HOME[] PROGMEM = "Головна";
const char INTL_BACK_TO_HOME[] PROGMEM = "На головну сторінку";
const char INTL_CURRENT_DATA[] PROGMEM = "Поточні показники";
const char INTL_ACTIVE_SENSORS_MAP[] PROGMEM = "Мапа активних сенсорів(зовнішнє посилання)";
const char INTL_CONFIGURATION_DELETE[] PROGMEM = "Видалити конфігурацію";
const char INTL_CONFIGURATION_REALLY_DELETE[] PROGMEM = "Ви точно хочете видалити конфігурацію?";
const char INTL_DELETE[] PROGMEM = "Видалити";
const char INTL_CANCEL[] PROGMEM = "Скасувати";
const char INTL_REALLY_RESTART_SENSOR[] PROGMEM = "Ви точно хочете перезавантажити сенсор?";
const char INTL_RESTART[] PROGMEM = "Перезавантажити";
const char INTL_SAVE_AND_RESTART[] PROGMEM = "Зберегти та перезавантажити";
const char INTL_FIRMWARE[] PROGMEM = "Версія мікропрограми";
const char INTL_DEBUG_SETTING_TO[] PROGMEM = "Зневадження: ";
const char INTL_NONE[] PROGMEM = "вимкнено";
const char INTL_ERROR[] PROGMEM = "лише помилки";
const char INTL_WARNING[] PROGMEM = "попередження";
const char INTL_MIN_INFO[] PROGMEM = "мінімум інформації";
const char INTL_MED_INFO[] PROGMEM = "помірно інформації";
const char INTL_MAX_INFO[] PROGMEM = "максимум інформації";
const char INTL_CONFIG_DELETED[] PROGMEM = "Конфігурацію видалено";
const char INTL_CONFIG_CAN_NOT_BE_DELETED[] PROGMEM = "Конфігурацію не можна видалити";
const char INTL_CONFIG_NOT_FOUND[] PROGMEM = "Конфігурацію не знайдено";
const char INTL_TIME_TO_FIRST_MEASUREMENT[] PROGMEM = "Ще {v} секунд до першого вимірювання";
const char INTL_TIME_SINCE_LAST_MEASUREMENT[] PROGMEM = "секунд від останнього вимірювання.";
const char INTL_PARTICLES_PER_LITER[] PROGMEM = "часток/літр";
const char INTL_PARTICULATE_MATTER[] PROGMEM = "Вимірювач дрібних часток";
const char INTL_TEMPERATURE[] PROGMEM = "температура";
const char INTL_HUMIDITY[] PROGMEM = "вологість";
const char INTL_PRESSURE[] PROGMEM = "атмосферний тиск";
const char INTL_LATITUDE[] PROGMEM = "Широта";
const char INTL_LONGITUDE[] PROGMEM = "Довгота";
const char INTL_ALTITUDE[] PROGMEM = "Висота";
const char INTL_DATE[] PROGMEM = "Дата";
const char INTL_TIME[] PROGMEM = "Час";
const char INTL_SIGNAL_STRENGTH[] PROGMEM = "потужність сигналу";
const char INTL_SIGNAL_QUALITY[] PROGMEM = "якість сигналу";
const char INTL_NUMBER_OF_MEASUREMENTS[] PROGMEM = "Кількість вимірювань:";
const char INTL_SENSOR[] PROGMEM = "Сенсор";
const char INTL_PARAMETER[] PROGMEM = "Параметр";
const char INTL_VALUE[] PROGMEM = "Значення";

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
