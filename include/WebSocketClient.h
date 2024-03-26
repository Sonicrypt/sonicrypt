#ifndef WEBSOCKET_CLIENT_H
#define WEBSOCKET_CLIENT_H

#include <ArduinoWebsockets.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>

using namespace websockets;

void initWebSocket();
void handleWebSocket();
void parseSubId(String message);
void parseTx(String message);
void finalizeTx();

extern WebsocketsClient client;

#endif