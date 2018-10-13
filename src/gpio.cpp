#include "gpio.h"

int freq = 5000;
uint8_t resolution = 8;
uint8_t led_channel_red = 0;
uint8_t led_channel_green = 1;
uint8_t led_channel_blue = 2;

void gpio_init(){
    ledcSetup(led_channel_blue, freq, resolution);
    ledcAttachPin(GPIO_BLUE, led_channel_blue);
}

void pwm_write(uint8_t gpio, uint8_t value){

    if(gpio == GPIO_RED){
        ledcWrite(led_channel_red, value);
    }
    else if(gpio == GPIO_GREEN){
        ledcWrite(led_channel_green, value);
    }
    else {
        ledcWrite(led_channel_blue, value);
    }

}