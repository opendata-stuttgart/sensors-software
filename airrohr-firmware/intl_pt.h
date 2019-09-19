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
const char INTL_PM_SENSOR[] PROGMEM = "Sensor de partículas finas";
const char INTL_CONFIGURATION[] PROGMEM = "Configuração";
const char INTL_WIFI_SETTINGS[] PROGMEM = "Configuração WiFi";
const char INTL_WIFI_NETWORKS[] PROGMEM = "A carregar redes WiFi ...";
const char INTL_LANGUAGE[] PROGMEM = "Idioma";
const char INTL_NO_NETWORKS[] PROGMEM =  "Redes WiFi não detetadas";
const char INTL_NETWORKS_FOUND[] PROGMEM = "Redes encontradas: ";
const char INTL_AB_HIER_NUR_ANDERN[] PROGMEM = "Configuração avançada (apenas se sabe o que está a fazer)";
const char INTL_SAVE[] PROGMEM = "Guardar";
const char INTL_SENSORS[] PROGMEM = "Sensores";
const char INTL_SDS011[] PROGMEM = "SDS011 ({pm})";
const char INTL_PMS[] PROGMEM = "Plantower PMS(1,3,5,6,7)003 ({pm})";
const char INTL_HPM[] PROGMEM = "Honeywell sensor de partículas finas";
const char INTL_SPS30[] PROGMEM = "Sensirion SPS30 ({pm})";
const char INTL_PPD42NS[] PROGMEM = "PPD42NS";
const char INTL_DHT22[] PROGMEM = "DHT22 ({t}, {h})";
const char INTL_HTU21D[] PROGMEM = "HTU21D ({t}, {h})";
const char INTL_BMP180[] PROGMEM = "BMP180 ({t}, {p})";
const char INTL_BMP280[] PROGMEM = "BMP280 ({t}, {p})";
const char INTL_BME280[] PROGMEM = "BME280 ({t}, {h}, {p})";
const char INTL_DS18B20[] PROGMEM = "DS18B20 ({t})";
const char INTL_DNMS[] PROGMEM = "DNMS ({l_a})";
const char INTL_DNMS_CORRECTION[] PROGMEM ="";
const char INTL_NEO6M[] PROGMEM = "GPS (NEO 6M)";
const char INTL_MHZ19[] PROGMEM = "MH-Z19 (CO₂)";
const char INTL_BASICAUTH[] PROGMEM = "Autorização";
const char INTL_FS_WIFI[] PROGMEM = "Sensor WiFi";
const char INTL_FS_WIFI_DESCRIPTION[] PROGMEM = "Nome do sensor WiFi em modo de configuração";
const char INTL_FS_WIFI_NAME[] PROGMEM = "Nome";
const char INTL_MORE_SETTINGS[] PROGMEM ="Outras configurações";
const char INTL_AUTO_UPDATE[] PROGMEM = "Atualização automática do Firmware";
const char INTL_USE_BETA[] PROGMEM = "Carregar Firmware Beta";
const char INTL_DISPLAY[] PROGMEM = "OLED SSD1306";
const char INTL_SH1106[] PROGMEM = "OLED SH1106";
const char INTL_FLIP_DISPLAY[] PROGMEM = "";
const char INTL_LCD1602_27[] PROGMEM = "LCD 1602 (I2C: 0x27)";
const char INTL_LCD1602_3F[] PROGMEM = "LCD 1602 (I2C: 0x3F)";
const char INTL_LCD2004_27[] PROGMEM = "LCD 2004 (I2C: 0x27)";
const char INTL_DISPLAY_WIFI_INFO[] PROGMEM = "";
const char INTL_DISPLAY_DEVICE_INFO[] PROGMEM = "";
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
const char INTL_HOME[] PROGMEM = "Visão geral";
const char INTL_BACK_TO_HOME[] PROGMEM = "Voltar ao início";
const char INTL_CURRENT_DATA[] PROGMEM = "Dados atuais";
const char INTL_ACTIVE_SENSORS_MAP[] PROGMEM = "Mapa de sensores ativos (ligação externa)";
const char INTL_CONFIGURATION_DELETE[] PROGMEM = "Apagar configuração";
const char INTL_CONFIGURATION_REALLY_DELETE[] PROGMEM = "Confirma que quere apagar a configuração?";
const char INTL_DELETE[] PROGMEM = "Apagar";
const char INTL_CANCEL[] PROGMEM = "Cancelar";
const char INTL_REALLY_RESTART_SENSOR[] PROGMEM = "Confirma que quere reiniciar o sensor?";
const char INTL_RESTART[] PROGMEM = "Reiniciar";
const char INTL_SAVE_AND_RESTART[] PROGMEM = "Salvar e reiniciar";
const char INTL_FIRMWARE[] PROGMEM = "Versão do Firmware";
const char INTL_DEBUG_SETTING_TO[] PROGMEM = "Ajustar Debug a ";
const char INTL_NONE[] PROGMEM = "nenhum";
const char INTL_ERROR[] PROGMEM = "erro";
const char INTL_WARNING[] PROGMEM = "Advertência";
const char INTL_MIN_INFO[] PROGMEM = "min. info";
const char INTL_MED_INFO[] PROGMEM = "mid. info";
const char INTL_MAX_INFO[] PROGMEM = "max. info";
const char INTL_CONFIG_DELETED[] PROGMEM = "A configuração foi apagada";
const char INTL_CONFIG_CAN_NOT_BE_DELETED[] PROGMEM = "A configuração pode ser apagada";
const char INTL_CONFIG_NOT_FOUND[] PROGMEM = "Configuração não encontrada";
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
const char INTL_CO2[] PROGMEM = "Dióxido de carbono";
const char INTL_DATE[] PROGMEM = "Data";
const char INTL_TIME[] PROGMEM = "Hora";
const char INTL_SIGNAL_STRENGTH[] PROGMEM = "Intensidade do Sinal";
const char INTL_SIGNAL_QUALITY[] PROGMEM = "Qualidade do Sinal";
const char INTL_NUMBER_OF_MEASUREMENTS[] PROGMEM = "Quantidade de medições:";
const char INTL_SENSOR[] PROGMEM = "Sensor";
const char INTL_PARAMETER[] PROGMEM = "Parâmetro";
const char INTL_VALUE[] PROGMEM = "Valor";

const char LUFTDATEN_INFO_LOGO_SVG[] PROGMEM = "<svg id=\"Layer_1\" xmlns=\"http://www.w3.org/2000/svg\" x=\"0px\" y=\"0px\" width=\"100px\" height=\"88.891px\" viewBox=\"0 0 100 88.891\" enable-background=\"new 0 0 100 88.891\"><path fill=\"#fff\" d=\"M90.28 66.57v.1H83.33c-2.04 0-3.7-1.66-3.7-3.7 0-2.05 1.66-3.7 3.7-3.7h5.56c2.03 0 3.7-1.67 3.7-3.7 0-2.06-1.67-3.72-3.7-3.72s-3.72-1.66-3.72-3.7c0-2.05 1.66-3.7 3.7-3.7.26 0 .5.02.75.07 5.8.4 10.37 5.15 10.37 11.04 0 5.66-4.24 10.32-9.72 11z\"/><path fill=\"#fff\" d=\"M70.37 44.44c-2.04 0-3.7-1.65-3.7-3.7 0-2.04 1.66-3.7 3.7-3.7.26 0 .5.02.75.07 5.78.4 10.36 5.17 10.36 11.05 0 5.66-4.24 10.33-9.72 11v.1H29.63c-2.04 0-3.7 1.67-3.7 3.7 0 2.06 1.65 3.72 3.7 3.72h42.14v.1c5.47.68 9.7 5.35 9.7 11 0 5.9-4.57 10.65-10.35 11.05-.25.04-.5.07-.75.07-2.04 0-3.7-1.67-3.7-3.7 0-2.06 1.66-3.72 3.7-3.72s3.7-1.66 3.7-3.7c0-2.05-1.66-3.7-3.7-3.7H28.23v-.1c-5.47-.7-9.7-5.35-9.7-11.02 0-1.95.53-3.76 1.42-5.35C8.35 53.6 0 42.6 0 29.64 0 13.27 13.27 0 29.63 0c11.12 0 20.8 6.13 25.86 15.2 1.22-.22 2.47-.38 3.76-.38 10.92 0 19.98 7.88 21.85 18.26-2.57-1.84-5.64-3.05-8.97-3.36-2.55-4.48-7.35-7.5-12.87-7.5-2.96 0-5.7.9-8.03 2.4-2.28-9.85-11.06-17.2-21.6-17.2C17.36 7.4 7.4 17.35 7.4 29.6c0 12.28 9.96 22.23 22.23 22.23h40.74c2.04 0 3.7-1.66 3.7-3.7 0-2.05-1.65-3.7-3.7-3.7z\"/></svg>";

/* const char LUFTDATEN_INFO_LOGO_SVG[] PROGMEM = "<svg viewBox=\"0 0 350 350\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\
<defs><path id=\"d\" d=\"m284.38 273.35v-62.5c-1.77-23.65-9.32-42.14-22.65-55.48-13.33-13.33-30.76-20.88-52.27-22.64h-34.46-29.37c-24.67 2.77-43.66 10.82-57 24.16-13.33 13.33-21 31.32-23 53.96v62.5\"/><path id=\"c\" d=\"m177.6 188.56v-112 112z\"/><path id=\"a\" d=\"m171.92 76.73c5.82 0 10.53 4.71 10.53 10.52v90.95c0 5.82-4.71 10.53-10.53 10.53h-17.2c-5.82 0-10.53-4.71-10.53-10.53v-90.95c0-5.81 4.71-10.52 10.53-10.52h17.2z\"/><path id=\"e\" d=\"m228.81 248.48h112-112z\"/><path id=\"b\" d=\"m340.81 243.19c0 5.82-4.71 10.53-10.52 10.53h-90.95c-5.81 0-10.53-4.71-10.53-10.53v-17.21c0-5.81 4.72-10.52 10.53-10.52h90.95c5.81 0 10.52 4.71 10.52 10.52v17.21z\"/></defs>\
<use fill-opacity=\"0\" stroke=\"#c0c0c0\" stroke-width=\"100\" xlink:href=\"#d\"/><use fill-opacity=\"0\" stroke=\"#c0c0c0\" stroke-width=\"50\" xlink:href=\"#c\"/><use fill=\"#c0c0c0\" xlink:href=\"#a\"/><use fill-opacity=\"0\" stroke=\"#c0c0c0\" stroke-width=\"50\" xlink:href=\"#e\"/><use fill=\"#c0c0c0\" xlink:href=\"#b\"/>\
</svg>";
*/
