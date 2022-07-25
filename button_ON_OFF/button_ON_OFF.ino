bool a0=1; // luu trang thai truoc cua phim bam
bool s=0; // Luu trang thai den

void setup() {
  pinMode(2,INPUT_PULLUP);
  pinMode(13,OUTPUT);
  Serial.begin(9600);
 }

void loop() {
  int a=digitalRead(2);
  Serial.println(a);
  if(a==0&&a0==1)
  {
    s=!s;
    digitalWrite(13,s);
  }
  a0=a;
  delay(100);
}
