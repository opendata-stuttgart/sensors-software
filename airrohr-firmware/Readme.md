IMPORTANT: All pull requests should be made to the beta branch. The master branch is for the actual stable version. 


# Version für Sensoren PPD42NS, SDS011, DHT22, BMP180, NEO-6M und weitere (siehe Konfigurationsseite)

Features:
* gleichzeitiger Betrieb mehrerer Sensoren
* Konfiguration über WLAN (Sensor als Access Point) möglich
* Unterstützung von OLED-Displays mit SSD1306, SH1106 und LCD1602, LCD2004
* Auswahl der API(s), an welche die Daten gesendet werden, inklusive der Möglichkeit, die Daten als CSV über USB auszugeben
* nutzbar mit ESP8266 (NodeMCU und kompatible Boards)

ToDo's:
* Optimierungen (eigentlich immer)
* neue Sensoren

Dateien in diesem Verzeichnis:
airrohr-firmware.ino	-	Sourcecode der eigentlichen Firmware
ext_dev.h				-	grundsätzliche Konfiguration der Parameter (WLAN, Sensoren, APIs)
html-content.h			-	allgemeine HTML-Sourcen und Bilder für HTML- und Text-Ausgaben
intl_xx.h				-	Dateien mit übersetzten Texten für die Internationalisierung, 'xx' ist der 2 letter ISO code der 'Sprache'
intl_template.h			-	Vorlage für Übersetzungen
astyle.rc				-	Formatierungsvorlage für Astyle
ppd42ns-wificonfig-ppd-sds-dht.spiffs.bin	-	Binary mit leerem Dateisystem, zum Löschen der Konfiguration, siehe Anleitung im Wiki

## WLAN Konfiguration
siehe auch Wiki-Seite auf Github [Konfiguration der Sensoren](https://github.com/opendata-stuttgart/meta/wiki/Konfiguration-der-Sensoren)

Wenn das vorgegebene WLAN nach 20 Sekunden nicht erreichbar ist, wird ein Access-Point eingerichtet, der über "Feinstaubsensor-\[Sensor-ID\]" erreichbar ist. Nach dem Verbinden zu diesem Accesspoint sollten alle Anfragen auf die Konfigurationsseite umgeleitet werden. Direkte Adresse der Seite ist http://192.168.4.1/ .

Konfigurierbar sind:
* WLAN-Name und Passwort
* Auszulesende Sensoren
* Ziele für den Versand der Daten

Nach 10 Minuten sollte der Access-Point wieder deaktiviert werden (funktioniert zur Zeit noch nicht stabil).


## Speichern als CSV

Die Daten können als CSV via USB ausgegeben werden. Dafür sollte sowohl in ext_def.h als auch in der WLAN-Konfiguration Debug auf 0 gesetzt werden, damit die ausgegebenen Daten nur noch die Sensordaten sind. Beim Neustart des ESP8266 erscheinen dann nur noch ein paar wenige Zeichen, die den Startzustand darstellen.

## Wiring

* SDS and DHT wiring: [https://raw.githubusercontent.com/opendata-stuttgart/meta/master/files/nodemcu-v3-schaltplan-sds011.jpg](https://raw.githubusercontent.com/opendata-stuttgart/meta/master/files/nodemcu-v3-schaltplan-sds011.jpg)

## Benötigte Software (in Klammern getestete Version und die Art der Lizenz):

* [Arduino IDE](https://www.arduino.cc/en/Main/Software)  (Version 1.8.7) (GNU Lesser General Public License v2.1)
* [ESP8266 für Arduino](http://arduino.esp8266.com/stable/package_esp8266com_index.json) (Version 2.4.2)


### Einstellungen Arduino IDE

* Board: NodeMCU 1.0 (ESP-12E Module)
* CPU Frequency: 160MHz
* Flash Size: 4M (3M SPIFFS)
Ab "ESP für Arduino 2.4.2":
* Debug Port: Disabled
* Debug Level: NoAssert-NDEBUG
* lwIP Variant: v2.0 Lower memory
* VTables. Flash
* Erase Flash: Only Sketch
* in der Datei platform.txt die Zeile
  'build.float=-u _printf_float -u _scanf_float'
  ändern in
  'build.float='

### Verwendete Bibliotheken (für ESP8266):

In Arduino enthalten:
* Wire (GNU Lesser General Public License v2.1)

In ESP8266 für Arduino IDE enthalten:
* FS (GNU Lesser Public License >=2.1)
* ESP8266WiFi (GNU Lesser Public License >=2.1)
* ESP8266WebServer (GNU Lesser Public License >=2.1)
* ESP8266httpUpdate (1.1.0) (GNU Lesser Public License >=2.1)
* DNSServer (GNU Lesser Public License >=2.1)
* SoftwareSerial (GNU Lesser Public License >=2.1). Don't install additional library!!!

Installierbar über Arduino IDE (Menü Sketch -> Bibliothek einbinden -> Bibliotheken verwalten, in Klammern die getestete Version und die Art der Lizenz):
* [ArduinoJson](https://github.com/bblanchon/ArduinoJson) (6.11.0) (MIT)
* [Adafruit Unified Sensor](https://github.com/adafruit/Adafruit_Sensor) (1.0.3) (Apache)
* [Adafruit BMP085 library](https://github.com/adafruit/Adafruit-BMP085-Library) (1.0.1) (BSD)
* [Adafruit BMP280 library](https://github.com/adafruit/Adafruit_BMP280_Library) (1.0.4) (BSD)
* [Adafruit BME280 library](https://github.com/adafruit/Adafruit_BME280_Library) (1.0.8) (BSD)
* [Adafruit HTU21DF library](https://github.com/adafruit/Adafruit_HTU21DF_Library) (1.0.1) (BSD)
* [DallasTemperature](https://github.com/milesburton/Arduino-Temperature-Control-Library) (3.8.0)
* [ESP8266 and ESP32 Oled driver for SSD1306 display](https://github.com/squix78/esp8266-oled-ssd1306) (4.0.0) (MIT)
* [OneWire](www.pjrc.com/teensy/td_libs_OneWire.html) (2.3.4)
* [LiquidCrystal I2C](https://github.com/marcoschwartz/LiquidCrystal_I2C) (1.1.2)

Manuell zu installieren:
* [TinyGPS++](http://arduiniana.org/libraries/tinygpsplus/) (0.95) (GNU Lesser Public License >=2.1)


Bis Version NRZ-2016-15:
* [DHT](https://github.com/adafruit/DHT-sensor-library)
  (`DHT.cpp` und `DHT.h` downloaden und in das Softwareverzeichnis kopieren)

Ich hoffe, alle Bibliotheken erwischt zu haben. Falls beim Kompilieren eine Bibliothek fehlt, bitte als [Issue](https://github.com/opendata-stuttgart/sensors-software/issues/) melden. Ich trage dann die Infos nach.

ACHTUNG: Die DHT sensor library hat ab Version 1.2 ein Problem auf den ESP8266. Daher unbedingt max. Version 1.1.1 benutzen
Um Probleme zu vermeiden, haben wir die letzte funktionierende Version als lokale Kopie eingebunden.

## Anschluss der Sensoren

Beim Anschluss von Sensoren mit 5V bitte die Board-Version beachten. NodeMCU v3 liefert 5V an `VU`, Version 2 fehlt dieser Anschluss und `VIN` kann dafür genutzt werden.

### SDS011
* Pin 1 (TX)   -> Pin D1 (GPIO5)
* Pin 2 (RX)   -> Pin D2 (GPIO4)
* Pin 3 (GND)  -> GND
* Pin 4 (2.5m) -> unused
* Pin 5 (5V)   -> VU
* Pin 6 (1m)   -> unused

### PPD42NS
* Pin 1 => GND
* Pin 2 => Pin D5 (GPIO14)
* Pin 3 => VU
* Pin 4 => Pin D6 (GPIO12)
* Pin 5 => unused

### DHT22
* Pin 1 => 3V3
* Pin 2 => Pin D7 (GPIO13)
* Pin 3 => unused
* Pin 4 => GND

### DS18B20 (OneWire interface)
Please check your version (pinout) at [https://datasheets.maximintegrated.com/en/ds/DS18B20.pdf]
Uses the same PIN D7 as DHT22, so DHT22 OR DS18B20 can be used. 
* GND  -> Pin GND
* DQ   -> Pin D7 (GPIO 13)
* VCC  -> Pin 3V3 or Pin VU

### PMS1003 to PMS6003
Pinout:
   8 7 6 5 4 3 2 1

* Pin 1 (VCC)   -> VU
* Pin 2 (GND)   -> GND
* Pin 3 (SET)   -> unused
* Pin 4 (RX)    -> Pin D2 (GPIO4)
* Pin 5 (TX)    -> Pin D1 (GPIO5)
* Pin 6 (RESET) -> unused
* Pin 7	(NC)	-> unused
* Pin 8 (NC)	-> unused

### PMS7003
Pinout PMS7003:
   9  7  5  3  1
  10  8  6  4  2

* Pin  1/2 (VCC) -> VU
* Pin  3/4 (GND) -> GND
* Pin  5 (RESET) -> GND
* Pin  6 (NC)    -> unused
* Pin  7 (RX)    -> Pin D2 (GPIO4)
* Pin  8 (NC)    -> unused
* Pin  9 (TX)    -> Pin D1 (GPIO5)
* Pin 10 (SET)   -> unused

### Honeywell PM sensor
Pinout:
   8 7 6 5 4 3 2 1
* Pin 1 (3.3V)   -> unused
* Pin 2 (5V)     -> VU
* Pin 3 (NC)     -> unused
* Pin 4 (NC)     -> unused
* Pin 5 TEST)    -> unused
* Pin 6 (TX)     -> Pin D1 (GPIO5)
* Pin 7	(RX)     -> Pin D2 (GPIO4)
* Pin 8 (GND)    -> GND

### BMP180 / BMP280 / BME280 (I2C)
* VCC  ->  Pin 3V3
* GND  ->  Pin GND
* SCL  ->  Pin D4 (GPIO2)
* SDA  ->  Pin D3 (GPIO0)

### HTU21D (I2C)
* VCC  ->  Pin 3V3
* GND  ->  Pin GND
* SCL  ->  Pin D4 (GPIO2)
* SDA  ->  Pin D3 (GPIO0)

### LCD1602 (I2C, 5V - check your version)
* VCC  ->  Pin VU
* GND  ->  Pin GND
* SCL  ->  Pin D4 (GPIO2)
* SDA  ->  Pin D3 (GPIO0)

### OLED displays with SSD1306 (I2C, 128x64 pixels)
* VCC -> Pin VU
* GND -> Pin GND
* SCL  ->  Pin D4 (GPIO2)
* SDA  ->  Pin D3 (GPIO0)

### GPS NEO 6M (seriell) ACHTUNG: Läuft sehr instabil
Strom und Masse vom Board. (GND und üblicherweise 3,3v, vorher prüfen/Anleitung, Beschreibung GPS!) 
TX (senden) und RX (empfangen) werden gekreuzt verkabelt! 
* TX von Neo -> Pin D5 (RX) 
* RX von Neo -> Pin D6 (TX) 

### Luftdaten.info API "Pins"
Bei Aktivierung von mehreren Sensoren, z.B. "gleichzeitig" DHT22 und PPD42NS, benötigt die API zur Zuordnung der Sensorwerte die Angabe eines Pins, an dem der Sensor (virtuell) angeschlossen ist.
Diese Firmware definiert die Pins für die verschiedenenen Sensoren wie folgt:
* PPD42NS => Pin 5
* DHT22 => Pin 7
* SDS011 => Pin 1
* BMP180 => Pin 3
* BMP280 => Pin 3
* BME280 => Pin 11
* GPS(Neo-6M) => Pin 9


## Translations
For new translations copy the file intl_template.h and rename it to intl_<2-letter-code>.h, where <2-letter-code> is the ISO-3166-2 2 letter country code. This file contains all strings used for output seen by normal users. Only debug output is (or better should be) English by default.  
Please take look at the existing translations. This should show you how it works ;-)
