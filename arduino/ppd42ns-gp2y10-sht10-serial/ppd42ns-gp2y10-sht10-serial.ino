/*
 Shinyei PPD42NS Particle Sensor
 publish via serial and raspberry pi/python

 specification: http://www.sca-shinyei.com/pdf/PPD42NS.pdf

 pin 1 (grey)  -> Arduino GND
 pin 3 (black) -> Arduino 5V
 pin 2 (green) -> Arduino Pin 9
 pin 4 (white) -> Arduino Pin 8
 pin 5 (red)   -> unused!

 Sharp GP2Y1010AU0F

 pin 5 (V0)    -> Arduino A0
 pin 3 (LED)   -> Arduino D2

 SHT10

 data          -> Arduino D10
 clk           -> Arduino D11

*/

#include <SHT1x.h>

// GP2Y10
int gp2y10_measurePin = 0; // V0 (Pin 5) to Arduino A0
int gp2y10_ledPower = 2;   // PIN 3 (LED) to Arduino D2

unsigned long gp2y10_samplingTime = 280;
unsigned long gp2y10_deltaTime = 40;
unsigned long gp2y10_sleepTime = 9680;

unsigned long gp2y10_current_time;
int gp2y10_trigger_step = 0;


// SHT10
#define shtdataPin  10
#define shtclockPin 11
SHT1x sht10(shtdataPin, shtclockPin);


// particles
boolean valP1 = HIGH;
boolean valP2 = HIGH;

unsigned long starttime;
unsigned long durationP1;
unsigned long durationP2;

boolean trigP1 = false;
boolean trigP2 = false;
unsigned long trigOnP1;
unsigned long trigOnP2;

unsigned long sampletime_ms = 15000;
unsigned long lowpulseoccupancyP1 = 0;
unsigned long lowpulseoccupancyP2 = 0;


void setup() {
  Serial.begin(9600);
  pinMode(8,INPUT);
  pinMode(9,INPUT);
  pinMode(gp2y10_ledPower,OUTPUT);
  gp2y10_trigger_step = 0;

  delay(100);
  starttime = millis();
}

void loop() {
  float ratio = 0;
  float concentration = 0;

  float gp2y10_voMeasured = 0;
  float gp2y10_calcVoltage = 0;
  float gp2y10_dustDensity = 0;

  // GP2Y10

  if (gp2y10_trigger_step == 0) {
    digitalWrite(gp2y10_ledPower,LOW); // power on the LED
    gp2y10_current_time = millis();
    gp2y10_trigger_step = 1;
  }

  if (gp2y10_trigger_step == 1 &&
      (millis()-gp2y10_current_time) > gp2y10_samplingTime) {
    gp2y10_voMeasured = analogRead(gp2y10_measurePin); // read the dust value
    gp2y10_current_time = millis();
    gp2y10_trigger_step = 2;
  }

  if (gp2y10_trigger_step == 2 &&
      (millis()-gp2y10_current_time) > gp2y10_deltaTime) {
    digitalWrite(gp2y10_ledPower,HIGH); // turn the LED off
    gp2y10_current_time = millis();
    gp2y10_trigger_step = 3;

    // 0 - 5V mapped to 0 - 1023 integer values
    // recover voltage
    gp2y10_calcVoltage = gp2y10_voMeasured * (5.0 / 1024.0);

    // linear eqaution taken from http://www.howmuchsnow.com/arduino/airquality/
    // Chris Nafis (c) 2012
    gp2y10_dustDensity = 0.17 * gp2y10_calcVoltage - 0.1;

    Serial.print("GP2Y10|vo_raw:");
    Serial.print(gp2y10_voMeasured);
    Serial.print(";voltage:");
    Serial.print(gp2y10_calcVoltage);
    Serial.print(";density:");
    Serial.println(gp2y10_dustDensity);
  }

  if (gp2y10_trigger_step == 3 &&
      (millis()-gp2y10_current_time) > gp2y10_sleepTime) {
    // reset
    gp2y10_current_time = millis();
    gp2y10_trigger_step = 0;
  }


  // PPD42NS

  valP1 = digitalRead(8);
  valP2 = digitalRead(9);

  if(valP1 == LOW && trigP1 == false){
    trigP1 = true;
    trigOnP1 = micros();
  }

  if (valP1 == HIGH && trigP1 == true){
    durationP1 = micros() - trigOnP1;
    lowpulseoccupancyP1 = lowpulseoccupancyP1 + durationP1;
    trigP1 = false;
  }

  if(valP2 == LOW && trigP2 == false){
    trigP2 = true;
    trigOnP2 = micros();
  }

  if (valP2 == HIGH && trigP2 == true){
    durationP2 = micros() - trigOnP2;
    lowpulseoccupancyP2 = lowpulseoccupancyP2 + durationP2;
    trigP2 = false;
  }

  if ((millis()-starttime) > sampletime_ms)
  {
    ratio = lowpulseoccupancyP1/(sampletime_ms*10.0);                 // int percentage 0 to 100
    concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // spec sheet curve
    Serial.print("PPD42NS|lowpulseoccupancyP1:");
    Serial.print(lowpulseoccupancyP1);
    Serial.print(";ratioP1:");
    Serial.print(ratio);
    Serial.print(";countP1:");
    Serial.print(concentration);

    ratio = lowpulseoccupancyP2/(sampletime_ms*10.0);
    concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62;

    Serial.print(";lowpulseoccupancyP2:");
    Serial.print(lowpulseoccupancyP2);
    Serial.print(";ratioP2:");
    Serial.print(ratio);
    Serial.print(";countP2:");
    Serial.println(concentration);

    Serial.print("SHT10|temperature:");
    Serial.print(sht10.readTemperatureC());
    Serial.print(";humidity:");
    Serial.println(sht10.readHumidity());

    lowpulseoccupancyP1 = 0;
    lowpulseoccupancyP2 = 0;
    starttime = millis();
  }
}
