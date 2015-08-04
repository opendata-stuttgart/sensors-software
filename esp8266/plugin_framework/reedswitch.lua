local config = require('config')

local last_level = -1

local function tmrCb()
    local level = gpio.read(config.PIN_REED_SWITCH)
    if last_level ~= level then
        last_level = level
        if level == 0 then
            ws2812.write(config.PIN_RGB_LED, string.char(0, 255, 0))
        else
            ws2812.write(config.PIN_RGB_LED, string.char(255, 0, 0))
        end
        tmr.alarm(3, 1000, 0, function ()
            ws2812.write(config.PIN_RGB_LED, string.char(0, 0, 0))
        end)
    end
end

local function start()
    print('Configuring reedswitch...')
    gpio.mode(config.PIN_REED_SWITCH, gpio.INPUT, gpio.PULLUP)
    tmr.alarm(2, 1000, 1, tmrCb)
end

start()

-- return {start = start}
