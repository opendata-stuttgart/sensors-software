#ifndef DHTPUSH_H
#define DHTPUSH_H

#include <DHT.h> // must be included in .ino

// define defaults, if not already done
// change the following in sensorconfig.h
#ifndef DHTPIN
#define DHTPIN 4 // = GPIO PIN, not D
#endif
#ifndef DHTTYPE
#define DHTTYPE DHT22
#endif


DHT dht(DHTPIN, DHTTYPE);

/* functions for DHT sensors */

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

/**********************************************/
/* DHT22 Sensor
/**********************************************/
void sensorDHT(){
  String data;
  float h = dht.readHumidity(); //Read Humidity
  float t = dht.readTemperature(); //Read Temperature

  // Check if valid number if non NaN (not a number) will be send.
  if (isnan(t) || isnan(h)) {
    Serial.println("DHT22 could not be read");
  } else {
    float hic = dht.computeHeatIndex(t, h, false);
    Serial.print("Humidity    : ");
    Serial.print(h);
    Serial.print(" %\n");
    Serial.print("Temperature : ");
    Serial.print(t);
    Serial.println(" C");
    Serial.print("Heat index : ");
    Serial.print(hic);
    Serial.println(" C");
   
    if ((t>84.99) & (t<85.01)){
        Serial.println("Temperature looks like a reading after a power reset (85 °C), discarding...");
        return;
    }
    // json for push to api: h t
    data = "{\"software_version\": \"";
    data += SOFTWARE_VERSION_INITIALS;
    data += "_";
    data += SOFTWARE_VERSION_NUMBER;
    data += "\",";
    data += "\"sensordatavalues\":[{";
    data += "\"value_type\":\"temperature\",\"value\":\"";
    data += Float2String(t);
    data += "\"},{";
    data += "\"value_type\":\"humidity\",\"value\":\"";
    data += Float2String(h);
    data += "\"}]}";
    Serial.println("#### Sending to Dusty: ");
    sendData(data, DHTPIN);
  }
}

#endif
