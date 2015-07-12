# Push DHT22 data with ESP8266 to api.dusti.xyz

Connect the DHT22 datapin to GPIO2

Edit `init.lua` and set your wifi credentials.  
Then copy `init.lua`, `dht_lib.lua` and `main.lua` to your ESP.

Restart and see how it pushes your data to the server every minute


## Troubleshooting

If you get `Not enough memory` errors compile the dht lib (via console on the esp):

```
> node.compile('dht_lib.lua')
```
then restart and it should work.
