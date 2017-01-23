local config = require('config')

local function setRandomColor()
    ws2812.write(config.PIN_RGB_LED, string.char(math.random(255), math.random(255), math.random(255)))
end

local function start()
    tmr.alarm(2, 500, 1, setRandomColor)
end

return {start = start}
