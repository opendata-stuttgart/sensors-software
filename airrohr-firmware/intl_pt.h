/*
 *	airRohr firmware
 *	Copyright (C) 2016-2018  Code for Stuttgart a.o.
 *
 *  Portuguese translations
 *
 *	Texts should be as short as possible
 *	We only have 512 kB for the entire firmware
 */

const char INTL_LANG[] = "PT";
#define INTL_PM_SENSOR "Sensor de partículas finas"
const char INTL_CONFIGURATION[] PROGMEM = "Configuração";
#define INTL_WIFI_SETTINGS "Configuração WiFi"
#define INTL_WIFI_NETWORKS "A carregar redes WiFi ..."
#define INTL_LANGUAGE "Idioma"
const char INTL_NO_NETWORKS[] PROGMEM =  "Redes WiFi não detetadas";
const char INTL_NETWORKS_FOUND[] PROGMEM = "Redes encontradas: ";
const char INTL_AB_HIER_NUR_ANDERN[] PROGMEM = "Configuração avançada (apenas se sabe o que está a fazer)";
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
const char INTL_DNMS_CORRECTION[] PROGMEM ="Valor de correção em dB(A)";
const char INTL_NEO6M[] PROGMEM = "GPS (NEO 6M)";
const char INTL_BASICAUTH[] PROGMEM = "Autorização";

const char INTL_FS_WIFI_DESCRIPTION[] PROGMEM = "Nome do sensor WiFi em modo de configuração";
const char INTL_FS_WIFI_NAME[] PROGMEM = "Nome";
const char INTL_MORE_SETTINGS[] PROGMEM ="Outras configurações";
const char INTL_AUTO_UPDATE[] PROGMEM = "Atualização automática do Firmware";
const char INTL_USE_BETA[] PROGMEM = "Carregar Firmware Beta";
const char INTL_DISPLAY[] PROGMEM = "OLED SSD1306";
const char INTL_SH1106[] PROGMEM = "OLED SH1106";
const char INTL_FLIP_DISPLAY[] PROGMEM = "Girar a tela OLED de 180°";
const char INTL_LCD1602_27[] PROGMEM = "LCD 1602 (I2C: 0x27)";
const char INTL_LCD1602_3F[] PROGMEM = "LCD 1602 (I2C: 0x3F)";
const char INTL_LCD2004_27[] PROGMEM = "LCD 2004 (I2C: 0x27)";
const char INTL_LCD2004_3F[] PROGMEM = "LCD 2004 (I2C: 0x3F)";
const char INTL_DISPLAY_WIFI_INFO[] PROGMEM = "Mostrar informações WiFi";
const char INTL_DISPLAY_DEVICE_INFO[] PROGMEM = "Mostrar informações do dispositivo";
const char INTL_DEBUG_LEVEL[] PROGMEM = "Debug&nbsp;Level";
const char INTL_MEASUREMENT_INTERVAL[] PROGMEM = "Intervalo de medição";
const char INTL_DURATION_ROUTER_MODE[] PROGMEM = "Duração&nbsp;Modo roteador";
const char INTL_MORE_APIS[] PROGMEM = "Outros API";
const char INTL_SEND_TO_OWN_API[] PROGMEM = "Enviar para a própria API";
const char INTL_SERVER[] PROGMEM = "Servidor";
const char INTL_PATH[] PROGMEM = "Caminho";
const char INTL_PORT[] PROGMEM = "Porta";
const char INTL_USER[] PROGMEM = "Utilizador";
const char INTL_PASSWORD[] PROGMEM = "Senha";
const char INTL_SEND_TO[] PROGMEM = "Enviar a {v}";
const char INTL_READ_FROM[] PROGMEM = "Ler {v}";
const char INTL_SENSOR_IS_REBOOTING[] PROGMEM = "O sensor esta a ser reiniciado.";
const char INTL_RESTART_DEVICE[] PROGMEM = "Reiniciar dispositivo";
const char INTL_DELETE_CONFIG[] PROGMEM = "Apagar configuração atual";
const char INTL_RESTART_SENSOR[] PROGMEM = "Reiniciar sensor";
#define INTL_HOME "Visão geral"
#define INTL_BACK_TO_HOME "Voltar ao início"
const char INTL_CURRENT_DATA[] PROGMEM = "Dados atuais";
const char INTL_DEVICE_STATUS[] PROGMEM = "Estado do dispositivo";
#define INTL_ACTIVE_SENSORS_MAP "Mapa de sensores ativos (ligação externa)"
#define INTL_CONFIGURATION_DELETE "Apagar configuração"
#define INTL_CONFIGURATION_REALLY_DELETE "Confirma que quere apagar a configuração?"
#define INTL_DELETE "Apagar"
#define INTL_CANCEL "Cancelar"
#define INTL_REALLY_RESTART_SENSOR "Confirma que quere reiniciar o sensor?"
#define INTL_RESTART "Reiniciar"
const char INTL_SAVE_AND_RESTART[] PROGMEM = "Salvar e reiniciar";
#define INTL_FIRMWARE "Versão do Firmware"
const char INTL_DEBUG_SETTING_TO[] PROGMEM = "Ajustar Debug a ";
#define INTL_NONE "nenhum"
#define INTL_ERROR "erro"
#define INTL_WARNING "Advertência"
#define INTL_MIN_INFO "min. info"
#define INTL_MED_INFO "mid. info"
#define INTL_MAX_INFO "max. info"
#define INTL_CONFIG_DELETED "A configuração foi apagada"
#define INTL_CONFIG_CAN_NOT_BE_DELETED "A configuração pode ser apagada"
#define INTL_CONFIG_NOT_FOUND "Configuração não encontrada"
const char INTL_TIME_TO_FIRST_MEASUREMENT[] PROGMEM = "Outros {v.} segundos para a primeira medição.";
const char INTL_TIME_SINCE_LAST_MEASUREMENT[] PROGMEM = " segundos desde a última medida.";
const char INTL_PARTICLES_PER_LITER[] PROGMEM = "Partículas/litro";
const char INTL_PARTICULATE_MATTER[] PROGMEM = "partículas finas";
const char INTL_TEMPERATURE[] PROGMEM = "Temperatura";
const char INTL_HUMIDITY[] PROGMEM = "Humidade";
const char INTL_PRESSURE[] PROGMEM = "Pressão atmosférica";
const char INTL_LEQ_A[] PROGMEM = "LAeq";
const char INTL_LA_MIN[] PROGMEM = "LA min";
const char INTL_LA_MAX[] PROGMEM = "LA max";
const char INTL_LATITUDE[] PROGMEM = "Latitude";
const char INTL_LONGITUDE[] PROGMEM = "Longitude";
const char INTL_ALTITUDE[] PROGMEM = "Altitude";
const char INTL_DATE[] PROGMEM = "Data";
const char INTL_TIME[] PROGMEM = "Hora";
const char INTL_SIGNAL_STRENGTH[] PROGMEM = "Intensidade do Sinal";
const char INTL_SIGNAL_QUALITY[] PROGMEM = "Qualidade do Sinal";
#define INTL_NUMBER_OF_MEASUREMENTS "Quantidade de medições"
#define INTL_TIME_SENDING_MS "Duração da transmissão das medições"
#define INTL_SENSOR "Sensor"
#define INTL_PARAMETER "Parâmetro"
#define INTL_VALUE "Valor"

#include "./airrohr-logo-common.h"
