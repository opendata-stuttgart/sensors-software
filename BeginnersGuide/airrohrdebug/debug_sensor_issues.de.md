# Sensorprobleme beheben

Dieses sind Dinge, die man prüfen sollte, falls ein Sensor mal nicht wie erwartet funktioniert.
Die [ID] ist durch die eigene Sensor-ID zu ersetzen (eine mehrstellige Zahl), [sensortyp] kann z.B. sein: `sds011`, `dht22`, `bme280`.

Online:

* wurden Daten online eingeliefert (madvi API)? 
    * https://www.madavi.de/sensor/graph.php?sensor=esp8266-[ID]-[sensortyp]
        * Nach der [ID] kann auch im Text auf der Seite https://www.madavi.de/sensor/graph.php gesucht werden
    * ist der Sensor via https://devices.sensor.community/ angemeldet und sendete Daten an die Haupt-API (Sichtbarkeit auf Karte)?
* schauen, ob der WLAN Signalpegel vielleicht etwas schwach in der Vergangenheit war:
  * hier ist das Signal-Log serverseitig: https://www.madavi.de/sensor/signal.php?sensor=esp8266-[ID]

Am USB-Kabel:

* Stromversorgung checken: USB Kabel
* Reboot (Stromversorgung unterbrechen, z.B. USB Stecker ziehen)
* Ist die WLAN Konfig OK (der Sensor verbindet auf das konfigurierte WLAN)?
    * macht der Sensor einen AP auf (in den ersten 2-7 Minuten nach einem Reboot)?
    * Nach airrohr-[ID] WLAN Netzwerk Ausschau halten. Geduld, es kann nach dem Boot 1-2 Minuten dauern.
* Auf dem eigenen Router nachsehen, ob der Sensor im Netzwerk angemeldet ist, dann die IP merken (alternativ flashtool https://github.com/opendata-stuttgart/airrohr-firmware-flasher/ und Discovery)
    * Falls ja: auf die IP mit einem Browser verbinden http://[IP]/ , dort sollte die Oberfläche erscheinen
    * Falls nein: der ESP hat Probleme, z.B. reboot loop o.ä.
* USB an einen Rechner anschließen und dort das Log ansehen 
    * Text auf serieller Schnittstelle mit seriellem Terminal-Programm verfolgen (Settings: baud 9600, 8N1)
        * Linux: screen, minicom, cutecom; Windows: Tera Term; MacOS: screen, minicom, ...?
        * evtl. sind passende usb2serial Treiber noch nötig, siehe https://github.com/opendata-stuttgart/meta/wiki/Firmware-einspielen
    * Dort sollte man erkennen können, was der Sensor gerade tut (Bootmeldungen, WLAN Verbindung oder AP, Messung - erst nach 3 Minuten)

An der Elektronik:

* Sensorelektronik aus dem Gehäuse nehmen und beobachten
* Stromversorgung noch einmal checken/tauschen
    * blinkt der ESP kurz nach Reboot?
    * SDS011: rote LED/Lüfter an nach Reboot?
    * die Kabel zu den Sensoren noch einmal checken/tauschen


