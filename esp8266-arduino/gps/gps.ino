/* config, move later to sensorconfig.h */

#define PUSHTO_SERIAL
// TODO implement
// #define PUSHTO_MQTT


#define GPS_ACTIVE
#ifdef GPS_ACTIVE
/* config, move later to sensorconfig.h */
// wiring: GPS6MV2-RX->GPSRXPin
static const int GPSRXPin = 5, GPSTXPin = 0;
static const uint32_t GPSBaud = 9600;
unsigned long gpsmaxtime_ms=2100;

#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include "gpsfunctions.h"
#endif //GPS_ACTIVE

void setup(){
#ifdef PUSHTO_SERIAL
    Serial.begin(9600);
    Serial.println("start");
    Serial.print("chipid\t");
    Serial.println(ESP.getChipId());
#endif //PUSHTO_SERIAL
#ifdef GPS_ACTIVE
    gps_setup();
#endif //GPS_ACTIVE
}

void loop(){
bool success=gps_read();
if (!success){
#ifdef PUSHTO_SERIAL
    Serial.print(millis());
    Serial.println("\tGPS failed");
#endif //PUSHTO_SERIAL
}
delay(30000);
}