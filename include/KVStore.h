#ifndef KVSTORE_H
#define KVSTORE_H

#include <vector>
#include <Arduino.h>
#include <Preferences.h>

bool initKVStore();

bool putKVStoreString(const char *key, const char *value);
bool putKVStoreUInt(const char *key, unsigned int value);
bool putKVStoreInt(const char *key, int value);
bool putKVStoreFloat(const char *key, float value);
bool putKVStoreDouble(const char *key, double value);
bool putKVStoreBool(const char *key, bool value);

const String getKVStoreString(const char *key);
unsigned int getKVStoreUInt(const char *key);
int getKVStoreInt(const char *key);
float getKVStoreFloat(const char *key);
double getKVStoreDouble(const char *key);
bool getKVStoreBool(const char *key);

bool removeKVStore(const char *key);

bool checkConfigs(std::vector<std::string> keys);

#endif