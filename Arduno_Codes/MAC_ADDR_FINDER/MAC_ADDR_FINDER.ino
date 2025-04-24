#include <BluetoothSerial.h>
#include <esp_bt_device.h>  // <-- ADD THIS LINE



BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_SLAVE"); // Give it a name
  Serial.println("Bluetooth started");


  // Print the MAC address of this ESP32
  const uint8_t* mac = esp_bt_dev_get_address();
  char macStr[18];
  sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X",
          mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  Serial.print("Slave Bluetooth MAC Address: ");
  Serial.println(macStr);
}

void loop() {
  delay(1000);
}
