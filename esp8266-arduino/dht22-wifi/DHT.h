/* DHT library

MIT license
written by Adafruit Industries
*/
#ifndef DHT_H
#define DHT_H

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif


// Uncomment to enable printing out nice debug messages.
//#define DHT_DEBUG

// Define where debug output will be printed.
#define DEBUG_PRINTER Serial

// Setup debug printing macros.
#ifdef DHT_DEBUG
  #define DEBUG_PRINT(...) { DEBUG_PRINTER.print(__VA_ARGS__); }
  #define DEBUG_PRINTLN(...) { DEBUG_PRINTER.println(__VA_ARGS__); }
#else
  #define DEBUG_PRINT(...) {}
  #define DEBUG_PRINTLN(...) {}
#endif

// Define types of sensors.
#define DHT11 11
#define DHT22 22
#define DHT21 21
#define AM2301 21


class DHT {
  public:
   DHT(uint8_t pin, uint8_t type, uint8_t count=6);
   void begin(void);
   float readTemperature(bool S=false, bool force=false);
   float convertCtoF(float);
   float convertFtoC(float);
   float computeHeatIndex(float temperature, float percentHumidity, bool isFahrenheit=true);
   float readHumidity(bool force=false);
   boolean read(bool force=false);

 private:
  uint8_t data[5];
  uint8_t _pin, _type;
  #ifdef __AVR
    // Use direct GPIO access on an 8-bit AVR so keep track of the port and bitmask
    // for the digital pin connected to the DHT.  Other platforms will use digitalRead.
    uint8_t _bit, _port;
  #endif
  uint32_t _lastreadtime, _maxcycles;
  bool _lastresult;

  uint32_t expectPulse(bool level);

};

class InterruptLock {
  public:
   InterruptLock() {
    noInterrupts();
   }
   ~InterruptLock() {
    interrupts();
   }

};

#endif



//Lang Konfig
#define CURRENT_LANG INTL_LANG

// WLAN Konfig
#define WLANSSID "Freifunk-disabled"
#define WLANPWD ""

// BasicAuth Konfig
#define WWW_USERNAME "admin"
#define WWW_PASSWORD "feinstaub"
#define WWW_BASICAUTH_ENABLED 0

// Wohin gehen die Daten?
#define SEND2DUSTI 1
#define SEND2MADAVI 1
#define SEND2SENSEMAP 0
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

// Definition eigene API
#define HOST_CUSTOM "192.168.234.1"
#define URL_CUSTOM "/data.php"
#define PORT_CUSTOM 80
#define USER_CUSTOM ""
#define PWD_CUSTOM ""

// Definition eigene InfluxDB
#define HOST_INFLUX "api.luftdaten.info"
#define URL_INFLUX "/write?db=luftdaten"
#define PORT_INFLUX 8086
#define USER_INFLUX "luftdaten"
#define PWD_INFLUX "info"

// DHT22, Sensor Temperatur und Luftfeuchte
#define DHT_READ 1
#define DHT_TYPE DHT22
#define DHT_API_PIN 7
#if defined(ESP8266)
#define DHT_PIN D7
#endif
#if defined(ARDUINO_SAMD_ZERO)
#define DHT_PIN D9
#endif

// HTU21D, Sensor Temperatur und Luftfeuchte
#define HTU21D_READ 0
#define HTU21D_API_PIN 7
#if defined(ESP8266)
#define HTU21D_PIN_SCL D4
#define HTU21D_PIN_SDA D3
#endif

// PPD42NS, der günstigere der beiden Feinstaubsensoren
#define PPD_READ 0
#define PPD_API_PIN 5
#if defined(ARDUINO_SAMD_ZERO) || defined(ESP8266)
#define PPD_PIN_PM1 D6
#define PPD_PIN_PM2 D5
#endif

// SDS011, der etwas teuerere Feinstaubsensor
#define SDS_READ 1
#define SDS_API_PIN 1
#if defined(ESP8266)
// Serial confusion: These definitions are based on SoftSerial
// TX (transmitting) pin on one side goes to RX (receiving) pin on other side
// SoftSerial RX PIN is D1 and goes to SDS TX
// SoftSerial TX PIN is D2 and goes to SDS RX
#define SDS_PIN_RX D1
#define SDS_PIN_TX D2
#endif

// PMS3003
#define PMS24_READ 0

// PMS1003, PMS7003
#define PMS32_READ 0

// all Plantower (PMS) sensors
#define PMS_API_PIN 1
#if defined(ESP8266)
#define PMS_PIN_RX D1
#define PMS_PIN_TX D2
#endif

// BMP180, Luftdruck-Sensor
#define BMP_READ 0
#define BMP_API_PIN 3
#if defined(ESP8266)
#define BMP_PIN_SCL D4
#define BMP_PIN_SDA D3
#endif

// BMP280, Luftdruck-Sensor
#define BMP280_READ 0
#define BMP280_API_PIN 3
#if defined(ESP8266)
#define BMP280_PIN_SCL D4
#define BMP280_PIN_SDA D3
#endif

// BME280, Luftdruck-Sensor
#define BME280_READ 0
#define BME280_API_PIN 11
#if defined(ESP8266)
#define BME280_PIN_SCL D4
#define BME280_PIN_SDA D3
#endif

// DS18B20, Temperatur-Sensor
#define DS18B20_READ 0
#define DS18B20_API_PIN 13
#if defined(ESP8266)
#define DS18B20_PIN D7
#endif


// GPS, bevorzugt Neo-6M
#define GPS_READ 0
#define GPS_API_PIN 9
#if defined(ESP8266)
#define GPS_PIN_RX D5
#define GPS_PIN_TX D6
#endif

// Automatische Firmware-Updates über WLAN
#define AUTO_UPDATE 1

// OLED Display SSD1306 angeschlossen?
#define HAS_DISPLAY 0

// LCD Display LCD1602 angeschlossen?
#define HAS_LCD1602 0

// Wieviele Informationen sollen über die serielle Schnittstelle ausgegeben werden?
#define DEBUG 3

// Definition der Debuglevel
#define DEBUG_ERROR 1
#define DEBUG_WARNING 2
#define DEBUG_MIN_INFO 3
#define DEBUG_MED_INFO 4
#define DEBUG_MAX_INFO 5
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
