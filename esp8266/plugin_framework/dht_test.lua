local config = require('config')

local function readDHT()
    print(dht.read(config.PIN_DHT))
end

local function start()
    tmr.alarm(2, 1000, 1, readDHT)
end

return {start = start}
