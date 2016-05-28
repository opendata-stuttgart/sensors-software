/*
PIN 4: Button below antenna on top board, pulls low when pressed
PIN 12: green LED in RGB-LED
PIN 13: blue LED in RGB-LED
PIN 15: red LED in RGB-LED
*/

uint8_t redPin = 15;
uint8_t greenPin = 12;
uint8_t bluePin = 13;
uint8_t buttonPin = 4;
uint8_t photoresistorPin = A0;
uint8_t photoVal = 0;

// my first photosensor yields suspicous low values (0-10)
// range should be 200-700? calibrate here
const int minphotosens=0;
const int maxphotosens=20;

uint8_t redVal = 0;
uint8_t greenVal = 0;
uint8_t blueVal = 0;

uint8_t buttonstate = LOW;
uint8_t buttonstate_prev = LOW;
uint8_t curcolor=0;

void setcolor(uint8_t r=0,uint8_t g=0,uint8_t b=0){
    analogWrite(redPin, r);
    redVal=r;
    analogWrite(greenPin, g);
    greenVal=g;
    analogWrite(bluePin, b);
    blueVal=b;
}

void fadetocolor(uint8_t r=0,uint8_t g=0,uint8_t b=0,int delays=10,uint8_t steps=10){
    uint8_t s=0;
    uint8_t rstart=redVal;
    uint8_t gstart=greenVal;
    uint8_t bstart=blueVal;
    
    float dr=float(r-redVal)/steps;
    float dg=float(g-greenVal)/steps;
    float db=float(b-blueVal)/steps;
    
    for(s=1;s<=steps;s++){
        setcolor(r=rstart+uint8(dr*s),
                 g=gstart+uint8(dg*s),
                 b=bstart+uint8(db*s));
        delay(delays);
    }
}

// read out photoresistor, transform to a uint8_t range
uint8_t photoSens(){
    int sensorValue;
    sensorValue = analogRead(photoresistorPin);
    Serial.print("photoSens: ");
    Serial.println(sensorValue);
    sensorValue=constrain(sensorValue,minphotosens,maxphotosens);
    return map(sensorValue, minphotosens, maxphotosens, 0, 255);
}

void setup(){
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
    pinMode(buttonPin,INPUT);
    pinMode(photoresistorPin,INPUT);
    Serial.begin(9600);

    setcolor(0,0,0);
    fadetocolor(255,0,0,10,20);
    fadetocolor(0,255,0,10,20);
    fadetocolor(0,0,255,10,20);
    fadetocolor(0,0,0,10,20);
    fadetocolor(255,255,255,10,20);
    fadetocolor(0,0,0,10,20);
}

void loop(){
    buttonstate=digitalRead(buttonPin);
    
    // check if button was pressed
    if (buttonstate != buttonstate_prev){
        Serial.println("button state changed");
        if(buttonstate == HIGH){
            Serial.println("button pressed");
            photoVal=photoSens();
            Serial.print("photo val:");
            Serial.println(photoVal);
            switch (curcolor) {
                case 0:
                    // change red
                    Serial.println("set red");
                    fadetocolor(photoVal,greenVal,blueVal,20,20);
                    curcolor++;
                break;
                case 1:
                    // change green
                    Serial.println("set green");
                    fadetocolor(redVal,photoVal,blueVal,20,20);
                    curcolor++;
                break;
                default:                     
                    // change blue
                    Serial.println("set blue");
                    fadetocolor(redVal,greenVal,photoVal,20,20);
                    curcolor=0;
                break;
            }
        }
        buttonstate_prev=buttonstate;
    }
    //fadetocolor(random(255),random(255),random(255),random(20,50),random(20,50));
    //delay(250);
    delay(100);
}
