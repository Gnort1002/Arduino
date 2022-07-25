// C++ code
//
void setup()
{
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
}

void loop()
{
  //int s = 0;
  int a = digitalRead(2);
  if (a == 1) {digitalWrite(13, HIGH);}
  if (a == 0) {digitalWrite(13, LOW);}
}
