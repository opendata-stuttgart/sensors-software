/* config, move later to sensorconfig.h */

#define PUSHTO_SERIAL
// TODO implement
// #define PUSHTO_MQTT

// GPIO PINSs <-> nodemcu PINs (Dx) mapping
//          0  1  2  3  4   5   6   7   8  9  10  11  12
int D[13]={16, 5, 4, 0, 2, 14, 12, 13, 15, 3,  1,  9, 10};

#define GPS_ACTIVE
#ifdef GPS_ACTIVE
/* config, move later to sensorconfig.h */
// wiring: GPS6MV2-RX->GPSRXPin
static const int GPSRXPin = D[7];
static const int GPSTXPin = D[8];
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