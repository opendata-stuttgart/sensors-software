NRZ-2018-104-B11
* wrong comparison in influx config
* combining pm sensor functions (start, stop, continuous mode)

NRZ-2018-104-B10
* one definition per interface (I2C, one wire, serial sensors, serial gps)

NRZ-2018-104-B9
* added missing '/' in path for API Madavi.de

NRZ-2018-104-B8
* switched to actual version of DHT library as local copy with changes for ESP8266 timing and pins

NRZ-2018-104-B7
* wrong comparison for default opensensemap box id

NRZ-2018-104-B6
* changed string constants to defines
* removed unneeded string conversions
* more strings moved to flash

NRZ-2018-104-B5
* unneeded source code removed

NRZ-2018-104-B4
* freeing some RAM and flash memory after adding SH1106 OLED

NRZ-2018-104-B3
* handling of special chars in config json and config page (i.e ', ", \)
* added support for OLED displays with SH1106 chipset
* some space optimisations

NRZ-2018-104-B2
* sending signal strength to InfluxDB
* optimizations in reading PM sensors 
* disable sending data to OpenSenseMap with 'default' BoxID
* disable sending data to InfluxDB at Luftdaten.info (only used internally)
* character ' in text input fields (i.e. wifi SSID) should be displayed correctly

NRZ-2018-104-B1
* double quote in config strings (i.e. passwords) should work now

NRZ-2018-103
online since 2018-06-02
* same as NRZ-2018-102-B2

NRZ-2018-102-B2
* added Prometheus endpoint
* optimizing flash and memory usage

NRZ-2018-102-B1
* test with DHT sensor library 1.1.1 instead of 1.3.0

NRZ-2018-101
* same as NRZ-2017-100-B16

NRZ-2017-100
beta
* optimizing display function: more than one 'screen' for infos
* added dependencies for OneWire
* added wiring for new sensors to Readme.md
* added support for Honeywell PM sensor
* enable configurable usage of beta firmware
* removing Arduino Feather code
* version B4: right align values
* version B4: added display of DS18B20 and HTU21D values
* version B5: wpa2 password can be configured for sensor in AP mode
* version B5: more info to sensors on config page
* version B5: some flash memory optimizations
* version B5: parseable data.json before first measurement
* version B5: GPS data on value page
* version B6: added swedish translations
* version B6: error in start/stop commands corrected
* version B7: showing GPS data on displays
* version B7: wrong output on config save corrected
* version B7: double date/time on values page corrected
* version B7: changed codefor logo to png
* version B8: new TinyGPS++ 0.94a -> 0.95
* version B8: larger buffer for GPS SoftSerial
* version B8: removed INPUT_PULLUP for DHT22
* version B9: wrong value for signal quality was shown on display
* version B9: 'memory leak' removed
* version B9: added LICENSE.md
* version B10: reduced amount of NMEA messages
* version B10: don't fall back to plain HTTP on WPA2 wifi
* version B10: larger buffer for serialGPS
* version B11: new languages RU and CZ
* version B11: changed lib for HTU21D from Sparkfun to Adafruit
* version B11: added LCD2004 display
* version B11: debug infos on LCD displays
* version B11: changed BME280 to forced measurements to get more accurate temperature values
* version B11: corrected error in sending HTU21D data to luftdaten.info API
* version B12: switched to ESP8266 library/extension version 2.4 (including KRACK patch)
* version B13: added new Arduino Options, CodeFor.de logo removed and other unneeded binary data removed, problem with lwIP v2 solved
* version B14: setting 'continuous mode' for pm sensors
* version B15: test of esp8266 lib 2.4.1 with prebuilt lwIP 1.4
* version B16: changed back to esp8266 lib 2.3.0

NRZ-2017-099
online since 2017-09-10
* time since last measurement counts in wrong direction

NRZ-2017-098
online as update since 2017-09-06
* added support for PMS5003, PMS6003
* portuguese version added
* reenabled masked passwords
* refactored sending to luftdaten.api
* time to first and time since last measurement had shown impossible values

NRZ-2017-097
online since 2017-08-21
* basic auth password was saved as stars on saving config again
* some minor changes to reduce flash memory usage

NRZ-2017-095
online as update since 2017-08-17
* added support for HTU21D
* added support for DS18B20
* added support for BMP280
* added support for PMS1003, PMS3003, PMS7003
* masked wifi password in config page

NRZ-2017-092
online as update since 2017-06-24
* added time of first measurement to value page
* timeout for wifi connect set to 20 seconds, some networks seem to need more than 10 seconds
* time between measurements and timeout of wifi config mode now configurable

NRZ-2017-090
online as update since 2017-06-17
* list of available wifi networks implemented as ajax request to speedup config page

NRZ-2017-089
online as update since 2017-06-06
* wifi strength always shown with 100%

NRZ-2017-087
online as update since 2017-06-05
* emergency update, gzip compressed svg logos not working on all sensors

NRZ-2017-086
online as update since 2017-06-02
* error in calculating median of PM values corrected
* italian and dutch version added

NRZ-2017-085
online as update since 2017-06-02
* gzip compressed svg logos, to save memory
* removing highest and lowest value from PM value array for mean calculation
