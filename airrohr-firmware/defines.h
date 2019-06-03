#define LEN_WLANSSID 35
#define LEN_WLANPWD 65

#define LEN_WWW_USERNAME 65
#define LEN_WWW_PASSWORD 65

#define LEN_FS_SSID 33
#define LEN_FS_PWD 65

#define LEN_SENSEBOXID 30

#define LEN_HOST_INFLUX 100
#define LEN_URL_INFLUX 100
#define LEN_USER_INFLUX 65
#define LEN_PWD_INFLUX 65
#define LEN_MEASUREMENT_NAME_INFLUX 100

#define LEN_HOST_CUSTOM 100
#define LEN_URL_CUSTOM 100
#define LEN_USER_CUSTOM 65
#define LEN_PWD_CUSTOM 65

#define MAX_PORT_DIGITS 5

// define debug levels
#define DEBUG_ERROR 1
#define DEBUG_WARNING 2
#define DEBUG_MIN_INFO 3
#define DEBUG_MED_INFO 4
#define DEBUG_MAX_INFO 5
/*

static const uint16_t suites[] PROGMEM = {
  BR_TLS_ECDHE_ECDSA_WITH_CHACHA20_POLY1305_SHA256,
  BR_TLS_ECDHE_RSA_WITH_CHACHA20_POLY1305_SHA256,
  BR_TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256,
  BR_TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256,
  BR_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256,
  BR_TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256
};
*/

// Definition GPIOs for Zero based Arduino Feather M0 LoRaWAN
#if defined(ARDUINO_SAMD_ZERO) && defined(SERIAL_PORT_USBVIRTUAL)
// Required for Serial on Zero based boards
#define Serial SERIAL_PORT_USBVIRTUAL
//GPIO Pins
#define D0 0
#define D1 1
#define D2 2
#define D3 3
#define D4 4
#define D5 5
#define D6 6
#define D7 7
#define D8 8
#define D9 9
#define D10 10
#define D11 11
#define D12 12
// LoRa module
#define RFM69_CS 8
#define RFM69_RST 4
#define RFM69_INT 3
#define RF69_FREQ 868.0
#define CLIENT_ADDRESS 2
#define SERVER_ADDRESS 100
#endif

#if defined(ESP32)
//GPIO Pins
#define D0 0
#define D1 12   // RX Serial SDS
#define D2 13   // TX Serial SDS
#define D3 4    // I2C SDA
#define D4 15   // I2C SCL
#define D5 22   // RX GPS
#define D6 23   // TX GPS
#define D7 36   // OneWire
#define D8 8
#define D9 9
#define D10 10
#define D11 11
#define D12 12
// LoRa module
#define RFM69_CS 8
#define RFM69_RST 4
#define RFM69_INT 3
#define RF69_FREQ 868.0
#define CLIENT_ADDRESS 2
#define SERVER_ADDRESS 100
#endif
