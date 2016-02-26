Version für Sensoren PPD42NS, SDS011 und DHT22.
Inklusive Konfiguration über WLAN.
Daten können gesendet werden an Dusti-API, Madavi-API oder können ausgegeben werden als CSV über USB.

ToDo's:
- TimeOut für WifiKonfig zum Laufen bekommen
- MQTT-Konfig ergänzen
- Debug-Ausgabe bis zum Schreiben der Konfiguration (dann steht endgültiger Zustand der Variable debug fest) zwischenspeichern und dann ausgeben.

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
SoftwareSerial <https://github.com/plerup/espsoftwareserial>  
WifiManager <https://github.com/tzapu/WiFiManager>  
  
In ESP8266 für Arduino IDE enthalten:  
FS  
ESP8266WiFi  
ESP8266WebServer  
DNSServer  
  
In Arduino IDE enthalten:
ArduinoJson  
