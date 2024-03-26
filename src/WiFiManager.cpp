#include <WiFi.h>
#include "WiFiManager.h"

const char* ssid = "Sumit";
const char* password = "sumit625";

void setupWiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}