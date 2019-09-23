/*
 *	airRohr firmware
 *	Copyright (C) 2016-2018  Code for Stuttgart a.o.
 * 
 *  Russian translations
 * 
 *	Texts should be as short as possible
 *	We only have 512 kB for the entire firmware
 */

const char INTL_LANG[] = "RU";
const char INTL_PM_SENSOR[] PROGMEM = "Датчик твердых мелкодисперсных частиц";
const char INTL_CONFIGURATION[] PROGMEM = "Конфигурация";
const char INTL_WIFI_SETTINGS[] PROGMEM = "Данные Wi-Fi";
const char INTL_WIFI_NETWORKS[] PROGMEM = "Загрузить сети Wi-Fi ...";
const char INTL_LANGUAGE[] PROGMEM = "Язык";
const char INTL_NO_NETWORKS[] PROGMEM =  "Cетей не найдено";
const char INTL_NETWORKS_FOUND[] PROGMEM = "Найденые сети: ";
const char INTL_AB_HIER_NUR_ANDERN[] PROGMEM = "Изменяйте значения ниже если действительно знаете что делаете";
const char INTL_SAVE[] PROGMEM = "Сохранить";
const char INTL_SENSORS[] PROGMEM = "Датчики";
const char INTL_SDS011[] PROGMEM = "SDS011 ({pm})";
const char INTL_PMS[] PROGMEM = "Plantower PMS(1,3,5,6,7)003 ({pm})";
const char INTL_HPM[] PROGMEM = "Honeywell PMS";
const char INTL_SPS30[] PROGMEM = "Sensirion SPS30 ({pm})";
const char INTL_PPD42NS[] PROGMEM = "PPD42NS";
const char INTL_DHT22[] PROGMEM = "DHT22 ({t}, {h})";
const char INTL_HTU21D[] PROGMEM = "HTU21D ({t}, {h})";
const char INTL_BMP180[] PROGMEM = "BMP180 ({t}, {p})";
const char INTL_BMX280[] PROGMEM = "BMP280/BME280 ({t}, {h}, {p})";
const char INTL_DS18B20[] PROGMEM = "DS18B20 ({t})";
const char INTL_DNMS[] PROGMEM = "DNMS ({l_a})";
const char INTL_DNMS_CORRECTION[] PROGMEM ="поправка в dB(A)";
const char INTL_NEO6M[] PROGMEM = "GPS (NEO 6M)";
const char INTL_BASICAUTH[] PROGMEM = "Активировать аутентификацию ";
const char INTL_FS_WIFI[] PROGMEM = "Датчик Wi-Fi";
const char INTL_FS_WIFI_DESCRIPTION[] PROGMEM = "Название WiFi устройства в режиме конфигурации";
const char INTL_FS_WIFI_NAME[] PROGMEM = "Имя";
const char INTL_MORE_SETTINGS[] PROGMEM ="Дополнительные настройки";
const char INTL_AUTO_UPDATE[] PROGMEM = "Автоматическое обновление";
const char INTL_USE_BETA[] PROGMEM = "Загружать бета-версии";
const char INTL_DISPLAY[] PROGMEM = "OLED SSD1306";
const char INTL_SH1106[] PROGMEM = "OLED SH1106";
const char INTL_FLIP_DISPLAY[] PROGMEM = "Перевернуть OLED экран";
const char INTL_LCD1602_27[] PROGMEM = "LCD 1602 (I2C: 0x27)";
const char INTL_LCD1602_3F[] PROGMEM = "LCD 1602 (I2C: 0x3F)";
const char INTL_LCD2004_27[] PROGMEM = "LCD 2004 (I2C: 0x27)";
const char INTL_DISPLAY_WIFI_INFO[] PROGMEM = "Отображарь информацию о WiFi";
const char INTL_DISPLAY_DEVICE_INFO[] PROGMEM = "Отображать информацию об устройстве";
const char INTL_DEBUG_LEVEL[] PROGMEM = "Уровень отладки";
const char INTL_MEASUREMENT_INTERVAL[] PROGMEM = "Измерительный интервал";
const char INTL_DURATION_ROUTER_MODE[] PROGMEM = "Длительность режима маршрутизатора";
const char INTL_MORE_APIS[] PROGMEM = "Другие API";
const char INTL_SEND_TO_OWN_API[] PROGMEM = "Отправить в свой собственный API";
const char INTL_SERVER[] PROGMEM = "Сервер"; 
const char INTL_PATH[] PROGMEM = "Путь"; 
const char INTL_PORT[] PROGMEM = "Порт"; 
const char INTL_USER[] PROGMEM = "Пользователь"; 
const char INTL_PASSWORD[] PROGMEM = "Пароль"; 
const char INTL_SEND_TO[] PROGMEM = "Отправлять в {v}"; 
const char INTL_READ_FROM[] PROGMEM = "Считывать с {v}";
const char INTL_SENSOR_IS_REBOOTING[] PROGMEM = "Устройство перезапускается...";
const char INTL_RESTART_DEVICE[] PROGMEM = "Перезапустить устройство";
const char INTL_DELETE_CONFIG[] PROGMEM = "Config.json удалить";
const char INTL_RESTART_SENSOR[] PROGMEM = "Перезапустить устройство";
const char INTL_HOME[] PROGMEM = "Меню";
const char INTL_BACK_TO_HOME[] PROGMEM = "Вернуться в основное меню";
const char INTL_CURRENT_DATA[] PROGMEM = "Текущие значения";
const char INTL_ACTIVE_SENSORS_MAP[] PROGMEM = "Карта активных датчиков (внешняя ссылка)";
const char INTL_CONFIGURATION_DELETE[] PROGMEM = "Удалить конфигурацию";
const char INTL_CONFIGURATION_REALLY_DELETE[] PROGMEM = "Подтвердите удаление конфигурации!";
const char INTL_DELETE[] PROGMEM = "Удалить";
const char INTL_CANCEL[] PROGMEM = "Отменить";
const char INTL_REALLY_RESTART_SENSOR[] PROGMEM = "Подтвердите перезапуск устройства!";
const char INTL_RESTART[] PROGMEM = "Перезапустить";
const char INTL_SAVE_AND_RESTART[] PROGMEM = "Сохранить и перезапустить";
const char INTL_FIRMWARE[] PROGMEM = "Прошивка";
const char INTL_DEBUG_SETTING_TO[] PROGMEM = "Настройки отладки";
const char INTL_NONE[] PROGMEM = "отключена";
const char INTL_ERROR[] PROGMEM = "только ошибки";
const char INTL_WARNING[] PROGMEM = "предупреждения";
const char INTL_MIN_INFO[] PROGMEM = "минимум информации";
const char INTL_MED_INFO[] PROGMEM = "среднеинформативно";
const char INTL_MAX_INFO[] PROGMEM = "максимум информации";
const char INTL_CONFIG_DELETED[] PROGMEM = "Config.json удалён";
const char INTL_CONFIG_CAN_NOT_BE_DELETED[] PROGMEM = "Config.json нельзя удалить";
const char INTL_CONFIG_NOT_FOUND[] PROGMEM = "Config.json не найден";
const char INTL_TIME_TO_FIRST_MEASUREMENT[] PROGMEM = "Еще {v} секунд до первого замера.";
const char INTL_TIME_SINCE_LAST_MEASUREMENT[] PROGMEM = " секунд после последнего замера.";
const char INTL_PARTICLES_PER_LITER[] PROGMEM = "Частицы/ литр";
const char INTL_PARTICULATE_MATTER[] PROGMEM = "Датчик пыли";
const char INTL_TEMPERATURE[] PROGMEM = "Температура";
const char INTL_HUMIDITY[] PROGMEM = "Относительная влажность";
const char INTL_PRESSURE[] PROGMEM = "Давление воздуха";
const char INTL_LEQ_A[] PROGMEM = "LAeq";
const char INTL_LA_MIN[] PROGMEM = "LA min";
const char INTL_LA_MAX[] PROGMEM = "LA max";
const char INTL_LATITUDE[] PROGMEM = "Широта";
const char INTL_LONGITUDE[] PROGMEM = "Долгота";
const char INTL_ALTITUDE[] PROGMEM = "Высота";
const char INTL_DATE[] PROGMEM = "Дата";
const char INTL_TIME[] PROGMEM = "Время";
const char INTL_SIGNAL_STRENGTH[] PROGMEM = "Сигнал";
const char INTL_SIGNAL_QUALITY[] PROGMEM = "Качество";
const char INTL_NUMBER_OF_MEASUREMENTS[] PROGMEM = "Количество измерений:";
const char INTL_SENSOR[] PROGMEM = "Датчик";
const char INTL_PARAMETER[] PROGMEM = "Параметр";
const char INTL_VALUE[] PROGMEM = "Значение";

#include "./airrohr-logo-common.h"
