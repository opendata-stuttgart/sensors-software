# SD card reader 

SPI interface, Arduino Micro SD Adapter, here: CATALEX v1.0

Default wiring, as in <https://www.youtube.com/watch?v=M-otJwRSpRQ>:

* CS     -> D8
* SC(L)K -> D5
* MOSI   -> D7
* MISO   -> D6
* VCC    -> 3V3
* GND    -> GND



Wiring according to nodemcu v3 schema, 'left' side (in order):
<https://github.com/opendata-stuttgart/meta/wiki/Pinouts-NodeMCU-v2,-v3>

* (unused) ADC0 = TOUT
* (unused) GND   
* (unused) VU = VUSB
* (unused) GPIO10 = SDD3
* (unused) GPIO09 = SDD2
* MOSI   -> SD1 = MOSI = SDD1
* CS     -> CMD = CS = SDCMD
* MISO   -> SD0 = MISO = SDD0
* SC(L)K -> CLK = SCLK = SDCLK
* GND    -> GND
* VCC    -> 3V3

With the ESP8266, you need the Library that comes in the ESP8266 lib tree, not the original Arduino one (which won't work). I deleted the Arduino one from the tree, when there was an error message about the wrong board type (avr) and "multiple libraries, using <the wrong one>"

source location here is in esp8266 package:
    
    ~/.arduino15/packages/esp8266/hardware/esp8266/2.2.0/libraries/SD/src/SD.h 


http://www.esp8266.com/wiki/doku.php?id=esp8266_and_sd_cards

* CS –> IO2 D4
    * D4 does not work as default
* DI(MOSI)–>IO13 D7
* VSS1–> GND 
* VDD–>3.3v 
* SCLK–>IO14 D5
* Vss2–>GND
* DO(MISO)–>IO12 D6



//   boolean begin(uint8_t csPin = SD_CHIP_SELECT_PIN, uint32_t speed = SPI_HALF_SPEED);


/*
extender board ESP-12 via Book Kolban:
VCC 3.3V.
GPIO 13 Also used for SPI MOSI.
GPIO 12 Also used for SPI MISO.
GPIO 14 Also used for SPI Clock.
GPIO 16
CH_PD
Chip enable. Should be high for normal operation.
• 0 – Disabled
• 1 – Enabled
ADC
REST External reset.
• 0 – Reset
• 1 – Normal
TXD UART 0 transmit.
RXD UART 0 Receive.
GPIO 4 Regular GPIO.
GPIO 5 Regular GPIO.
GPIO 0 Should be high on boot, low for flash update.
GPIO 2 Should be high on boot.
GND Ground.
*/

// GPIO PINSs <-> nodemcu PINs (Dx) mapping
//          0  1  2  3  4   5   6   7   8  9  10  11  12
//int D[13]={16, 5, 4, 0, 2, 14, 12, 13, 15, 3,  1,  9, 10};
//unsigned int pin_mosi=D[]; 
