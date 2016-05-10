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
unsigned int pin_led = D[0];

//#define DEBUG_GPS_NMEA

#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include "gpsfunctions.h"
#endif //GPS_ACTIVE

void blink_led(unsigned int pin,unsigned int n=2, unsigned int interval=100){
unsigned int i=0;
    digitalWrite(pin, LOW);
    delay(interval);
    for (i=0; i<n;i++){
        digitalWrite(pin, HIGH);
        delay(interval);
        digitalWrite(pin, LOW);
        delay(interval);
    }
}

void setup(){
#ifdef PUSHTO_SERIAL
    Serial.begin(9600);
    Serial.println("start");
    Serial.print("chipid\t");
    Serial.println(ESP.getChipId());
#endif //PUSHTO_SERIAL

    pinMode(pin_led, OUTPUT);
    blink_led(pin_led,3,500);
    
#ifdef GPS_ACTIVE
    gps_setup();
#endif //GPS_ACTIVE

    pinMode(pin_led, OUTPUT);
    blink_led(pin_led,2,500);

}

void loop(){
blink_led(pin_led,2,200);
bool success=gps_read();
if (!success){
blink_led(pin_led,5,100);
#ifdef PUSHTO_SERIAL
    Serial.print(millis());
    Serial.println("\tGPS failed");
#endif //PUSHTO_SERIAL
}else{
    push_gps_location();
    blink_led(pin_led,1,1000);
    Serial.println("\tGPS read success");

}    
delay(10000);
}