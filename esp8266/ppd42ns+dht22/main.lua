-- esp8266-12
pin_P1=6  -- gpio12   black
pin_P2=5  -- gpio14   white

sampletime=30000 -- 30 seconds
filter_time=10000 -- in us

durationP1=0
trigOnP1=0
lastTriggerP1=0
lowpulseoccupancyP1=0

durationP2=0
trigOnP2=0
lastTriggerP2=0
lowpulseoccupancyP2=0

temperature=-999
humidity=-999
tempdec=99
humidec=99
-- set to nil (false) to disable DHT
PIN_DHT22=3

PIN_GREEN_LED = 2 -- GPIO4
PIN_RED_LED = 1
gpio.mode(PIN_GREEN_LED, gpio.OUTPUT)
gpio.write(PIN_GREEN_LED, gpio.HIGH)
c = gpio.HIGH


gpio.mode(pin_P1, gpio.INT)
function pin4change(level)
   if (tmr.now() - lastTriggerP1) > filter_time then
      if level == gpio.LOW then
	 trigOnP1 = tmr.now()
      else
	 durationP1 = tmr.now() - trigOnP1
	 lowpulseoccupancyP1 = lowpulseoccupancyP1 + durationP1
      end
      lastTriggerP1 = tmr.now()
   end
   gpio.trig(pin_P1, "both")
end
gpio.trig(pin_P1, "both", pin4change)


gpio.mode(pin_P2, gpio.INT)
function pin2change(level)
   if (tmr.now() - lastTriggerP2) > filter_time then	
      if level == gpio.LOW then
	 trigOnP2 = tmr.now()
      else
	 durationP2 = tmr.now() - trigOnP1
	 lowpulseoccupancyP2 = lowpulseoccupancyP2 + durationP2
      end
      lastTriggerP2 = tmr.now()
   end
   gpio.trig(pin_P2, "both")
end
gpio.trig(pin_P2, "both", pin2change)


function send_it()
    if wifi.sta.getip() == nil then
        status = wifi.sta.status()
        if status == 1 then -- connecting
	   gpio.write(PIN_GREEN_LED, c)
	   if c == gpio.HIGH then
	      c = gpio.LOW
	   else
	      c = gpio.HIGH
	   end
        elseif status <= 4 then
	   gpio.write(PIN_GREEN_LED, gpio.LOW)
        elseif status == 5 then
	   gpio.write(PIN_GREEN_LED, gpio.HIGH)
        end
    else
        print('IP: ',wifi.sta.getip())
	send_to_api(lowpulseoccupancyP1, lowpulseoccupancyP2, sampletime)
        if (PIN_DHT22 and (dht~=nil)) then
            status,temperature,humidity,tempdec,humidec=dht.readxx(PIN_DHT22)
            if( status == dht.OK ) then
                temperature=math.floor(temperature).."."..tempdec
                humidity=math.floor(humidity).."."..humidec
                print("DHT Temperature: "..temperature.." ".."Humidity: "..humidity)
                send_to_api_dht(temperature,humidity)
            else
                print ("DHT error, status="..status.." PIN_DHT22="..PIN_DHT22)
            end
        end
    end
    -- even if the data could not be sent.
    -- throw it away and try again after samplingtime
    lowpulseoccupancyP1 = 0
    lowpulseoccupancyP2 = 0
    tmr.alarm(0, sampletime, 0, send_it)
end

tmr.alarm(0, sampletime, 0, send_it)
dofile('http.lua')
