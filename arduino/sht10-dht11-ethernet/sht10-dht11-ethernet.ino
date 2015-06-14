#include <Ethernet.h>
#include <SHT1x.h>
#include "Wire.h"
#include "DHT.h"

// to store the secret ID used to authenticate the sensor
#include "sensor_id.h"

////////////////////////////////////////////////////////////////////////////////
// Specify data and clock connections and instantiate SHT1x object
#define dataPin  8
#define clockPin 9
SHT1x sht11(dataPin, clockPin);

////////////////////////////////////////////////////////////////////////////////
// DHT11
#define DHTTYPE DHT11   // DHT 11 
#define DHTPIN1 2     // pin of first DHT
#define DHTPIN2 3     // pin of second DHT

DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);


////////////////////////////////////////////////////////////////////////////////
// Photocell

int photocellPin = 0;     // the cell and 10K pulldown are connected to a0
int photocellReading;     // the analog reading from the sensor divider


////////////////////////////////////////////////////////////////////////////////
// Ethernet data
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x01 };
byte gateway[] = { 192, 168, 1, 1};
byte subnet[] = { 255, 255, 255, 0 };

char server[] = "api.dusti.xyz";

// initialize the library instance:
IPAddress ip(192,168,1, 42);
EthernetClient client;

const int postingInterval = 29000;   // delay between updates
long lastConnectionTime = 0;         // last time connected to the server
boolean lastConnected = false;       // state of the connection
long counter = 1;

void sendData(const String& sensor_id,
	      const String& data) {

  Serial.println("...");

  if (client.connect(server, 80)) {
    Serial.println("connecting...");

    client.print("POST /v1/push-sensor-data/ HTTP/1.1\n");

    client.print("Host: api.dusti.xyz\n");
    client.print("Sensor: ");
    client.println(sensor_id);

    client.println("User-Agent: Arduino");
    client.println("Accept: text/html");
    client.print("Content-Length: ");
    client.println(data.length(), DEC);

    client.print("Content-Type: text/json\n");
    client.println("Connection: close\n");

    client.println(data);

    lastConnectionTime = millis();
    counter += 1;
    Serial.println("sent...");
  }
  else {
    Serial.println("connection failed");
    delay(1000);
  }
}

////////////////////////////////////////////////////////////////////////////////

String Float2String(float value)
{
  // Convert a float to String with two decimals.
  String s;
  s = String(int(value));
  s += '.';
  s += int((value - int(value)) * 100);

  return s;
}

void setup()
{
  // start the Ethernet connection:
  Ethernet.begin(mac, ip);
  Wire.begin();

  Serial.begin(9600);

  // DHT init
  dht1.begin();
  dht2.begin();

  // delay for the ethernet to get up
  delay(1000);
}

void loop()
{
  float sht11_c, sht11_h;
  float dht1_c, dht1_h, dht2_c, dht2_h;
  String data;
  String sensor_id;

  if(millis() - lastConnectionTime > postingInterval) {
    // disconnect old client
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();

    delay(1000);

    // Read values from the SHT11
    sht11_c = sht11.readTemperatureC();
    sht11_h = sht11.readHumidity();

    // Read values from DHT11
    dht1_h = dht1.readHumidity();
    dht1_c = dht1.readTemperature();
    dht2_h = dht2.readHumidity();
    dht2_c = dht2.readTemperature();
    
    // photocell
    photocellReading = analogRead(photocellPin);  

    // debug messages
    Serial.print("Temperature: ");
    Serial.print(sht11_c);
    Serial.print("C / ");
    Serial.print("Humidity: ");
    Serial.print(sht11_h);
    Serial.println("%");
    Serial.print("photocell = ");
    Serial.println(photocellReading);

    Serial.print("DHT1: "); 
    Serial.print(dht1_h);
    Serial.print(" %\t");
    Serial.print(dht1_c);
    Serial.println(" *C");
    Serial.print("DHT2: "); 
    Serial.print(dht2_h);
    Serial.print(" %\t");
    Serial.print(dht2_c);
    Serial.println(" *C");
    
    // SHT11
    if(sht11_h > 0.0)
    {
      data = "{";
      data += "\"temperature\":";
      data += Float2String(sht11_c);
      data += ", \"humidity\":";
      data += Float2String(sht11_h);
      data += "}";
      sensor_id = String(SENSOR_ID) + String("SHT11");
      sendData(sensor_id, data);
    }
    // DHT11 (1)
    data = "{";
    data += ", \"dht1_temperature\":";
    data += Float2String(dht1_c);
    data += ", \"dht1_humidity\":";
    data += Float2String(dht1_h);
    data += "}";
    sensor_id = String(SENSOR_ID) + String("DHT11a");
    sendData(sensor_id, data);
    // DHT11 (2)
    data = "{";
    data += ", \"dht1_temperature\":";
    data += Float2String(dht1_c);
    data += ", \"dht1_humidity\":";
    data += Float2String(dht1_h);
    data += "}";
    sensor_id = String(SENSOR_ID) + String("DHT11b");
    sendData(sensor_id, data);
    // photocell
    data = "{";
    data += ", \"photocell\":";
    data += photocellReading;
    data += "}";
    sensor_id = String(SENSOR_ID) + String("photocell");
    sendData(sensor_id, data);

  }

  lastConnected = client.connected();
}
