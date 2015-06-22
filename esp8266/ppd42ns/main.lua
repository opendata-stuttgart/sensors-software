print("start main")
-- esp8266-01
pin_P1=4  -- gpio2

-- esp8266-12
pin_P2=6  -- gpio12

sampletime=15000 -- 15 seconds
durationP1=0
trigOnP1=0
lowpulseoccupancyP1=0

durationP2=0
trigOnP2=0
lowpulseoccupancyP2=0

gpio.mode(pin_P1, gpio.INT, gpio.PULLUP)
function pin4change(level)

   if level == gpio.LOW then
      trigOnP1 = tmr.now()
      gpio.trig(pin_P1, "up")
   end
   
   if level == gpio.HIGH then
      durationP1 = tmr.now() - trigOnP1
      lowpulseoccupancyP1 = lowpulseoccupancyP1 + durationP1
      gpio.trig(pin_P1, "down")
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
	     ratio = lowpulseoccupancyP1 / (sampletime*10.0)
	     print("P1: ")
	     print(lowpulseoccupancyP1)
	     print(ratio)

	     ratio = lowpulseoccupancyP2 / (sampletime*10.0)
	     print("P2: ")
	     print(lowpulseoccupancyP2)
	     print(ratio)

	     lowpulseoccupancyP1 = 0
	     lowpulseoccupancyP2 = 0
end)
