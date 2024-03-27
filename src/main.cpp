#include <vector>
#include <Arduino.h>
#include "WiFiManager.h"
#include "WebSocketClient.h"
#include "Notify.h"
#include "Config.h"
#include "KVStore.h"
#include "BLEManager.h"

Config config;
WifiConfig wifi_config;
std::vector<std::string> configKeys = {"ssid", "password", "net", "address"};

void setup()
{
  Serial.begin(115200);
  initKVStore();

  pinMode(CONFIRM_LED_PIN, OUTPUT);
  pinMode(FINALIZE_LED_PIN, OUTPUT);
  pinMode(ERROR_LED_PIN, OUTPUT);

  bool checkConfig = checkConfigs(configKeys);

  if (checkConfig)
  {
    Serial.println("Config found, using it");
    wifi_config.ssid = strdup(getKVStoreString("ssid").c_str());
    wifi_config.password = strdup(getKVStoreString("password").c_str());
    config.address = strdup(getKVStoreString("address").c_str());
    config.net = strdup(getKVStoreString("net").c_str());
  }
  else
  {
    Serial.println("Config not found, starting config server");
    setupConfig();

    wifi_config.ssid = strdup(getKVStoreString("ssid").c_str());
    wifi_config.password = strdup(getKVStoreString("password").c_str());
    config.address = strdup(getKVStoreString("address").c_str());
    config.net = strdup(getKVStoreString("net").c_str());
  }

  bool wifiConnected = setupWiFi(wifi_config);
  while (!wifiConnected)
  {
    setupConfig();

    wifi_config.ssid = strdup(getKVStoreString("ssid").c_str());
    wifi_config.password = strdup(getKVStoreString("password").c_str());

    wifiConnected = setupWiFi(wifi_config);
  }

  initWebSocket(config);

  // memory cleanup :') i am missing rust T_T
  free((void*)wifi_config.ssid);
  free((void*)wifi_config.password);
  free((void*)config.address);
  free((void*)config.net);
}

void loop()
{
  handleWebSocket();
  delay(10);
}