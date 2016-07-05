# HC-SR04 ultrasonic distance sensor module

Pins 

* Vcc
* Trig
* Echo
* End

     git clone https://github.com/eadf/esp8266_ping 
     suggests a level-shifter 5V-3V3 (Ultrasonic works on 5V level).

## NewPing

Library http://playground.arduino.cc/Code/NewPing

failed with 

    Arduino/libraries/NewPing/NewPing.cpp: In constructor 'NewPing::NewPing(uint8_t, uint8_t, unsigned int)':
    Arduino/libraries/NewPing/NewPing.cpp:19:17: error: cannot convert 'volatile uint32_t* {aka volatile unsigned int*}' to 'volatile uint8_t* {aka volatile unsigned char*}' in assignment
    _triggerOutput = portOutputRegister(digitalPinToPort(trigger_pin)); // Get the output port register for the trigger pin.
                    ^
    Arduino/libraries/NewPing/NewPing.cpp:20:13: error: cannot convert 'volatile uint32_t* {aka volatile unsigned int*}' to 'volatile uint8_t* {aka volatile unsigned char*}' in assignment
    _echoInput = portInputRegister(digitalPinToPort(echo_pin));         // Get the input port register for the echo pin.


Compilation according to this bug report https://github.com/PaulStoffregen/NewPing/issues/2

by changing the following:


    diff --git a/NewPing.h b/NewPing.h
    index a648687..5538274 100644
    --- a/NewPing.h
    +++ b/NewPing.h
    @@ -214,8 +214,8 @@ class NewPing {
    #endif
                    uint8_t _triggerBit;
                    uint8_t _echoBit;
    -               volatile uint8_t *_triggerOutput;
    -               volatile uint8_t *_echoInput;
    +               volatile uint32_t *_triggerOutput;^M
    +               volatile uint32_t *_echoInput;^M
                    volatile uint8_t *_triggerMode;
                    unsigned int _maxEchoTime;
                    unsigned long _max_time;

