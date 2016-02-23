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

String dht_s_temperature;
String dht_s_humidity;
String dht_s_hic;

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
#ifdef PUSHTO_MQTT
    mqtt_publish_topic(logtopic.c_str(),"DHT22 error: could not be read");
#endif
    
  } else {
    float hic = dht.computeHeatIndex(t, h, false);
    dht_s_temperature=Float2String(t);
    dht_s_humidity=Float2String(h);
    dht_s_hic=Float2String(hic);
    Serial.print("Humidity    : ");
    Serial.print(dht_s_humidity);
    Serial.print(" %\n");
    Serial.print("Temperature : ");
    Serial.print(dht_s_temperature);
    Serial.println(" C");
    Serial.print("Heat index : ");
    Serial.print(dht_s_hic);
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
    data += dht_s_temperature;
    data += "\"},{";
    data += "\"value_type\":\"humidity\",\"value\":\"";
    data += dht_s_humidity;
    data += "\"}]}";
    sendData(data, DHTPIN);
    //
#ifdef PUSHTO_MQTT
    mqtt_publish_subtopic("json/DHT22",data);
    mqtt_publish_subtopic("DHT22/temperature",dht_s_temperature);
    mqtt_publish_subtopic("DHT22/humidity",dht_s_humidity);
#endif
 }
}

#endif
