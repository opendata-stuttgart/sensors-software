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


/* ATTENTION: 

   THIS CODE FAILS ON A LEONARDO + RedFly-Wifi-Shield with a DNS ERR.
   Or a JOIN ERR or a BEGIN ERR. But the best was DNS ERR.

 */


#include <RedFly.h>
#include <RedFlyClient.h>

// to store the secret ID used to authenticate the sensor
#include "sensor_id.h"

byte server[]    = {104, 31, 92, 177 };
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
unsigned long counter = 0;


String Float2String(float value)
{
  // Convert a float to String with two decimals.
  String s;
  s = String(int(value));
  s += '.';
  s += int((value - int(value)) * 100);

  return s;
}


void setup() {
  Serial.begin(9600);
  pinMode(8,INPUT);
  pinMode(9,INPUT);
  starttime = millis();
}


void sendData(const String& sensor_id,
	      const String& data) {

  char buffer[1000];
  String ln;

  Serial.println("start sending ...");

  client.print_P(PSTR("POST /v1/push-sensor-data/ HTTP/1.1\n"));
  
  client.print_P(PSTR("Host: api.dusti.xyz\n"));
  client.print_P(PSTR("Sensor: "));
  sensor_id.toCharArray(buffer, sensor_id.length()+1);
  client.println(buffer);
  
  client.println_P(PSTR("User-Agent: Arduino"));
  client.println_P(PSTR("Accept: text/html"));
  client.print_P(PSTR("Content-Length: "));
  ln = String(data.length(), DEC);
  ln.toCharArray(buffer, ln.length()+1);
  client.println(buffer);
  
  client.print_P(PSTR("Content-Type: text/json\n"));
  client.println_P(PSTR("Connection: close\n"));
  
  data.toCharArray(buffer, data.length()+1);
  client.println(buffer);
  
  counter += 1;
  Serial.println("sent...");
}


int send_data_via_wifi(const String& data)
{
  uint8_t ret;
  String sensor_id;
  uint8_t c_ip[4];

  Serial.println("wifi connect start");
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
	RedFly.getlocalip(c_ip);
	Serial.print(c_ip[0]);
	Serial.print("-");
	Serial.print(c_ip[1]);
	Serial.print("-");
	Serial.print(c_ip[2]);
	Serial.print("-");
	Serial.print(c_ip[3]);
	Serial.print("\n");

	if(RedFly.getip(HOSTNAME, server) == 0) //get ip
	  {
          if(client.connect(server, 80))
          {
	    sensor_id = String(SENSOR_ID) + String("PPD42NS");
	    sendData(sensor_id, data);
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
  String data;
  char receive[512];  //receive buffer

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

  if ((millis() - starttime) > sampletime_ms)
  {
    ratio = lowpulseoccupancyP1/(sampletime_ms*10.0);                 // int percentage 0 to 100
    concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // spec sheet curve

    data = "{";
    data += "\"durP1\":";
    data += Float2String(lowpulseoccupancyP1);
    data += "\";ratioP1\":";
    data += Float2String(ratio);
    data += "\";P1\":";
    data += Float2String(concentration);

    ratio = lowpulseoccupancyP2/(sampletime_ms*10.0);
    concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62;

    data += "\";durP2\":";
    data += Float2String(lowpulseoccupancyP2);
    data += "\";ratioP2\":";
    data += Float2String(ratio);
    data += "\";P2\":";
    data += Float2String(concentration);
    data += "}";

    // send data to API
    send_data_via_wifi(data);
  }

  //if there are incoming bytes available 
  //from the server then read them 
  if(client.available())
  {
    do
    {
      c = client.read();
      if((c != -1) && (len < (sizeof(receive)-1)))
      {
        receive[len++] = c;
      }
    }while(c != -1);
  }
  
  //if the server's disconnected, stop the client and print the received data
  if(len && !client.connected())
  {
    client.stop();
    RedFly.disconnect();
  
    receive[len] = 0;
    Serial.print(receive);
    
    len = 0;

    // IMPORTANT:
    // start again after disconnect, so no http interaction can harm data collection
    lowpulseoccupancyP1 = 0;
    lowpulseoccupancyP2 = 0;
    starttime = millis();
  }

}
