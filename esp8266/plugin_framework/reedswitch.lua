local config = require('config')

local function intCb(level)
    print('Reedswitch state: '..level)
    if level == 1 then
        gpio.write(config.PIN_GREEN_LED, 0) 
        gpio.write(config.PIN_RED_LED, 1) 
    else
        gpio.write(config.PIN_RED_LED, 0) 
        gpio.write(config.PIN_GREEN_LED, 1) 
    end
end

local function start()
    print('Initializing reedswitch...')
    -- gpio.mode(config.PIN_GREEN_LED, gpio.OUTPUT)
    -- gpio.mode(config.PIN_RED_LED, gpio.OUTPUT)
    gpio.mode(config.PIN_REED_SWITCH, gpio.INPUT)
    local state = gpio.read(config.PIN_REED_SWITCH)
    print('state: '..state)
    intCb(state)
    gpio.mode(config.PIN_REED_SWITCH, gpio.INT, gpio.PULLUP)
    gpio.trig(config.PIN_REED_SWITCH, "both", intCb)
end

return {start = start}
