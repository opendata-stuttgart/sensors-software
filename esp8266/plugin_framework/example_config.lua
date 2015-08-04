local gpio = {[0]=3,[1]=10,[2]=4,[3]=9,[4]=1,[5]=2,[10]=12,[12]=6,[13]=7,[14]=5,[15]=8,[16]=0}

return {
    SKIP_WIFI_CONNECT = false,
    WIFI_SSID = '<ssid>',
    WIFI_KEY = '<key>',

    PLUGINS = {
        -- 'dht_reader',
        -- 'wsledtest',
        'dht_test',
    },

    PIN_REED_SWITCH = gpio[4],
    PIN_GREEN_LED = nil, 
    PIN_RED_LED = nil,
    PIN_RGB_LED = gpio[5],
    PIN_DHT = gpio[14],
}
