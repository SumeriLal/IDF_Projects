#include <stdio.h>
#include "driver/gpio.h"       // driver for GPIO
#include "freertos/FreeRTOS.h" // For delay function
#include "freertos/task.h"

#define PIN 0  // Pin defination
#define PIN1 4 // Pin defination

void app_main(void)
{
  gpio_pad_select_gpio(PIN); //Selection of GPIO
  gpio_pad_select_gpio(PIN1);
  gpio_set_direction(PIN, GPIO_MODE_OUTPUT);  // Mode Setting of GPIO
  gpio_set_direction(PIN1, GPIO_MODE_OUTPUT); // Mode Setting of GPIO
  int isOn = 0;                               //State declaration
  while (1)
  {
    isOn = !isOn;               //State toggle
    gpio_set_level(PIN, !isOn); //State level setting
    gpio_set_level(PIN1, isOn);
    vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay
  }
}
