#ifndef DS18X20PUSH_H
#define DS18X20PUSH_H

#ifndef ONEWIRE_PIN
#define ONEWIRE_PIN 15 // GPIO15=D8
#endif

#define DS18S20_ID 0x10
#define DS18B20_ID 0x28
#define DS1822_ID 0x22

OneWire ds(ONEWIRE_PIN);

byte dsaddr[8];

void DSinit(){
  byte i;
  byte type_s;
    ds.reset_search();
    if (!ds.search(dsaddr)) {
    Serial.println("No more addresses. No DS device found");
    Serial.println();
    ds.reset_search();
    delay(250);
    return;
  }

  Serial.print("ROM =");
  for( i = 0; i < 8; i++) {
    Serial.write(' ');
    Serial.print(dsaddr[i], HEX);
  }

  if (OneWire::crc8(dsaddr, 7) != dsaddr[7]) {
      Serial.println("CRC is not valid!");
      return;
  }
  Serial.println();
 
  // the first ROM byte indicates which chip
  switch (dsaddr[0]) {
    case DS18S20_ID:
      Serial.println("  Chip = DS18S20");  // or old DS1820
      type_s = 1;
      break;
    case DS18B20_ID:
      Serial.println("  Chip = DS18B20");
      type_s = 0;
      break;
    case DS1822_ID:
      Serial.println("  Chip = DS1822");
      type_s = 0;
      break;
    default:
      Serial.println("Device is not a DS18x20 family device.");
      return;
  ds.reset();


  }
}

void DSpush(){
  String data;
  byte i;
  byte present = 0;
  byte type_s;
  byte dat[12];
//  byte addr[8]; // replaced by dsaddr - a global var
  float celsius = -999;
  float fahrenheit = -999;

  ds.reset();
  ds.select(dsaddr);
//  ds.write(0x44, 1);        // start conversion, with parasite power on at the end
  ds.write(0x44, 0);        // start conversion, with parasite power off at the end
  
  delay(750);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.
  
  present = ds.reset();
  ds.select(dsaddr);    
  ds.write(0xBE);         // Read Scratchpad
  Serial.print("  Data = ");
  Serial.print(present, HEX);
  Serial.print(" ");
  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    dat[i] = ds.read();
    Serial.print(dat[i], HEX);
    Serial.print(" ");
  }
  Serial.print(" CRC=");
  Serial.print(OneWire::crc8(dat, 8), HEX);
  Serial.println();

  // Convert the dat to actual temperature
  // because the result is a 16 bit signed integer, it should
  // be stored to an "int16_t" type, which is always 16 bits
  // even when compiled on a 32 bit processor.
  int16_t raw = (dat[1] << 8) | dat[0];
  if (type_s) {
    raw = raw << 3; // 9 bit resolution default
    if (dat[7] == 0x10) {
      // "count remain" gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - dat[6];
    }
  } else {
    byte cfg = (dat[4] & 0x60);
    // at lower res, the low bits are undefined, so let's zero them
    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
    //// default is 12 bit resolution, 750 ms conversion time
  }
  celsius = (float)raw / 16.0;
  fahrenheit = celsius * 1.8 + 32.0;
  Serial.print("  Temperature = ");
  Serial.print(celsius);
  Serial.print(" Celsius, ");
  Serial.print(fahrenheit);
  Serial.println(" Fahrenheit");
  // TODO: call API

    Serial.println("#### Sending to Dusty: ");
    
    // json for push to api: h t
    data = "{\"sensordatavalues\":[{";
    data += "\"value_type\":\"temperature\",\"value\":\"";
    data += Float2String(celsius);
    data += "\"}]}";
    Serial.println("#### Sending to Dusty: ");
    sendData(data);
}

float DSgetTemperature(){
    float temp;
    byte i;
    byte present = 0;
    byte data[12];
    byte addr[8];
    //find a device
    if (!ds.search(addr)) {
        ds.reset_search();
        delay(250);
        return -999;
    }
    if (OneWire::crc8( addr, 7) != addr[7]) {
        return -999;
    }
    if (addr[0] != DS18S20_ID && addr[0] != DS18B20_ID) {
        return -999;
    }
    ds.reset();
    ds.select(addr);
    // Start conversion, 0=non-parasitic,  1= parasitic
    ds.write(0x44, 0);
    // Wait some time...
    delay(150);
    present = ds.reset();
    ds.select(addr);
    // Issue Read scratchpad command
    ds.write(0xBE);
    // Receive 9 bytes
    for ( i = 0; i < 9; i++) {
        data[i] = ds.read();
    }
    // Calculate temperature value
    temp = ( (data[1] << 8) + data[0] )*0.0625;
    return temp;
}
#endif