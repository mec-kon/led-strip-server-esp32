#ifndef ESP32_STRUCTS_H
#define ESP32_STRUCTS_H

#include "Arduino.h"
#include "defines.h"

typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;

}color_t;

typedef struct {
    color_t color_array[DATA_SIZE];
    uint8_t time;
    char mode[15];
    uint8_t number_of_colors;

}color_data_t;

#endif //ESP32_STRUCTS_H
