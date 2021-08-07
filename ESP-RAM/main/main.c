#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_heap_caps.h"
#include "esp_log.h"
#define TAG "Memory"

void aTask(void *param)
{

  int stackmem = uxTaskGetStackHighWaterMark(NULL);
  ESP_LOGI(TAG, "free = %d\n", stackmem);
  char buffer[6000];
  memset(&buffer, 1, sizeof(buffer));
  while (true)
    vTaskDelay(1000);
}

void app_main(void)
{
  ESP_LOGI(TAG, "xPortGetFreeHeapSize %dk = DRAM", xPortGetFreeHeapSize());
  int Dram = heap_caps_get_free_size(MALLOC_CAP_8BIT);
  int Iram = heap_caps_get_free_size(MALLOC_CAP_32BIT) - heap_caps_get_free_size(MALLOC_CAP_8BIT);
  ESP_LOGI(TAG, "DRAM \t\t %d", Dram);
  ESP_LOGI(TAG, "IRAM \t\t %d", Iram);
  int free = heap_caps_get_largest_free_block(MALLOC_CAP_8BIT);
  printf("Variables\n");
  ESP_LOGI(TAG, "free = %d\n", free);
  xTaskCreate(&aTask, "a Task", 8000, NULL, 1, NULL);
}
