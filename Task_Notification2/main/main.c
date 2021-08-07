#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static TaskHandle_t receiverHandler = NULL; // Creating handler for the receiver

void sender(void *param)
{
  while (true)
  {
    xTaskNotify(receiverHandler, (1 << 0), eSetBits); // For giving notification to the receiver with value (1<<0)
    xTaskNotify(receiverHandler, (1 << 1), eSetBits);
    xTaskNotify(receiverHandler, (1 << 2), eSetBits);
    xTaskNotify(receiverHandler, (1 << 3), eSetBits);
    vTaskDelay(3000 / portTICK_PERIOD_MS);
  }
}

void receiver(void *param)
{
  uint state;
  while (true)
  {
    xTaskNotifyWait(0xffffff, 0, &state, portMAX_DELAY);
    printf("Received notification %d \n", state);
  }
}

void app_main(void)
{
  xTaskCreate(&receiver, "sender", 2048, NULL, 2, &receiverHandler); //task1 call function with passing parameter
  xTaskCreate(&sender, "receiver", 2048, "Task 2", 2, NULL);         //task2 call function with passing parameter
}
