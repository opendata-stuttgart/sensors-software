
status,temp,humi,temp_decimial,humi_decimial=dht.readxx(PIN_DHT22)
if( status == dht.OK ) then
    print("DHT Temperature: "..temp.." ".."Humidity: "..humi)
    print("DHT Temperature_decimial: "..temp_decimial.." ".."Humidity_decimial: "..humi_decimial)
    send_to_api_dht22(status,temp,humi,temp_decimial,humi_decimial)
else
    --elseif( status ~= dht.OK ) then
    print ("DHT error, status="..status.." PIN_DHT22="..PIN_DHT22)
end

   -- from pluginframework: send_data_to_api('{"sensordatavalues":[{"value_type":"temperature","value":"'..temperature..'"},{"value_type":"humidity","value":"'..humidity..'"}]}')

-- =dht.readxx(3)
