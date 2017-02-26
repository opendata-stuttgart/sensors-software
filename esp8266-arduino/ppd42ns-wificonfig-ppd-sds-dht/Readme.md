# Version für Sensoren PPD42NS, SDS011, DHT22, BMP180 und NEO-6M.

Features:
* gleichzeitiger Betrieb mehrerer Sensoren
* Konfiguration über WLAN (Sensor als Access Point) möglich
* Unterstützung von OLED-Displays mit SSD1306
* Auswahl der API(s), an welche die Daten gesendet werden, inklusive der Möglichkeit, die Daten als CSV über USB auszugeben
* nutzbar für ESP8266 und Arduino Feather M0 (LoRa)

ToDo's:
* TimeOut für WifiKonfig zum Laufen bekommen
* MQTT-Konfig ergänzen

Die grundsätzliche Konfiguration der Parameter erfolgt über die Datei `ext_dev.h`.

## WLAN Konfiguration

(siehe auch Wiki-Seite auf Github [https://github.com/opendata-stuttgart/meta/wiki/Konfiguration-der-Sensoren](Konfiguration der Sensoren)

Wenn das vorgegebene WLAN nach 10 Sekunden nicht erreichbar ist, wird ein Access-Point eingerichtet, der über "Feinstaubsensor-\[Sensor-ID\]" erreichbar ist. Nach dem Verbinden zu diesem Accesspoint sollten alle Anfragen auf die Konfigurationsseite umgeleitet werden. Direkte Adresse der Seite ist http://192.168.4.1/ .

Konfigurierbar sind:
* WLAN-Name und Passwort
* Auszulesende Sensoren
* Ziele für den Versand der Daten

Nach 5 Minuten sollte der Access-Point wieder deaktiviert werden (funktioniert zur Zeit noch nicht stabil).


## Speichern als CSV

Die Daten können als CSV via USB ausgegeben werden. Dafür sollte sowohl in ext_def.h als auch in der WLAN-Konfiguration Debug auf 0 gesetzt werden, damit die ausgegebenen Daten nur noch die Sensordaten sind. Beim Neustart des ESP8266 erscheinen dann nur noch ein paar wenige Zeichen, die den Startzustand darstellen.

## Wiring

* SDS and DHT wiring: [pdf/sds_dht_wiring.pdf](pdf/sds_dht_wiring.pdf)

## Benötigte Software:

* [Arduino IDE](https://www.arduino.cc/en/Main/Software)  (Version 1.8.1)
* [ESP8266 für Arduino](http://arduino.esp8266.com/stable/package_esp8266com_index.json) (Version 2.3.0)

### Verwendete Bibliotheken (für ESP8266):

In Arduino enthalten:
* Wire

In ESP8266 für Arduino IDE enthalten:
* FS
* ESP8266WiFi
* ESP8266WebServer
* DNSServer

Installierbar über Arduino IDE (Menü Sketch -> Bibliothek einbinden -> Bibliotheken verwalten, in Klammern die getestete Version):
* [ArduinoJson](https://github.com/bblanchon/ArduinoJson) (5.8.2)
* [Adafruit Unified Sensor](https://github.com/adafruit/Adafruit_Sensor) (1.0.2)
* [Adafruit BMP085 library](https://github.com/adafruit/Adafruit-BMP085-Library) (1.0.0)
* [Adafruit BME280 library](https://github.com/adafruit/Adafruit_BME280_Library) (1.0.4)
* [DHT sensor library](https://github.com/adafruit/DHT-sensor-library) (1.3.0)
* [ESP8266 Oled driver for SSD1306 display](https://github.com/squix78/esp8266-oled-ssd1306) (3.2.5)
* ESP8266httpUpdate (1.1.0)
* [PubSubClient](http://pubsubclient.knolleary.net/) (2.6.0)
* [SoftwareSerial](https://github.com/plerup/espsoftwareserial) (1.0.0)

Manuell zu installieren:
* [TinyGPS++](http://arduiniana.org/libraries/tinygpsplus/) (0.94b)


Bis Version NRZ-2016-15:
* [DHT](https://github.com/adafruit/DHT-sensor-library)
  (`DHT.cpp` und `DHT.h` downloaden und in das Softwareverzeichnis kopieren)


## Anschluss der Sensoren

Beim Anschluss von Sensoren mit 5V bitte die Board-Version beachten. NodeMCU v3 liefert 5V an `VU`, Version 2 fehlt dieser Anschluss und `VIN` kann dafür genutzt werden.

### PPD42NS
* Pin 1 => GND
* Pin 2 => Pin D5 / GPIO14
* Pin 3 => VU
* Pin 4 => Pin D6 / GPIO12
* Pin 5 => unused

### DHT22
* Pin 1 => 3V3
* Pin 2 => Pin D7 / GPIO13
* Pin 3 => unused
* Pin 4 => GND

### SDS011
* Pin 1 (TX)   -> Pin D1 / GPIO5
* Pin 2 (RX)   -> Pin D2 / GPIO4
* Pin 3 (GND)  -> GND
* Pin 4 (2.5m) -> unused
* Pin 5 (5V)   -> VU
* Pin 6 (1m)   -> unused


Luftdaten.info API "Pins"
Bei Aktivierung von mehreren Sensoren, z.B. "gleichzeitig" DHT22 und PPD42NS, benötigt die API zur Zuordnung der Sensorwerte die Angabe eines Pins, an dem der Sensor (virtuell) angeschlossen ist.
Diese Firmware definiert die Pins für die verschiedenenen Sensoren wie folgt:
* PPD42NS => Pin 5
* DHT22 => Pin 7
* SDS011 => Pin 1
* BMP180 => Pin 3
* BME280 => Pin 11
* GPS(Neo-6M) => Pin 9


Verwendete Bibliotheken für Adafruit Feather M0 LoRa:

Für die Verwendung der Adafruit Feather Boards muss im Arduino IDE noch der Adafruit Board Index eingetragen werden. Dazu in den Einstellungen die URL
https://adafruit.github.io/arduino-board-index/package_adafruit_index.json als zusätzliche Boardverwalter-URL eintragen. Nach einem Neustart der IDE im Boardverwalter "Adafruit SAMD boards" installieren.

In Arduino enthalten:
* Wire
* SPI

In "Adafruit SAMD Boards" enthalten:


Installierbar über Arduino IDE (für Versionen siehe auch ESP8266):
* [Adafruit BMP085 library](https://github.com/adafruit/Adafruit-BMP085-Library) (1.0.0)
* [ArduinoJson](https://github.com/bblanchon/ArduinoJson) (5.6.4)
* [DHT sensor library](https://github.com/adafruit/DHT-sensor-library) (1.2.3)
* [PubSubClient](http://pubsubclient.knolleary.net/) (2.6.0)
* [SoftwareSerial](https://github.com/plerup/espsoftwareserial) (1.0.0)
* [NTPClient](https://github.com/arduino-libraries/NTPClient) (3.1.0)

Manuell zu installieren:
* [RadioHead Packet Radio library](http://www.airspayce.com/mikem/arduino/RadioHead/) (1.6.1), Link zum Download des Ziparchivs im 2. Abschnitt
* [TinyGPS++](http://arduiniana.org/libraries/tinygpsplus/) (0.94b)

Ich hoffe, alle Bibliotheken erwischt zu haben. Falls beim Kompilieren eine Bibliothek fehlt, bitte als [Issue](https://github.com/opendata-stuttgart/sensors-software/issues/) melden. Ich trage dann die Infos nach.
