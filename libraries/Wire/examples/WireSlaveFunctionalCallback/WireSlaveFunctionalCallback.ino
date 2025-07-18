// This example demonstrates the use of functional callbacks with the Wire library
// for I2C slave communication. It shows how to handle requests and data reception

#include "Wire.h"

#define I2C_DEV_ADDR 0x55

uint32_t i = 0;

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);

  Wire.onRequest([]() {
    Wire.print(i++);
    Wire.print(" Packets.");
    Serial.println("onRequest");
  });

  Wire.onReceive([](int len) {
    Serial.printf("onReceive[%d]: ", len);
    while (Wire.available()) {
      Serial.write(Wire.read());
    }
    Serial.println();
  });

  Wire.begin((uint8_t)I2C_DEV_ADDR);

#if CONFIG_IDF_TARGET_ESP32
  char message[64];
  snprintf(message, 64, "%lu Packets.", i++);
  Wire.slaveWrite((uint8_t *)message, strlen(message));
#endif
}

void loop() {}
