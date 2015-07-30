local function build_post_request(host, uri, data)
    request = "POST "..uri.." HTTP/1.1\r\n"..
    "Host: "..host.."\r\n"..
    "Connection: close\r\n"..
    "Content-Type: application/json\r\n"..
    "User-Agent: esp8266\r\n"..
    "Sensor: esp8266-"..node.chipid().."\r\n"..
    "Content-Length: "..string.len(data).."\r\n"..
    "\r\n"..
    data

    return request
end

local function send_data_to_api(data)
   -- print("start api connect")
   api=net.createConnection(net.TCP, 0)
   -- print("connect")
   api:on("receive", function(sck, c) print(c) end )
   api:connect(80, "api.dusti.xyz")
   api:on("connection", function(sck)
	     local post_request = build_post_request("api.dusti.xyz", "/v1/push-sensor-data/", data)
	     sck:send(post_request)
	     -- print("sent")
   end)
end

local function send_ppd42ns_to_api(lowpulseoccupancyP1, lowpulseoccupancyP2, sampletime)
   local ratioP1 = lowpulseoccupancyP1 / (sampletime*10.0)
   local P1 = 1.1*ratioP1*ratioP1*ratioP1-3.8*ratioP1*ratioP1+520*ratioP1+0.62
   local ratioP2 = lowpulseoccupancyP2 / (sampletime*10.0)
   local P2 = 1.1*ratioP2*ratioP2*ratioP2-3.8*ratioP2*ratioP2+520*ratioP2+0.62
   local data = '{"sensordatavalues":[{"value_type":"durP1","value":"'..lowpulseoccupancyP1..'"},{"value_type":"ratioP1","value":"'..ratioP1..'"},{"value_type":"P1","value":"'..P1..'"}'
   data = data .. ',{"value_type":"durP2","value":"'..lowpulseoccupancyP2..'"},{"value_type":"ratioP2","value":"'..ratioP2..'"},{"value_type":"P2","value":"'..P2..'"}]}'
   send_data_to_api(data)
end

local function send_dht22_to_api(temperature, humidity)
   send_data_to_api('{"sensordatavalues":[{"value_type":"temperature","value":"'..temperature..'"},{"value_type":"humidity","value":"'..humidity..'"}]}')
end

return {
    send_dht22_to_api = send_dht22_to_api,
    send_ppd42ns_to_api = send_ppd42ns_to_api
}
