Version für Sensoren PPD42NS, SDS011 und DHT22. Inklusive Konfiguratin über WLAN.

Grundsätzliche Konfiguration der Parameter über die Datei ext_dev.h .

WLAN Konfiguration:

Wenn das vorgegebene WLAN nach 10 Sekunden nicht erreichbar ist, wird ein Access-Point eingerichtet, der über "Feinstaubsensor-<Sensor-ID>" erreichbar ist. Nach dem Verbinden zu diesem Accesspoint werden alle Anfragen auf die Konfigurationsseite umgeleitet.

Konfigurierbar sind:
- WLAN-Name und Passwort
- welche Sensoren sollen ausgelesen werden
- an wen werden die Daten gesendet
