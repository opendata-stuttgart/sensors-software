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
    Serial.print("Humidity    : ");
    Serial.print(h);
    Serial.print(" %\n");
    Serial.print("Temperature : ");
    Serial.print(t);
    Serial.println(" C");
    
    // json for push to api: h t
    data = "{\"sensordatavalues\":[{";
    data += "\"value_type\":\"temperature\",\"value\":\"";
    data += Float2String(t);
    data += "\"},{";
    data += "\"value_type\":\"humidity\",\"value\":\"";
    data += Float2String(h);
    data += "\"}]}";
    Serial.println("#### Sending to Dusty: ");
    sendData(data);
  }
}

#endif
