#!/bin/bash

set -e

./luatool.py -f init.lua
./luatool.py -f pluginloader.lua
./luatool.py -f wificonnect.lua
./luatool.py -f config.lua
# ./luatool.py -f wsledtest.lua
# ./luatool.py -c -f drf_api.lua
# ./luatool.py -f dht_reader.lua
