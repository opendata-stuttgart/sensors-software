-- hardware:
-- esp8266-01 with nodemcu 0.9.5
-- DHT22 sensor

-- powersource: USB power supply for 5V + LM317 for 3.3V

-- node.compile('dht_lib.lua')

function build_post_request(host, uri, data)

    request = "POST "..uri.." HTTP/1.1\r\n"..
    "Host: "..host.."\r\n"..
    "Connection: close\r\n"..
    "Content-Type: application/json\r\n"..
    "User-Agent: esp8266\r\n"..
    "Sensor: "..node.chipid().."\r\n"..
    "Content-Length: "..string.len(data).."\r\n"..
    "\r\n"..
    data

    print(request)

    return request
end

function getSensorData()
    PIN = 4 --  data pin, GPIO2

    local DHT = require("dht_lib")
    DHT.read22(PIN)

    t = DHT.getTemperature() * 0.1
    h = DHT.getHumidity() * 0.1

    if h == nil then
        print("Error reading from DHT11/22")
        return nil, nil
    else
        return t, h
        -- print("Temperature: "..t.." deg C")
        -- print("Humidity: "..h.."%")
        -- print("################################")
    end
    DHT = nil
    package.loaded["dht_lib"]=nil
end

function send_to_api()
    t, h = getSensorData()
    print("start api connect")
    api=net.createConnection(net.TCP, 0)
    print("connect")
    api:on("receive", function(sck, c) print(c) end )
    api:connect(80, "api.dusti.xyz")
    local data = '{"sensordatavalues":[{"value_type":"temperature","value":"'..t..'"},{"value_type":"humidity","value":"'..h..'"}]}'
    api:on("connection", function(sck) 
        local post_request = build_post_request("api.dusti.xyz", "/v1/push-sensor-data/", data)
        sck:send(post_request)
        print("sent")
    end)
end

tmr.alarm(0, 1000, 1, function()
    if wifi.sta.getip() == nil then
        print("Connecting to AP...")
    else
        print('IP: ',wifi.sta.getip())
        tmr.stop(0)
        send_to_api()
        tmr.alarm(0, 60000, 1, send_to_api)
    end
end)
