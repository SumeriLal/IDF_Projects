#include <stdio.h>
#include "driver/gpio.h" // driver for GPIO
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define SWITCH_PIN 15 //
#define PIN1 4        // Pin defination

void app_main(void)
{
  gpio_pad_select_gpio(SWITCH_PIN); //Selection of GPIO
  gpio_pad_select_gpio(PIN1);
  gpio_set_direction(SWITCH_PIN, GPIO_MODE_INPUT); // Mode Setting of GPIO as output
  gpio_set_direction(PIN1, GPIO_MODE_OUTPUT);      // Mode Setting of GPIO as input
  //gpio_pulldown_en(SWITCH_PIN);                    //Adding pulldown internal resistor. Switch pin must connect with 3.3v
  gpio_pullup_en(SWITCH_PIN); //Adding pullup internal resistor. Switch pin must connect with GND
  //gpio_pullup_dis(SWITCH_PIN); // For disable the internal pullup resistor

  while (1)
  {
    int level = gpio_get_level(SWITCH_PIN);
    gpio_set_level(PIN1, level);
    printf("Level Value %d\n", level);
    vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay
  }
}
