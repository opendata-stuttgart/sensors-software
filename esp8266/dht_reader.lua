local config = require('config')

local drf_api = require('drf_api')
local DHT = require("dht_lib")

local function timerCB()
    DHT.read22(4) -- GPIO2
    t = DHT.getTemperature()
    h = DHT.getHumidity()
    if t == nil or h == nil then
        print("Error reading from DHT11/22")
    else
        t = t * 0.1
        h = h * 0.1
        drf_api.send_dht22_to_api(t, h)
    end
end

local function start()
    timerCB()
    tmr.alarm(1, 60000, 1, timerCB)
end


return {
    start = start
}
