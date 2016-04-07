/*
  This a simple example of the aREST Library for the ESP8266 WiFi chip.
  This example illustrate the cloud part of aREST that makes the board accessible from anywhere
  See the README file for more details.

  Written in 2015 by Marco Schwartz under a GPL license.
*/

// Import required libraries
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <aREST.h>

// Clients
WiFiClient espClient;
PubSubClient client(espClient);

// Create aREST instance
aREST rest = aREST(client);//,"mqtt.opendataset.click");

// Unique ID to identify the device for cloud.arest.io
char device_id[16]="aRESTtest";

// WiFi parameters
const char* ssid = "Freifunk";
const char* password = "";

// Variables to be exposed to the API
int temperature;
int humidity;

// Functions
void callback(char* topic, byte* payload, unsigned int length);

void setup(void)
{
   ltoa(ESP.getChipId(),device_id,10);
//   device_id="aRESTtest";
  // Start Serial
  Serial.begin(115200);
  Serial.println(ESP.getChipId());

  // Set callback
  client.setCallback(callback);

  // Init variables and expose them to REST API
  temperature = 24;
  humidity = 40;
  rest.variable("temperature",&temperature);
  rest.variable("humidity",&humidity);

  // Give name and ID to device
  rest.set_id(device_id);
  rest.set_name("esp8266");

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  WiFi.printDiag(Serial);
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.RSSI());
  // Set output topic
  char* out_topic = rest.get_topic();

}

void loop() {

  // Connect to the cloud
  rest.handle(client);

}

// Handles message arrived on subscribed topic(s)
void callback(char* topic, byte* payload, unsigned int length) {

  rest.handle_callback(client, topic, payload, length);

}