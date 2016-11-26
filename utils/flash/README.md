# Flash script for Linux

[Here](https://github.com/opendata-stuttgart/sensors-software/tree/master/utils/flash) you find a tool for flashing an ESP8266 with the most recent firmware release of the fine dust measuring station.

The script asks some more info, which is required by the admins to let the sensors data into the database.
Usally, the device should be available on `/dev/ttyUSB0` (if you have no other usb2serial attached).
The script makes use of two tools, both named esptool(.py):

* one comes with the ESP8266 plugin for the the Android development IDE https://github.com/esp8266/arduino-esp8266fs-plugin
* the other is a python script from https://github.com/themadinventor/esptool

The script tries to find them in standard paths. You can set variables to point to them.

## transcript of a flash session with the script (2016-11-26)

    export gitlocation=/path/to/gitrepoparent # change path here, or just cd into the right location
    cd $gitlocation/sensors-software/utils/flash
    ./flashlatest.sh 

    usage: [esptool=/path/to/esptool] [esptoolpy=/path/to/esptool.py] [devserial=/dev/ttyUSB0] ./flashlatest.sh
    writes output to listofflashed.csv
    devserial=/dev/ttyUSB0 # define to change
  
    ask more infos? [Y/n]Y
    PM sensor revision (on back/flat side top left corner)? [default: ]V2-006
    PM sensor serial number (SN on sticker, besides fan, below barcode)? [default: ]5000-C537
    Adress?  [like: 70000 Stuttgart, Staubweg 00]70000 Stuttgart, Staubweg 00
    Email?  [like: unknown@example.com]
    latitude?  [like: 00.0000]48.000
    longitude?  [like: 00.0000]9.000
    DBID	esp8266-2331040	0x002391a0	5c:cf:7f:23:91:a0	V2-006:5000-C537	@	48.000	9.000	70000 Stuttgart, Staubweg 00	SID1	SNAME1	SID2	SNAME2
    patch Freifunk to XXXXXXXX? [y/N] N
    --2016-11-26 18:19:28--  https://www.madavi.de/sensor/update/data/latest.bin
    Auflösen des Hostnamen »www.madavi.de (www.madavi.de)«... 2a01:238:4202:e00:342a:970a:ad33:75fd, 85.214.240.94
    Verbindungsaufbau zu www.madavi.de (www.madavi.de)|2a01:238:4202:e00:342a:970a:ad33:75fd|:443... verbunden.
    HTTP-Anforderung gesendet, warte auf Antwort... 416 Requested Range Not Satisfiable

    Download der Datei schon vollständig; kein Download notwendig.
    flash now? [y/N] y
    esptool v0.4.9 - (c) 2014 Ch. Klippel <ck@atelier-klippel.de>
    	setting board to nodemcu
	[...]
    	writing flash
	[...]
    ................................................................................ [ 90% ]
    ........................................                                         [ 100% ]
    starting app without reboot
    	espcomm_send_command: sending command header
    	espcomm_send_command: sending command payload
    	espcomm_send_command: receiving 2 bytes of data
    closing bootloader
    to erase SPIFF (config data) use arduino IDE and https://github.com/esp8266/arduino-esp8266fs-plugin
    see https://github.com/esp8266/arduino-esp8266fs-plugin
    
    to erase SPIFF (config data) use arduino IDE and https://github.com/esp8266/arduino-esp8266fs-plugin
    see https://github.com/esp8266/arduino-esp8266fs-plugin
    or overwrite SPIFFS now? [y/N] N

Now the information about your sensor is added at the end of file listofflashed.csv

