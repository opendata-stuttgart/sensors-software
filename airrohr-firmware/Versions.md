NRZ-2017-100
beta
* optimizing display function: more than one 'screen' for infos
* added dependencies for OneWire
* added wiring for new sensors to Readme.md
* added support for Honeywell PM sensor
* enable configurable usage of beta firmware
* removing Arduino Feather code

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
