// Language config
#define CURRENT_LANG INTL_LANG

// Wifi config
#define WLANSSID "Freifunk-disabled"
#define WLANPWD ""

// BasicAuth config
#define WWW_USERNAME "admin"
#define WWW_PASSWORD "feinstaub"
#define WWW_BASICAUTH_ENABLED 0

// Sensor Wifi config (config mode)
#define FS_SSID ""
#define FS_PWD ""

// Where to send the data?
#define SEND2DUSTI 1
#define SSL_DUSTI 0
#define SEND2MADAVI 1
#define SSL_MADAVI 0
#define SEND2SENSEMAP 0
#define SEND2FSAPP 0
#define SEND2AIRCMS 0
#define SEND2MQTT 0
#define SEND2INFLUX 0
#define SEND2LORA 0
#define SEND2CSV 0
#define SEND2CUSTOM 0

// NTP Server
#define NTP_SERVER "0.europe.pool.ntp.org"

// OpenSenseMap
#define SENSEBOXID ""


// IMPORTANT: NO MORE CHANGES TO VARIABLE NAMES NEEDED FOR EXTERNAL APIS

// define own API
#define HOST_CUSTOM "192.168.234.1"
#define URL_CUSTOM "/data.php"
#define PORT_CUSTOM 80
#define USER_CUSTOM ""
#define PWD_CUSTOM ""

// define own InfluxDB
#define HOST_INFLUX "influx.server"
#define URL_INFLUX "/write?db=luftdaten"
#define PORT_INFLUX 8086
#define USER_INFLUX ""
#define PWD_INFLUX ""
#define MEASUREMENT_NAME_INFLUX "feinstaub"
#define SSL_INFLUX 0

// define pins for I2C
#define I2C_PIN_SCL D4
#define I2C_PIN_SDA D3

// define pin for one wire sensors
#if defined(ESP8266)
#define ONEWIRE_PIN D7
#endif
#if defined(ARDUINO_SAMD_ZERO)
#define ONEWIRE_PIN D7
#endif
#if defined(ESP32)
#define ONEWIRE_PIN D7
#endif

// define serial interface pins for particle sensors
// Serial confusion: These definitions are based on SoftSerial
// TX (transmitting) pin on one side goes to RX (receiving) pin on other side
// SoftSerial RX PIN is D1 and goes to SDS TX
// SoftSerial TX PIN is D2 and goes to SDS RX
#if defined(ESP8266)
#define PM_SERIAL_RX D1
#define PM_SERIAL_TX D2
#endif

// define serial interface pins for GPS modules
#if defined(ESP8266)
#define GPS_SERIAL_RX D5
#define GPS_SERIAL_TX D6
#endif

// DHT22, temperature, humidity
#define DHT_READ 1
#define DHT_TYPE DHT22
#define DHT_API_PIN 7

// HTU21D, temperature, humidity
#define HTU21D_READ 0
#define HTU21D_API_PIN 7

// PPD42NS, the cheaper version of the particle sensor
#define PPD_READ 0
#define PPD_API_PIN 5
#if defined(ARDUINO_SAMD_ZERO) || defined(ESP8266) || defined(ESP32)
#define PPD_PIN_PM1 D6
#define PPD_PIN_PM2 D5
#endif

// SDS011, the more expensive version of the particle sensor
#define SDS_READ 1
#define SDS_API_PIN 1

// PMS1003, PMS300, 3PMS5003, PMS6003, PMS7003
#define PMS_READ 0
#define PMS_API_PIN 1

// Honeywell PM sensor
#define HPM_READ 0
#define HPM_API_PIN 1

// BMP180, temperature, pressure
#define BMP_READ 0
#define BMP_API_PIN 3

// BMP280, temperature, pressure
#define BMP280_READ 0
#define BMP280_API_PIN 3

// BME280, temperature, humidity, pressure
#define BME280_READ 0
#define BME280_API_PIN 11

// DS18B20, temperature
#define DS18B20_READ 0
#define DS18B20_API_PIN 13


// GPS, preferred Neo-6M
#define GPS_READ 0
#define GPS_API_PIN 9

// automatic firmware updates
#define AUTO_UPDATE 1

// use beta firmware
#define USE_BETA 0

// OLED Display SSD1306 connected?
#define HAS_DISPLAY 0

// OLED Display SH1106 connected?
#define HAS_SH1106 0

// LCD Display LCD1602 connected?
#define HAS_LCD1602 0

// LCD Display LCD1602 (0x27) connected?
#define HAS_LCD1602_27 0

// LCD Display LCD2004 (0x27) connected?
#define HAS_LCD2004_27 0

// Set debug level for serial outpur?
#define DEBUG 3
