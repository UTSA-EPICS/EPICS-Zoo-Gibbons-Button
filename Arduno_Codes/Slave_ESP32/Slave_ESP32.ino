#include <BluetoothSerial.h>
BluetoothSerial SerialBT; // Create a Bluetooth Serial object

#define PUMP_PIN 18 // Pin where the relay controlling the pump is connected

void setup() {
  Serial.begin(115200); // Common rate for ESP32
  SerialBT.begin("ESP32_SLAVE"); // Device name
  Serial.println("ESP32 Slave is ready. Waiting for connection...");

  pinMode(PUMP_PIN, OUTPUT);  // Sets Pin for the Pump to an OUTPUT pin
  digitalWrite(PUMP_PIN, LOW); // Pump OFF initially
}

void loop() {
  // Check if data has been received over Bluetooth
  if (SerialBT.available()) {
    String incoming = SerialBT.readStringUntil('\n'); // Read incoming Bluetooth data until newline character
    incoming.trim(); // Remove any extra spaces or newlines
    Serial.print("Received via BT: ");
    Serial.println(incoming);

    // Control the pump based on the received message
    if (incoming == "1") {
      digitalWrite(PUMP_PIN, HIGH); // Turn ON pump
      Serial.println("Pump ON");
    } else if (incoming == "0") {
      digitalWrite(PUMP_PIN, LOW); // Turn OFF pump
      Serial.println("Pump OFF");
    }
  }

  // Optional: Echo back via Serial monitor if you type anything manually
  if (Serial.available()) {
    String msg = Serial.readStringUntil('\n');  // Read incoming Serial message until newline
    SerialBT.println("Echo: " + msg); // Send it back to the Master as an "Echo"
  }
}
