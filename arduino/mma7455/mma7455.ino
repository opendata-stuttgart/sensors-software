// Example which uses the MMA_7455 library
// Moritz Kemper, IAD Physical Computing Lab
// moritz.kemper@zhdk.ch
// ZHdK, 03/04/2012
// Released under Creative Commons Licence

#include <Wire.h> //Include the Wire library
#include "MMA_7455.h" //Include the MMA_7455 library

MMA_7455 mySensor = MMA_7455(); //Make an instance of MMA_7455

long xVal, yVal, zVal; //Variables for the values from the sensor
long xVal_base, yVal_base, zVal_base;

long cnt = 0;

void setup()
{
  Serial.begin(9600);
  // Set the sensitivity you want to use
  // 2 = 2g, 4 = 4g, 8 = 8g
  mySensor.initSensitivity(2);
  // Calibrate the Offset, that values corespond in 
  // flat position to: xVal = -30, yVal = -20, zVal = +20
  // !!!Activate this after having the first values read out!!!
  mySensor.calibrateOffset(0, 0, 0);

  xVal = 0;
  yVal = 0;
  zVal = 0;

  xVal_base = mySensor.readAxis('x'); //Read out the 'x' Axis
  yVal_base = mySensor.readAxis('y'); //Read out the 'y' Axis
  zVal_base = mySensor.readAxis('z'); //Read out the 'z' Axis

  Serial.print("start");
}

void loop()
{
  cnt++;
  xVal += abs(mySensor.readAxis('x') - xVal_base); //Read out the 'x' Axis
  yVal += abs(mySensor.readAxis('y') - yVal_base); //Read out the 'y' Axis
  zVal += abs(mySensor.readAxis('z') - zVal_base); //Read out the 'z' Axis

  if (cnt > 99) {
    Serial.print("x: ");
    Serial.println(xVal, 10);
    Serial.print("y: ");
    Serial.println(yVal, 10);
    Serial.print("z: ");
    Serial.println(zVal, 10);
    cnt = 0;
    xVal = 0;
    yVal = 0;
    zVal = 0; 
  }
  delay(1);
}
