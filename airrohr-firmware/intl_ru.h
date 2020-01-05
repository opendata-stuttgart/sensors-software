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
#define INTL_PM_SENSOR "Датчик твердых мелкодисперсных частиц"
const char INTL_CONFIGURATION[] PROGMEM = "Конфигурация";
#define INTL_WIFI_SETTINGS "Доступы к локальной сети Wi-Fi"
#define INTL_WIFI_NETWORKS "Загрузить сети Wi-Fi ..."
#define INTL_LANGUAGE "Язык"
const char INTL_NO_NETWORKS[] PROGMEM =  "Cетей не найдено";
const char INTL_NETWORKS_FOUND[] PROGMEM = "Найденые сети: ";
const char INTL_AB_HIER_NUR_ANDERN[] PROGMEM = "Изменяйте значения ниже если действительно знаете что делаете";
const char INTL_SAVE[] PROGMEM = "Сохранить";
const char INTL_SENSORS[] PROGMEM = "Датчики";
const char INTL_MORE_SENSORS[] PROGMEM = "More Sensors";
const char INTL_SDS011[] PROGMEM = "SDS011 ({pm})";
const char INTL_PMS[] PROGMEM = "Plantower PMS(1,3,5,6,7)003 ({pm})";
const char INTL_HPM[] PROGMEM = "Honeywell PM ({pm})";
const char INTL_SPS30[] PROGMEM = "Sensirion SPS30 ({pm})";
const char INTL_PPD42NS[] PROGMEM = "PPD42NS ({pm})";
const char INTL_DHT22[] PROGMEM = "DHT22 ({t}, {h})";
const char INTL_HTU21D[] PROGMEM = "HTU21D ({t}, {h})";
const char INTL_BMP180[] PROGMEM = "BMP180 ({t}, {p})";
const char INTL_BMX280[] PROGMEM = "BMP280/BME280 ({t}, {h}, {p})";
const char INTL_SHT3X[] PROGMEM = "SHT3X ({t}, {h})";
const char INTL_DS18B20[] PROGMEM = "DS18B20 ({t})";
const char INTL_DNMS[] PROGMEM = "DNMS ({l_a})";
const char INTL_DNMS_CORRECTION[] PROGMEM ="поправка в dB(A)";
const char INTL_NEO6M[] PROGMEM = "GPS (NEO 6M)";
const char INTL_BASICAUTH[] PROGMEM = "Активировать аутентификацию для входа в интерфейс сенсора";

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
const char INTL_LCD2004_3F[] PROGMEM = "LCD 2004 (I2C: 0x3F)";
const char INTL_DISPLAY_WIFI_INFO[] PROGMEM = "Отображать информацию о WiFi";
const char INTL_DISPLAY_DEVICE_INFO[] PROGMEM = "Отображать информацию об устройстве";
const char INTL_DEBUG_LEVEL[] PROGMEM = "Уровень&nbsp;отладки";
const char INTL_MEASUREMENT_INTERVAL[] PROGMEM = "Измерительный интервал";
const char INTL_DURATION_ROUTER_MODE[] PROGMEM = "Длительность режима маршрутизатора";
const char INTL_MORE_APIS[] PROGMEM = "Другие API";
const char INTL_SEND_TO_OWN_API[] PROGMEM = "Отправить в свой API";
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
#define INTL_HOME "Меню"
#define INTL_BACK_TO_HOME "Вернуться в основное меню"
const char INTL_CURRENT_DATA[] PROGMEM = "Текущие значения";
const char INTL_DEVICE_STATUS[] PROGMEM = "Состояние устройства";
#define INTL_ACTIVE_SENSORS_MAP "Карта активных датчиков (внешняя ссылка)"
#define INTL_CONFIGURATION_DELETE "Удалить конфигурацию"
#define INTL_CONFIGURATION_REALLY_DELETE "Подтвердите удаление конфигурации!"
#define INTL_DELETE "Удалить"
#define INTL_CANCEL "Отменить"
#define INTL_REALLY_RESTART_SENSOR "Подтвердите перезапуск устройства!"
#define INTL_RESTART "Перезапустить"
const char INTL_SAVE_AND_RESTART[] PROGMEM = "Сохранить и перезапустить";
#define INTL_FIRMWARE "Прошивка"
const char INTL_DEBUG_SETTING_TO[] PROGMEM = "Настройки отладки";
#define INTL_NONE "отключена"
#define INTL_ERROR "только ошибки"
#define INTL_WARNING "предупреждения"
#define INTL_MIN_INFO "минимум информации"
#define INTL_MED_INFO "среднеинформативно"
#define INTL_MAX_INFO "максимум информации"
#define INTL_CONFIG_DELETED "Config.json удалён"
#define INTL_CONFIG_CAN_NOT_BE_DELETED "Config.json нельзя удалить"
#define INTL_CONFIG_NOT_FOUND "Config.json не найден"
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
#define INTL_NUMBER_OF_MEASUREMENTS "Количество измерений"
#define INTL_TIME_SENDING_MS "Время, потраченное на отправку"
#define INTL_SENSOR "Датчик"
#define INTL_PARAMETER "Параметр"
#define INTL_VALUE "Значение"

#include "./airrohr-logo-common.h"
