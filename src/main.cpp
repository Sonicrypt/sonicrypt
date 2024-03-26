#include <Arduino.h>
#include "WiFiManager.h"
#include "WebSocketClient.h"
#include "Notify.h"
#include "Config.h"

Config config;
WifiConfig wifi_config;

void setup() {
  Serial.begin(115200);

  pinMode(CONFIRM_LED_PIN, OUTPUT);
  pinMode(FINALIZE_LED_PIN, OUTPUT);
  pinMode(ERROR_LED_PIN, OUTPUT);

  wifi_config.ssid = "Sumit";
  wifi_config.password = "sumit625";

  setupWiFi(wifi_config);

  config.address = "7LwsCzvPoJJD8d15yiH9D411RPpQJTb3QTePR7HgBQKH";
  config.net = "devnet";

  initWebSocket(config);
}

void loop() {
  handleWebSocket();
  delay(10);
}