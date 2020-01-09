# Contributing Guidelines


## IMPORTANT Information

All new development changes should be done as pull requests against the **beta** branch.

The default **master** branch is only used as a source reference for the
currently active (enrolled) firmware version.


## Reporting bugs

Before creating bug reports, please check [this list](#before-submitting-a-bug-report) as you might find out that you don't need to create one. When you are creating a bug report, please include as many details as possible in literal form (e.g. copy, don't interpret).

**Note:** If you find a **Closed** issue that seems like it is the same thing that you're experiencing, open a new issue and include a link to the original issue in the body of your new one.


### Before Submitting A Bug Report

* **Check the [FAQs on luftdaten.info](https://luftdaten.info/faq/)** for a list of common questions and problems.
* **Perform a [cursory search](https://github.com/search?utf8=%E2%9C%93&q=+is%3Aissue+user%3Aopendata-stuttgart+repo%3Asensors-software&type=)** to see if the problem has already been reported. If it has **and the issue is still open**, add a comment to the existing issue instead of opening a new one.


## Build Instrutions

### Recommended Build using PlatformIO

Current revisions of airRohr firmware are being tested and released by using
[PlatformIO Core](https://platformio.org/install/cli). The included `platformio.ini`
file is used to install and update all required dependencies into the correct
and required version. While the dependencies are listed here in more detail, the
authoritative versions and references are in the platformio.ini file.

PlatformIO provides [many IDE integrations](https://platformio.org/install/integration). 


### Build using Arduino IDE

As a fall back it should be possible to build the firmware via the Arduino IDE. This
method is only a fallback over the PlatformIO. Any submission to the repository
must pass building and work with a PlatformIO based build.

Settings needed:
* [Arduino IDE](https://www.arduino.cc/en/Main/Software)  (Version 1.8.10) (GNU Lesser General Public License v2.1)
* [ESP8266 für Arduino](http://arduino.esp8266.com/stable/package_esp8266com_index.json) (Version 2.6.2)

Configuration Settings in Arduino IDE:
* Board: NodeMCU 1.0 (ESP-12E Module)
* CPU Frequency: 160MHz
* Flash Size: 4M (3M SPIFFS)
* Debug Port: Disabled
* Debug Level: NoAssert-NDEBUG
* lwIP Variant: v2.0 Lower memory
* VTables. Flash
* Erase Flash: Only Sketch

Libraries used from ESP8266 Arduino:
* Wire (GNU Lesser General Public License v2.1)
* FS (GNU Lesser Public License >=2.1)
* ESP8266WiFi (GNU Lesser Public License >=2.1)
* ESP8266WebServer (GNU Lesser Public License >=2.1)
* ESP8266HTTPClient (GNU Lesser Public License >=2.1)
* DNSServer (GNU Lesser Public License >=2.1)

Additional Libraries needed for building:
* [ArduinoJson](https://github.com/bblanchon/ArduinoJson) (6.13.0) (MIT)
* [Adafruit BMP085 library](https://github.com/adafruit/Adafruit-BMP085-Library) (1.0.1) (BSD)
* [Adafruit HTU21DF library](https://github.com/adafruit/Adafruit_HTU21DF_Library) (1.0.2) (BSD)
* [Adafruit SHT31 library](https://github.com/adafruit/Adafruit_SHT31)(1.1.5) (BSD)
* [DallasTemperature](https://github.com/milesburton/Arduino-Temperature-Control-Library) (3.8.0)
* [ESP8266 and ESP32 Oled driver for SSD1306 display](https://github.com/squix78/esp8266-oled-ssd1306) (4.1.0) (MIT)
* [OneWire](www.pjrc.com/teensy/td_libs_OneWire.html) (2.3.4)
* [LiquidCrystal I2C](https://github.com/marcoschwartz/LiquidCrystal_I2C) (1.1.2)
* [EspSoftwareSerial](https://github.com/plerup/espsoftwareserial)(6.3.0)
* [TinyGPS++](http://arduiniana.org/libraries/tinygpsplus/) (1.0.2) (GNU Lesser Public License >=2.1)


## Source Layout

| Dateiname                                 | Beschreibung                                                                                               |
| ----------------------------------------- | ---------------------------------------------------------------------------------------------------------- |
| `airrohr-firmware.ino`                      | Sourcecode der eigentlichen Firmware                                                                       |
| `ext_def.h`                                 | grundsätzliche Konfiguration der Parameter (WLAN, Sensoren, APIs)                                          |
| `html-content.h`                            | allgemeine HTML-Sourcen und Bilder für HTML- und Text-Ausgaben                                             |
| `intl_xx.h`                                 | Dateien mit übersetzten Texten für die Internationalisierung, 'xx' ist der 2 letter ISO code der 'Sprache' |
| `intl_template.h`                           | Vorlage für Übersetzungen                                                                                  |
| `astyle.rc`                                 | Formatierungsvorlage für Astyle                                                                            |
| `ppd42ns-wificonfig-ppd-sds-dht.spiffs.bin` | Binary mit leerem Dateisystem, zum Löschen der Konfiguration, siehe Anleitung im Wiki                      |


## Translations

For new translations copy the file `intl_template.h` and rename it to `intl_xx.h`, where `xx` is the ISO-3166-2 two letter country code. This file contains all strings used for
output seen by normal users. Only debug output is remaining EN by default.

Please take look at the existing translations and try to adhere and improve
consistency accross and within the particular translation.


## TODOs

* [Bug fixes](https://github.com/opendata-stuttgart/sensors-software/issues?q=is%3Aopen+label%3Abug+sort%3Aupdated-desc)
* [Enhancements (New Sensors, Larger Efforts)](https://github.com/opendata-stuttgart/sensors-software/issues?q=is%3Aopen+label%3Aenhancement+sort%3Aupdated-desc)
* Optimisations
