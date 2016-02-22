/************************************************************/
/* DHT22 -> luftdaten.info api                              */
/************************************************************/

// increment on change
#define SOFTWARE_VERSION "MFA-2015-001-DHT22"

/**********************************************/
/* DHT declaration 
/**********************************************/
#include "DHT.h"
#define DHTPIN 4  // D2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

/**********************************************/
/* WiFi declarations
/**********************************************/
#include <ESP8266WiFi.h>

const char* ssid = "Freifunk";
const char* password = "";
// const char* host = "192.168.1.12";
const char* host = "api.dusti.xyz";
// const int httpPort = 8000;
const int httpPort = 80;
int value = 0;


unsigned long starttime;
unsigned long sampletime_ms = 30000;


/**********************************************/
/* WiFi connecting script
/**********************************************/
void connectWifi() {
  WiFi.begin(ssid, password); // Start WiFI
  
  Serial.print("Connecting ");
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
/**********************************************/
/* send data to rest api
/**********************************************/
void sendData(const String& data, int pin=-1) {
  //  delay(60000);
  ++value;

  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  // create an URI for the request
  String url = "/v1/push-sensor-data/";
  
  Serial.print("Requesting URL: ");
  Serial.println(url);
  Serial.println(data);

  String pinstr=String('-');
  if (pin > 0 ){pinstr=String(pin);}
  // send request to the server
  client.print(String("POST ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Pin: " + pinstr + "\r\n" +
               "Content-Type: application/json\r\n" +
               "Sensor: esp8266-");
  client.println(ESP.getChipId());
  client.print("Content-Length: ");
  client.println(data.length(), DEC);
  client.println("Connection: close\r\n");

  client.println(data);

  delay(1);
  
  // Read reply from server and print them
  while(client.available()){
    char c = client.read();
    Serial.print(c);
  }
  
  Serial.println();
  Serial.println("closing connection");
}

String Float2String(float value)
{
  // Convert a float to String with two decimals.
  char temp[15];
  String s;

  dtostrf(value,13, 2, temp);
  s = String(temp);
  s.trim();
  return s;
}

// DHT22 Sensor
void sensorDHT(){
  String data;
 float h = dht.readHumidity(); //Read Humidity
 float t = dht.readTemperature(); //Read Temperature

 // Check if valid number if non NaN (not a number) will be send.
 if (isnan(t) || isnan(h)) {
   Serial.println("DHT22 couldn’t be read");
 } else {
   Serial.print("Humidity    : ");
   Serial.print(h);
   Serial.print(" %\n");
   Serial.print("Temperature : ");
   Serial.print(t);
   Serial.println(" C");
   
   // json for push to api: h t
   data = "{\"software_version\": \"";
   data += SOFTWARE_VERSION;
   data += "\",";
   data += "\"sensordatavalues\":[{";
   data += "\"value_type\":\"temperature\",\"value\":\"";
   data += Float2String(t);
   data += "\"},{";
   data += "\"value_type\":\"humidity\",\"value\":\"";
   data += Float2String(h);
   data += "\"}]}";
   sendData(data, DHTPIN);
 
 }
}


/**********************************************/
/* The Setup
/**********************************************/
void setup() {
  Serial.begin(9600); //Output to Serial at 9600 baud
  pinMode(DHTPIN,INPUT);
  delay(10);
  starttime = millis(); // store the start time
  dht.begin(); // Start DHT
  delay(1000);
  connectWifi(); // Start ConnecWifi 
  Serial.print("\n"); 
  Serial.println("ChipId: ");
  Serial.println(ESP.getChipId());
}

/**********************************************/
/* And action
/**********************************************/
void loop() {
  // Checking if it is time to sample
  if ((millis()-starttime) > sampletime_ms)
  {
    starttime = millis(); // store the start time
    sensorDHT();  // getting temperature and humidity
    Serial.println("------------------------------");
  }
}


