#ifndef LED_STRIP_SERVER_ESP32_GPIO_H
#define LED_STRIP_SERVER_ESP32_GPIO_H

#include "Arduino.h"
#include "defines.h"

extern void gpio_init();
extern void pwm_write(uint8_t gpio, uint8_t value);

#endif //LED_STRIP_SERVER_ESP32_GPIO_H
