PIN = 2
gpio.mode(PIN, gpio.OUTPUT)
c = gpio.HIGH

tmr.alarm(0, 1000, 1, function()
    if wifi.sta.getip() == nil then
        gpio.write(PIN, c)
        if c == gpio.HIGH then
            c = gpio.LOW
        else
            c = gpio.HIGH
        end
        -- print("Connecting to AP...")
    else
        print('IP: ',wifi.sta.getip())
        tmr.stop(0)
        send_to_api()
        tmr.alarm(0, 60000, 1, send_to_api)
    end
end)
