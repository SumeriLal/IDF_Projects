#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/touch_pad.h"

void app_main()
{
  touch_pad_init();
  touch_pad_set_voltage(TOUCH_HVOLT_2V7, TOUCH_LVOLT_0V5, TOUCH_HVOLT_ATTEN_1V);
  touch_pad_config(TOUCH_PAD_GPIO13_CHANNEL, -1);
  uint16_t val;
  while (true)
  {
    touch_pad_read(TOUCH_PAD_GPIO13_CHANNEL, &val);
    printf("Touch values: %d\n", val);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
