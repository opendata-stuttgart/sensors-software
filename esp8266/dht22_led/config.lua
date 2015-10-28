
return {

 gpio = {[0]=3,
              [1]=10,
              [2]=4,
              [3]=9,
              [4]=1,
              [5]=2,
              [10]=12,
              [12]=6,
              [13]=7,
              [14]=5,
              [15]=8,
              [16]=0}
-- ESP-1: GPIO0->3 GPIO2->4

  WIFI_SSID = 'Freifunk',
  WIFI_KEY = '',

    PLUGINS = {
        'dht_reader',
--         'dht_test',
--         'reedswitch',
    },

--     PIN_REED_SWITCH = nil, -- gpio[4],
--     PIN_GREEN_LED = gpio[5], 
--     PIN_RED_LED = nil,
--     PIN_RGB_LED = nil --gpio[5],
--     PIN_DHT = gpio[14],

    -- on dev-board: Dn == nodemcu n
    PIN_DHT=2,
    PIN_REED_SWITCH = nil,  -- 5 -- GPIO 14
    PIN_GREEN_LED = 4, 
    PIN_RED_LED = nil
    
}
