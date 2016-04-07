/*
  This a simple example of the aREST Library for the ESP8266 WiFi chip.
  See the README file for more details.

  Written in 2015 by Marco Schwartz under a GPL license.
*/

// Import required libraries
#include <ESP8266WiFi.h>
#include <aREST.h>

// Create aREST instance
aREST rest = aREST();

// WiFi parameters
const char* ssid = "Freifunk";
const char* password = "";

// The port to listen for incoming TCP connections
#define LISTEN_PORT           80
#define PIN_LED BUILTIN_LED

// Create an instance of the server
WiFiServer server(LISTEN_PORT);

// Variables to be exposed to the API
int temperature;
int humidity;
int myvar=0;

// Declare functions to be exposed to the API
int ledControl(String command);

void setup(void)
{
    
  pinMode(PIN_LED, OUTPUT);
  // Start Serial
  Serial.begin(115200);

  // Init variables and expose them to REST API
  temperature = 24;
  humidity = 40;
  rest.variable("temperature",&temperature);
  rest.variable("humidity",&humidity);
  rest.variable("myvar",&myvar);

  // Function to be exposed
  rest.function("led",ledControl);
  rest.function("myvar",myvarControl);

  String idstr=String(ESP.getChipId());
  // Give name and ID to device
  rest.set_id(idstr.c_str());
  Serial.print("DeviceID: ");
  Serial.println(idstr);
  idstr=String("esp8266-")+idstr;
  Serial.print("Name: ");
  Serial.println(idstr);
  rest.set_name(idstr.c_str());
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {

  // Handle REST calls
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while(!client.available()){
    delay(1);
  }
  rest.handle(client);

}

// Custom function accessible by the API
int ledControl(String command) {

  // Get state from command
  int state = command.toInt();

  digitalWrite(PIN_LED,state);
  return 1;
}

// Custom function accessible by the API
int myvarControl(String command){

  // Get var value from command
  myvar = command.toInt();

  Serial.print("set myvar from");
  Serial.print(command);
  Serial.print(" to ");
  Serial.println(myvar);
  return 1;
}