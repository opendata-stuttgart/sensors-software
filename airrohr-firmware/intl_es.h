/*
 *	airRohr firmware
 *	Copyright (C) 2016-2018  Code for Stuttgart a.o.
 *
 *  Spanish translations
 *
 *	Texts should be as short as possible
 *	We only have 512 kB for the entire firmware
 */

const char INTL_LANG[] = "ES";
#define INTL_PM_SENSOR "Sensor de partículas finas"
const char INTL_CONFIGURATION[] PROGMEM = "Configuración";
#define INTL_WIFI_SETTINGS "Configuración WiFi"
#define INTL_WIFI_NETWORKS "Carga de redes wifi ..."
#define INTL_LANGUAGE "Idioma"
const char INTL_NO_NETWORKS[] PROGMEM =  "Red WiFi no detectada";
const char INTL_NETWORKS_FOUND[] PROGMEM = "Redes encontradas: ";
const char INTL_AB_HIER_NUR_ANDERN[] PROGMEM = "Configuración avanzada (solo si sabes que lo que estas haciendo)";
const char INTL_SAVE[] PROGMEM = "Guardar";
const char INTL_SENSORS[] PROGMEM = "Sensores";
const char INTL_MORE_SENSORS[] PROGMEM = "More Sensores";
const char INTL_SDS011[] PROGMEM = "SDS011 ({pm})";
const char INTL_PMS[] PROGMEM = "Plantower PMS(1,3,5,6,7)003 ({pm})";
const char INTL_HPM[] PROGMEM = "Honeywell sensor de partículas finas";
const char INTL_SPS30[] PROGMEM = "Sensirion SPS30 ({pm})";
const char INTL_PPD42NS[] PROGMEM = "PPD42NS ({pm})";
const char INTL_DHT22[] PROGMEM = "DHT22 ({t}, {h})";
const char INTL_HTU21D[] PROGMEM = "HTU21D ({t}, {h})";
const char INTL_BMP180[] PROGMEM = "BMP180 ({t}, {p})";
const char INTL_BMX280[] PROGMEM = "BMP280/BME280 ({t}, {h}, {p})";
const char INTL_SHT3X[] PROGMEM = "SHT3X ({t}, {h})";
const char INTL_DS18B20[] PROGMEM = "DS18B20 ({t})";
const char INTL_DNMS[] PROGMEM = "DNMS ({l_a})";
const char INTL_DNMS_CORRECTION[] PROGMEM = "corrección en dB (A)";
const char INTL_NEO6M[] PROGMEM = "GPS (NEO 6M)";
const char INTL_BASICAUTH[] PROGMEM = "Autorización";

const char INTL_FS_WIFI_DESCRIPTION[] PROGMEM = "Sensor iFi en modo de configuración";
const char INTL_FS_WIFI_NAME[] PROGMEM = "Nombre";
const char INTL_MORE_SETTINGS[] PROGMEM ="Otras configruaciones";
const char INTL_AUTO_UPDATE[] PROGMEM = "Actualización automática del Firmware";
const char INTL_USE_BETA[] PROGMEM = "Cargar del firmware beta";
const char INTL_DISPLAY[] PROGMEM = "OLED SSD1306";
const char INTL_SH1106[] PROGMEM = "OLED SH1106";
const char INTL_FLIP_DISPLAY[] PROGMEM = "Pantalla OLED flip";
const char INTL_LCD1602_27[] PROGMEM = "LCD 1602 (I2C: 0x27)";
const char INTL_LCD1602_3F[] PROGMEM = "LCD 1602 (I2C: 0x3F)";
const char INTL_LCD2004_27[] PROGMEM = "LCD 2004 (I2C: 0x27)";
const char INTL_LCD2004_3F[] PROGMEM = "LCD 2004 (I2C: 0x3F)";
const char INTL_DISPLAY_WIFI_INFO[] PROGMEM = "Mostrar información de WiFi";
const char INTL_DISPLAY_DEVICE_INFO[] PROGMEM = "Mostrar información del dispositivo";
const char INTL_DEBUG_LEVEL[] PROGMEM = "Debug&nbsp;Level";
const char INTL_MEASUREMENT_INTERVAL[] PROGMEM = "Intervalo de medición";
const char INTL_DURATION_ROUTER_MODE[] PROGMEM = "Duración del modo enrutador";
const char INTL_MORE_APIS[] PROGMEM = "Otros API";
const char INTL_SEND_TO_OWN_API[] PROGMEM = "Mandar a propio API";
const char INTL_SERVER[] PROGMEM = "Servidor";
const char INTL_PATH[] PROGMEM = "Ruta";
const char INTL_PORT[] PROGMEM = "Puerto";
const char INTL_USER[] PROGMEM = "Usuario";
const char INTL_PASSWORD[] PROGMEM = "Contraseña";
const char INTL_SEND_TO[] PROGMEM = "Enviar a {v}";
const char INTL_READ_FROM[] PROGMEM = "Leer {v}";
const char INTL_SENSOR_IS_REBOOTING[] PROGMEM = "El sensor se está reiniciando.";
const char INTL_RESTART_DEVICE[] PROGMEM = "Reiniciar dispositivo";
const char INTL_DELETE_CONFIG[] PROGMEM = "Borrar configruación actual";
const char INTL_RESTART_SENSOR[] PROGMEM = "Reiniciar sensor";
#define INTL_HOME "Visión general"
#define INTL_BACK_TO_HOME "Volver al inicio"
const char INTL_CURRENT_DATA[] PROGMEM = "Datos actuales";
const char INTL_DEVICE_STATUS[] PROGMEM = "El estado del dispositivo";
#define INTL_ACTIVE_SENSORS_MAP "Mapa de sensores activos (enlace externo)"
#define INTL_CONFIGURATION_DELETE "Borrar configuración"
#define INTL_CONFIGURATION_REALLY_DELETE "Estas seguro que quieres borrar la configuración?"
#define INTL_DELETE "Borrar"
#define INTL_CANCEL "Cancelar"
#define INTL_REALLY_RESTART_SENSOR "Estas seguro que quieres reiniciar el sensor?"
#define INTL_RESTART "Reiniciar"
const char INTL_SAVE_AND_RESTART[] PROGMEM = "Guardar y reiniciar";
#define INTL_FIRMWARE "Versión del Firmware"
const char INTL_DEBUG_SETTING_TO[] PROGMEM = "Ajustar Debug a ";
#define INTL_NONE "off"
#define INTL_ERROR "Error"
#define INTL_WARNING "Advertencia"
#define INTL_MIN_INFO "min. info"
#define INTL_MED_INFO "mid. info"
#define INTL_MAX_INFO "max. info"
#define INTL_CONFIG_DELETED "Configuración fue borrada"
#define INTL_CONFIG_CAN_NOT_BE_DELETED "Configuración no puede ser borrada"
#define INTL_CONFIG_NOT_FOUND "Configuración no encontrada"
const char INTL_TIME_TO_FIRST_MEASUREMENT[] PROGMEM = "Otros {v} segundos a la primera medición.";
const char INTL_TIME_SINCE_LAST_MEASUREMENT[] PROGMEM = "segundos desde la última medición.";
const char INTL_PARTICLES_PER_LITER[] PROGMEM = "Partículas/litro";
const char INTL_PARTICULATE_MATTER[] PROGMEM = "partículas finas";
const char INTL_TEMPERATURE[] PROGMEM = "Temperatura";
const char INTL_HUMIDITY[] PROGMEM = "Humedad";
const char INTL_PRESSURE[] PROGMEM = "Presión atmosférica";
const char INTL_LEQ_A[] PROGMEM = "LAeq";
const char INTL_LA_MIN[] PROGMEM = "LA min";
const char INTL_LA_MAX[] PROGMEM = "LA max";
const char INTL_LATITUDE[] PROGMEM = "Latitud";
const char INTL_LONGITUDE[] PROGMEM = "Longitud";
const char INTL_ALTITUDE[] PROGMEM = "Altitud";
const char INTL_DATE[] PROGMEM = "Fecha";
const char INTL_TIME[] PROGMEM = "Tiempo";
const char INTL_SIGNAL_STRENGTH[] PROGMEM = "Intensidad de Señal";
const char INTL_SIGNAL_QUALITY[] PROGMEM = "Calidad de Señal";
#define INTL_NUMBER_OF_MEASUREMENTS "Numero de mediciones"
#define INTL_TIME_SENDING_MS "Tiempo empleado para enviar"
#define INTL_SENSOR "Sensor"
#define INTL_PARAMETER "Parámetro"
#define INTL_VALUE "Valor"

#include "./airrohr-logo-common.h"
