print('init.lua ver 1.2')
print('chip: ',node.chipid())
print('heap: ',node.heap())

local config = require('config')

function go()
    gpio.mode(3, gpio.OUTPUT)
    ws2812.write(config.PIN_RGB_LED, string.char(0, 0, 0))
    if config.SKIP_WIFI_CONNECT then
        local plugin_loader = require('pluginloader')
        plugin_loader.start_plugins()
    else
        dofile('wificonnect.lua')
    end
    if config.PIN_REED_SWITCH then
        dofile('reedswitch.lua')
    end
end

print('Waiting 3 seconds before continuing... Press GPIO 0 to interrupt')
if config.PIN_RGB_LED then
    ws2812.write(config.PIN_RGB_LED, string.char(50, 0, 50))
end
tmr.alarm(0, 3000, 0, go)

gpio.mode(3, gpio.INT, gpio.PULLUP)
gpio.trig(3, "down", function(level)
    print("Stopping timer. Not starting wificonnect")
    if config.PIN_RGB_LED then
        ws2812.write(config.PIN_RGB_LED, string.char(50, 50, 0))
    end
    tmr.stop(0)
    gpio.mode(3, gpio.OUTPUT)
end)
