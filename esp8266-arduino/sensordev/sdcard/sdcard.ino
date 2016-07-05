/* SD Card */

// various necessary defs from sensorconfig
unsigned int verbosity=6;
unsigned long loopcounter=0;

#include "serialfunctions.h"
#define SDCARD_ACTIVE
#ifdef SDCARD_ACTIVE

#include <SPI.h>
#include <SD.h>
// to config file
uint8_t pin_sd_cs=SD_CHIP_SELECT_PIN;
// uint8_t pin_sd_cs=D8;
#include "sdcardfunctions.h"


#endif

unsigned long curmillis=0;
void setup()
{
   
   setup_serial();
   serial_outln("\n------\nsetup()\n-------");
   serial_outln(system_info(String("sdcard")));
   setup_sd(); // pin_sd_cs will be used
   sdcard_debug_info();
//    sdcard_echooutfile();
   
}

void loop()
{
    curmillis=millis();
#ifdef SDCARD_ACTIVE
    outfile.print("loop ");
    outfile.println(loopcounter,DEC);
    outfile.print("millis ");
    outfile.println(curmillis,DEC);
    outfile.flush();
#endif //SDCARD_ACTIVE
    serial_out("loop+millis");
    serial_outln(loopcounter);
    serial_outln(curmillis);

    loopcounter++;
    delay(5000);
}


