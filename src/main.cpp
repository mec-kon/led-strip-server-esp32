/*
 *  This sketch demonstrates how to scan WiFi networks.
 *  The API is almost the same as with the WiFi Shield library,
 *  the most obvious difference being the different file you need to include:
 */

#include "Arduino.h"

#include "WebServer.h"
#include "WiFi.h"

#include "defines.h"
#include "structs.h"
#include "http.h"
#include "mode.h"
#include "gpio.h"

QueueHandle_t queue_data;

void setup() {

    Serial.begin(115200);

    queue_data = xQueueCreate(QUEUE_SIZE, sizeof(color_data_t));

    http_init(&queue_data);
    gpio_init();

    xTaskCreatePinnedToCore(led_task,   /* Function to implement the task */
                            "led_task", /* Name of the task */
                            10000,      /* Stack size in words */
                            (void *) &queue_data,       /* Task input parameter */
                            0,          /* Priority of the task */
                            NULL,       /* Task handle. */
                            0);  /* Core where the task should run */
    Serial.println("led task created...");
}


void loop() {
    server.handleClient(); //Handling of incoming requests
}

