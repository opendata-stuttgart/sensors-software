function build_post_request(host, uri, data)
    request = "POST "..uri.." HTTP/1.1\r\n"..
    "Host: "..host.."\r\n"..
    "Connection: close\r\n"..
    "Content-Type: application/json\r\n"..
    "User-Agent: esp8266\r\n"..
    "Sensor: esp8266-"..node.chipid().."\r\n"..
    "Content-Length: "..string.len(data).."\r\n"..
    "\r\n"..data
    return request
end

function send_to_dusty(ratioP1, P1, ratioP2, P2)
    local data = '{"sensordatavalues":[{"value_type":"durP1","value":"'..lowpulseoccupancyP1..'"},{"value_type":"ratioP1","value":"'..ratioP1..'"},{"value_type":"P1","value":"'..P1..'"}' ..
            ',{"value_type":"durP2","value":"'..lowpulseoccupancyP2..'"},{"value_type":"ratioP2","value":"'..ratioP2..'"},{"value_type":"P2","value":"'..P2..'"}]}'

    print("start api connect")
    api=net.createConnection(net.TCP, 0)
    print("connect")

    api:on("receive", function(sck, c) print(c) end )
    api:connect(80, "api.dusti.xyz")
    api:on("connection", function(sck)
        local post_request = build_post_request("api.dusti.xyz", "/v1/push-sensor-data/", data)
        sck:send(post_request)
        print("sent")
    end)
end

-- connect
function connect_broker()
    print "Connecting to MQTT broker. Please wait..."
    m:connect( BROKER , BRPORT, 0, function(conn)
        print("Connected to MQTT:" .. BROKER .. ":" .. BRPORT .." as " .. CLIENTID )
    end)
end

-- pub
pub_sem = 0
function publish_mqtt(msg)
    print("Publish to " .. TOPIC .. ":" .. msg)
    print('heap: ',node.heap())

    if pub_sem == 0 then
        pub_sem = 1
        m:publish(TOPIC,msg,0,0,function(conn)
            print("sent mqtt")
            pub_sem = 0
        end)
    else
        print("Oh noes! Semaphore was 1, stop nao!")
    end
end

-- pub to broker
function send_to_broker(ratioP1, P1, ratioP2, P2)
    publish_mqtt('{"durP1": "'..lowpulseoccupancyP1..'","ratioP1":"'..ratioP1..'","P1":"'..P1..'","durP2":"'..lowpulseoccupancyP2..'","ratioP2":"'..ratioP2..'","P2":"'..P2..'"}')
end

-- http post
function send_to_api(lowpulseoccupancyP1, lowpulseoccupancyP2, sampletime)
    local ratioP1 = lowpulseoccupancyP1 / (sampletime*10.0)
    local P1 = 1.1*ratioP1*ratioP1*ratioP1-3.8*ratioP1*ratioP1+520*ratioP1+0.62
    local ratioP2 = lowpulseoccupancyP2 / (sampletime*10.0)
    local P2 = 1.1*ratioP2*ratioP2*ratioP2-3.8*ratioP2*ratioP2+520*ratioP2+0.62
    -- http
    --send_to_dusty(ratioP1, P1, ratioP2, P2)
    -- mqtt
    send_to_broker(ratioP1, P1, ratioP2, P2)
end
