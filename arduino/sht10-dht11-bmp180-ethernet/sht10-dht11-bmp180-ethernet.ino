/*

SHT11
 +      -> 3.3V
 -      -> GND
 data   -> 8
 Clock  -> 9


DHT11
 +      -> 5V
 -      -> GND
 data   -> 2


photoresistor
 +      -> 5V
 data   -> analog 0

BMP180
 +      -> 3.3V
 -      -> GND
 data   -> analog 4
 Clock  -> analog 5

 */

#include <Ethernet.h>
#include <SHT1x.h>
#include "Wire.h"
#include <Adafruit_BMP085.h>
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

DHT dht1(DHTPIN1, DHTTYPE);

////////////////////////////////////////////////////////////////////////////////
// Photocell

int photocellPin = 0;     // the cell and 10K pulldown are connected to a0
int photocellReading;     // the analog reading from the sensor divider


////////////////////////////////////////////////////////////////////////////////
// BMP180

Adafruit_BMP085 bmp;

////////////////////////////////////////////////////////////////////////////////
// Ethernet data
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x01 };
byte gateway[] = { 192, 168, 1, 1};
byte subnet[] = { 255, 255, 255, 0 };

char server[] = "api.luftdaten.info";

// initialize the library instance:
IPAddress ip(192,168,1, 42);
EthernetClient client;

const int postingInterval = 29000;   // delay between updates
long lastConnectionTime = 0;         // last time connected to the server
boolean lastConnected = false;       // state of the connection
long counter = 1;

void sendData(const String& sensor_id,
	      const String& data) {

  Serial.print("Sensor: ");
  Serial.println(sensor_id);
  Serial.println(data);

  if (client.connect(server, 80)) {
    Serial.println("connecting...");

    client.print("POST /v1/push-sensor-data/ HTTP/1.1\n");

    client.print("Host: api.dusti.xyz\n");
    client.print("Sensor: ");
    client.println(sensor_id);

    client.println("User-Agent: Arduino");
    client.println("Accept: application/json");
    client.print("Content-Length: ");
    client.println(data.length(), DEC);

    client.print("Content-Type: application/json\n");
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

  if (!bmp.begin()) {
	Serial.println("# Could not find a valid BMP085 sensor!");
  }

  // delay for the ethernet to get up
  delay(1000);
}

int disconnected = 0;
int next = 1;

void loop()
{
  float sht11_c, sht11_h;
  float dht1_c, dht1_h;
  String data;
  String sensor_id;

  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  if (!client.connected()) {
    Serial.print("next: ");
    Serial.println(next);

    client.stop();

    delay(1000);

    switch(next)
      {
      case 1:
	// Read values from the SHT11
	sht11_c = sht11.readTemperatureC();
	sht11_h = sht11.readHumidity();
	
	// SHT11
	if(sht11_h > 0.0)
	  {
	    data = "{\"sensordatavalues\":[{";
	    data += "\"value_type\":\"temperature\",\"value\":\"";
	    data += Float2String(sht11_c);
	    data += "\"},{";
	    data += "\"value_type\":\"humidity\",\"value\":\"";
	    data += Float2String(sht11_h);
	    data += "\"}]}";
	    sensor_id = String(SENSOR_ID) + String("SHT11");
	    sendData(sensor_id, data);
	  }
	next=2;
	break;
      case 2:
	// Read values from DHT11
	dht1_h = dht1.readHumidity();
	dht1_c = dht1.readTemperature();

	// DHT11
	data = "{\"sensordatavalues\":[{";
	data += "\"value_type\":\"temperature\",\"value\":\"";
	data += Float2String(dht1_c);
	data += "\"},{";
	data += "\"value_type\":\"humidity\",\"value\":\"";
	data += Float2String(dht1_h);
	data += "\"}]}";
	sensor_id = String(SENSOR_ID) + String("DHT11");
	sendData(sensor_id, data);

	next=3;
	break;
      case 3:
	// bmp180
	data = "{\"sensordatavalues\":[{";
	data += "\"value_type\":\"temperature\",\"value\":\"";
	data += Float2String(bmp.readTemperature());
	data += "\"},{";
	data += "\"value_type\":\"pressure\",\"value\":\"";
	data += Float2String(bmp.readPressure());
	data += "\"},{";
	data += "\"value_type\":\"altitude\",\"value\":\"";
	data += Float2String(bmp.readAltitude());
	//	data += "\"},{";
	//	data += "\"value_type\":\"pressure_sealevel\",\"value\":\"";
	//	data += Float2String(bmp.readSealevelPressure());
	data += "\"}]}";
	sensor_id = String(SENSOR_ID) + String("BMP180");
	sendData(sensor_id, data);
 	next=4;
	break;
      case 4:
	// photocell
	photocellReading = analogRead(photocellPin);  
	data = "{\"sensordatavalues\":[{";
	data += "\"value_type\":\"brightness\",\"value\":\"";
	data += photocellReading;
	data += "\"}]}";
	sensor_id = String(SENSOR_ID) + String("photoresistor");
	sendData(sensor_id, data);
 	next=5;
	break;
      case 5:
	delay(60000);
 	next=1;
	break;
      }
  }
}
