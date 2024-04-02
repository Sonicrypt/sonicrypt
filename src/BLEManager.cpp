#include <sstream>
#include "BLEManager.h"
#include "KVStore.h"
#include "Notify.h"
#include "ArduinoJson.h"

BLEServer *pServer = NULL;
bool isConfigComplete = false; // Flag to track if all config keys are received

bool startFlag = false;
bool endFlag = false;
bool deviceConnected = false;
bool oldDeviceConnected = false;

String configData;

BLECharacteristic *message_characteristic = NULL;
BLECharacteristic *box_characteristic = NULL;

void processConfig();
void storeConfig(String message);

class MyServerCallbacks : public BLEServerCallbacks
{
  void onConnect(BLEServer *pServer)
  {
    Serial.println("Connected");
    notifyBLEConnected();
  };

  void onDisconnect(BLEServer *pServer)
  {
    Serial.println("Disconnected");
  }
};

class CharacteristicsCallbacks : public BLECharacteristicCallbacks
{
  void onWrite(BLECharacteristic *pCharacteristic)
  {
    String message = pCharacteristic->getValue().c_str();
    Serial.println(message);
    storeConfig(message);
  }
};

void checkToReconnect()
{
  // disconnected so advertise
  if (!deviceConnected && oldDeviceConnected)
  {
    delay(500);                  // give the bluetooth stack the chance to get things ready
    pServer->startAdvertising(); // restart advertising
    Serial.println("Disconnected: start advertising");
    oldDeviceConnected = deviceConnected;
  }
  // connected so reset boolean control
  if (deviceConnected && !oldDeviceConnected)
  {
    // do stuff here on connecting
    Serial.println("Reconnected");
    oldDeviceConnected = deviceConnected;
  }
}

void setupBLE()
{
  BLEDevice::init(BLEName);

  // BLE server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // BLE service
  BLEService *pService = pServer->createService(SERVICE_UUID);
  delay(100);

  message_characteristic = pService->createCharacteristic(
      MESSAGE_CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_READ |
          BLECharacteristic::PROPERTY_WRITE |
          BLECharacteristic::PROPERTY_NOTIFY |
          BLECharacteristic::PROPERTY_INDICATE);

  // Start the service
  pService->start();

  // Start advertising
  pServer->getAdvertising()->start();

  message_characteristic->setValue("Connection Established");
  message_characteristic->setCallbacks(new CharacteristicsCallbacks());

  Serial.println("BLE setup done");
}

void sendText(String message)
{
  message_characteristic->setValue(message.c_str());
  message_characteristic->notify();
}

void storeConfig(String message)
{
  if (message == "end")
  {
    setConfigComplete(true);
    return;
  }

  if (message.charAt(0) == startChar)
  {
    startFlag = true;
    Serial.println("Start flag set");
  }

  if (message.charAt(message.length() - 1) == endChar)
  {
    endFlag = true;
    Serial.println("End flag set");
  }

  // Append the message to configData as long as startFlag is set
  if (startFlag)
  {
    configData += message;

    // Reset endFlag if endChar is encountered
    if (endFlag)
    {
      endFlag = false;
      startFlag = false;

      // Process the configData
      Serial.println(configData);
      processConfig();
      configData = "";
    }
  }
}

void processConfig()
{
  JsonDocument doc;
  const char *jsonChar = configData.c_str();
  DeserializationError err = deserializeJson(doc, jsonChar);

  if (err)
  {
    Serial.print("Error parsing JSON: ");
    Serial.println(err.c_str());
    notifyError();
    return;
  }

  // store in KV store
  for (JsonPair kv : doc.as<JsonObject>())
  {
    Serial.print("Key: ");
    Serial.println(kv.key().c_str());

    Serial.print("Value: ");
    Serial.println(kv.value().as<String>().c_str());
    putKVStoreString(kv.key().c_str(), kv.value().as<String>().c_str());
  }
}

void disconnectBLE()
{
  pServer->getAdvertising()->stop();
  pServer->removeService(pServer->getServiceByUUID(SERVICE_UUID));
  BLEDevice::deinit();
}

bool gotConfig()
{
  return isConfigComplete;
}

void setConfigComplete(bool value)
{
  isConfigComplete = value;
}