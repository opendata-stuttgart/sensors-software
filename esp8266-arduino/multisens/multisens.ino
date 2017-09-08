 /*******************************************************/
/* OK LAB Particulate Matter Sensor                    */
/*      - nodemcu-LoLin board                          */
/*      - Shinyei PPD42NS                              */
/*      http://www.sca-shinyei.com/pdf/PPD42NS.pdf     */
/*                                                     */       
/*******************************************************/

/**********************************************/
/* configure your sensors,                    */
/* PINs and WIFI in sensorconfig.h            */
/**********************************************/
#include "sensorconfig.h"
unsigned int  debug = verbosity;
String software_version = String(SOFTWARE_VERSION_INITIALS)+String("_")+String(SOFTWARE_VERSION_NUMBER);

#ifdef WIRELESS_ACTIVE
#include <ESP8266WiFi.h>
#endif
int value = 0;
String software_version_s=String(SOFTWARE_VERSION_INITIALS)+"_"+String(SOFTWARE_VERSION_NUMBER);
#include "apifunctions.h"
#include "serialfunctions.h"
#include "ledfunctions.h"


/* GPS  */
#ifdef GPS_ACTIVE
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include "gpsfunctions.h"
#endif //GPS_ACTIVE


/**********************************************/
/* The Setup
/**********************************************/

void setup() {



  Serial.begin(9600); //Output to Serial at 9600 baud
  delay(10);
  Serial.print("Software version: ");
  Serial.print(software_version_s);

  Serial.println("ESP startup, chipid:");
  Serial.println(ESP.getChipId());
  Serial.print("Heap free:");
  Serial.println(ESP.getFreeHeap());
  Serial.print("sampletime [s]:");
  Serial.println(Float2String(sampletime_ms/1000.0));
  int i;
  Serial.println("GPIOx Dx PIN matching");

  for (i = 0; i < 13; i = i + 1) {
        Serial.print(i);
        Serial.print("\t");
        Serial.println(D[i]);
    }






#ifdef GPS_ACTIVE
gps_setup();
#endif //GPS_ACTIVE

  starttime = millis(); // store the start time
}

/**********************************************/
/* And action
/**********************************************/
void loop() {
  String data;


   
    #ifdef GPS_ACTIVE
    gps_read();
    #endif //GPS_ACTIVE

    /
    // reset start time at the very end
    starttime = millis(); // store the start time
    }

}// loop()
