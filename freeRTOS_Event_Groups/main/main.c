#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/event_groups.h"

EventGroupHandle_t evtGrp;
const int gotHttp = BIT0;
const int gotBLE = BIT1;

void listenForHTTP(void *param)
{
  while (true)
  {
    xEventGroupSetBits(evtGrp, gotHttp);
    printf("got http \n");
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

void listenForBluetooth(void *param)
{
  while (true)
  {
    xEventGroupSetBits(evtGrp, gotBLE);
    printf("Got BLE \n");
    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}

void task1(void *param)
{
  while (true)
  {
    xEventGroupWaitBits(evtGrp, gotHttp | gotBLE, true, true, portMAX_DELAY);
    printf("Received from http and BLE \n");
  }
}

void app_main(void)
{
  evtGrp = xEventGroupCreate();
  xTaskCreate(&listenForHTTP, "get http", 2048, NULL, 2, NULL);       //task1 call function with passing parameter
  xTaskCreate(&listenForBluetooth, "got BLE", 2048, NULL, 1, NULL);   //task2 call function with passing parameter
  xTaskCreate(&task1, "do something with http", 2048, NULL, 1, NULL); //task2 call function with passing parameter
}
