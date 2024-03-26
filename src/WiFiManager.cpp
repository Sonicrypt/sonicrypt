#include <WiFi.h>
#include "WiFiManager.h"

const char* ssid;
const char* password;

void setupWiFi(WifiConfig wifie_config) {
  ssid = wifie_config.ssid;
  password = wifie_config.password;

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}