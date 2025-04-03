// C++ code for simple arduino (no bluetooth)
//
int buttonPin = 2;
int motorPin = 9;

void setup()
{
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(motorPin, OUTPUT);
}

void loop()
{
  int buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    digitalWrite(motorPin, LOW);
    delay(5000)
  }
  else {
    digitalWrite(motorPin, HIGH);
  }
  
}