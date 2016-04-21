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
#define DHT_PIN 13
#define DHT_TYPE DHT22

// PPD42NS, der günstigere der beiden Feinstaubsensoren
#define PPD_READ 1
#define PPD_PIN_PM1 12
#define PPD_PIN_PM2 14

// SDS011, der etwas teuerere Feinstaubsensor
#define SDS_READ 0
#define SDS_PIN_RX 5
#define SDS_PIN_TX 4

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
