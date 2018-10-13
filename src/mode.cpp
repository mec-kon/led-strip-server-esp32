#include "Arduino.h"

#include "mode.h"
#include "structs.h"

void one_color(color_data_t *color_data) {
    color_t color = color_data->color_array[0];
    pwm_write(GPIO_RED, color.red);
    pwm_write(GPIO_GREEN, color.green);
    pwm_write(GPIO_BLUE, color.blue);
}

void fade(color_data_t *color_data, QueueHandle_t *queue_data) {
    uint8_t i = 0;
    color_t color1;
    color_t color2;

    while (uxQueueMessagesWaiting(*queue_data) == 0) {
        if (i == color_data->number_of_colors - 1) {
            color1 = color_data->color_array[color_data->number_of_colors - 1];
            color2 = color_data->color_array[0];
        }
        else {
            if (i == color_data->number_of_colors) {
                i = 0;
            }
            color1 = color_data->color_array[i];
            color2 = color_data->color_array[i + 1];
        }
        i++;
        while (color1.red != color2.red || color1.blue != color2.blue || color1.green != color2.green) {
            if (uxQueueMessagesWaiting(*queue_data) != 0) {
                break;
            }

            if (color1.red > color2.red) {
                color1.red--;
            }
            else if (color1.red < color2.red) {
                color1.red++;
            }

            if (color1.green > color2.green) {
                color1.green--;
            }
            else if (color1.green < color2.green) {
                color1.green++;
            }

            if (color1.blue > color2.blue) {
                color1.blue--;
            }
            else if (color1.blue < color2.blue) {
                color1.blue++;
            }

            pwm_write(GPIO_RED, color1.red);
            pwm_write(GPIO_GREEN, color1.green);
            pwm_write(GPIO_BLUE, color1.blue);

            delay(color_data->time);
        }
    }
}

void changing_colors(color_data_t *color_data, QueueHandle_t *queue_data) {
    uint8_t i = 0;
    color_t color;

    while (uxQueueMessagesWaiting(*queue_data) == 0) {

        if (i == color_data->number_of_colors) {
            i = 0;
        }
        color = color_data->color_array[i];
        i++;

        pwm_write(GPIO_RED, color.red);
        pwm_write(GPIO_GREEN, color.green);
        pwm_write(GPIO_BLUE, color.blue);

        delay(color_data->time * 100);
    }
}

void led_task(void *parameters) {

    QueueHandle_t *queue_data = (QueueHandle_t *) parameters;
    color_data_t color_data;

    while (true) {
        xQueueReceive(*queue_data, &color_data, portMAX_DELAY);
        Serial.print("queue received : ");
        Serial.println(color_data.mode);

        if (strcmp(color_data.mode, "fade") == 0) {
            fade(&color_data, queue_data);
        }
        else if (strcmp(color_data.mode, "changingColors") == 0) {
            changing_colors(&color_data, queue_data);
        }
        else {
            one_color(&color_data);
        }
    }
}