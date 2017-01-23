-- first try

-- hardware:
-- esp8266-01 with nodemcu 0.9.5
-- ppd42ns sensor

-- powersource: arduino leonardo for 3.3V and 5V

local SSID = "stuttgart.freifunk.net"
local SSID_PASSWORD = ""
local TIMEOUT   = 10000000  -- 10 seconds

function connect(timeout)
   local time = tmr.now()
   wifi.sta.connect()

   -- Wait for IP address; check each 1000ms; timeout
   tmr.alarm(1, 1000, 1, 
	     function() 
		if wifi.sta.status() == 5 then 
		   tmr.stop(1)
		   print("Station: connected! IP: " .. wifi.sta.getip())
		   send_to_api()
		else
		   if tmr.now() - time > timeout then
		      tmr.stop(1)
		      print("Timeout!")
		      return false
		   end
		end 
	     end
   )
end

function build_post_request(host, uri, data_table)
 
     local data = ""
     
     for param,value in pairs(data_table) do
          data = data .. param.."="..value.."&"
     end
 
     request = "POST "..uri.." HTTP/1.1\r\n"..
     "Host: "..host.."\r\n"..
     "Connection: close\r\n"..
     "Content-Type: application/x-www-form-urlencoded\r\n"..
     "User-Agent: esp8266\r\n"..
-- FIXME: add authentication
     "Content-Length: "..string.len(data).."\r\n"..
     "\r\n"..
     data
 
     print(request)
     
     return request
end

function send_to_api()
   print("start api connect")
   api=net.createConnection(net.TCP, 0)
   print("connect")
   api:on("receive", function(sck, c) print(c) end )
   api:connect(80, "api.dusti.xyz")
   -- FIXME: add read data
   local data = {
      a = 1
   }
   api:on("connection", function(sck) 
	     local post_request = build_post_request("api.dusti.xyz", "/v1/push-sensor-data/", data)
	     sck:send(post_request)
	     print("sent")
   end)
end

-- configure ESP as a station
wifi.setmode(wifi.STATION)
wifi.sta.config(SSID,SSID_PASSWORD)
wifi.sta.autoconnect(1)

connect(TIMEOUT)
     
-- read from gpio2
-- save to file if no wifi found
-- push to api if wifi found
