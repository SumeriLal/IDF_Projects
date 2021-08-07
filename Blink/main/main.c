#include <stdio.h>

#include "esp_log.h"

void app_main(void)
{
  esp_log_level_set("LOG", ESP_LOG_INFO);
  ESP_LOGE("LOG", "This is an error");
  ESP_LOGW("LOG", "This is a warning");
  ESP_LOGI("LOG", "This is an information");
  ESP_LOGD("LOG", "This is an Debug Statement");
  ESP_LOGV("LOG", "This is an Debug Verbose");
  int number = 0;
  ESP_LOGE("Tag2", "This is an error %d", number++);
  ESP_LOGW("Tag2", "This is a warning %d", number++);
  ESP_LOGI("Tag2", "This is an information %d", number++);
  ESP_LOGD("Tag2", "This is an Debug Statement %d", number++);
  ESP_LOGV("Tag2", "This is an Debug Verbose %d", number++);

  printf("How are you ?\n");
}
