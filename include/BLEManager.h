#ifndef BLEMANAGER_H
#define BLEMANAGER_H

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include "Config.h"

#define BLEName "Sonicrypt"
#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define MESSAGE_CHARACTERISTIC_UUID "6d68efe5-04b6-4a85-abc4-c2670b7bf7fd"

const int MAX_PAYLOAD_SIZE = 20; // Maximum payload size in bytes
const char delimiter = ';';
const char startChar = '{';
const char endChar = '}';
const char keyValSplitChar = ':';

void setupBLE();
void disconnectBLE();
void checkToReconnect();
void sendText(String message);
bool  gotConfig();
void setConfigComplete(bool value);

#endif