#ifndef CONFIG_H
#define CONFIG_H

typedef struct {
  char* net;
  char* address;
} Config;

typedef struct {
  char* ssid;
  char* password;
} WifiConfig;

#endif
