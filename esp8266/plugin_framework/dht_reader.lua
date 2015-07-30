local config = require('config')

local drf_api = require('drf_api')

local function timerCB()
    status,temp,humi,temp_decimial,humi_decimial = dht.readxx(config.PIN_DHT)
    if( status == dht.OK ) then
        drf_api.send_dht22_to_api(temp, humi)
    elseif( status == dht.ERROR_CHECKSUM ) then
        print( "DHT Checksum error." );
    elseif( status == dht.ERROR_TIMEOUT ) then
        print( "DHT Time out." );
    end
end

local function start()
    timerCB()
    tmr.alarm(1, 60000, 1, timerCB)
end


return {
    start = start
}
