// C++ code for simple arduino (no bluetooth)
//
int buttonPin = 2;
int motorPin = 9;

void setup()
{
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);
  if (buttonState == HIGH) {
    digitalWrite(motorPin, LOW);
    Serial.println("Pin: LOW");
  }
  else {
    digitalWrite(motorPin, HIGH);
    Serial.println("Pin: HIGH");
    delay(5000);
  }
  	
}