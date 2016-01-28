

void setup() {
  Serial.begin(9600);
  Serial.println("booted.");
  
  pinMode(1,INPUT);
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(6,INPUT);
  pinMode(7,INPUT);
  pinMode(8,INPUT);
  pinMode(9,INPUT);
  pinMode(10,INPUT);
}

void loop() {
   Serial.print("1: ");
   Serial.println(digitalRead(1));
   
   Serial.print("2: ");
   Serial.println(digitalRead(2));
   
   Serial.print("3: ");
   Serial.println(digitalRead(3));
   
   Serial.print("4: ");
   Serial.println(digitalRead(4));
   
   Serial.print("5: ");
   Serial.println(digitalRead(5));
   
   Serial.print("6: ");
   Serial.println(digitalRead(6));
   
   Serial.print("7: ");
   Serial.println(digitalRead(7));
   
   Serial.print("8: ");
   Serial.println(digitalRead(8));
   
   Serial.print("9: ");
   Serial.println(digitalRead(9));
   
   Serial.print("10: ");
   Serial.println(digitalRead(10));

    delay(500);
}
