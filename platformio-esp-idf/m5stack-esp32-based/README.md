# SENSOR SENSEI

https://api.sensor.community/v1/
https://github.com/opendata-stuttgart/meta/wiki/EN-APIs

# PROJECT SETUP
The board in use in this project is M5stack series with ESP-IDF with ArduinoEsp32 framework as component(This to can esaly program the M5stack screen).

- ## Hardware Requirements

- ## Software Requirements
This tools need to be installed in your pc:
>> - Visual studio code (https://code.visualstudio.com/)
>> - Platformio IDE extension for Vs code (https://platformio.org/platformio-ide)
>> - Platformio CLI (https://docs.platformio.org/en/stable/core/installation/methods/installer-script.html)

- ## Project Creation Steps
>> - 1- Click the Platformio icon extension in your vscode
>> - 2- Click Project
>> - 3- Select the m5stack model board of your choice with the Arduino Framework
>> - 4- After the initialization add to the platformio.ini the arduino tho the framework parameter split by a comma.
>> - 5- Access the project tasks of platformio extension in your vscode and run build to refresh your project. If gettin some errors, please refer to [COMMON ERRORS] section

# COMMON ERRORS
In this section we're listing some common errors we encounter during the project. 

## Errors while Setting up the project:
- -Werror=unused-const-variable and -Werror=format-truncation
```
    Solved by adding this config to platformio.ini:
    build_unflags = -Werror=all
```

- Bluetooth with ESP-IDF (fatal error: esp_bt.h: No such file or directory)
```
    Solved by adding this configs to sdkconfig:
    CONFIG_BT_ENABLED=y
    CONFIG_BT_CLASSIC_ENABLED=y
    CONFIG_BT_SPP_ENABLED=y
```