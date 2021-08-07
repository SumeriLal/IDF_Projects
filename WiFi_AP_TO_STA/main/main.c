#include <stdio.h>
#include "string.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_event_loop.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "cJSON.h"
#include "connect.h"
#include "server.h"

#define SSID CONFIG_WIFI_SSID
#define PASSWORD CONFIG_WIFI_PASSWORD

#define TAG "DATA"

xSemaphoreHandle connectionSemaphore;
xSemaphoreHandle initSemaphore;

void OnConnected(void *para)
{

  while (true)
  {
    if (xSemaphoreTake(connectionSemaphore, portMAX_DELAY))
    {
      RegisterEndPoints();
    }
  }
}

void app_main()
{
  esp_log_level_set(TAG, ESP_LOG_DEBUG);
  connectionSemaphore = xSemaphoreCreateBinary();
  initSemaphore = xSemaphoreCreateBinary();

  xTaskCreate(&wifiInit, "init comms", 1024 * 3, NULL, 10, NULL);
  xSemaphoreGive(initSemaphore);
  xTaskCreate(&OnConnected, "handel comms", 1024 * 5, NULL, 5, NULL);
}