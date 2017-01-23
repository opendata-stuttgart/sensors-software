

void setup()
{
  Serial.begin(9600);
  delay(500);
  Serial.println("SETUP");
}

void loop()
{
  Serial.print('-');
  delay(100);
}
