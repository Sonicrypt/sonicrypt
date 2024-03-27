#include <WiFi.h>
#include "WiFiManager.h"
#include "BLEManager.h"

const char* ssid;
const char* password;
int retries = 0;
const int max_retries = 5;

bool setupWiFi(WifiConfig wifi_config) {
  retries = 0;
  ssid = wifi_config.ssid;
  password = wifi_config.password;

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED && retries <= max_retries) {
    delay(1000);
    Serial.print("Connecting to WiFi...");
    Serial.println(retries + 1);
    retries++;
  }

  if (retries > max_retries) {
    Serial.println("Failed to connect to WiFi");
    return false;
  }
  return true;
}