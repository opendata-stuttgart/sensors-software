#ifndef APIFUNCTIONS_H
#define APIFUNCTIONS_H
// #include <ESP8266WiFi.h>
/**********************************************/
/* WiFi connecting script
/**********************************************/

void PrintMacAddress(void) {
#ifndef WIRELESS_ACTIVE
    Serial.println("MAC: no WiFi -> no MAC")
#endif
#ifdef WIRELESS_ACTIVE
  uint8_t  MAC_STA[6];
  uint8_t  MAC_softAP[]          = {0,0,0,0,0,0};
  char temp[20];      // buffer for formatting the output (xx:xx:xx:xx:xx:xx\r\n) = 20 bytes
  uint8_t macaddr[6];   // array that will receive the MAC address from the chip
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
#endif //WIRELESS_ACTIVE
}

void connectWifi() {
#ifdef WIRELESS_ACTIVE
  if (WiFi.status() == WL_CONNECTED){
    // nothing to do
    return;
  }
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
#endif
}

/**********************************************/
/* send data to rest api
/**********************************************/
void sendData(const String& data, int pin=-1) {
  //  delay(60000);
  ++value;

#ifdef WIRELESS_ACTIVE
#ifdef PUSHTO_DJANGOAPI
Serial.print("#### Sending to ");
Serial.print(String(host));
Serial.print(":");
Serial.print(httpPort);
#ifdef PIN_LED_STATUS
digitalWrite(PIN_LED_STATUS, LOW);
#endif
  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient wificlient;
  if (!wificlient.connect(host, httpPort)) {
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
  wificlient.print(String("POST ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Pin: " + pinstr + "\r\n" +
               "Content-Type: application/json\r\n" +
               "Sensor: esp8266-");
  wificlient.println(ESP.getChipId());
  wificlient.print("Content-Length: ");
  wificlient.println(data.length(), DEC);
  wificlient.println("Connection: close\r\n");
  wificlient.println(data);
  delay(1);
  
  // Read reply from server and print them
  while(wificlient.available()){
    char c = wificlient.read();
    Serial.print(c);
  }
  
  Serial.println();
  Serial.println("closing connection");
// endif PUSHTO_DJANGOAPI
#endif
#ifdef PIN_LED_STATUS
digitalWrite(PIN_LED_STATUS, HIGH);
#endif
#endif //WIRELESS_ACTIVE
#ifndef WIRELESS_ACTIVE
    #ifdef PIN_LED_STATUS
    digitalWrite(PIN_LED_STATUS, LOW);
    delay(100);
    digitalWrite(PIN_LED_STATUS, HIGH);
    delay(100);
    digitalWrite(PIN_LED_STATUS, LOW);
    delay(100);
    digitalWrite(PIN_LED_STATUS, HIGH);
    delay(100);
    #endif
#endif // WIRELESS_ACTIVE
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

#endif // APIFUNCTIONS_H
