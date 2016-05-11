// WLAN Konfig
#define WLANSSID "Freifunk"
#define WLANPWD ""

// Wohin gehen die Daten?
#define SEND2DUSTI 1
#define SEND2MADAVI 0
#define SEND2MQTT 0
#define SEND2CSV 0
#define SEND2CUSTOM 0

// Definition eigene API
#define HOST_CUSTOM "192.168.234.1"
#define URL_CUSTOM "/data.php"
#define HTTPPORT_CUSTOM 80

// MQTT Definitionen (noch nicht genutzt)
#define HOST_MQTT "mqtt.opensensors.io"
#define MQTT_PORT 1883
#define MQTT_USER ""
#define MQTT_PWD ""
#define MQTT_CLIENT_ID ""
#define MQTT_TOPIC ""

// DHT22, Sensor Temperatur und Luftfeuchte
#define DHT_READ 0
#define DHT_PIN D7
#define DHT_TYPE DHT22
#define DHT_API_PIN 7

// PPD42NS, der günstigere der beiden Feinstaubsensoren
#define PPD_READ 1
#define PPD_PIN_PM1 D6
#define PPD_PIN_PM2 D5
#define PPD_API_PIN 5

// SDS011, der etwas teuerere Feinstaubsensor
#define SDS_READ 0
#define SDS_PIN_RX D1
#define SDS_PIN_TX D2
#define SDS_API_PIN 1

// BMP180, Luftdruck-Sensor
#define BMP_READ 0
#define BMP_PIN_SCL D4
#define BMP_PIN_SDA D3
#define BMP_API_PIN 3

// Automatische Firmware-Updates über WLAN
#define AUTO_UPDATE 1

// OLED Display SSD1306 angeschlossen?
#define HAS_DISPLAY 0

// Wieviele Informationen sollen über die serielle Schnittstelle ausgegeben werden?
#define DEBUG 3

// Definition der Debuglevel
#define DEBUG_ERROR 1
#define DEBUG_WARNING 2
#define DEBUG_MIN_INFO 3
#define DEBUG_MED_INFO 4
#define DEBUG_MAX_INFO 5
