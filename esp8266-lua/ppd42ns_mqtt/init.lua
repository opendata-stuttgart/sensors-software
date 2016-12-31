SSID   = ""
KEY    = ""
BROKER = "mqtt.opensensors.io"          -- Ip/hostname of MQTT broker
BRPORT = 1883                           -- MQTT broker port
BRUSER = ""                             -- If MQTT authenitcation is used then define the user
BRPWD  = ""                         -- The above user password
CLIENTID = ""                       -- The MQTT ID. Change to something you like
TOPIC = "/orgs/topic"
SEND_TO_DUSTY = true

-- do not change below this line
sampletime = 30000 -- 30 seconds
filter_time = 10000 -- in us

-- esp8266-12
pin_P1=6  -- gpio12   black
pin_P2=5  -- gpio14   white

dofile('main.lua')