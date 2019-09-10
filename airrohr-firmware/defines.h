#define LEN_WLANSSID 35				// credentials for wifi connection
#define LEN_WLANPWD 65

#define LEN_WWW_USERNAME 65			// credentials for basic auth of server internal website
#define LEN_WWW_PASSWORD 65

#define LEN_FS_SSID 33				// credentials for sensor access point mode
#define LEN_FS_PWD 65

#define LEN_DNMS_CORRECTION 10

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
// RFM69 FSK module
#define RF69_FREQ 868.0
#define CLIENT_ADDRESS 2
#define SERVER_ADDRESS 100
#endif

#if defined(ESP32)
//GPIO Pins
// the mapping should _not_ be done on this level. The mapping between
// the Dxx Arduino Digital Pin Numbers and the xx IO number is defined
// by the board manufacturer because the Dxx numbers are printed on the board
// only numbers of usable pins are defined (pins internal used to
// access flash and PSRAM pins are omitted). Actually it depends on
// the concrete board which pins are available.
#define D0 0
//#define D1 1  // USB serial RX
#define D2 2
//#define D3 3  // USB serial TX
#define D4 4
#define D5 5
// pins 12 to 15 are needed by JTAG and should not be used when debugging is required
//#define D12 12
//#define D13 13
//#define D14 14
//#define D15 15
#define D18 18
#define D19 19
#define D21 21
#define D22 22
#define D23 23
#define D25 25
#define D26 26
#define D27 27
#define D32 32
#define D33 33
#define D34 34
#define D35 35
#define D36 36
#define D39 39

// RFM69 FSK module
#define RF69_FREQ 868.0
#define CLIENT_ADDRESS 2
#define SERVER_ADDRESS 100
#endif
