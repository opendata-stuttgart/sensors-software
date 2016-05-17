#ifndef PPDFUNCTIONS_H
#define PPDFUNCTIONS_H

#ifdef PPD_ACTIVE

// P1 for PM10 & P2 for PM25
boolean valP1 = HIGH;
boolean valP2 = HIGH;
boolean trigP1 = false;
boolean trigP2 = false;

unsigned long durationP1;
unsigned long durationP2;
unsigned long trigOnP1;
unsigned long trigOnP2;
unsigned long lowpulseoccupancyP1 = 0;
unsigned long lowpulseoccupancyP2 = 0;

float ratio_p1 = 0;
float concentration_p1 = 0;
float ratio_p2 = 0;
float concentration_p2 = 0;

// String versions (convert only once)
String ratio_p1s;
String ratio_p2s;
String concentration_p1s;
String concentration_p2s;
String lowpulseoccupancyP1s;
String lowpulseoccupancyP2s;


// #ifndef PPD42_P1_PIN
// #define  PPD42_P1_PIN 12
// #endif
// 
// #ifndef PPD42_P2_PIN
// #define  PPD42_P2_PIN 14
// #endif

void setup_ppd(unsigned int pin_p1, unsigned int pin_p2){
  pinMode(pin_p1,INPUT); // Listen at the designated PIN
  pinMode(pin_p2,INPUT); //Listen at the designated PIN
}

void ppd_measure(){
    if (!ppd_read){
        delay(10);
        return;
    }
  // measure
  // create string
  // push
    String data;
    String serialmsg;
  // Read pins connected to ppd42ns
#ifdef PPD_ACTIVE
  valP1 = digitalRead(pin_ppd_p1);
  valP2 = digitalRead(pin_ppd_p2);

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
#endif
}

void push_ppd(){
#ifdef PPD_ACTIVE
    ratio_p1 = lowpulseoccupancyP1/(sampletime_ms*10.0);                 // int percentage 0 to 100
    concentration_p1 = 1.1*pow(ratio_p1,3)-3.8*pow(ratio_p1,2)+520*ratio_p1+0.62; // spec sheet curve
    ratio_p1s=Float2String(ratio_p1);
    concentration_p1s=Float2String(concentration_p1);
    lowpulseoccupancyP1s=String(lowpulseoccupancyP1);
    // Begin printing
    serialmsg=String("LPO P10     : ")+String(lowpulseoccupancyP1)
    serialmsg+="\nRatio PM10  : ";
    serialmsg+=String(ratio_pls);
    serialmsg+=String(" %\nPM10 Count  : ")+concentration_p1s;

    // json for push to api / P1
    data = "{\"software_version\": \"";
    data += software_version_s;
    data += "\",";
    data += "\"sensordatavalues\":[{";
    data += "\"value_type\":\"durP1\",\"value\":\"";
    data += lowpulseoccupancyP1s;
    data += "\"},{";
    data += "\"value_type\":\"ratioP1\",\"value\":\"";
    data += ratio_p1s;
    data += "\"},{";
    data += "\"value_type\":\"P1\",\"value\":\"";
    data += concentration_p1s;
    data += "\"},{";

    ratio_p2 = lowpulseoccupancyP2/(sampletime_ms*10.0);
    concentration_p2 = 1.1*pow(ratio_p2,3)-3.8*pow(ratio_p2,2)+520*ratio_p2+0.62;
    ratio_p2s=Float2String(ratio_p2);
    concentration_p2s=Float2String(concentration_p2);
    lowpulseoccupancyP2s=String(lowpulseoccupancyP2);
    // Begin printing
    serialmsg+=String("LPO P25     : ")+String(lowpulseoccupancyP2);
    serialmsg+="\nRatio PM25  : "+ratio_p2s;
    serialmsg+=" %\nPM10 Count  : "+concentration_p2s;
    Serial.print("LPO PM25    : ")+lowpulseoccupancyP2s;
    Serial.print("Ratio PM25  : ")+ratio_p2s+" %\n";
    Serial.print("PM25 Count  : ")+concentration_p2s;

    // json for push to api / P2
    data += "\"value_type\":\"durP2\",\"value\":\"";
    data += lowpulseoccupancyP2s;
    data += "\"},{";
    data += "\"value_type\":\"ratioP2\",\"value\":\"";
    data += ratio_p2s;
    data += "\"},{";
    data += "\"value_type\":\"P2\",\"value\":\"";
    data += concentration_p2s;
    data += "\"}]}";

    //sending to dustix api
    Serial.println("#### Sending to dusti.xyz: ");
    // -1 -> '-' is default for ppd
    sendData(data,-1);
    
    #ifdef PUSHTO_MQTT//process incoming data/ping
       Serial.print("PubSubClient::loop");
       if (psclient.loop()){
           Serial.println("OK");
        }else{
           Serial.println("failed");
        }
        mqtt_publish_subtopic("json/PPD42NS",data);
        mqtt_publish_subtopic("PPD42NS/durP1",lowpulseoccupancyP1s);
        mqtt_publish_subtopic("PPD42NS/durP2",lowpulseoccupancyP2s);
        mqtt_publish_subtopic("PPD42NS/ratioP1",ratio_p1s);
        mqtt_publish_subtopic("PPD42NS/ratioP2",ratio_p2s);
        mqtt_publish_subtopic("PPD42NS/P1",concentration_p1s);
        mqtt_publish_subtopic("PPD42NS/P2",concentration_p2s);
    #endif
#endif

}

#endif //PPD_ACTIVE
#endif //PPDFUNCTIONS_H