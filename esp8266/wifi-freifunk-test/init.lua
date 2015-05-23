--[[--------------------------
   test connecting to Freifunk without password.
--------------------------]]--

----------- CONFIG -----------
SSID      = "stuttgart.freifunk.net"   -- later: "Freifunk"
PASSWORD  = ""
TIMEOUT   = 10000000  -- 10 seconds
------------------------------

function connect(timeout)
   local time = tmr.now()
   wifi.sta.connect()

   -- Wait for IP address; check each 1000ms; timeout
   tmr.alarm(1, 1000, 1, 
	     function() 
		if wifi.sta.status() == 5 then 
		   tmr.stop(1)
		   print("Station: connected! IP: " .. wifi.sta.getip())
		   return true
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

--[[ Main loop ]]--
print("Setting up Wi-Fi connection..")
wifi.setmode(wifi.STATION)
wifi.sta.config(SSID, PASSWORD)
connect(TIMEOUT)
