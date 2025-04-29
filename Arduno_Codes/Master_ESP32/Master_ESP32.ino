#include <BluetoothSerial.h>
BluetoothSerial SerialBT; // Create a Bluetooth Serial object

#define BUTTON_PIN 21 // Button connected to GPIO21 (says "D21" on board)
uint8_t slaveAddress[] = {0x14, 0x33, 0x5C, 0x02, 0xB0, 0xDA}; // Replace with your slave MAC

void setup() {
  Serial.begin(115200); // Common rate for ESP32
  SerialBT.begin("ESP32_MASTER", true); // true = Master mode
  Serial.println("ESP32 Master starting...");

  pinMode(BUTTON_PIN, INPUT_PULLUP); // Button with internal pull-up (Has to be INPUT_PULLUP, so we dont get any random values!)

  delay(3000); // delay for slave module to get ready

  connectToSlave(); // Try to connect once
}

void loop() {
  //  sets the button input to HIGH
  static int lastButtonState = HIGH;  
  int buttonState = digitalRead(BUTTON_PIN);  //reads the button input and assings it to "buttonState"

  if (SerialBT.connected()) { // If modules are connected
    if (buttonState != lastButtonState) { // If button has not changed value
      lastButtonState = buttonState;  //  button value stays the same

      if (buttonState == LOW) { // Button Pressed
        SerialBT.println("1");  //  Sends a "1" to the Slave module
        Serial.println("Sent: 1 (Button Pressed)"); //  Prints in the Master Terminal
      } else { // Button Released
        SerialBT.println("0");  //  Sends a "0" to the Slave module
        Serial.println("Sent: 0 (Button Released)");  //  Prints in the Master Terminal
      }
    }

    // Read incoming messages if any
    if (SerialBT.available()) {
      String response = SerialBT.readStringUntil('\n'); //  Read the Slave message until newline character
      Serial.print("Received: "); // Prints in the Master Terminal
      Serial.println(response); // Prints in the Master Terminal incoming message
    }
    // there is no incoming message and BT disconnects
  } else {
    Serial.println("Disconnected. Trying to reconnect..."); // Prints in Master Terminal disconnect message
    connectToSlave(); // Attempts connect to Slave
    delay(2000); // Wait 2 seconds before retrying
  }

  delay(50); // Short delay for stability
}

// Function to connect to the Slave device using its MAC address
void connectToSlave() {
  Serial.println("Attempting to connect to Slave...");  // Prints to Master Terminal connection attempt
  if (SerialBT.connect(slaveAddress)) { // If connection is successful
    Serial.println("Connected to Slave!");  // Prints in master terminal connected message
  } else {  // If connection fails
    Serial.println("Failed to connect. Retrying..."); // Prints in master Terminal failure message
  }
}
