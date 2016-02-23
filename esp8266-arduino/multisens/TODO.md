MQTT: reconnecting does not work, what to re-init, if network changes?
MQTT: howto timestamps (must be on server side or we need to use a "timestamp ticker" topic to subscribe to)

DONE implement MQTT
DONE merge software ID from esp8266-arduino/ppd42ns-wifi-dht/ppd42ns-wifi-dht.ino
DONE implement status LEDs
DONE Move sensor specific code to header files, add conditionals to include/exclude via #define #ifdef 
DONE dhtpush.h
DONE ds18x20push.h
DONE also for PPD? -> yes, via #define
DONE use sensorconfig.h to configure also the #define statements
DONE WIRELESS_ACTIVE option to log only via serial (HDM copter)

# TODOs

# optimised Onewire code: 
http://www.cupidcontrols.com/2014/10/moteino-arduino-and-1wire-optimize-your-read-for-speed/
see also Asynchronous vs. Synchronous read/write on
http://playground.arduino.cc/Learning/OneWire

* non-parasitic mode read? is it really
ds.write(0x44, 0);        // start conversion, with parasite power off at the end
From the header file OneWire.h:
    
    // Write a byte. If 'power' is one then the wire is held high at
    // the end for parasitically powered devices.
    
http://openenergymonitor.org/emon/buildingblocks/DS18B20-temperature-sensing
what lib is this?
//  int numberOfDevices = ds.getDeviceCount();
//  Serial.print("Found ");
//  Serial.print(numberOfDevices, DEC);
//  Serial.println(" devices.");

//  Serial.print("Parasite power is: "); 
//  if (ds.isParasitePowerMode()) Serial.println("ON");
//  else Serial.println("OFF");

