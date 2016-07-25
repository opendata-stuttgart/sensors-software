#ifndef GPSFUNCTIONS_H
#define GPSFUNCTIONS_H
// include in .ino
// #include <TinyGPS++.h>
// get from http://arduiniana.org/libraries/tinygpsplus/
// #include <SoftwareSerial.h>

// The TinyGPS++ object
TinyGPSPlus gps;
// The serial connection to the GPS device
SoftwareSerial ss(GPSRXPin, GPSTXPin);

void gps_setup(){
  ss.begin(GPSBaud);
}

// This custom version of delay() ensures that the gps object
// is being "fed".
bool feedDelayGPS(unsigned long ms=200)
{
  #ifdef DEBUG_GPS_NMEA
  char recchar;
  #endif
  unsigned long start = millis();
  do
  {
    while (ss.available()){
      #ifdef DEBUG_GPS_NMEA
      recchar=ss.read();
      Serial.print(recchar);
      gps.encode(recchar);
      #endif
      #ifndef DEBUG_GPS_NMEA
      gps.encode(ss.read());
      #endif
      yield();
      if (gps.location.isUpdated()){
          return true;
      }
    }
  } while (millis() - start < ms);
#ifdef DEBUG_GPS_NMEA
    Serial.println("charsProcessed() sentencesWithFix() failedChecksum() passedChecksum()");
    Serial.println(gps.charsProcessed());
    Serial.println(gps.sentencesWithFix());
    Serial.println(gps.failedChecksum());
    Serial.println(gps.passedChecksum());
#endif
  return false;
}

bool push_gps_location(){
    if (!gps.location.isValid()){
        return false;   
    }
#ifdef PUSHTO_SERIAL
Serial.print("LatLonAlt\t");
Serial.print(gps.location.lat(),6);
Serial.print("\t");
Serial.print(gps.location.lng(),6);
Serial.print("\t");
Serial.println(gps.altitude.meters());
#endif
        #ifdef PUSHTO_MQTT
        mqtt_publish_subtopic("GPS/lat",gps.location.lat());
        mqtt_publish_subtopic("GPS/lon",gps.location.lng());
        mqtt_publish_subtopic("GPS/height",gps.altitude.meters());
        #endif
}

bool push_gps_datetime(){
    TinyGPSDate d=gps.date;
    TinyGPSTime t=gps.time;
    char sz[64];
    if (!d.isValid()){
        return false;
    }else{
        sprintf(sz, "%02d-%02d-%02d", d.year(), d.month(), d.day());
        #ifdef PUSHTO_SERIAL
        Serial.print("DateTimeAge\t");
        Serial.print(sz);
        #endif
        #ifdef PUSHTO_MQTT
        mqtt_publish_subtopic("GPS/date",gps.hdop.value());
        #endif
    }
    if (!t.isValid()){
        Serial.println("");
        return false;
    }else{
        sprintf(sz, "%02d:%02d:%02d", t.hour(), t.minute(), t.second(),gps.location.age());
        #ifdef PUSHTO_SERIAL
        Serial.print(" ");
        Serial.println(sz);
        #endif
        #ifdef PUSHTO_MQTT
        mqtt_publish_subtopic("GPS/time",sz);
        #endif
        sprintf(sz, "%02d", gps.location.age());
        #ifdef PUSHTO_SERIAL
        Serial.print("\t");
        Serial.println(sz);
        #endif
        #ifdef PUSHTO_MQTT
        mqtt_publish_subtopic("GPS/locationage",sz);
        #endif
    }
    return true;
}
bool push_gps_info(){
      bool retval = (gps.hdop.isValid() & gps.satellites.isValid());
      #ifdef PUSHTO_SERIAL
      Serial.print("HdopSat\t");
      if(gps.hdop.isValid()){
          Serial.print(gps.hdop.value());
      }
      Serial.print("\t");
      if(gps.satellites.isValid()){
          Serial.print(gps.satellites.value());
      }
      Serial.println("");
      #endif
#ifdef PUSHTO_MQTT    
      if(gps.hdop.isValid()){
        mqtt_publish_subtopic("GPS/HDOP",gps.hdop.value());
      }
      if(gps.satellites.isValid()){
        mqtt_publish_subtopic("GPS/satellites",gps.satellites.value());
      }
#endif
      return retval;
}
bool gps_read(){
    bool success=false;
    // ss.flush(); //only outgoing data
    if(!feedDelayGPS(gpsmaxtime_ms)){
        // no news from GPS
        #ifdef PUSHTO_SERIAL
        Serial.println("no news from GPS");
        #endif
        return false;
    }
//     if(gps.location.isUpdated()){
//     unsigned long starttime=millis();
//     while(millis()-gpsmaxtime_ms<starttime){
//      if((ss.available() > 0)){
//        if (gps.encode(ss.read())){
//          if (gps.location.isUpdated()){
            success=(success|push_gps_location());
            success=(success|push_gps_datetime());
            success=(success|push_gps_info());
            return success;
//         }
//       }
//      }
//     }

//     Serial.print("debug: starttime=");
//     Serial.println (starttime);
//     if(!success){
//         #ifdef PUSHTO_SERIAL
//         Serial.println("error reading GPS");
//         #endif
//         return false;
//     }
//     return success;
}

#endif // GPSFUNCTIONS_H