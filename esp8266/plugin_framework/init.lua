print('init.lua ver 1.2')
print('chip: ',node.chipid())
print('heap: ',node.heap())

local config = require('config')

function go()
    dofile('wifi_connect.lua')
end

print('Waiting 10 seconds before continuing...')
tmr.alarm(0, 10000, 0, go)
