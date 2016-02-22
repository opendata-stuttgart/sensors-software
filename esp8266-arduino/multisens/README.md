Arduino sketch for multiple sensors

Configure your sensors in sensorconfig.h (copy sensorconfig.h.template if not yet done)

	cp sensorconfig.h.template sensorconfig.h

* #include <SENSOR>_ACTIVE statements to compile sensor type
* PINS (=GPIO of esp8266)
* WiFi credentials
* server name, api to push to

You will need to set the additional boards manager URL in file->settings (Datei->Voreinstellungen):
http://arduino.esp8266.com/stable/package_esp8266com_index.json

for the esp8266 board then select:

* select in Werkzeuge->Platine->BoardsManager (tools->boards->BoardsManager): esp8266
* select board "NodeMCU 0.9 (ESP-12 Module)"

Libraries:

* Sketch -> Include library -> Library manager 
* Add "DHT sensor library"
* "OneWire" should be there already
* MQTT PubSubClient https://github.com/knolleary/pubsubclient/

