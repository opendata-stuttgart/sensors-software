/*
 *	airRohr firmware
 *	Copyright (C) 2016-2018  Code for Stuttgart a.o.
 * 
 *  Bulgarian translations
 * 
 *	Texts should be as short as possible
 *	We only have 512 kB for the entire firmware
 */

const char INTL_LANG[] = "BG";
const char INTL_FEINSTAUBSENSOR[] PROGMEM = "Сензор за прахови частици";
const char INTL_KONFIGURATION[] PROGMEM = "Конфигурация";
const char INTL_WLAN_DATEN[] PROGMEM = "Настройки за WiFi";
const char INTL_WLAN_LISTE[] PROGMEM = "Зареждането WiFi мрежи ...";
const char INTL_SPRACHE[] PROGMEM = "Език";
const char INTL_KEINE_NETZWERKE[] PROGMEM =  "Няма намерени мрежи";
const char INTL_NETZWERKE_GEFUNDEN[] PROGMEM = "Намерени мрежи: ";
const char INTL_AB_HIER_NUR_ANDERN[] PROGMEM = "Разширени настройки (само ако знаете какво правите)";
const char INTL_SPEICHERN[] PROGMEM = "Запиши";
const char INTL_SENSOREN[] PROGMEM = "Сензори";
const char INTL_SDS011[] PROGMEM = "SDS011 (прахови частици)";
const char INTL_PMS24[] PROGMEM = "PMS3003";
const char INTL_PMS32[] PROGMEM = "PMS1003, PMS5003, PMS6003, PMS7003";
const char INTL_HPM[] PROGMEM = "Honeywell сензора за прахови частици";
const char INTL_PPD42NS[] PROGMEM = "PPD42NS";
const char INTL_DHT22[] PROGMEM = "DHT22 ({t}, {h})";
const char INTL_HTU21D[] PROGMEM = "HTU21D ({t}, {h})";
const char INTL_BMP180[] PROGMEM = "BMP180 ({t}, {p})";
const char INTL_BMP280[] PROGMEM = "BMP280 ({t}, {p})";
const char INTL_BME280[] PROGMEM = "BME280 ({t}, {h}, {p})";
const char INTL_DS18B20[] PROGMEM = "DS18B20 ({t})";
const char INTL_NEO6M[] PROGMEM = "GPS (NEO 6M)";
const char INTL_BASICAUTH[] PROGMEM = "Оторизация";
const char INTL_FS_WIFI[] PROGMEM = "";
const char INTL_FS_WIFI_BESCHREIBUNG[] PROGMEM = "";
const char INTL_FS_WIFI_NAME[] PROGMEM = "";
const char INTL_WEITERE_EINSTELLUNGEN[] PROGMEM ="Още настройки";
const char INTL_AUTO_UPDATE[] PROGMEM = "Автоматична актуализация";
const char INTL_USE_BETA[] PROGMEM = "";
const char INTL_DISPLAY[] PROGMEM = "OLED SSD1306";
const char INTL_SH1106[] PROGMEM = "OLED SH1106";
const char INTL_LCD1602_27[] PROGMEM = "LCD 1602 (I2C: 0x27)";
const char INTL_LCD1602_3F[] PROGMEM = "LCD 1602 (I2C: 0x3F)";
const char INTL_LCD2004_27[] PROGMEM = "LCD 2004 (I2C: 0x27)";
const char INTL_DEBUG_LEVEL[] PROGMEM = "Debug&nbsp;Level";
const char INTL_MESSINTERVALL[] PROGMEM = "";
const char INTL_DAUER_ROUTERMODUS[] PROGMEM = "";
const char INTL_WEITERE_APIS[] PROGMEM = "Още API";
const char INTL_AN_EIGENE_API_SENDEN[] PROGMEM = "Изпращане към собствено API";
const char INTL_SERVER[] PROGMEM = "Сървър"; 
const char INTL_PFAD[] PROGMEM = "Път"; 
const char INTL_PORT[] PROGMEM = "Порт"; 
const char INTL_BENUTZER[] PROGMEM = "Потребител"; 
const char INTL_PASSWORT[] PROGMEM = "Парола"; 
const char INTL_SENDEN_AN[] PROGMEM = "Изпрати до {v}"; 
const char INTL_LESE[] PROGMEM = "Получено от {v}";
const char INTL_GERAT_WIRD_NEU_GESTARTET[] PROGMEM = "";
const char INTL_GERAT_NEU_STARTEN[] PROGMEM = "Рестартирайте устройството";
const char INTL_CONFIG_LOSCHEN[] PROGMEM = "Изтриване на Конфигурацията";
const char INTL_SENSOR_NEU_STARTEN[] PROGMEM = "Рестартиране на сензора";
const char INTL_UBERSICHT[] PROGMEM = "Начало";
const char INTL_ZURUCK_ZUR_STARTSEITE[] PROGMEM = "Обратно към начало";
const char INTL_AKTUELLE_WERTE[] PROGMEM = "Текущи данни";
const char INTL_KARTE_DER_AKTIVEN_SENSOREN[] PROGMEM = "Карта на активните сензори (външен линк)";
const char INTL_KONFIGURATION_LOSCHEN[] PROGMEM = "Изтриване на Конфигурацията";
const char INTL_KONFIGURATION_WIRKLICH_LOSCHEN[] PROGMEM = "Наистина ли искате да изтриете конфигурацията?";
const char INTL_LOSCHEN[] PROGMEM = "Изтрий";
const char INTL_ABBRECHEN[] PROGMEM = "Отказ";
const char INTL_SENSOR_WIRKLICH_NEU_STARTEN[] PROGMEM = "Наистина ли искате да рестартирате сензора?";
const char INTL_NEU_STARTEN[] PROGMEM = "Рестарт";
const char INTL_FIRMWARE[] PROGMEM = "Софтуер версия";
const char INTL_SETZE_DEBUG_AUF[] PROGMEM = "Настройки дебъгването на";
const char INTL_NONE[] PROGMEM = "изключено";
const char INTL_ERROR[] PROGMEM = "само грешки";
const char INTL_WARNING[] PROGMEM = "предупреждения";
const char INTL_MIN_INFO[] PROGMEM = "минимална информация";
const char INTL_MED_INFO[] PROGMEM = "средна информация";
const char INTL_MAX_INFO[] PROGMEM = "пълна информация";
const char INTL_CONFIG_GELOSCHT[] PROGMEM = "Конфигурацията е изтрита";
const char INTL_CONFIG_KONNTE_NICHT_GELOSCHT_WERDEN[] PROGMEM = "Конфигурацията не може да бъде изтрита";
const char INTL_CONFIG_NICHT_GEFUNDEN[] PROGMEM = "Конфигурацията не е открита";
const char INTL_ERSTER_MESSZYKLUS[] PROGMEM = "Oще {v} секунди до първото измерване.";
const char INTL_ZEIT_SEIT_LETZTER_MESSUNG[] PROGMEM = "";
const char INTL_PARTIKEL_LITER[] PROGMEM = "частици/литър";
const char INTL_TEMPERATUR[] PROGMEM = "Температура";
const char INTL_LUFTFEUCHTE[] PROGMEM = "Влажност на въздуха";
const char INTL_LUFTDRUCK[] PROGMEM = "Атмосферно налягане";
const char INTL_LATITUDE[] PROGMEM = "";
const char INTL_LONGITUDE[] PROGMEM = "";
const char INTL_ALTITUDE[] PROGMEM = "";
const char INTL_DATE[] PROGMEM = "";
const char INTL_TIME[] PROGMEM = "";
const char INTL_SIGNAL[] PROGMEM = "Сила на сигнала";
const char INTL_QUALITAT[] PROGMEM = "Качество на сигнала";
const char INTL_ANZAHL_MESSUNGEN[] PROGMEM = "";
const char INTL_SENSOR[] PROGMEM = "Сензор";
const char INTL_PARAMETER[] PROGMEM = "Параметър";
const char INTL_WERT[] PROGMEM = "Стойност";

const char LUFTDATEN_INFO_LOGO_SVG[] PROGMEM = "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"128\" height=\"128\" viewBox=\"0 0 128 128\"><path fill=\"#009A93\" d=\"M123.58 77.76c0-6.22-3.2-11.66-7.96-14.66 2.36-3.87 3.73-8.42 3.73-13.3 0-14.1-11.44-25.52-25.53-25.52-4 0-7.8.93-11.17 2.57C80.63 19.6 74 14.3 66.1 14.3c-7.7 0-14.22 5.07-16.4 12.07-3.05-1.2-6.4-1.87-9.88-1.87-14.94 0-27.06 12.07-27.16 27-5.43 4.47-8.9 11.3-8.9 18.95 0 13.5 10.8 24.45 24.1 24.45h79.32c9.07-.06 16.4-7.7 16.4-17.14z\"/><path fill=\"#fff\" d=\"M55.5 49.92v19.05c0 9.37-7.64 17-17.1 17-9.36 0-17-7.63-17-17 0-9.38 7.64-17.02 17-17.02h.7V56h-.7c-7.1 0-12.88 5.84-12.88 12.96 0 7.13 5.77 12.97 12.9 12.97 7.2 0 12.96-5.85 12.96-12.97V49.92c0-7.2-5.77-12.97-12.97-12.97-7.1 0-12.8 5.78-12.8 12.9v.75h-4.2v-.75c0-9.37 7.7-17.02 17-17.02 9.5 0 17.1 7.65 17.1 17.1zm-5.47 0v19.05c0 6.37-5.17 11.54-11.62 11.54-6.3 0-11.5-5.1-11.5-11.5 0-6.3 5.2-11.5 11.6-11.5h.7v4.1h-.7c-4.1 0-7.5 3.4-7.5 7.5s3.4 7.5 7.5 7.5c4.2 0 7.6-3.4 7.6-7.5V49.9c0-4.2-3.3-7.57-7.5-7.57-4.1 0-7.5 3.38-7.5 7.5v.75H27v-.75c0-6.37 5.17-11.55 11.54-11.55 6.46 0 11.63 5.18 11.63 11.62zm-5.47 0v19.05c0 3.37-2.7 6.14-6.15 6.14-3.3 0-6-2.7-6-6.1 0-3.4 2.7-6.1 6.1-6.1h.7V67h-.7c-1.1 0-2 .9-2 2.02 0 1.1.9 2 2 2 1.2 0 2.1-.9 2.1-2V49.9c0-1.2-.9-2.1-2.1-2.1-1.1 0-2 .9-2 2.03v.75h-4.1v-.75c0-3.38 2.7-6.08 6.1-6.08 3.5 0 6.2 2.7 6.2 6.15zm13.94-2.17v-15h4.05v15H58.5zm4.05 38.16H58.5V49.2h4.05v36.7zm1.42-38.1v-15h4.05v15h-4.05zm0 38.2V49.2h4.05v36.7h-4.05zm5.48-38.1v-15h4.04v15h-4.1zm0 38.2V49.2h4.04v36.7h-4.1zM93.43 33c9.38 0 17.02 7.56 17.02 17 0 9.37-7.64 17-17 17h-.7v-4.1h.68c7.13 0 12.9-5.76 12.9-12.9 0-7.2-5.77-12.95-12.9-12.95-7.2 0-12.96 5.78-12.96 12.98v36h-4.05V49.9c0-9.45 7.57-17.02 17.02-17.02zm0 5.4c6.38 0 11.55 5.16 11.55 11.6 0 6.37-5.17 11.54-11.54 11.54h-.68v-4.1h.67c4.13 0 7.5-3.37 7.5-7.5 0-4.2-3.37-7.5-7.5-7.5-4.2 0-7.5 3.3-7.5 7.5V86h-4.1V49.9c-.03-6.46 5.17-11.6 11.6-11.6zM91.33 86H87.3V49.9c0-3.37 2.76-6.14 6.14-6.14s6.07 2.8 6.07 6.17-2.7 6.06-6 6.06h-.7v-4.1h.7c1.2 0 2.1-.9 2.1-2.1s-.9-2.1-2-2.1-2.1.9-2.1 2.1v36.1zm8.18 0h-4V68.24c1.4-.2 2.7-.5 4-.9.1.6.2 1.16.2 1.68v17zm5.5 0h-4V69c0-.76-.1-1.44-.3-2.1 1.3-.6 2.5-1.28 3.6-2.1.5 1.5.8 2.62.8 4.2v17zm1.4-17c0-1.8-.3-3.38-.9-5.03 1.1-1.04 2-2.1 3-3.22 1.4 2.8 2.1 5.1 2.1 8.27v17h-4.1V69zm-79.8 39.1c1.3.4 1.8 1.27 1.8 2.7 0 2.1-1.2 3-3.9 3h-3.4c-.2 0-.4-.12-.4-.4v-10.45c0-.26.2-.4.4-.4h3.2c2.7 0 4 .9 4 2.96 0 1.3-.5 2.1-1.5 2.6v.1zm-2.4-.86c1.3 0 1.9-.46 1.9-1.46s-.5-1.46-1.9-1.46h-1.5v2.94h1.5zm.3 4.8c1.3 0 1.9-.48 1.9-1.53s-.6-1.5-1.9-1.5h-1.8v3.1h1.8zm16.2-1.96c0 2.55-1.4 3.94-3.9 3.94s-3.9-1.37-3.9-3.92v-7.13c0-.26.1-.4.4-.4h1.3c.2 0 .4.14.4.4v6.98c0 1.58.6 2.32 1.9 2.32 1.3 0 1.9-.74 1.9-2.32v-6.98c0-.26.1-.4.4-.4h1.2c.2 0 .4.14.4.4v7.13zm12 3.34c0 .28-.1.4-.4.4h-6.2c-.2 0-.4-.12-.4-.4v-10.45c0-.26.2-.4.4-.4h1.3c.3 0 .4.14.4.4v9.1h4.5c.3 0 .4.14.4.4v.97zm11.9-3.54c0 2.7-1.4 4.16-4 4.16s-4.1-1.43-4.1-4.06v-3.52c0-2.63 1.4-4.07 4.1-4.07 1.7 0 3 .6 3.7 1.9.1.2.1.4-.1.5l-.9.5c-.2.1-.4 0-.5-.2-.5-.8-1.2-1.1-2.2-1.1-1.3 0-2 .8-2 2.5v3.1c0 1.7.7 2.5 2.1 2.5 1.4 0 2.1-.9 2.1-2.6v-.4H61c-.25 0-.4-.2-.4-.4v-1c0-.3.15-.4.4-.4h3.27c.28 0 .4.1.4.4v1.9zm12.9 3.5c.1.28 0 .45-.3.45h-1.4c-.2 0-.3-.1-.4-.3l-.5-1.77h-4l-.5 1.76c-.02.2-.2.3-.4.3h-1.3c-.3 0-.4-.16-.3-.43l3.4-10.5c.08-.2.2-.3.45-.3h1.5c.2 0 .35.1.4.3l3.4 10.5zm-4.6-8.4L71.2 110h3l-1.5-5.06zm11.1 8.46c0 .27-.1.4-.4.4h-1.2c-.2 0-.4-.13-.4-.4v-10.46c0-.26.2-.4.4-.4h3.1c2.8 0 4.1 1.15 4.1 3.5 0 1.75-.7 2.85-2.2 3.3l2.3 4c.2.26.1.46-.2.46H88c-.2 0-.37-.08-.47-.27l-2.1-3.96H84v3.9zm1.5-5.6c1.4 0 2.1-.55 2.1-1.72 0-1.2-.6-1.77-2-1.77H84v3.5h1.46zm10.9 5.6c0 .27-.1.4-.4.4h-1.2c-.2 0-.4-.13-.4-.4v-10.46c0-.26.2-.4.4-.4H96c.26 0 .4.14.4.4v10.47zm13.6-.04c.1.27 0 .44-.3.44h-1.3c-.2 0-.4-.1-.4-.32l-.5-1.76h-4l-.52 1.76c-.1.22-.2.32-.45.32H101c-.3 0-.4-.17-.33-.44l3.4-10.5c.08-.2.2-.3.45-.3h1.5c.2 0 .34.1.4.3l3.4 10.5zm-4.6-8.42l-1.4 5.05h3l-1.42-5.05h-.02z\"/></svg>";
