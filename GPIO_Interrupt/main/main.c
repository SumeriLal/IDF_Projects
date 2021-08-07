#include <stdio.h>
#include "driver/gpio.h"       // driver for GPIO
#include "freertos/FreeRTOS.h" // For delay function
#include "freertos/task.h"
#include "freertos/queue.h"

#define SWITCH_PIN 15 //
#define PIN1 4        // Pin defination

xQueueHandle interruptQueue;

static void IRAM_ATTR gpio_isr_handler(void *args)
{
  int pinNumber = (int)args;
  xQueueSendFromISR(interruptQueue, pinNumber, NULL);
}

void buttonPushedTask(void *params)
{
  int pinNumber, count = 0;
  while (true)
  {
    if (xQueueReceive(interruptQueue, &pinNumber, portMAX_DELAY))
    {
      printf("GPIO %d\n", pinNumber);
      printf("Pressed times %d\n", count++);
      printf("State%d\n", gpio_get_level(SWITCH_PIN));
    }
  }
}

void app_main(void)
{
  gpio_pad_select_gpio(SWITCH_PIN); //Selection of GPIO
  gpio_pad_select_gpio(PIN1);
  gpio_set_direction(SWITCH_PIN, GPIO_MODE_INPUT);   // Mode Setting of GPIO as output
  gpio_set_direction(PIN1, GPIO_MODE_OUTPUT);        // Mode Setting of GPIO as input
  gpio_pulldown_en(SWITCH_PIN);                      //Adding pulldown internal resistor. Switch pin must connect with 3.3v
  gpio_pullup_dis(SWITCH_PIN);                       // For disable the internal pullup resistor
  gpio_set_intr_type(SWITCH_PIN, GPIO_INTR_POSEDGE); // Set interrupt for positive edge.

  interruptQueue = xQueueCreate(10, sizeof(int));
  xTaskCreate(buttonPushedTask, "buttonPushedTask", 3072, NULL, 2, NULL);
  gpio_install_isr_service(0);                                            //install the interrup service rutein for service 0
  gpio_isr_handler_add(SWITCH_PIN, gpio_isr_handler, (void *)SWITCH_PIN); // Adding the ISR handler with switch pin.
}
