const int  buttonPin = 2;
const int led1 = 13, led2 =12;

int pressCount = 0;
int buttonState = 0;
int lastButtonState = 0;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  digitalWrite(led1, 0);
  digitalWrite(led2, 0);
  // initialize serial communication:
  Serial.begin(9600);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  
  if (buttonState != lastButtonState) {
    if (buttonState == 0) {
      pressCount++;
    }
    // Delay a little bit to avoid bouncing
    delay(50);
    lastButtonState = buttonState;

    if (pressCount % 4 == 0) {
        digitalWrite(led1, 0);
        digitalWrite(led2, 0);
    }
    else if (pressCount % 4 == 1) {
        digitalWrite(led1, 1);
        digitalWrite(led2, 0);
    }
    else if (pressCount % 4 == 2) {
        digitalWrite(led1, 1);
        digitalWrite(led2, 1);
    }
    else (pressCount % 4 == 3){
        digitalWrite(led1, 0);
        digitalWrite(led2, 1);
    }
   if (pressCount == 3) pressCount = 0;
  }
}
