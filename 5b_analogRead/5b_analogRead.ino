void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  int a = analogRead(A5);
  Serial.println(a);
  digitalWrite(LED_BUILTIN, 1);
  delay(a);
  digitalWrite(LED_BUILTIN, 0);
  delay(a);

}
