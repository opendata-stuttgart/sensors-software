/*
 dsm501a
  
 publish via serial and raspberry pi/python

 specification: http://i.publiclab.org/system/images/photos/000/003/726/original/tmp_DSM501A_Dust_Sensor630081629.pdf

dsm501a
 pin 1 () -> unused!
 pin 2 (PM10) -> Arduino Pin 8
 pin 3 () -> Arduino 5V
 pin 4 (PM25) -> Arduino Pin 9
 pin 5 () -> Arduino GND

bmp180
 +      -> 3.3V
 -      -> GND
 data   -> anaolog 4
 Clock  -> anaolog 5

*/

#include <Wire.h>
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;

//

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
  if (!bmp.begin()) {
	Serial.println("# Could not find a valid BMP085 sensor!");
  }
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
    Serial.print("durP10:");
    Serial.print(lowpulseoccupancyP1);
    Serial.print(";ratioP10:");
    Serial.print(ratio);
    Serial.print(";P10:");
    Serial.print(concentration);

    ratio = lowpulseoccupancyP2/(sampletime_ms*10.0);
    concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62;

    Serial.print(";durP25:");
    Serial.print(lowpulseoccupancyP2);
    Serial.print(";ratioP25:");
    Serial.print(ratio);
    Serial.print(";P25:");
    Serial.print(concentration);

    // bmp180
    Serial.print(";temperature:");
    Serial.print(bmp.readTemperature());
    Serial.print(";pressure:");
    Serial.print(bmp.readPressure());
    Serial.print(";altitude:");
    Serial.print(bmp.readAltitude());
    Serial.print(";pressure_sealevel:");
    Serial.println(bmp.readSealevelPressure());

    lowpulseoccupancyP1 = 0;
    lowpulseoccupancyP2 = 0;
    starttime = millis();
  }
}
