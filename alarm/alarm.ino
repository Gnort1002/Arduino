//set the starting time 01:24:50 PM
const int h=1, m=23, s=50;
String c = "PM";
//set the alarm
const int hA = 1, mA = 24, sA = 0;
//buzzer pin 12
int speakerPin = 12;
int numTones = 10; 
int tones[] = {261, 277, 294, 311, 330, 349, 370, 392, 415, 440};
//1000 millis
int timer = 1000;


//add "0" before the number less than 10
void printDigit(int d){
  if (d < 10) Serial.print("0");
  Serial.print(d);
}

//function to print the current time (from the starting time)
void printClock(int h, int m, int s, String now){
   Serial.print("Thoi gian hien tai: ");
   printDigit(h);
   Serial.print(":");
   printDigit(m);
   Serial.print(":");
   printDigit(s);
   Serial.print(" ");
   Serial.print(now);
   Serial.println(); 
}

//print the starting time
void setup() {
 pinMode(13, OUTPUT);
 pinMode(speakerPin, OUTPUT); 
 Serial.begin(9600);
 Serial.println("DONG HO BAO THUC");
 printClock(h, m, s, "PM");
 delay(timer);

}

//function to blink the 13-LED
void blink(){
  digitalWrite(13, HIGH);   
  delay(1000);                       
  digitalWrite(13, LOW);    
  delay(1000);   
}

//
void speaker(int i){
 tone(speakerPin, tones[i]); // play the tone in each array position
 delay(timer);
 noTone(speakerPin); // stop playing
}
  
void loop() {
 String c = "PM";
 int t2 = millis()/1000;
 int s1 = (s + t2)%60;
 int m1 = (m + (s + t2)/60)%60;
 int h1 = (h + (m + (s + t2)/60)/60)%12;
 if (c == "PM" && h1 == 0) c = "AM";
 if (c == "AM" && h1 == 0) c = "PM";

 printClock(h1, m1, s1, c);
 delay(timer);

 //blink and ring 10 times = 30 seconds
 if (h1 == hA && m1 == mA && s1 == sA) {
   for (int i = 0; i < 10; i++) {
     blink();
     speaker(i);
   }
  }
}       
