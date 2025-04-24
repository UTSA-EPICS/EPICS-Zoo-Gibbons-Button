#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_SLAVE"); // Bluetooth name
  Serial.println("ESP32 Slave is ready. Waiting for connection...");
}

void loop() {
  if (SerialBT.available()) {
    String incoming = SerialBT.readString();
    Serial.print("Received via BT: ");
    Serial.println(incoming);
  }

  // Optionally, send back a response
  if (Serial.available()) {
    String msg = Serial.readString();
    SerialBT.println("Echo: " + msg);
  }
}
