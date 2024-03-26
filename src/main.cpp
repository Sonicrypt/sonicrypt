#include <Arduino.h>
#include "WiFiManager.h"
#include "WebSocketClient.h"
#include "Notify.h"

void setup() {
  Serial.begin(115200);

  pinMode(CONFIRM_LED_PIN, OUTPUT);
  pinMode(FINALIZE_LED_PIN, OUTPUT);
  pinMode(ERROR_LED_PIN, OUTPUT);

  setupWiFi();
  initWebSocket();
}

void loop() {
  handleWebSocket();
  delay(10);
}