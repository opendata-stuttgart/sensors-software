/*
  print voltage on A0
 */

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(analogRead(A0) * (5.0 / 1023.0));
  delay(1000);
}
