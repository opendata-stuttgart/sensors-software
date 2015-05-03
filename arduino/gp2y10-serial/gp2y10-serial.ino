/*
 Standalone Sketch to use with a Arduino UNO and a
 Sharp Optical Dust Sensor GP2Y1010AU0F
*/
  
int measurePin = 0; // V0 (Pin 5) to Arduino A0
int ledPower = 2;   // PIN 3 (LED) to Arduino D2
  
int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;
  
float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;
  
void setup(){
  Serial.begin(9600);
  pinMode(ledPower,OUTPUT);
}
  
void loop(){
  digitalWrite(ledPower,LOW); // power on the LED
  delayMicroseconds(samplingTime);
  
  voMeasured = analogRead(measurePin); // read the dust value
  
  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH); // turn the LED off
  delayMicroseconds(sleepTime);
  
  // 0 - 5V mapped to 0 - 1023 integer values
  // recover voltage
  calcVoltage = voMeasured * (5.0 / 1024.0);
  
  // linear eqaution taken from http://www.howmuchsnow.com/arduino/airquality/
  // Chris Nafis (c) 2012
  dustDensity = 0.17 * calcVoltage - 0.1;
  
  Serial.print("GP2Y1010AU0F_vo_raw:");
  Serial.print(voMeasured);
  
  Serial.print(";GP2Y1010AU0F_voltage:");
  Serial.print(calcVoltage);
  
  Serial.print(";GP2Y1010AU0F_dust_density:");
  Serial.println(dustDensity); // unit: mg/m3
  
  delay(1000);
}
