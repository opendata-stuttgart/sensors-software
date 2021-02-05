/*
 *	airRohr firmware
 *	Copyright (C) 2016-2018  Code for Stuttgart a.o.
 *
 *  Serbian translations
 *
 *	Texts should be as short as possible
 */

#define INTL_LANG "SR"
#define INTL_PM_SENSOR "Сензор суспендованих честица"
const char INTL_CONFIGURATION[] PROGMEM = "Подешавања";
#define INTL_WIFI_SETTINGS "WiFi подешавања"
#define INTL_WIFI_NETWORKS "Тражење WiFi мрежа..."
#define INTL_LANGUAGE "Језик"
const char INTL_NO_NETWORKS[] PROGMEM =  "Није пронађена ниједна WiFi мрежа";
const char INTL_NETWORKS_FOUND[] PROGMEM = "Пронађене мреже: ";
const char INTL_AB_HIER_NUR_ANDERN[] PROGMEM = "Напредна подешавања (само ако знате шта радите)";
const char INTL_SAVE[] PROGMEM = "Сачувај";
const char INTL_SENSORS[] PROGMEM = "Сензори";
const char INTL_MORE_SENSORS[] PROGMEM = "Још сензора";
const char INTL_SDS011[] PROGMEM = "SDS011 ({pm})";
const char INTL_PMS[] PROGMEM = "Plantower PMS(1,3,5,6,7)003 ({pm})";
const char INTL_HPM[] PROGMEM = "Honeywell PM ({pm})";
const char INTL_NPM[] PROGMEM = "Tera Sensor Next PM ({pm})";
const char INTL_SPS30[] PROGMEM = "Sensirion SPS30 ({pm})";
const char INTL_PPD42NS[] PROGMEM = "PPD42NS ({pm})";
const char INTL_DHT22[] PROGMEM = "DHT22 ({t}, {h})";
const char INTL_HTU21D[] PROGMEM = "HTU21D ({t}, {h})";
const char INTL_BMP180[] PROGMEM = "BMP180 ({t}, {p})";
const char INTL_BMX280[] PROGMEM = "BME280 ({t}, {h}, {p}), BMP280 ({t}, {p})";
const char INTL_SHT3X[] PROGMEM = "SHT3X ({t}, {h})";
const char INTL_DS18B20[] PROGMEM = "DS18B20 ({t})";
const char INTL_DNMS[] PROGMEM = "DNMS ({l_a})";
const char INTL_DNMS_CORRECTION[] PROGMEM = "Исправка у dB(A)";
const char INTL_TEMP_CORRECTION[] PROGMEM = "Исправка у °C";
const char INTL_NEO6M[] PROGMEM = "GPS (NEO 6M)";
const char INTL_BASICAUTH[] PROGMEM = "Ауторизација";
#define INTL_REPORT_ISSUE "Пријавите проблем"

const char INTL_FS_WIFI_DESCRIPTION[] PROGMEM = "WiFi сензор у режиму подешавања";
const char INTL_FS_WIFI_NAME[] PROGMEM = "Назив";
const char INTL_MORE_SETTINGS[] PROGMEM = "Још подешавања";
const char INTL_AUTO_UPDATE[] PROGMEM = "Аутоматски ажурирај фирмвер";
const char INTL_USE_BETA[] PROGMEM = "Користи фирмвер у бети";
const char INTL_DISPLAY[] PROGMEM = "OLED SSD1306";
const char INTL_SH1106[] PROGMEM = "OLED SH1106";
const char INTL_FLIP_DISPLAY[] PROGMEM = "Окрени OLED дисплеј (180°)";
const char INTL_LCD1602_27[] PROGMEM = "LCD 1602 (I2C: 0x27)";
const char INTL_LCD1602_3F[] PROGMEM = "LCD 1602 (I2C: 0x3F)";
const char INTL_LCD2004_27[] PROGMEM = "LCD 2004 (I2C: 0x27)";
const char INTL_LCD2004_3F[] PROGMEM = "LCD 2004 (I2C: 0x3F)";
const char INTL_DISPLAY_WIFI_INFO[] PROGMEM = "Прикажи WiFi податке";
const char INTL_DISPLAY_DEVICE_INFO[] PROGMEM = "Прикаже информације о уређају";
const char INTL_DEBUG_LEVEL[] PROGMEM = "Ниво&nbsp;исправке";
const char INTL_MEASUREMENT_INTERVAL[] PROGMEM = "Интервал мерења";
const char INTL_DURATION_ROUTER_MODE[] PROGMEM = "Трајање режима рутера";
const char INTL_MORE_APIS[] PROGMEM = "Још API-ја";
const char INTL_SEND_TO_OWN_API[] PROGMEM = "Пошаљи податке мом API-ју";
const char INTL_SERVER[] PROGMEM = "Сервер";
const char INTL_PATH[] PROGMEM = "Путања";
const char INTL_PORT[] PROGMEM = "Порт";
const char INTL_USER[] PROGMEM = "Корисник";
const char INTL_PASSWORD[] PROGMEM = "Лозинка";
const char INTL_MEASUREMENT[] PROGMEM = "Мерење";
const char INTL_SEND_TO[] PROGMEM = "Пошаљи на {v}";
const char INTL_READ_FROM[] PROGMEM = "Прочитај из {v}";
const char INTL_SENSOR_IS_REBOOTING[] PROGMEM = "Сензор се поново покреће.";
const char INTL_RESTART_DEVICE[] PROGMEM = "Поново покрени уређај";
const char INTL_DELETE_CONFIG[] PROGMEM = "Избриши сачувана подешавања";
const char INTL_RESTART_SENSOR[] PROGMEM = "Поново покрени сензор";
#define INTL_HOME "Почетна"
#define INTL_BACK_TO_HOME "Повратак на почетну страну"
const char INTL_CURRENT_DATA[] PROGMEM = "Тренутна мерења";
const char INTL_DEVICE_STATUS[] PROGMEM = "Статус уређаја";
#define INTL_ACTIVE_SENSORS_MAP "Мапа активних сензора (спољашњи линк)"
#define INTL_CONFIGURATION_DELETE "Избриши подешавања"
#define INTL_CONFIGURATION_REALLY_DELETE "Јесте ли сигурни да желите да избришете подешавања?"
#define INTL_DELETE "Избриши"
#define INTL_CANCEL "Откажи"
#define INTL_REALLY_RESTART_SENSOR "Јесте ли сигурни да желите да поново покренете сензор?"
#define INTL_RESTART "Поново покрени"
const char INTL_SAVE_AND_RESTART[] PROGMEM = "Сачувај и поново покрени";
#define INTL_FIRMWARE "Верзија фирмвера"
const char INTL_DEBUG_SETTING_TO[] PROGMEM = "Подеси уклањање грешака на";
#define INTL_NONE "ништа"
#define INTL_ERROR "грешке"
#define INTL_WARNING "упозорења"
#define INTL_MIN_INFO "најмање информација"
#define INTL_MED_INFO "средње информација"
#define INTL_MAX_INFO "највише информцаија"
#define INTL_CONFIG_DELETED "Config.json је избрисан"
#define INTL_CONFIG_CAN_NOT_BE_DELETED "Config.json се не може избрисати"
#define INTL_CONFIG_NOT_FOUND "Config.json није пронађен"
const char INTL_TIME_TO_FIRST_MEASUREMENT[] PROGMEM = "Још {v} секунди до првог мерења.";
const char INTL_TIME_SINCE_LAST_MEASUREMENT[] PROGMEM = " секунди од последњег мерења.";
const char INTL_PARTICLES_PER_LITER[] PROGMEM = "честица/литру";
const char INTL_PARTICULATE_MATTER[] PROGMEM = "суспендоване честице";
const char INTL_TEMPERATURE[] PROGMEM = "температура";
const char INTL_HUMIDITY[] PROGMEM = "влажност ваздуха";
const char INTL_PRESSURE[] PROGMEM = "ваздушни притисак";
const char INTL_LEQ_A[] PROGMEM = "LAeq";
const char INTL_LA_MIN[] PROGMEM = "LA мин";
const char INTL_LA_MAX[] PROGMEM = "LA макс";
const char INTL_LATITUDE[] PROGMEM = "Географска ширина";
const char INTL_LONGITUDE[] PROGMEM = "Географска дужина";
const char INTL_ALTITUDE[] PROGMEM = "Надморска висина";
const char INTL_TIME_UTC[] PROGMEM = "Време (UTC)";
const char INTL_SIGNAL_STRENGTH[] PROGMEM = "јачина сигнала";
const char INTL_SIGNAL_QUALITY[] PROGMEM = "квалитет сигнала";
#define INTL_NUMBER_OF_MEASUREMENTS "Број мерења"
#define INTL_TIME_SENDING_MS "Време утрошено за слање"
#define INTL_SENSOR "Сензор"
#define INTL_PARAMETER "Параметар"
#define INTL_VALUE "Вредност"

#include "./airrohr-logo-common.h"
