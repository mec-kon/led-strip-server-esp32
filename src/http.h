#ifndef ESP32_HTTP_H
#define ESP32_HTTP_H

#include "defines.h"
#include "structs.h"
#include "../.piolibdeps/ArduinoJson_ID64/src/ArduinoJson.h"
#include <WebServer.h>


extern WebServer server;

extern void handle_request_body();
extern void http_init(queue_data_t * queue_data1);

#endif //ESP32_HTTP_H
