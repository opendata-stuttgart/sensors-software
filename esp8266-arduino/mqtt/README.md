# MQTT implementations

Other repos with MQTT implementations:

git clone https://github.com/Pfannex/AktSen
git clone https://github.com/tuanpmt/espduino
git clone https://github.com/adafruit/Adafruit_MQTT_Library/
git clone https://github.com/tuanpmt/esp_mqtt

http://pubsubclient.knolleary.net/
Arduino Client for MQTT
git clone https://github.com/knolleary/pubsubclient/

Adafruit API only? did not evaluate for other servers
* https://github.com/adafruit/Adafruit_MQTT_Library/
* https://www.youtube.com/watch?v=VjpONmC2tac very nice intro into Adafruit MQTT with an ESP

# aREST

aREST can be used to control ESP8266 boards from anywhere in the world, by communicating with the board via MQTT commands.

* https://arest.io/esp8266-cloud/


# InfluxDB 


The following instruction appears, if you get rid of the nagging overlay on https://influxdata.com/downloads/

## Install on Ubuntu & Debian

Telegraf

    wget http://get.influxdb.org/telegraf/telegraf_0.12.0-1_amd64.deb
    sudo dpkg -i telegraf_0.12.0-1_amd64.deb
    #MD5: 6fc5150433655fedd91bd8c124d30fab

InfluxDB

    #MD5: 465e6cd66eb6dd23592386ce7d19136f
    wget https://s3.amazonaws.com/influxdb/influxdb_0.12.1-1_amd64.deb
    sudo dpkg -i influxdb_0.12.1-1_amd64.deb


Chronograf

    #MD5: 3392f10416e43ae818d1fda2f83e3514
    wget https://s3.amazonaws.com/get.influxdb.org/chronograf/chronograf_0.12.0_amd64.deb
    sudo dpkg -i chronograf_0.12.0_amd64.deb

Kapacitor


    #MD5: a74a7a20a67fd7f061c3179061250b17
    wget https://s3.amazonaws.com/kapacitor/kapacitor_0.12.0-1_amd64.deb
    sudo dpkg -i kapacitor_0.12.0-1_amd64.deb


## Standalone Binaries (64-bit)

Telegraf

    wget http://get.influxdb.org/telegraf/telegraf-0.12.0-1_linux_amd64.tar.gz
    tar xvfz telegraf-0.12.0-1_linux_amd64.tar.gz
    #MD5: e44b7c959d168ef03f4e8f2854384a77

InfluxDB

    #MD5: 203e98cdd3dd050c78b06c083d2d5d3e
    wget https://s3.amazonaws.com/influxdb/influxdb-0.12.1-1_linux_amd64.tar.gz
    tar xvfz influxdb-0.12.1-1_linux_amd64.tar.gz



