tmr.delay(100000)

wifi.setmode(wifi.STATION)
wifi.sta.autoconnect(1)
print('set mode=STATION (mode='..wifi.getmode()..')')
print('MAC: ',wifi.sta.getmac())
print('chip: ',node.chipid())
print('heap: ',node.heap())

wifi.sta.config("Freifunk","")

-- dofile('main.lua')
