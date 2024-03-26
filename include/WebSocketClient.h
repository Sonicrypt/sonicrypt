#ifndef WEBSOCKET_CLIENT_H
#define WEBSOCKET_CLIENT_H

#include <ArduinoWebsockets.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include "Config.h"

using namespace websockets;

void initWebSocket(Config config);
void connect();
void handleWebSocket();
void parseSubId(String message);
void parseTx(String message);
void finalizeTx();

extern WebsocketsClient client;

#endif