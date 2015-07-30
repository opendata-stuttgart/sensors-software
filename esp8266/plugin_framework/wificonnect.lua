local config = require('config')

-- setup
wifi.setmode(wifi.STATION)
wifi.sta.autoconnect(1)
wifi.sta.config(config.WIFI_SSID, config.WIFI_KEY)

print('MAC: ',wifi.sta.getmac())

if not config.PIN_RED_LED or not config.PIN_GREEN_LED then
    gpio.mode(config.PIN_GREEN_LED, gpio.OUTPUT)
    gpio.mode(config.PIN_RED_LED, gpio.OUTPUT)
    c = gpio.HIGH
end

-- watch wifi connect state

tmr.alarm(0, 1000, 1, function()
    if wifi.sta.getip() == nil then
        if not config.PIN_RED_LED or not config.PIN_GREEN_LED then
            status = wifi.sta.status()
            if status == 1 then -- connecting
                gpio.write(config.PIN_GREEN_LED, c)
                if c == gpio.HIGH then
                    c = gpio.LOW
                else
                    c = gpio.HIGH
                end
                gpio.write(config.PIN_RED_LED, c)
            elseif status <= 4 then
                gpio.write(config.PIN_GREEN_LED, gpio.LOW)
                gpio.write(config.PIN_RED_LED, gpio.HIGH)
            elseif status == 5 then
                gpio.write(config.PIN_GREEN_LED, gpio.HIGH)
                gpio.write(config.PIN_RED_LED, gpio.LOW)
            end
        end
        -- print("Connecting to AP...")
    else
        print('IP: ',wifi.sta.getip())
        if not config.PIN_RED_LED or not config.PIN_GREEN_LED then
            gpio.write(config.PIN_RED_LED, gpio.LOW)
            gpio.write(config.PIN_GREEN_LED, gpio.LOW)
        end
        tmr.stop(0)
        local plugin_loader = require('pluginloader')
        plugin_loader.start_plugins()
    end
end)
