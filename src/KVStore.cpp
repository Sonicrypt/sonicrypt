#include "KVStore.h"

Preferences preferences;

// Initialize the key-value store
bool initKVStore() {
  return preferences.begin("namespace", false);
}

/*
    * Write operations
    * Put the key-value pair in the key-value store
    * @param key: The key to store the value
    * @param value: The value to store
    * @return: True if the key-value pair is stored successfully, false otherwise
*/
bool putKVStoreString(const char *key, const char *value) {
  return preferences.putString(key, value);
}

bool putKVStoreUInt(const char *key, unsigned int value) {
  return preferences.putUInt(key, value);
}

bool putKVStoreInt(const char *key, int value) {
  return preferences.putInt(key, value);
}

bool putKVStoreFloat(const char *key, float value) {
  return preferences.putFloat(key, value);
}

bool putKVStoreDouble(const char *key, double value) {
  return preferences.putDouble(key, value);
}

bool putKVStoreBool(const char *key, bool value) {
  return preferences.putBool(key, value);
}

/*
    * Read operations
    * Get the value from the key-value store
    * @param key: The key to get the value
    * @return: The value of the key
*/
const String getKVStoreString(const char *key) {
  return preferences.getString(key);
}

unsigned int getKVStoreUInt(const char *key) {
  return preferences.getUInt(key);
}

int getKVStoreInt(const char *key) {
  return preferences.getInt(key);
}

float getKVStoreFloat(const char *key) {
  return preferences.getFloat(key);
}

double getKVStoreDouble(const char *key) {
  return preferences.getDouble(key);
}

bool getKVStoreBool(const char *key) {
  return preferences.getBool(key);
}

// Remove the key-value pair from the key-value store
bool removeKVStore(const char *key) {
  return preferences.remove(key);
}

// checkConfigs
bool checkConfigs(std::vector<std::string> keys) {
  for (std::string key : keys) {
    if (getKVStoreString(key.c_str()).length() == 0) {
      return false;
    }
  }
  return true;
}