// serial functions, debug output, csv output

void setup_serial(const unsigned int baudrate = 9600){ 
  Serial.begin(baudrate); //Output to Serial at x baud
  delay(10);
}

void serial_out(String msg, unsigned int level=1,boolean newline=false){
  if (level<=verbosity){return;}
  Serial.print(String("")+msg);
  if(newline){Serial.println("");}
}
/*
void serial_outln(String msg, unsigned int level=1){
  if (level<=verbosity){return;}
  Serial.println(String("")+msg);
}
*/
void serial_out(long msg, unsigned int level=1,boolean newline=false){
  if (level<=verbosity){return;}
  Serial.print(msg);
  if(newline){Serial.println("");}
}
/*
void serial_out(int32_t msg, unsigned int level=1,boolean newline=false){
  if (level<=verbosity){return;}
  Serial.print(msg);
  if(newline){Serial.println("");}
 
}
*/
/*
void serial_outln(long msg, unsigned int level=1){
  if (level<=verbosity){return;}
  Serial.println(msg);
}
*/
void serial_out(unsigned long msg, unsigned int level=1,boolean newline=false){
  if (level<=verbosity){return;}
  Serial.print(msg);
  if(newline){Serial.println("");}
}
void serial_out(double msg, unsigned int level=1,boolean newline=false){
  if (level<=verbosity){return;}
  Serial.print(msg);
  if(newline){Serial.println("");}
}
/*
void serial_outln(unsigned long msg, unsigned int level=1){
  if (level<=verbosity){return;}
  Serial.println(msg);
}
*/

// print uint8_t as int
void serial_out(uint8_t msg, unsigned int level=1,boolean newline=false){
  if (level<=verbosity){return;}
  Serial.print(int(msg));
  if(newline){Serial.println("");}
}
/*
void serial_outln(uint8_t msg, unsigned int level=1){
  if (level<=verbosity){return;}
  Serial.println(int(msg));
}
*

void serial_out(float msg, unsigned int level=1){
  if (level<=verbosity){return;}
  Serial.print(msg);
}
void serial_outln(float msg, unsigned int level=1){
  if (level<=verbosity){return;}
  Serial.println(msg);
}


String system_info(String software_version="unknown"){
  String info="Software version: "+software_version;
  info+="\nESP chipid: ";
  info+=String(ESP.getChipId());
  info+="\nHeap free: ";
  info+=String(ESP.getFreeHeap());
  info+="\nSketch size: ";
  info+=String(ESP.getSketchSize());
  info+="\nFree size: ";
  info+=String(ESP.getFreeSketchSpace());
  info+="\n";
  return (info);
}

/*
String config_info(){
  String info="sampletime [s]: ";
  info+=Float2String(sampletime_ms/1000.0);
  info+="\n";
  info+="GPIOx Dx PIN matching:\n";
  int i;
  for (i = 0; i < 13; i = i + 1) {
      info+=String(i)+"\t"+String(D[i])+"\n";
  }
  info+="Sensors:\n";
  info+="ppd_read = "+String(ppd_read)+"\n";
  info+="dht_read = "+String(dht_read)+"\n";
  info+="sds_read = "+String(sds_read)+"\n";
  info+="ds_read = "+String(ds_read)+"\n";

  info+="Pins (GPIO):\n";
  info+="Pin PPD P1 = "+String(pin_ppd_p1)+"\n";
  info+="Pin PPD P2 = "+String(pin_ppd_p2)+"\n";
  info+="Pin DHT    ="+String(pin_dht)+"\n";
  info+="Pin DS     ="+String(pin_ds)+"\n";
  info+="Pin LED    ="+String(pin_led_status)+"\n";
  
  info+="Activations:\n";
  
  info+="wireless_active = "+String(wireless_active)+"\n"; // use wireless
  info+="wificonfig      = "+String(wificonfig)+"\n"; // enable configuration via wifi (AP mode)
  info+="send2dusti      = "+String(send2dusti)+"\n"; // send data to api.luftdaten.info API
  info+="send2madavi     = "+String(send2madavi)+"\n"; // TODO: implement madavi
  info+="send2mqtt       = "+String(send2mqtt)+"\n"; // send data to MQTT
  info+="send2csv        = "+String(send2csv)+"\n"; // output as csv over serial
  info+="debug           = "+String(debug)+"\n"; // debug outputs over serial

  info+="SSID: "+ssid+"\n"; // do not output password
  info+="Django API: "+djangoapihost+":"+String(djangoapihttpPort)+"\n";
  info+="MQTT API: "+mqttusername+"@"++mqttserver+":"+mqttport;
  info+="\n\ttopicbase:"+mqtttopicbase;
  info+="\n\tconfigtopic:"+mqttintopic;
  
  info+="\nMADAVI: "+madaviapihost+":"+madaviapihttpPort+madaviapiurl;

  return(info);
}
*/


/*****************************************************************
/* Debug output                                                  *
/*****************************************************************/
void debug_out(const String& text, int level, bool linebreak) {
    if (level <= debug) {
        if (linebreak) {
            Serial.println(text);
        } else {
            Serial.print(text);
        }
    }
}

