#ifdef PUSHTO_MQTT
#ifdef WIRELESS_ACTIVE
// connect/push to an MQTT server
// #include <PubSubClient.h> // include in .ino
// configure mqttserver, mqttport, mqtttopicbase in sensorconfig.h
//
// const char mqttserver[] = "mqtt.opendataset.click"; const int mqttport = 1883; const char mqtttopicbase[]="/dusti/";
// derived from example of PubSubClient lib: mqtt_esp8266.ino

WiFiClient mqttwificlient;
String mqttclientid="esp8266-"+String(ESP.getChipId());
String logtopic="log";
PubSubClient psclient;

boolean pubsubclient_reconnect(){
  // Loop until we're reconnected
  int ccnt=10;
  while ((!psclient.connected())&&(ccnt>0)) {
    Serial.print("Attempting MQTT connection...");
    if(psclient.connect(mqttclientid.c_str())){
        Serial.println("OK");
    }else{
        Serial.print("try ");
        Serial.println(ccnt);
        ccnt=ccnt-1;
    }
  }
  if(psclient.connected()){
    return true;
  }else{
    Serial.println("connection failed, giving up");
    return false;
  }
}

void mqttcallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("mqttcallback: message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  //TODO: analyse message here (not yet used)
}


void mqtt_publish_subtopic(const char* subtopic, const char* payload) {
    String topictopub=String(mqtttopicbase) + "/" + mqttclientid + "/" + subtopic;
    Serial.println("Publish to MQTT server...");
    boolean success=false;
    if (!psclient.connected()) {
        success=pubsubclient_reconnect();
        if(!success){
           Serial.println("connect failed, no publishing");
           return;
        }
    }
   // Once connected, publish payload...
   Serial.println("publish payload: ");
   Serial.println(payload);
   success=psclient.publish(topictopub.c_str(), payload);
   Serial.print("publish topic ");
   if (success){
       Serial.println(" OK");
   }else{
       Serial.println(" failed");
   }
}

// publish String
void mqtt_publish_subtopic(const char* subtopic, String payload) {
    mqtt_publish_subtopic(subtopic, payload.c_str());
}

// TODO: check the following, unused and unfinished yet
void mqtt_subscribetosubtopic(const char* subtopic){
   String subscribetopic=String(mqtttopicbase) + "/" + mqttclientid + "/" + String(subtopic);
   Serial.print("mqtt_subscribetosubtopic to ");
   Serial.print(subscribetopic);
   // ... and subscribe
   boolean success=false;
   success=psclient.subscribe(subscribetopic.c_str());
   if (success){
       Serial.println("OK");
   }else{
       Serial.println("failed");
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
  String msg="MQTT start String";
  if (!psclient.publish(String(String(mqtttopicbase) + "/" + mqttclientid + "/" + logtopic).c_str(), msg.c_str())){
    Serial.print("MQTT: publish init message failed ");
  }
  mqtt_publish_subtopic(logtopic.c_str(), "MQTT started");
  mqtt_subscribetosubtopic(mqttintopic);
}


// endif WIRELESS_ACTIVE
#endif
// endif PUSHTO_MQTT
#endif
