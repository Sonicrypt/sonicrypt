#include <Arduino.h>
#include "WiFiManager.h"
#include "WebSocketClient.h"

void setup() {
  Serial.begin(115200);
  setupWiFi();
  initWebSocket();
}

void loop() {
  handleWebSocket();
  delay(10);
}