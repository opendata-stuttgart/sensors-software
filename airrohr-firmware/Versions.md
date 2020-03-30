NRZ-2020-130-B4
* Prevent password leakage in configuration dialogs
* Change default password for webpage auth to ""
* Ignore measurement interval settings below 5s
* Track API sending errors for each API separately

NRZ-2020-130-B3
* Serial debug output on webpage
* Refactoring

NRZ-2020-130-B2
* Avoid crash on WiFi network scan failure (Related to #615)
* Only do OTA after sensor measurements are finished
* Remove uninitialized memory read in NTP handling
* Accept larger flash sizes also as compatible
* Switch to a tab based configuration page
* Skip initialization of display's when not configured
* Delay OneWire initialization until configured
* Fix bulgarian translation error (Fixes #622)
* Fix hang on BME/P280 measurement read
* Connect up to wifi channel 13 if locale is not EN (Fixes #626)
* Use IPv6 LWIP (Related to #605)
* Add configurable temperature correction (Fixes #607)

NRZ-2020-130-B1
* next beta version

NRZ-2020-129
online since 2020-01-07
* same as NRZ-2019-128-B8 (+build date is shown in header)

NRZ-2019-128-B8
* Improve NTP handling and status reporting
* Fix weird placement of "save and restart" button in config
* Fix handling of short intervals with SDS011 (Fixes #426)
* Erase SDK config on OTA restart (Fixes #590)
* Add link to report an issue to web ui
* Add self-test
* Split less recommended sensors into a subsection of config page (Fixes #171)

NRZ-2019-128-B7
* More introspection status for OTA and sending errors
* Resorting Language selection alphabetically
* Disable language and beta selector when OTA is disabled

NRZ-2019-128-B6
* Fix crash on device status page in some locales

NRZ-2019-128-B5
* Avoid calling wifi off on startup which seems to cause some issues (Fixes #598)

NRZ-2019-128-B4
* perfom blocking reads on SDS011 serial responses
* Add Device Status webpage
* Set DHCP hostname to the firmware config wifi name (Fixes #595)
* Polish translation fixes
* Mark potentially destructive actions with red highlight (idea from nettigo FW)
* Add support for LCD 2004 on I2C 0x3F address

NRZ-2019-128-B3
* Fix startup hang on wifis without NTP access (#580)
* Update SHT3.x to 1.1.6

NRZ-2019-127-1 (intermediate version)
online since 2019-12-03
* same as NRZ-2019-127-B2

NRZ-2019-128-B2
* Initialize MDNS after wifi to restore functionality

NRZ-2019-128-B1
* next beta version

NRZ-2019-127
online since 2019-12-02
* same as NRZ-2019-126-B9

NRZ-2019-126-B9
* Update to Arduino Core 2.6.2 to fix WiFi stability issues

NRZ-2019-126-B8
* Updated translations
* Collect error counters
* Serbian localization added

NRZ-2019-126-B7
* Updated italian translations - thanks stewecar
* Fix instabilities in SDS011 measurement decoding

NRZ-2019-126-B6
* Read SDS011 version once on startup
* Discard power-on self-test dust sensor measurements
* Do not store WiFi station credentials in SDK protected flash
* Switch to ArduinoJson 6.13
* show SDS011 manufacturing date in values HTML page
* Update to Arduino Core 2.6.1, including many fixes for SSL, WiFi and SoftwareSerial
* Update SHT3.x to 1.1.5

NRZ-2019-126-B5
* Rename Luftdaten.info to Sensors.Community everywhere
* Report the submitted wifi signal quality level in the web UI
* Keep WiFi information persistent over restarts
* Perform WiFi Tx power calibration on boot

NRZ-2019-126-B4
* Try to configure system time from 3 different NTP sources
* When system time is invalid, disable TLS verification
* Use TLS for Feinstaub-App reporting

NRZ-2019-126-B3
* OTA updater validates loader checksums prior update
* Maintain config setting backups and fall back if current version is corrupt
* Code cleanups
* Fix regression in Humidity Reading of BME280
* Fix regression in logging to Feinstaub App

NRZ-2019-126-B2
* Switch to Arduino Core 2.5.2
* Switch OTA updater to use TLS with server certificate verification
* SSL server certificate verification for Madavi, Sensor Community and OpenSensemap
* Update ESPSoftwareSerial to 5.0.4
* Add support for Sensirion SHT3x Temperature/Humidity sensors
* Code size optimisations
* Fix pressure precision of BMP/BME280

NRZ-2019-126-B1
* next beta version

NRZ-2019-125-B1
* Revert unintentional default senseboxid change

NRZ-2019-125
online since 2019-10-31
* same as NRZ-2019-124-B10
  (+ renaming PM value names for SDS30)

NRZ-2019-124-B10
* Persist Wifi configuration in flash
* Rewrite config using current format when version changes
* Fix truncation of wifi password
* prometheus endpoint: esp prefix was missing

NRZ-2019-124-B9
* Handle Si7021 for HTU21d replacement
* Fix GPS regression

NRZ-2019-124-B8
* bug fixes
* translation updates

NRZ-2019-124-B7
* Fix update checking interval

NRZ-2019-124-B6
* noise sensor added
* Sensirion SPS30 added
* option to flip OLED output
* Fix crash on selecting available networks in AP mode
* add options to disable display of wifi and device infos
* Code size optimisations
* Serve config pages incrementally to avoid running out of memory
* Write more compliant config JSON
* Advertise as http://airrohr-$espid.local/ in AP mode
* BMP280/BME280 sensors are merged into one implementation
* Switch OTA updater two a two-Stage implemenation allowing more than 512kb of sketch size
* Fix memory corruption when using displays
* Reduce memory consumption in data sending which allows keeping the HTTP server available

NRZ-2019-124-B5
* some comments removed
* Var2Json casts optimized
* new name "airRohr"
* new logo (license CC0)

NRZ-2019-124-B4
* wrong variable use in PMSx003 function
* showing text on wrong LCD display

NRZ-2019-124-B4
* SSL options for custom and influxdb added

NRZ-2019-124-B3
* merged changes for aircms support
* some optimizations of html code
* changes for support of ESP32 (not working completely until now)

NRZ-2018-124-B2
* redefine function overload

NRZ-2018-124-B1
* code cleanup

NRZ-2018-123
online since 2018-12-23
* set CPUFreqency to 160MHz (for faster TLS handling)

NRZ-2018-123
online since 2018-12-23
* same as NRZ-2018-122-B1

NRZ-2018-122-B1
* try NTP server given by dhcp first
* try router/gateway as NTP server as third
* handle ntp time setting
* turkish translation added
* compile with Arduino esp8266 lib 2.4.2

NRZ-2018-121C
online since 2018-12-03
* disable HTTPS as default

NRZ-2018-121B
online since 2018-12-03
* added danish translation
* limit SNTP retries to 15 seconds

NRZ-2018-121B
online since 2018-12-03
* back to Arduino esp8266 lib 2.3

NRZ-2018-121A
online since 2018-12-03
* disabled cert verify

NRZ-2018-121
online since 2018-12-02
* same as NRZ-2018-121

NRZ-2018-120-B1
* added first parts for change to BearSSL
* changed SSL as default to non-SSL

NRZ-2018-117
online since 2018-11-19
* same as NRZ-2018-116-B1

NRZ-2018-116-B1
* disabling cert verification, seems to need too long, blocking server resources

NRZ-2018-115
online since 2018-11-19
* same as NRZ-2018-114-B2

NRZ-2018-114-B2
* more code cleanup
* replacing default Arial_MT font with Roboto_Mono_9

NRZ-2018-114-B1
* going back to beta
* more code cleanup
* reactivated sending as CSV to serial

NRZ-2018-113
NOT published
* same as NRZ-2018-112-B5

NRZ-2018-112-B5
* more merged pull requests (fmeerkoetter), i.e. move font to own include file
* move ca cert to own include file

NRZ-2018-112-B4
* merged pull requests (fmeerkoetter), i.e. refactoring some functions, memory optimizations
* added translations

NRZ-2018-112-B3
* changing config to restart after every change/save
* translations (PROGMEM var names from german to english)

NRZ-2018-112-B3
* verify certificates for HTTPS connections to Luftdaten.info and Madavi.de API
  (works only with Let's Encrypt certs)
* memory optimizations

NRZ-2018-112-B2
* merged pull requests (fmeerkoetter) typedef, duplicate code in function
* same read function for all Plantower sensors

NRZ-2018-112-B1
* setting PHY layer to 802.11n in station mode
* switching to Arduino EXP8266 library 2.4.2 (see README.md)
* added cert validation for API requests (Letsencrypt only at the moment)

NRZ-2018-111
online since 2018-09-20
* same as NRZ-2018-110-B11

NRZ-2018-110-B11
* config for sending data to "Feinstaub App" server
* corrected removing hidden SSIDs from wifi list

NRZ-2018-110-B10
removing debug output of wifi password

NRZ-2018-110-B9
* removing hidden SSIDs from wifi list
* another change for Captive portal support for iOS devices

NRZ-2018-110-B8
* changing back to previous version of Captive portal for iOS

NRZ-2018-110-B7
* adding SSL switch for API server (Luftdaten.info, Madavi.de, OpenSenseMap)
* changes added to avoid message "Initialize indices array with constant value" in some IDEs
* disable caching of config page, just in case that the client has received a blank page before
* modified Captive portal for iOS devices

NRZ-2018-110-B6
* shorter config page in AP mode
* removing 'save' buttons except the last on config page
* deleting password for AP mode (for WPA/WPA2) wasn't possible

NRZ-2018-110-B5
* captive portal should work with iOS devices also
* setting PHY layer 802.11g and max. signal strength just to be sure
* removing some unneeded wifi connects after wifi config

NRZ-2018-110-B4
* scan for wifi networks before going to config mode to avoid wifi mode changes
* select channel with lowest signal for AP mode

NRZ-2018-110-B3
* cosmetic changes to get rid of some compiler warnings

NRZ-2018-110-B2
* changed deprecated ArduinoJSON function calls

NRZ-2018-110-B1
* setting wifi mode to AP only in config mode

NRZ-2018-109
online since 2018-09-04
* same as NRZ-2018-108-B1

NRZ-2018-108-B1
* wrong string in BMP280 function

NRZ-2018-107
online since 2018-08-09
* same as NRZ-2018-106-B1

NRZ-2018-106-B1
* OLED SH1106 only showing text if SSD1306 if enabled
* LCD2004 only showing text if LCS1602 is enabled

NRZ-2018-105
online since 2018-08-07
* same as NRZ-2018-104-B12

NRZ-2018-104-B12
* config page didn't load before the first measurement
  seems it was a memory problem
  removing some unneeded html reduced size to 9,5kByte, page is loading

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
