#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static TaskHandle_t receiverHandler = NULL; // Creating handler for the receiver

void sender(void *param)
{
  while (true)
  {
    xTaskNotifyGive(receiverHandler); // For giving notification to the receiver
    xTaskNotifyGive(receiverHandler);
    xTaskNotifyGive(receiverHandler);
    xTaskNotifyGive(receiverHandler);
    xTaskNotifyGive(receiverHandler);
    xTaskNotifyGive(receiverHandler);
    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}

void receiver(void *param)
{
  while (true)
  {
    // ulTaskNotifyTake(pdFALSE, portMAX_DELAY); // For taking notification from sender
    // int count = ulTaskNotifyTake(pdFALSE, portMAX_DELAY); // For counting and showing of triggered notification  from sender
    int count = ulTaskNotifyTake(pdTRUE, portMAX_DELAY); // For counting of triggered notification  from sender
    printf("Received notification %d \n", count);
  }
}

void app_main(void)
{
  xTaskCreate(&receiver, "sender", 2048, NULL, 2, &receiverHandler); //task1 call function with passing parameter
  xTaskCreate(&sender, "receiver", 2048, "Task 2", 2, NULL);         //task2 call function with passing parameter
}
