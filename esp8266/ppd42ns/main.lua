-- esp8266-12
pin_P1=6  -- gpio12
pin_P2=5  -- gpio14

sampletime=30000 -- 30 seconds
durationP1=0
trigOnP1=0
lowpulseoccupancyP1=0

durationP2=0
trigOnP2=0
lowpulseoccupancyP2=0


PIN_GREEN_LED = 2
PIN_RED_LED = 1
gpio.mode(PIN_GREEN_LED, gpio.OUTPUT)
gpio.mode(PIN_RED_LED, gpio.OUTPUT)
gpio.write(PIN_GREEN_LED, gpio.HIGH)
c = gpio.HIGH


gpio.mode(pin_P1, gpio.INT, gpio.PULLUP)
function pin4change(level)

   if level == gpio.LOW then
      trigOnP1 = tmr.now()
      gpio.trig(pin_P1, "up")
--      gpio.write(PIN_GREEN_LED, gpio.HIGH)
   end
   
   if level == gpio.HIGH then
      durationP1 = tmr.now() - trigOnP1
      lowpulseoccupancyP1 = lowpulseoccupancyP1 + durationP1
      gpio.trig(pin_P1, "down")
--      gpio.write(PIN_GREEN_LED, gpio.LOW)
   end
end
gpio.trig(pin_P1, "down", pin4change)


gpio.mode(pin_P2, gpio.INT, gpio.PULLUP)
function pin2change(level)

   if level == gpio.LOW then
      trigOnP2 = tmr.now()
      gpio.trig(pin_P2, "up")
   end
   
   if level == gpio.HIGH then
      durationP2 = tmr.now() - trigOnP2
      lowpulseoccupancyP2 = lowpulseoccupancyP2 + durationP2
      gpio.trig(pin_P2, "down")
   end
end
gpio.trig(pin_P2, "down", pin2change)


tmr.alarm(0,sampletime,1,function()

    if wifi.sta.getip() == nil then
        status = wifi.sta.status()
        if status == 1 then -- connecting
	   gpio.write(PIN_GREEN_LED, c)
	   if c == gpio.HIGH then
	      c = gpio.LOW
	   else
	      c = gpio.HIGH
	   end
	   gpio.write(PIN_RED_LED, c)
        elseif status <= 4 then
	   gpio.write(PIN_GREEN_LED, gpio.LOW)
	   gpio.write(PIN_RED_LED, gpio.HIGH)
        elseif status == 5 then
	   gpio.write(PIN_GREEN_LED, gpio.HIGH)
	   gpio.write(PIN_RED_LED, gpio.LOW)
        end
    else
        print('IP: ',wifi.sta.getip())
        gpio.write(PIN_RED_LED, gpio.LOW)
        pwm.setup(PIN_GREEN_LED, 100, 10)
        pwm.start(PIN_GREEN_LED)
	send_to_api(lowpulseoccupancyP1, lowpulseoccupancyP2, sampletime)
    end
    -- even if the data could not be sent.
    -- throw it away and try again after samplingtime
    lowpulseoccupancyP1 = 0
    lowpulseoccupancyP2 = 0
end)

dofile('http.lua')
