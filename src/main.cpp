#include <Arduino.h>
#include "WiFiManager.h"
#include "WebSocketClient.h"
#include "Notify.h"
#include "Config.h"

Config config;

void setup() {
  Serial.begin(115200);

  pinMode(CONFIRM_LED_PIN, OUTPUT);
  pinMode(FINALIZE_LED_PIN, OUTPUT);
  pinMode(ERROR_LED_PIN, OUTPUT);

  setupWiFi();

  config.address = "7LwsCzvPoJJD8d15yiH9D411RPpQJTb3QTePR7HgBQKH";
  config.net = "devnet";

  initWebSocket(config);
}

void loop() {
  handleWebSocket();
  delay(10);
}