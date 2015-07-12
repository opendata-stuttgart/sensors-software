# esp8266 with nodemcu

## Intro

Howto flash nodemcu on esp8266: http://blog.madflex.de/first-steps-with-the-esp8266/

## Getting this to work

Put your wifi credentials in `config.lua` and activate the plugins you want to use by uncommenting them.

Upload the files `init.lua`, `config.lua`, `wifi_connect.lua` and the plugins (and their dependencies) you activated to your ESP.


## Some Links

* pin layout: http://playground.boxtec.ch/doku.php/wireless/esp8266
* lua module reference: http://www.nodemcu.com/docs/

## Troubleshooting

If you get `Not enough memory` errors compile the lib you want to load (via console on the esp):

```
> node.compile('file.lua')
```
then restart and it should work.


# dht_reader.lua

Push DHT22 data with ESP8266 to api.dusti.xyz

## Dependencies

* [dht_lib.lua](https://github.com/nodemcu/nodemcu-firmware/tree/master/lua_modules/dht_lib/dht_lib.lua)
* `drf_api.lua`

## Instructions

Connect the DHT22 datapin to GPIO2
