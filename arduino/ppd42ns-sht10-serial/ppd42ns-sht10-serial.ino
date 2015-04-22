/*
 Shinyei PPD42NS Particle Sensor
 publish via serial and raspberry pi/python

 specification: http://www.sca-shinyei.com/pdf/PPD42NS.pdf

 pin 1 (grey)  -> Arduino GND
 pin 3 (black) -> Arduino 5V
 pin 2 (green) -> Arduino Pin 9
 pin 4 (white) -> Arduino Pin 8
 pin 5 (red)   -> unused!

*/

#include <SHT1x.h>

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
  pinMode(5,OUTPUT);
  digitalWrite(5, HIGH); 
  pinMode(8,INPUT);
  pinMode(9,INPUT);
  starttime = millis();
}

void loop() {
  float ratio = 0;
  float concentration = 0;

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
    Serial.print("durP1:");
    Serial.print(lowpulseoccupancyP1);
    Serial.print(";ratioP1:");
    Serial.print(ratio);
    Serial.print(";P1:");
    Serial.print(concentration);

    ratio = lowpulseoccupancyP2/(sampletime_ms*10.0);
    concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62;

    Serial.print(";durP2:");
    Serial.print(lowpulseoccupancyP2);
    Serial.print(";ratioP2:");
    Serial.print(ratio);
    Serial.print(";P2:");
    Serial.print(concentration);

    Serial.print("temperature:");
    Serial.print(sht10.readTemperatureC());
    Serial.print(";humidity:");
    Serial.println(sht10.readHumidity());

    lowpulseoccupancyP1 = 0;
    lowpulseoccupancyP2 = 0;
    starttime = millis();
  }
}
