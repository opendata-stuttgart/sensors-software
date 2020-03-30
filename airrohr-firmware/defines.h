#if defined(ESP8266)
#define SENSOR_BASENAME "esp8266-"
#define OTA_BASENAME "/airrohr"
#endif


#if defined(ESP32)
#define SENSOR_BASENAME "esp32-"
#define OTA_BASENAME "/airrohr/esp32"
#endif



#define SSID_BASENAME "airRohr-"
#define HOSTNAME_BASE "airRohr-"
#define LEN_CFG_STRING 65
#define LEN_CFG_PASSWORD 65
#define LEN_WLANSSID 35				// credentials for wifi connection
#define LEN_WWW_USERNAME 65			// credentials for basic auth of server internal website
#define LEN_FS_SSID 33				// credentials for sensor access point mode
#define LEN_DNMS_CORRECTION 8
#define LEN_TEMP_CORRECTION 8
#define LEN_SENSEBOXID 30
#define LEN_HOST_INFLUX 100
#define LEN_URL_INFLUX 100
#define LEN_USER_INFLUX 65
#define LEN_MEASUREMENT_NAME_INFLUX 100
#define LEN_HOST_CUSTOM 100
#define LEN_URL_CUSTOM 100
#define LEN_USER_CUSTOM 65
#define MAX_PORT_DIGITS 5

// define debug levels
#define DEBUG_ERROR 1
#define DEBUG_WARNING 2
#define DEBUG_MIN_INFO 3
#define DEBUG_MED_INFO 4
#define DEBUG_MAX_INFO 5

/******************************************************************
 * Constants                                                      *
 ******************************************************************/
constexpr const unsigned long SAMPLETIME_MS = 30000;									// time between two measurements of the PPD42NS
constexpr const unsigned long SAMPLETIME_SDS_MS = 1000;								// time between two measurements of the SDS011, PMSx003, Honeywell PM sensor
constexpr const unsigned long WARMUPTIME_SDS_MS = 15000;								// time needed to "warm up" the sensor before we can take the first measurement
constexpr const unsigned long READINGTIME_SDS_MS = 5000;								// how long we read data from the PM sensors
constexpr const unsigned long SAMPLETIME_NPM_MS = 1000;
constexpr const unsigned long WARMUPTIME_NPM_MS = 15000;
constexpr const unsigned long READINGTIME_NPM_MS = 15000;                // how long we read data from the PM sensors
constexpr const unsigned long SAMPLETIME_GPS_MS = 50;
constexpr const unsigned long DISPLAY_UPDATE_INTERVAL_MS = 5000;						// time between switching display to next "screen"
constexpr const unsigned long ONE_DAY_IN_MS = 24 * 60 * 60 * 1000;
constexpr const unsigned long PAUSE_BETWEEN_UPDATE_ATTEMPTS_MS = ONE_DAY_IN_MS;		// check for firmware updates once a day
constexpr const unsigned long DURATION_BEFORE_FORCED_RESTART_MS = ONE_DAY_IN_MS * 28;	// force a reboot every ~4 weeks

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

//REVOIR POUR LE DEVKIT + IF POUR LE NPM


//GPIO Pins
// the IO pins which can be used for what depends on the following:
//   - The board which is used
//     - onboard peripherials like LCD or LoRa chips which already occupy an IO pin
//     - the ESP32 module which is used
//         - the WROVER board uses the IOs 16 and 17 to access the PSRAW
//         - on WROOM boards the IOs 16 and 17 can be freely used
//   - if JTAG debugging shall be used
//   - some IOs have constraints
//     - configuration of ESP32 module configuration options ("strapping") like operating voltage and boot medium
//     - some IOs can only be used for inputs (34, 35, 36, 39)
// see https://randomnerdtutorials.com/esp32-pinout-reference-gpios/
//     https://github.com/va3wam/TWIPi/blob/master/Eagle/doc/feather-pinout-map.pdf
#define D0_STRAPPING 0
#if defined(NO_USB_SERIAL_ON_UART0)
#define D1 1  // often used for USB serial RX
#endif
#define D2_STRAPPING 2
#if defined(NO_USB_SERIAL_ON_UART0)
#define D3 3  // often used USB serial TX
#endif
#define D4 4
#define D5 5
#define D13 13
// pins 12 to 15 are needed by JTAG and should not be used to allow debugging (if you can afford it)
//#define D9 9
//#define D10 10

#if not defined(USING_JTAG_DEBUGGER_PINS)
#define D12_JTAG_TDI_LOW_DURING_BOOT 12
#define D13_JTAG_TCK 13
#define D14_JTAG_TMS 14
#define D15_JTAG_TDO_HIGH_DURING_BOOT 15
#endif





#if defined(ESP32_WROOM_MODULE)
// these two pins are used to access PSRAM on WROVER modules
#define D16_WROOM_ONLY 16
#define D17_WROOM_ONLY 17
#endif


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
#define D34_INPUTONLY 34
#define D35_INPUTONLY 35
#define D36_INPUTONLY 36
#define D39_INPUTONLY 39

// RFM69 FSK module
#define RF69_FREQ 868.0
#define CLIENT_ADDRESS 2
#define SERVER_ADDRESS 100
#endif
