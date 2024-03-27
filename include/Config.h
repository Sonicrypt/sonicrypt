#ifndef CONFIG_H
#define CONFIG_H

#include <vector>

typedef struct {
  const char* net;
  const char* address;
} Config;

typedef struct {
  const char* ssid;
  const char* password;
} WifiConfig;

extern std::vector<std::string> configKeys;

#endif
