Version für Sensoren PPD42NS, SDS011 und DHT22.
Inklusive Konfiguration über WLAN.
Daten können gesendet werden an Dusti-API, Madavi-API oder können ausgegeben werden als CSV über USB.

ToDo's:
- TimeOut für WifiKonfig zum Laufen bekommen
- MQTT-Konfig ergänzen

Die grundsätzliche Konfiguration der Parameter erfolgt über die Datei ext_dev.h .
    
WLAN Konfiguration:

Wenn das vorgegebene WLAN nach 10 Sekunden nicht erreichbar ist, wird ein Access-Point eingerichtet, der über "Feinstaubsensor-\[Sensor-ID\]" erreichbar ist. Nach dem Verbinden zu diesem Accesspoint sollten alle Anfragen auf die Konfigurationsseite umgeleitet werden. Direkte Adresse der Seite ist http://192.168.4.1/ .

Konfigurierbar sind:  
- WLAN-Name und Passwort  
- welche Sensoren sollen ausgelesen werden  
- an wen werden die Daten gesendet  
  
Nach 5 Minuten sollte der Access-Point wieder deaktiviert werden (Funktioniert zur Zeit noch nicht stabil).  
  
  
Speichern als CSV:  
Die Daten können als CSV via USB ausgegeben werden. Dafür sollte sowohl in ext_def.h als auch in der WLAN-Konfiguration Debug auf 0 gesetzt werden, damit ide ausgegebenen Daten nur noch die Sensordaten sind. Beim Neustart des ESP8266 erscheinen dann nur noch ein paar wenige Zeichen, die den Startzustand darstellen.  
  
  
Benötigte Software:  
Arduino IDE <https://www.arduino.cc/en/Main/Software>  
ESP8266 für Arduino <http://arduino.esp8266.com/stable/package_esp8266com_index.json>  
  
  
Verwendete Bibliotheken:  
  
DHT <https://github.com/adafruit/DHT-sensor-library>  
(DHT.cpp und DHT.h downloaden und in das Softwareverzeichnis kopieren)  
  
In ESP8266 für Arduino IDE enthalten:  
FS  
ESP8266WiFi  
ESP8266WebServer  
DNSServer  
Wire  
  
Installierbar über Arduino IDE (Menü Sketch -> Bibliothek einbinden -> Bibliotheken verwalten, in Klammern die getestete Version):  
ArduinoJson <https://github.com/bblanchon/ArduinoJson> (5.1.1)  
ESP8266 Oled driver for SSD1306 display <https://github.com/squix78/esp8266-oled-ssd1306> (2.0.0)  
ESP8266httpUpdate (1.1.0)  
PubSubClient <http://pubsubclient.knolleary.net/> (2.6.0)  
SoftwareSerial <https://github.com/plerup/espsoftwareserial> (1.0.0)  
WifiManager <https://github.com/tzapu/WiFiManager>  (unbedingt 0.10.0, da sonst Fehler wegen undefinierter isnan())
