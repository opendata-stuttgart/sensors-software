
pin = 4  -- gpio2

sampletime=15000; -- 15 seconds
durationP1=0 ;

trigOnP1=0;
lowpulseoccupancyP1=0;

gpio.mode(pin, gpio.INT, gpio.PULLUP)

function pin4change(level)

   if level == gpio.LOW then
--  and trigP1 == false
--      trigP1 = true;
      trigOnP1 = tmr.now();
      gpio.trig(pin, "up")
   end
   
   if level == gpio.HIGH then
-- and trigP1 == true
      durationP1 = tmr.now() - trigOnP1;
      lowpulseoccupancyP1 = lowpulseoccupancyP1 + durationP1;
--      trigP1 = false;
      gpio.trig(pin, "down")
   end
end
gpio.trig(pin, "down", pin4change)


tmr.alarm(0,sampletime,1,function()
	     ratio = lowpulseoccupancyP1 / (sampletime*10.0);
	     print(lowpulseoccupancyP1);
	     print(ratio);
	     lowpulseoccupancyP1 = 0;
end)
