#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_heap_caps.h"
#include "esp_log.h"
#define TAG "Memory"

void print_memory()
{
  ESP_LOGI(TAG, "stack %d, total ram %d, internal memory %d, external memory %d\n",
           uxTaskGetStackHighWaterMark(NULL), heap_caps_get_free_size(MALLOC_CAP_8BIT),
           heap_caps_get_free_size(MALLOC_CAP_INTERNAL), heap_caps_get_free_size(MALLOC_CAP_SPIRAM));
}

void app_main(void)
{
  print_memory();
  printf("Hello world!\n");
}
