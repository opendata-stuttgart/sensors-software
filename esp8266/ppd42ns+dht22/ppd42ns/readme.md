# ppd42ns

## some links for implementation

- http://esp8266.co.uk/tutorials/introduction-to-the-gpio-api/
- http://www.nodemcu.com/docs/gpio-module/#gpio-module-gpio-trig
- https://github.com/nodemcu/nodemcu-firmware/issues/179


## other implementations

### 1

https://github.com/marcel12bell/feinstaub-app/blob/master/init.lua

seems wrong, because no interrupt is used. one value each second via alarm timer.

### ?

# DHT22 

####
####
####
||||
1234

PIN     connections
1       3V3     4.6kOhm|        4.7muF[+]      
2               4.6kOhm|        GPIO
3
4       GND     4.7muF[-]
