#ifndef APIFUNCTIONS_H
#define APIFUNCTIONS_H
// #include <ESP8266WiFi.h>
/**********************************************/
/* WiFi connecting script
/**********************************************/

void PrintMacAddress(void) {
  uint8_t  MAC_STA[6];
  uint8_t  MAC_softAP[]          = {0,0,0,0,0,0};
  char temp[20];      // buffer for formatting the output (xx:xx:xx:xx:xx:xx\r\n) = 20 bytes
  uint8_t macaddr[6];   // array that will receive the MAC address from the chip
  
  //
  // get the mac address from the API. This is described in the  documentation from
  // SDK 0.9.1. The document is/was missing in SDK 0.9.2. If anyone needs it, let me know
  //
  Serial.print("MAC[SoftAP]");
  uint8_t* MAC  = WiFi.softAPmacAddress(MAC_softAP);                   //get MAC address of softAP interface
    for (int i = 0; i < sizeof(MAC)+2; ++i){                                                          //this line needs cleaning up.
         Serial.print(":");
         Serial.print(MAC[i],HEX);
         MAC_softAP[i] = MAC[i];                                         //copy back to global variable
    }
    Serial.println();
  //wifi_get_macaddr(0x00, macaddr);
  //
  // format the a string into temp field as 6 hex numbers with a colon in between
  //
  Serial.println();
  Serial.print("MAC[STA]");
  MAC  = WiFi.macAddress(MAC_STA);                   //get MAC address of STA interface
  for (int i = 0; i < sizeof(MAC)+2; ++i){
       Serial.print(":");
       Serial.print(MAC[i],HEX);
       MAC_STA[i] = MAC[i];                                            //copy back to global variable
  }
  Serial.println();
}

void connectWifi() {
  PrintMacAddress();
  WiFi.begin(ssid, password); // Start WiFI
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.println();
  int counter=0;
  while (WiFi.status() != WL_CONNECTED)
  {
    #ifdef PIN_LED_STATUS
    digitalWrite(PIN_LED_STATUS, LOW);
    #endif
    delay(250);
    Serial.print(".");
    if (counter++==50){
      Serial.println();
      counter =0;
    }
    #ifdef PIN_LED_STATUS
    digitalWrite(PIN_LED_STATUS, HIGH);
    #endif
    delay(250);
  }
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  //Serial.print("MAC address: ");
  // for (int i = 0; i < 6; ++i) {
  //   Serial.print(String(mac[i], 16));
  //  if (i < 5)
  //    Serial.print(":");
  //  }
    Serial.println();
  WiFi.printDiag(Serial);
}
/**********************************************/
/* send data to rest api
/**********************************************/
void sendData(const String& data, int pin=-1) {
  //  delay(60000);
  ++value;

#ifdef PIN_LED_STATUS
digitalWrite(PIN_LED_STATUS, LOW);
#endif

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
  Serial.println(ESP.getChipId());
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
#ifdef PIN_LED_STATUS
digitalWrite(PIN_LED_STATUS, HIGH);
#endif
}

String Float2String(float value)
{
  // Convert a float to String with two decimals.
  String s;
  s = String(int(value));
  s += '.';
  s += int((value - int(value)) * 100);

  return s;
}

#endif
