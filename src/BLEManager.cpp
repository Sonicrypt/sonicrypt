#include <sstream>
#include "BLEManager.h"
#include "KVStore.h"
#include "Notify.h"

BLEServer *pServer = NULL;
bool isConfigComplete = false; // Flag to track if all config keys are received

bool startFlag = false;
bool endFlag = false;
bool deviceConnected = false;
bool oldDeviceConnected = false;

String configData;

BLECharacteristic *message_characteristic = NULL;
BLECharacteristic *box_characteristic = NULL;

void processConfig(char startChar, char endChar, char delimiter, char keyValSplitChar, std::vector<std::string> configKeys);
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
      processConfig(startChar, endChar, delimiter, keyValSplitChar, configKeys);
      configData = "";
    }
  }
}

void processConfig(char startChar, char endChar, char delimiter, char keyValSplitChar, std::vector<std::string> configKeys)
{
  // Remove the curly braces from configData
  configData.remove(0, 1);                    // Remove the first character '{'
  configData.remove(configData.length() - 1); // Remove the last character '}'

  // Split the configData into individual key-value pairs based on the delimiter ';'
  int separatorIndex;
  int prevSeparatorIndex = -1;

  while ((separatorIndex = configData.indexOf(delimiter, prevSeparatorIndex + 1)) != -1)
  {
    String pair = configData.substring(prevSeparatorIndex + 1, separatorIndex);

    // Split the key-value pair into key and value based on the delimiter ':'
    int colonIndex = pair.indexOf(keyValSplitChar);

    if (colonIndex != -1)
    {
      String key = pair.substring(0, colonIndex);
      String value = pair.substring(colonIndex + 1);

      // if the key is in configKeys vector, store the key-value pair in the key-value store
      if (std::find(configKeys.begin(), configKeys.end(), key.c_str()) != configKeys.end())
      {
        Serial.print("Key: ");
        Serial.println(key);
        Serial.print("Value: ");
        Serial.println(value);

        // Store the key-value pair in the key-value store
        Serial.println("Storing key-value pair in key-value store");
        putKVStoreString(key.c_str(), value.c_str());
      }
      else
      {
        // Error handling if the key is not in configKeys vector
        Serial.println("Invalid key");
        Serial.print("Key: ");
        Serial.println(key);
        Serial.print("Value: ");
        Serial.println(value);
      }
    }
    else
    {
      // Error handling if delimiter ':' is not found
      Serial.println("Invalid key-value pair format");
    }

    prevSeparatorIndex = separatorIndex;
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