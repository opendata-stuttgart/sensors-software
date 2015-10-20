SSID   = ""
KEY    = ""
BROKER = "mqtt.opensensors.io"          -- Ip/hostname of MQTT broker
BRPORT = 1883                           -- MQTT broker port
BRUSER = ""                       -- If MQTT authenitcation is used then define the user
BRPWD  = ""                     -- The above user password
CLIENTID = ""                       -- The MQTT ID. Change to something you like
TOPIC = "/orgs/exampletopix"

dofile('main.lua')