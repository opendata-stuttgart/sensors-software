// GPS functions
#ifdef GPS_ACTIVE

// include in .ino
// #include <TinyGPS++.h>
// get from http://arduiniana.org/libraries/tinygpsplus/
// #include <SoftwareSerial.h>

// The TinyGPS++ object
TinyGPSPlus gps;
// The serial connection to the GPS device
SoftwareSerial ss(pin_gps_rx,pin_gps_tx);

void gps_setup(){
  ss.begin(gps_baudrate);
}

// This custom version of delay() ensures that the gps object
// is being "fed".
bool feedDelayGPS(unsigned long ms)
{
  unsigned long start = millis();
  do
  {
    while (ss.available())
      gps.encode(ss.read());
      if (gps.location.isUpdated()){
          return true;
      }
  } while (millis() - start < ms);
  return false;
}

bool push_gps_location(){
    if (!gps.location.isValid()){
        return false;   
    }
#ifdef PUSHTO_SERIAL
serial_out("LatLonAlt\t");
serial_out(gps.location.lat(),6);
serial_out("\t");
serial_out(gps.location.lng(),6);
serial_out("\t");
serial_outln(gps.altitude.meters());
#endif
}

bool push_gps_datetime(){
    TinyGPSDate d=gps.date;
    TinyGPSTime t=gps.time;
    char sz[64];
    if (!d.isValid()){
        return false;
    }else{
        sprintf(sz, "DateTimeAge\t%02d-%02d-%02d", d.year(), d.month(), d.day());
        #ifdef PUSHTO_SERIAL
        serial_out(sz);
        #endif
    }
    if (!t.isValid()){
        serial_outln("");
        return false;
    }else{
        sprintf(sz, " %02d:%02d:%02d\t%02d", t.hour(), t.minute(), t.second(),gps.location.age());
        #ifdef PUSHTO_SERIAL
        serial_outln(sz);
        #endif
    }
    return true;
}

bool push_gps_info(){
      bool retval = ( gps.hdop.isValid() & gps.satellites.isValid() );
      #ifdef PUSHTO_SERIAL
      serial_out("HdopSat\t");
      if(gps.hdop.isValid()){
          serial_out(gps.hdop.value());
      }
      serial_out("\t");
      if(gps.satellites.isValid()){
          serial_out(gps.satellites.value());
      }
      serial_outln("");
      #endif
      return retval;
}

bool gps_read(){
    bool success=false;
    #ifdef PUSHTO_SERIAL
    serial_outln("gps_read", 5);
    #endif
    // ss.flush(); //only outgoing data
    if(!feedDelayGPS(gpsmaxtime_ms)){
        // no news from GPS
        #ifdef PUSHTO_SERIAL
        serial_out("no news from GPS");
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

//     serial_out("debug: starttime=");
//     serial_outln (starttime);
//     if(!success){
//         #ifdef PUSHTO_SERIAL
//         serial_outln("error reading GPS");
//         #endif
//         return false;
//     }
//     return success;
}

#endif