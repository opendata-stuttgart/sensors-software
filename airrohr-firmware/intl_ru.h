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
const char INTL_PM_SENSOR[] PROGMEM = "Датчик пыли";
const char INTL_CONFIGURATION[] PROGMEM = "Конфигурация";
const char INTL_WIFI_SETTINGS[] PROGMEM = "Данные Wi-Fi";
const char INTL_WIFI_NETWORKS[] PROGMEM = "Загрузить сети Wi-Fi ...";
const char INTL_LANGUAGE[] PROGMEM = "Язык";
const char INTL_NO_NETWORKS[] PROGMEM =  "Cетей не найдено";
const char INTL_NETWORKS_FOUND[] PROGMEM = "Найденые сети: ";
const char INTL_AB_HIER_NUR_ANDERN[] PROGMEM = "Измените это только, если вы действительно знаете, что делаете";
const char INTL_SAVE[] PROGMEM = "Сохранить";
const char INTL_SENSORS[] PROGMEM = "Датчики";
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
const char INTL_BASICAUTH[] PROGMEM = "Активировать аутентификацию ";
const char INTL_FS_WIFI[] PROGMEM = "Датчик Wi-Fi";
const char INTL_FS_WIFI_DESCRIPTION[] PROGMEM = "Название Wi-Fi датчика в режиме конфигурации";
const char INTL_FS_WIFI_NAME[] PROGMEM = "Имя";
const char INTL_MORE_SETTINGS[] PROGMEM ="Дополнительные настройки";
const char INTL_AUTO_UPDATE[] PROGMEM = "Автоматическое обновление";
const char INTL_USE_BETA[] PROGMEM = "Загрузить бета-версии";
const char INTL_DISPLAY[] PROGMEM = "OLED SSD1306";
const char INTL_SH1106[] PROGMEM = "OLED SH1106";
const char INTL_LCD1602_27[] PROGMEM = "LCD 1602 (I2C: 0x27)";
const char INTL_LCD1602_3F[] PROGMEM = "LCD 1602 (I2C: 0x3F)";
const char INTL_LCD2004_27[] PROGMEM = "LCD 2004 (I2C: 0x27)";
const char INTL_DEBUG_LEVEL[] PROGMEM = "Дебаг&nbsp;Уровень";
const char INTL_MEASUREMENT_INTERVAL[] PROGMEM = "Измерительный интервал";
const char INTL_DURATION_ROUTER_MODE[] PROGMEM = "Продолжительность&nbsp;Режим маршрутизатора";
const char INTL_MORE_APIS[] PROGMEM = "Другие API";
const char INTL_SEND_TO_OWN_API[] PROGMEM = "Отправить в свой собственный API";
const char INTL_SERVER[] PROGMEM = "Сервер"; 
const char INTL_PATH[] PROGMEM = "Путь"; 
const char INTL_PORT[] PROGMEM = "Порт"; 
const char INTL_USER[] PROGMEM = "Пользователь"; 
const char INTL_PASSWORD[] PROGMEM = "Пароль"; 
const char INTL_SEND_TO[] PROGMEM = "Отправить {v}"; 
const char INTL_READ_FROM[] PROGMEM = "Читает {v}";
const char INTL_SENSOR_IS_REBOOTING[] PROGMEM = "Датчик перезапускается.";
const char INTL_RESTART_DEVICE[] PROGMEM = "Перезапустить устройство";
const char INTL_DELETE_CONFIG[] PROGMEM = "Config.json удалить";
const char INTL_RESTART_SENSOR[] PROGMEM = "Датчик Перезапустить";
const char INTL_HOME[] PROGMEM = "Сводка";
const char INTL_BACK_TO_HOME[] PROGMEM = "Вернуться на главную страницу";
const char INTL_CURRENT_DATA[] PROGMEM = "Текущие значения";
const char INTL_ACTIVE_SENSORS_MAP[] PROGMEM = "Карта активных датчиков (внешняя ссылка)";
const char INTL_CONFIGURATION_DELETE[] PROGMEM = "Удалить конфигурацию";
const char INTL_CONFIGURATION_REALLY_DELETE[] PROGMEM = "Действительно удалить конфигурацию?";
const char INTL_DELETE[] PROGMEM = "Удалить";
const char INTL_CANCEL[] PROGMEM = "Отменить";
const char INTL_REALLY_RESTART_SENSOR[] PROGMEM = "Действительно перезапустить датчик";
const char INTL_RESTART[] PROGMEM = "Перезапустить";
const char INTL_SAVE_AND_RESTART[] PROGMEM = "Сохранить и перезапустить";
const char INTL_FIRMWARE[] PROGMEM = "Прошивки";
const char INTL_DEBUG_SETTING_TO[] PROGMEM = "Установка отладки";
const char INTL_NONE[] PROGMEM = "none";
const char INTL_ERROR[] PROGMEM = "ошибка";
const char INTL_WARNING[] PROGMEM = "предупреждение";
const char INTL_MIN_INFO[] PROGMEM = "мин. информация";
const char INTL_MED_INFO[] PROGMEM = "мед. информация";
const char INTL_MAX_INFO[] PROGMEM = "макс. информация";
const char INTL_CONFIG_DELETED[] PROGMEM = "Config.json удалён";
const char INTL_CONFIG_CAN_NOT_BE_DELETED[] PROGMEM = "Config.json нельзя удалить";
const char INTL_CONFIG_NOT_FOUND[] PROGMEM = "Config.json не найден";
const char INTL_TIME_TO_FIRST_MEASUREMENT[] PROGMEM = "Еще {v} секунд до первого измерения.";
const char INTL_TIME_SINCE_LAST_MEASUREMENT[] PROGMEM = " Секунд после последнего измерения.";
const char INTL_PARTICLES_PER_LITER[] PROGMEM = "Частицы/ литр";
const char INTL_PARTICULATE_MATTER[] PROGMEM = "Датчик пыли";
const char INTL_TEMPERATURE[] PROGMEM = "Температура";
const char INTL_HUMIDITY[] PROGMEM = "Относительная влажность";
const char INTL_PRESSURE[] PROGMEM = "Давление воздуха";
const char INTL_LATITUDE[] PROGMEM = "Широта";
const char INTL_LONGITUDE[] PROGMEM = "Длина";
const char INTL_ALTITUDE[] PROGMEM = "Высота";
const char INTL_DATE[] PROGMEM = "Дата";
const char INTL_TIME[] PROGMEM = "Время";
const char INTL_SIGNAL_STRENGTH[] PROGMEM = "Сигнал";
const char INTL_SIGNAL_QUALITY[] PROGMEM = "Качество";
const char INTL_NUMBER_OF_MEASUREMENTS[] PROGMEM = "Количество измерений:";
const char INTL_SENSOR[] PROGMEM = "Датчик";
const char INTL_PARAMETER[] PROGMEM = "Параметр";
const char INTL_VALUE[] PROGMEM = "Значение";

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
