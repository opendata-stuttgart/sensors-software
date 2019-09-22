# ppd42ns

## some links for implementation

- http://esp8266.co.uk/tutorials/introduction-to-the-gpio-api/
- http://www.nodemcu.com/docs/gpio-module/#gpio-module-gpio-trig
- https://github.com/nodemcu/nodemcu-firmware/issues/179


## other implementations

1. https://github.com/marcel12bell/feinstaub-app/blob/master/init.lua
(Seems wrong, because no interrupt is used. One value each second via alarm timer.)

# DHT22 

Pins and orientation (Front view)

<pre>
####
####
####
||||
1234
</pre>

How to connect R1 = 4.7kOhm and C1 = 4.7uF/6.3V correctly:

|PIN | Function | Connections |
| ------------- |:-------------:| -----:|
| 1 | 3V3 | R1  , C1 (+) | 
| 2 | Data | R1 ,  GPIO (Null) |
| 3 | NC | - |
| 4 | GND | C1 (-) |
