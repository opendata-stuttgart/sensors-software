#ifdef PUSHTO_MQTT
#ifdef WIRELESS_ACTIVE
// connect/push to an MQTT server
// #include <PubSubClient.h> // include in .ino
// configure mqttserver, mqttport, mqtttopicbase in sensorconfig.h
//
// const char mqttserver[] = "mqtt.opendataset.click"; const int mqttport = 1883; const char mqtttopicbase[]="/dusti/";
// derived from example of PubSubClient lib: mqtt_esp8266.ino
WiFiClient mqttwificlient; // a wificlient for our mqtt connection
String mqttclientid="esp8266-"+String(ESP.getChipId());
String logtopic=String(String(mqtttopicbase) + "/" + mqttclientid + "/" + "log");
PubSubClient psclient;
String mqttmsg;
// do everything without String?
//char msg [MQTT_MAX_PACKET_SIZE] = "";

boolean pubsubclient_reconnect(){
  // Loop to reconnect
  int ccnt=10;
  while ((!psclient.connected())&&(ccnt>0)) {
    Serial.print("Attempting MQTT connection...");
    if(psclient.connect(mqttclientid.c_str())){
        Serial.println("OK");
    }else{
        Serial.print("try ");
        Serial.print(ccnt);
        ccnt=ccnt-1;
        Serial.print(", client state: ");
        Serial.print(psclient.state());
    }
  }
  if(psclient.connected()){
    mqttmsg="(re)connected, state: "+String(psclient.state());
    psclient.publish(logtopic.c_str(), mqttmsg.c_str());
    Serial.println(psclient.state());
    return true;
  }else{
    Serial.println("connection failed, giving up");
    return false;
  }
}

void mqtt_publish_topic(const char* topic, const char* payload) {
    //Serial.println("Publish to MQTT server...");
    boolean success=false;
    if (!psclient.connected()) {
        success=pubsubclient_reconnect();
        if(!success){
           Serial.println("connect failed, no publishing");
           return;
        }
    }
   // Once connected, publish payload...
   Serial.print("MQTT: publish topic ");
   Serial.println(topic);
   Serial.println(payload);
   success=psclient.publish(topic, payload);
   if (success){
       Serial.println(" OK");
   }else{
       Serial.println(" failed");
       mqttmsg=String("topic pub fail: ") +topic;
       psclient.publish(logtopic.c_str(), mqttmsg.c_str());
   }
}
// publish String
void mqtt_publish_topic(const char* subtopic, String payload) {
    mqtt_publish_topic(subtopic, payload.c_str());
}
void mqtt_publish_subtopic(const char* subtopic, const char* payload) {
    String topictopub=String(mqtttopicbase) + "/" + mqttclientid + "/" + subtopic;
    mqtt_publish_topic(topictopub.c_str(),payload);
}
// publish String
void mqtt_publish_subtopic(const char* subtopic, String payload) {
    mqtt_publish_subtopic(subtopic, payload.c_str());
}

void mqttcallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("mqttcallback: message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  // acknowledge reception
  psclient.publish(logtopic.c_str(), "received incoming msg");
  //TODO: analyse message here (not yet used)
}


// check the following, unused and unfinished yet
void mqtt_subscribetosubtopic(const char* subtopic){
   String subscribetopic=String(mqtttopicbase) + "/" + mqttclientid + "/" + String(subtopic);
   Serial.print("mqtt_subscribetosubtopic to ");
   Serial.print(subscribetopic);
   // ... and subscribe
   boolean success=false;
   success=psclient.subscribe(subscribetopic.c_str());
   if (success){
       Serial.println("OK");
       mqtt_publish_topic(logtopic.c_str(), String("subscribed successfully to ")+subscribetopic);
   }else{
       Serial.println("failed");
       mqtt_publish_topic(logtopic.c_str(), "subscribe failed");
   }
}

void mqtt_setup() {
  //setup_wifi();
  //Serial.begin(9600);
  Serial.print("MQTT setup, client id: ");
  Serial.println(mqttclientid);
  int ccnt=10;
  while((WiFi.status() != WL_CONNECTED)&&(ccnt>0)){
    Serial.print("MQTT: wifi not connected, trying to connect, try ");
    Serial.println(ccnt);
    connectWifi(); // in apifunctions.h
    ccnt=ccnt-1;
  }
  if(WiFi.status() != WL_CONNECTED){
      Serial.print("MQTT error: wifi not connected, giving up");
      return;
  }
  psclient.setClient(mqttwificlient);
  psclient.setServer(mqttserver, mqttport);
  psclient.setCallback(mqttcallback);
  pubsubclient_reconnect();
  //mqtt_publish_topic(logtopic.c_str(), "MQTT started");
  mqttmsg=String("MQTT start, max packet size is ")+String(MQTT_MAX_PACKET_SIZE)+String(" sampletime[ms]: ")+String(sampletime_ms);
  mqtt_publish_topic(logtopic.c_str(), mqttmsg);
  mqttmsg=String("heap free: ")+String(ESP.getFreeHeap())+String(" software version: ")+software_version_s;
  mqtt_subscribetosubtopic(mqttintopic);
}


// endif WIRELESS_ACTIVE
#endif
// endif PUSHTO_MQTT
#endif
