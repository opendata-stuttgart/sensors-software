Arduino sketch for multiple sensors

Configure your sensors in sensorconfig.h (copy sensorconfig.h.template if not yet done)

	cp sensorconfig.h.template sensorconfig.h

* #include <SENSOR>_ACTIVE statements to compile sensor type
* PINS (=GPIO of esp8266)
* WiFi credentials
* server name, api to push to

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

