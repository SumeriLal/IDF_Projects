#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

void app_main(void)
{
  while (true)
  {
    esp_log_level_set("LOG", ESP_LOG_VERBOSE);
    ESP_LOGE("LOG", "This is an error.");
    ESP_LOGW("LOG", "This is a warning");
    ESP_LOGI("LOG", "This is an information.");
    ESP_LOGD("LOG", "This is a Debug.");
    ESP_LOGV("LOG", "This is an verbose");
    printf("a printf \n");
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}
