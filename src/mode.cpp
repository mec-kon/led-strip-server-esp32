#include "Arduino.h"

#include "mode.h"
#include "structs.h"

void led_task(void *parameters){

    queue_data_t *queue_data = (queue_data_t *) parameters;
    color_data_t color_data;

    while(true){
        xQueueReceive(queue_data->queue, &color_data, portMAX_DELAY);
        Serial.println("queue received");
    }
}