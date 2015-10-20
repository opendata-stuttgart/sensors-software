print('init.lua ver 1.2')
print('chip: ',node.chipid())
print('heap: ',node.heap())

local config = require('config')

function go()
--     dofile('wificonnect.lua')
--       dofile('led22_led.lua')
-- https://github.com/nodemcu/nodemcu-firmware/blob/master/lua_examples/onewire-ds18b20.lua
       dofile('onewire-ds18b20.lua')
end

print('Waiting 10 seconds before continuing...')
tmr.alarm(0, 10000, 0, go)
