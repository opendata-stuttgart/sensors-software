// Language config
#define CURRENT_LANG INTL_LANG

// Wifi config
const char WLANSSID[] PROGMEM = "Freifunk-disabled";
const char WLANPWD[] PROGMEM = "";

// BasicAuth config
const char WWW_USERNAME[] PROGMEM = "admin";
const char WWW_PASSWORD[] PROGMEM = "";
#define WWW_BASICAUTH_ENABLED 0

// Sensor Wifi config (config mode)
#define FS_SSID ""
#define FS_PWD ""

// Where to send the data?
#define SEND2SENSORCOMMUNITY 1
#define SSL_SENSORCOMMUNITY 0
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

// OpenSenseMap
#define SENSEBOXID ""

enum LoggerEntry {
    LoggerSensorCommunity,
    LoggerMadavi,
    LoggerSensemap,
    LoggerFSapp,
    Loggeraircms,
    LoggerInflux,
    LoggerCustom,
    LoggerCount
};

struct LoggerConfig {
    uint16_t destport;
    uint16_t errors;
#if defined(ESP8266)
    BearSSL::Session* session;
#else
    void* session;
#endif
};

// IMPORTANT: NO MORE CHANGES TO VARIABLE NAMES NEEDED FOR EXTERNAL APIS
static const char HOST_MADAVI[] PROGMEM = "api-rrd.madavi.de";
static const char URL_MADAVI[] PROGMEM = "/data.php";
#define PORT_MADAVI 80

static const char HOST_SENSORCOMMUNITY[] PROGMEM = "api.sensor.community";
static const char URL_SENSORCOMMUNITY[] PROGMEM = "/v1/push-sensor-data/";
#define PORT_SENSORCOMMUNITY 80

static const char HOST_SENSEMAP[] PROGMEM = "ingress.opensensemap.org";
static const char URL_SENSEMAP[] PROGMEM = "/boxes/{v}/data?luftdaten=1";
#define PORT_SENSEMAP 443

static const char HOST_FSAPP[] PROGMEM = "h2801469.stratoserver.net";
static const char URL_FSAPP[] PROGMEM = "/data.php";
#define PORT_FSAPP 443

static const char HOST_AIRCMS[] PROGMEM = "doiot.ru";
static const char URL_AIRCMS[] PROGMEM = "/php/sensors.php?h=";
// As of 2019/09 uses invalid certifiates on ssl/port 443 and does not support Maximum Fragment Length Negotiation (MFLN)
// So we can not use SSL
#define PORT_AIRCMS 80

static const char FW_DOWNLOAD_HOST[] PROGMEM = "firmware.sensor.community";
#define FW_DOWNLOAD_PORT 443

static const char FW_2ND_LOADER_URL[] PROGMEM = OTA_BASENAME "/loader-002.bin";

static const char NTP_SERVER_1[] PROGMEM = "0.pool.ntp.org";
static const char NTP_SERVER_2[] PROGMEM = "1.pool.ntp.org";

// define own API
static const char HOST_CUSTOM[] PROGMEM = "192.168.234.1";
static const char URL_CUSTOM[] PROGMEM = "/data.php";
#define PORT_CUSTOM 80
#define USER_CUSTOM ""
#define PWD_CUSTOM ""
#define SSL_CUSTOM 0

// define own InfluxDB
static const char HOST_INFLUX[] PROGMEM = "influx.server";
static const char URL_INFLUX[] PROGMEM = "/write?db=sensorcommunity";
#define PORT_INFLUX 8086
#define USER_INFLUX ""
#define PWD_INFLUX ""
static const char MEASUREMENT_NAME_INFLUX[] PROGMEM = "feinstaub";
#define SSL_INFLUX 0

//  === pin assignments for NodeMCU V2 board ===================================
#if defined(ESP8266)
// define pin for one wire sensors
#define ONEWIRE_PIN D7

// define serial interface pins for particle sensors
// Serial confusion: These definitions are based on SoftSerial
// TX (transmitting) pin on one side goes to RX (receiving) pin on other side
// SoftSerial RX PIN is D1 and goes to SDS TX
// SoftSerial TX PIN is D2 and goes to SDS RX
#define PM_SERIAL_RX D1
#define PM_SERIAL_TX D2

// define pins for I2C
#define I2C_PIN_SCL D4
#define I2C_PIN_SDA D3

// define serial interface pins for GPS modules
#define GPS_SERIAL_RX D5
#define GPS_SERIAL_TX D6

// PPD42NS, the cheaper version of the particle sensor
#define PPD_PIN_PM1 GPS_SERIAL_TX
#define PPD_PIN_PM2 GPS_SERIAL_RX
#endif


//  === pin assignments for Arduino SAMD Zero board ===================================
#if defined(ARDUINO_SAMD_ZERO)
#define ONEWIRE_PIN D7
#define PPD_PIN_PM1 GPS_SERIAL_TX
#define PPD_PIN_PM2 GPS_SERIAL_RX
#if defined(SERIAL_PORT_USBVIRTUAL)
#define RFM69_CS 8
#define RFM69_RST 4
#define RFM69_INT 3
#endif
#endif


//  === pin assignments for dev kit board ===================================
#ifdef ESP32
#define ONEWIRE_PIN D32
#define PM_SERIAL_RX D27 
#define PM_SERIAL_TX D33 
#define PIN_CS D13

#if defined(FLIP_I2C_PMSERIAL) // exchange the pins of the ports to use external i2c connector for gps
#define I2C_PIN_SCL D23
#define I2C_PIN_SDA D19
#define GPS_SERIAL_RX D22
#define GPS_SERIAL_TX D21
#else
#define I2C_PIN_SCL D22
#define I2C_PIN_SDA D21
#define GPS_SERIAL_RX D19
#define GPS_SERIAL_TX D23
#endif
#define PPD_PIN_PM1 GPS_SERIAL_TX
#define PPD_PIN_PM2 GPS_SERIAL_RX
//#define RFM69_CS D0
//#define RFM69_RST D2
//#define RFM69_INT D4
#endif

//  === pin assignments for lolin_d32_pro board ===================================
#if defined(ARDUINO_LOLIN_D32_PRO)
#define ONEWIRE_PIN D32
#define PM_SERIAL_RX D27
#define PM_SERIAL_TX D33
#if defined(FLIP_I2C_PMSERIAL) // exchange the pins of the ports to use external i2c connector for gps
#define I2C_PIN_SCL D23
#define I2C_PIN_SDA D19
#define GPS_SERIAL_RX D22
#define GPS_SERIAL_TX D21
#else
#define I2C_PIN_SCL D22
#define I2C_PIN_SDA D21
#define GPS_SERIAL_RX D19
#define GPS_SERIAL_TX D23
#endif
#define PPD_PIN_PM1 GPS_SERIAL_TX
#define PPD_PIN_PM2 GPS_SERIAL_RX
//#define RFM69_CS D0
//#define RFM69_RST D2
//#define RFM69_INT D4
#endif

//  === pin assignments for heltec_wifi_lora_32_V2 board ===================================
#if defined(WIFI_LoRa_32_V2)
#define ONEWIRE_PIN D32
#define I2C_PIN_SCL D22
#define I2C_PIN_SDA D17_WROOM_ONLY
#define PM_SERIAL_RX D23
#define PM_SERIAL_TX D2_STRAPPING
#define GPS_SERIAL_RX D13_JTAG_TCK
#define GPS_SERIAL_TX D0_STRAPPING
#define PPD_PIN_PM1 GPS_SERIAL_TX
#define PPD_PIN_PM2 GPS_SERIAL_RX
#endif

//  === pin assignments for heltec_wifi_lora_32 board ===================================
#if defined(WIFI_LoRa_32)
#define ONEWIRE_PIN D25 // TODO: this overlaps with LED, so it might not work
#define I2C_PIN_SCL D22
#define I2C_PIN_SDA D17_WROOM_ONLY
#define PM_SERIAL_RX D23
#define PM_SERIAL_TX D2_STRAPPING
#define GPS_SERIAL_RX D13_JTAG_TCK
#define GPS_SERIAL_TX D0_STRAPPING
#define PPD_PIN_PM1 GPS_SERIAL_TX
#define PPD_PIN_PM2 GPS_SERIAL_RX
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

// SDS011, the more expensive version of the particle sensor
#define SDS_READ 1
#define SDS_API_PIN 1

// PMS1003, PMS300, 3PMS5003, PMS6003, PMS7003
#define PMS_READ 0
#define PMS_API_PIN 1

// Honeywell PM sensor
#define HPM_READ 0
#define HPM_API_PIN 1

// Tera Sensor Next PM sensor
#define NPM_READ 0
#define NPM_API_PIN 1

// Sensirion SPS30, the more expensive version of the particle sensor
#define SPS30_READ 0
#define SPS30_API_PIN 1
#define SPS30_WAITING_AFTER_LAST_READ 11000   // waiting time after last reading mesurement data in ms
#define SPS30_AUTO_CLEANING_INTERVAL 7200 // time in seconds

// BMP180, temperature, pressure
#define BMP_READ 0
#define BMP_API_PIN 3

// BMP280/BME280, temperature, pressure (humidity on BME280)
#define BMX280_READ 0
#define BMP280_API_PIN 3
#define BME280_API_PIN 11

// SHT3x, temperature, pressure
#define SHT3X_READ 0
#define SHT3X_API_PIN 7

// DS18B20, temperature
#define DS18B20_READ 0
#define DS18B20_API_PIN 13

// DNMS Noise Measurement
#define DNMS_READ 0
#define DNMS_API_PIN 15
#define DNMS_CORRECTION "0.0"

// Temp compensation
#define TEMP_CORRECTION "0.0"

// GPS, preferred Neo-6M
#define GPS_READ 0
#define GPS_API_PIN 9

// MHZ19 CO2 sensor
#define MHZ19_READ 0

// automatic firmware updates
#define AUTO_UPDATE 1

// use beta firmware
#define USE_BETA 0

// OLED Display SSD1306 connected?
#define HAS_DISPLAY 0

// OLED Display SH1106 connected?
#define HAS_SH1106 0

// OLED Display um 180° gedreht?
#define HAS_FLIPPED_DISPLAY 0

// LCD Display LCD1602 connected?
#define HAS_LCD1602 0

// LCD Display LCD1602 (0x27) connected?
#define HAS_LCD1602_27 0

// LCD Display LCD2004 connected?
#define HAS_LCD2004 0

// LCD Display LCD2004 (0x27) connected?
#define HAS_LCD2004_27 0

// Show wifi info on displays
#define DISPLAY_WIFI_INFO 1

// Show device info on displays
#define DISPLAY_DEVICE_INFO 1

// Set debug level for serial output?
#define DEBUG 3
