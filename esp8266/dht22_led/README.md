# dht+LED

## config.lua

mapping of gpios 
* does not match 

https://github.com/nodemcu/nodemcu-firmware

from Build 20141219 on:
    
    0 [*]   GPIO16  
    1       GPIO5   
    2       GPIO4   
    3       GPIO0   
    4       GPIO2   
    5       GPIO14 (SPI CLK)                
    6       GPIO12 (SPI MISO)               
    7       GPIO13 (SPI MOSI)               
    8       GPIO15 (SPI CS)
    9       GPIO3 (UART RX)
    10      GPIO1 (UART TX)
    11      GPIO9
    12      GPIO10

# temperature sensor ds18b20

With ds18b20.lua (from nodemcu lib):

Weird result:
    > print(t.read(addrs[1],t.K))
    277.025
    > print(t.read(addrs[1],t.C))
    3.8125


-- read temperature with DS18B20
-- node.compile("ds18b20.lua")   --  run this only once to compile and save to "ds18b20.lc"
t=require("ds18b20")
t.setup(4)
addrs=t.addrs()
-- Total DS18B20 numbers, assume it is 2
print(table.getn(addrs))
-- The first DS18B20
print(t.read(addrs[1],t.C))
print(t.read(addrs[1],t.F))
print(t.read(addrs[1],t.K))
-- The second DS18B20
print(t.read(addrs[2],t.C))
print(t.read(addrs[2],t.F))
print(t.read(addrs[2],t.K))
-- Just read
print(t.read())
-- Just read as centigrade
print(t.read(nil,t.C))
-- Don't forget to release it after use
t = nil
ds18b20 = nil
package.loaded["ds18b20"]=nil


# dust sensor 

http://www.sca-shinyei.com/pdf/PPD42NS.pdf

Model PPD42NS

This sensor is to create Digital (Lo Pulse) output to Particulate Matters(PM). Lo Pulse Occupancy time (LPO
time) is in proportion to PM concentration. The output from “P1” is for PM whose size is around 1 micro meter
or larger. “P1” Output characteristics is shown in the attached drawing Fig2.,when tested in standard
condition stipulated below.

Model | PPD42NS
Detectable particle size | approx. 1μm (minimum.)
Detectable range of concentration | 0~28,000 pcs/liter (0~8,000pcs/0.01 CF=283ml)
Supply Voltage | DC5V +/- 10% (CN1:Pin1=GND, Pin3=+5V) Ripple Voltage within 30mV
Operating Temperature Range | 0~45°C
Operating Humidity Range | 95%rh or less (without dew condensation)
Power consumption  | 90mA
Storage temperature | -30~60°C
Time for stabilization | 1 minute after power turned on
Dimensions | 59(W) × 45(H) × 22(D) [mm]
Weight | 24g(approx.)
Output Method | Negative Logic, Digital output, Hi : over 4.0V(Rev.2) Lo : under 0.7V (As Input impedance : 200kΩ) OP-Amp output, Pull-up resistor : 10kΩ



PINs

    CN : S5B-EH(JST)
    1 : COMMON(GND)      green
    2 : OUTPUT(P2)       white
    3 : INPUT(5VDC 90mA) yellow
    4 : OUTPUT(P1)       black
    5 : INPUT(T1)        white
        FOR THRESHOLD FOR [P2]
    
    
    