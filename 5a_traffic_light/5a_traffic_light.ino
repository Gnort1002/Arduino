// C++ code
//
int g1 = 2, y1 = 3, r1 = 4, g2 = 11, y2 = 12, r2 = 13;
const int timer = 1000;
void setup()
{
  for(int i = 11; i <= 13; i++)
    pinMode(i, OUTPUT);

  for(int i = 2; i <= 4; i++)
    pinMode(i, OUTPUT);
}

void loop()
{
  //Cycle 1: g1,r2: On, g2, r1, y1, y2: Off (60s)
  digitalWrite(g1, 1);
  digitalWrite(r2, 1);
  digitalWrite(r1, 0);
  digitalWrite(y2, 0);
  delay(timer*10);
  // Cycle 2: g1: Off, y1: On
  digitalWrite(g1, 0);
  digitalWrite(y1, 1);
  delay(timer*3); 
  // Cycle 3: g1, y1, r2: Off, r1, g2: On
  digitalWrite(y1, 0);
  digitalWrite(r1, 1);
  digitalWrite(g2, 1);
  digitalWrite(r2, 0);
  delay(timer*10); 
  // Cycle 4: g2: Off, y2: On
  digitalWrite(g2, 0);
  digitalWrite(y2, 1);
  delay(timer*3); 
}
