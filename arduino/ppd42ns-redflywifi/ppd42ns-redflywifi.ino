/*
 Shinyei PPD42NS Particle Sensor
 publish via redfly-wifi-shield

 specification: http://www.sca-shinyei.com/pdf/PPD42NS.pdf

 pin 1 (grey)  -> Arduino GND
 pin 3 (black) -> Arduino 5V
 pin 2 (green) -> Arduino Pin 9
 pin 4 (white) -> Arduino Pin 8
 pin 5 (red)   -> unused!

*/

#include <RedFly.h>
#include <RedFlyClient.h>

byte server[]    = {  104, 31, 92, 177 };
#define HOSTNAME "api.dusti.xyz"  //host

unsigned int len=0; //receive buffer length
int sensor[100];
int count = 0;

RedFlyClient client(server, 80);

/* sensor variables */

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
  starttime = millis();
}


int send_data()
{
  uint8_t ret;
  String txtMsg;

  Serial.println("senddata start");
  //init the WiFi module on the shield
  ret = RedFly.init();
  if(ret)
  {
    Serial.println("INIT ERR"); //there are problems with the communication between the Arduino and the RedFly
  }
  else
  {
    //scan for wireless networks (must be run before join command)
    RedFly.scan();

    //join network
    ret = RedFly.join("Freifunk");
    if(ret)
    {
      Serial.println("JOIN ERR");
      // try again later
      return 1;
    }
    else
    {
      //set ip config
      ret = RedFly.begin(); //DHCP
      if(ret)
      {
        Serial.println("BEGIN ERR");
        RedFly.disconnect();
        // try again later
        return 1;
      }
      else
      {
	if(RedFly.getip(HOSTNAME, server) == 0) //get ip
	  {
          if(client.connect(server, 80))
          {

	  // FIXME: add sensor data for ppd42ns
	    txtMsg = "{ \"count\": ";
	    txtMsg += count;
	    for(int j=0;j<count;j++)
	      {
		txtMsg += ", \"value";
		txtMsg += j;
		txtMsg += "\": ";
		txtMsg += sensor[j];
	      }
	    txtMsg += "}";
	    txtMsg += "\0";

	    Serial.println(txtMsg);


            //make a HTTP request
	    client.print("POST /v1/ HTTP/1.1\n");

	    client.print("Host: api.dusti.xyz\n");
	    // add sensor-id
	    client.print("SENSOR: FIXME\n");

	    client.println("User-Agent: Arduino");
	    client.println("Accept: text/html");
	    client.print("Content-Length: ");
	    client.println(txtMsg.length(), DEC);

	    client.print("Content-Type: text/json\n");
	    client.println("Connection: close\n");

	    client.println(txtMsg);

	    // MAYBE not here?
            // reset count of data
	    count = 0;

          }
          else
          {
            Serial.println("CLIENT ERR");
            RedFly.disconnect();
            // try again later
            return 1;
          }
        }
        else
        {
          Serial.println("DNS ERR");
          RedFly.disconnect();
          // try again later
          return 1;
        }
      }
    }

  }
  Serial.println("senddata end");
  return 0;
}


void loop() {
  int ret;
  int c;
  char data[512];  //receive buffer

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
    Serial.print("lowpulseoccupancyP1:");
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

    // send data to API
    // FIXME: add parameters for data
    ret = send_data();
    // FIXME: do sth with ret?
  }

  //if there are incoming bytes available 
  //from the server then read them 
  if(client.available())
  {
    do
    {
      c = client.read();
      if((c != -1) && (len < (sizeof(data)-1)))
      {
        data[len++] = c;
      }
    }while(c != -1);
  }
  
  //if the server's disconnected, stop the client and print the received data
  if(len && !client.connected())
  {
    client.stop();
    RedFly.disconnect();
  
    data[len] = 0;
    Serial.print(data);
    
    len = 0;

    // IMPORTANT:
    // start again after disconnect, so no http interaction can harm data collection
    lowpulseoccupancyP1 = 0;
    lowpulseoccupancyP2 = 0;
    starttime = millis();
  }

}
