#ifdef PIN_LED_STATUS
int ledsstate=LOW;
#endif

void setup_led(){
#ifdef PIN_LED_STATUS
pinMode(pin_led_status, OUTPUT);
digitalWrite(pin_led_status, ledsstate);
ledsstate=HIGH;
digitalWrite(pin_led_status, ledsstate);
#endif
}

void led_on(unsigned int delayafter=0){
#ifdef PIN_LED_STATUS
ledsstate=HIGH;
digitalWrite(pin_led_status, ledsstate);
delay(delayafter);
#endif
}

void led_off(unsigned int delayafter=0){
#ifdef PIN_LED_STATUS
ledsstate=LOW;
digitalWrite(pin_led_status, ledsstate);
delay(delayafter);
#endif
}
