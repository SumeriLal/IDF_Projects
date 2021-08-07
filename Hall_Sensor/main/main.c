#include <stdio.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"

uint32_t hall_sens_read();
void app_main(void)
{
  while (1)
  {
    printf("Hall Sensitivity: %d\n", hall_sens_read());
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }

  printf("Hello world!\n");
}
