#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "math.h"
#define Tag "Dice"

int dice_role()
{
  int random = esp_random();
  int positiveNumber = abs(random);
  int diceNumber = (positiveNumber % 6) + 1;
  return diceNumber;
}

void app_main(void)
{
  while (1)
  {
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    ESP_LOGI(Tag, "Random number %d", dice_role());
  }
}
