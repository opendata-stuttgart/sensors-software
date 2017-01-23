// GPS functions
#ifdef GPS_ACTIVE

// include in .ino
// #include <TinyGPS++.h>
// get from http://arduiniana.org/libraries/tinygpsplus/
// #include <SoftwareSerial.h>

// The TinyGPS++ object
TinyGPSPlus gps;
// The serial connection to the GPS device
SoftwareSerial serialGPS(pin_gps_rx,pin_gps_tx);


String last_gps_lat;
String last_gps_lng;
String last_gps_date;
String last_gps_time;
String last_gps_alt;
unsigned long starttime_GPS;



void gps_setup(){
  serialGPS.begin(gps_baudrate);
}

// This custom version of delay() ensures that the gps object
// is being "fed".
bool feedDelayGPS(unsigned long ms)
{
  unsigned long start = millis();
  do
  {
    while (serialGPS.available())
      gps.encode(serialGPS.read());
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

bool gps_pollread(){
    bool success=false;
    #ifdef PUSHTO_SERIAL
    serial_outln("gps_read", 5);
    #endif
    // serialGPS.flush(); //only outgoing data
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
//      if((serialGPS.available() > 0)){
//        if (gps.encode(serialGPS.read())){
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


/*****************************************************************
/* read GPS sensor values                                        *
/*****************************************************************/
String sensorGPS() {
    String s = "";
#if defined(ARDUINO_SAMD_ZERO) || defined(ESP8266)
    String gps_lat = "";
    String gps_lng = "";
    String gps_alt = "";
    String gps_date = "";
    String gps_time = "";

    debug_out("Reading GPS",DEBUG_MED_INFO,1);

    while (serialGPS.available() > 0) {
        if (gps.encode(serialGPS.read())) {
            if (gps.location.isValid()) {
                last_gps_lat = String(gps.location.lat(),6);
                last_gps_lng = String(gps.location.lng(),6);
            } else {
                debug_out("Lat/Lng INVALID",DEBUG_MAX_INFO,1);
            }
            if (gps.altitude.isValid()) {
                last_gps_alt = String(gps.altitude.meters(),2);
            } else {
                debug_out("Altitude INVALID",DEBUG_MAX_INFO,1);
            }
            if (gps.date.isValid()) {
                gps_date = "";
                if (gps.date.month() < 10) gps_date += "0";
                gps_date += String(gps.date.month());
                gps_date += "/";
                if (gps.date.day() < 10) gps_date += "0";
                gps_date += String(gps.date.day());
                gps_date += "/";
                gps_date += String(gps.date.year());
                last_gps_date = gps_date;
            } else {
                debug_out("Date INVALID",DEBUG_MAX_INFO,1);
            }
            if (gps.time.isValid()) {
                gps_time = "";
                if (gps.time.hour() < 10) gps_time += "0";
                gps_time += String(gps.time.hour());
                gps_time += ":";
                if (gps.time.minute() < 10) gps_time += "0";
                gps_time += String(gps.time.minute());
                gps_time += ":";
                if (gps.time.second() < 10) gps_time += "0";
                gps_time += String(gps.time.second());
                gps_time += ".";
                if (gps.time.centisecond() < 10) gps_time += "0";
                gps_time += String(gps.time.centisecond());
                last_gps_time = gps_time;
            } else {
                debug_out("Time: INVALID",DEBUG_MAX_INFO,1);
            }
        }
    }

    if ((act_milli-starttime) > sampletime_ms) {
        debug_out("Lat/Lng: "+last_gps_lat+","+last_gps_lng,DEBUG_MIN_INFO,1);
        debug_out("Altitude: "+last_gps_alt,DEBUG_MIN_INFO,1);
        debug_out("Date: "+last_gps_date,DEBUG_MIN_INFO,1);
        debug_out("Time "+last_gps_time,DEBUG_MIN_INFO,1);
        debug_out("------------------------------",DEBUG_MIN_INFO,1);
        s += "{\"value_type\":\"GPS_Lat\",\"value\":\"";
        s += last_gps_lat;
        s += "\"},";
        s += "{\"value_type\":\"GPS_Lng\",\"value\":\"";
        s += last_gps_lng;
        s += "\"},";
        s += "{\"value_type\":\"GPS_Alt\",\"value\":\"";
        s += last_gps_alt;
        s += "\"},";
        s += "{\"value_type\":\"GPS_Date\",\"value\":\"";
        s += last_gps_date;
        s += "\"},";
        s += "{\"value_type\":\"GPS_Time\",\"value\":\"";
        s += last_gps_time;
        s += "\"},";
        last_gps_lat = "";
        last_gps_lng = "";
        last_gps_alt = "";
        last_gps_date = "";
        last_gps_time = "";
    }
#endif
    return s;
}
