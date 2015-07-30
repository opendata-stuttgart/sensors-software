local config = require('config')

local function start_plugins()
    for i, plugin in ipairs(config.PLUGINS) do
        print("Starting plugin: "..plugin)
        local plugin_lib = require(plugin)
        if plugin_lib == nil then
            print("error loading plugin")
        else
            plugin_lib.start()
        end
    end
end

return {start_plugins = start_plugins}
