#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_MASTER", true); // true = master mode
  Serial.println("ESP32 Master starting...");

  // Wait a moment to let slave get ready
  delay(3000);

  uint8_t mac[] = {0x14, 0x33, 0x5C, 0x02, 0xB0, 0xDA}; // replace with your slave MAC
  if (SerialBT.connect(mac)) {
    Serial.println("Connected to slave!");
  } else {
    Serial.println("Failed to connect. Check MAC and make sure slave is on.");
  }
}

void loop() {
  static unsigned long lastSend = 0;
  if (SerialBT.connected() && millis() - lastSend > 2000) {
    SerialBT.println("Hello from Master!");
    Serial.println("Sent: Hello from Master!");
    lastSend = millis();
  }

  if (SerialBT.available()) {
    String response = SerialBT.readString();
    Serial.print("Received: ");
    Serial.println(response);
  }
}
