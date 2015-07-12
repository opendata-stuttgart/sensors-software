local config = require('config')

gpio.mode(config.PIN_REED_SWITCH, gpio.INT)

local function timerCB(level)
    print('Door state: '..level)
    if level == 1 then
        gpio.write(config.PIN_GREEN_LED, 1) 
        gpio.write(config.PIN_RED_LED, 0) 
    else
        gpio.write(config.PIN_RED_LED, 1) 
        gpio.write(config.PIN_GREEN_LED, 0) 
    end
end

gpio.trig(config.PIN_REED_SWITCH, "both", doorCb)


local function start()
    timerCB()
    tmr.alarm(0, 60000, 1, timerCB)
end


return {start = start}
