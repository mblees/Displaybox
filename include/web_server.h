#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <Arduino.h>

// WLAN-Access-Point mit Weboberflaeche zur Farbwahl. Standardmaessig aus;
// aktivieren per build_flags in platformio.ini (-D ENABLE_WEB_SERVER=1) und
// include/secrets.h aus include/secrets_example.h anlegen.
#ifndef ENABLE_WEB_SERVER
#define ENABLE_WEB_SERVER 0
#endif

#include <WiFi.h>      // seit Arduino-ESP32 3.x nicht mehr ueber WebServer.h
#include <WebServer.h>
#include "led_controller.h"

#ifdef __cplusplus
extern "C"
{
#endif

void handleRoot();
void init_web_server();
void web_server_do_work();

#ifdef __cplusplus
}
#endif

#endif // WEB_SERVER_H
