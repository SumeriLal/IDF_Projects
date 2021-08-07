#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

xQueueHandle queue; // Creating binary queue variable/object

void listenForHTTP(void *param)
{
  int count = 0;
  while (true)
  {
    count++;
    printf("Received http message \n");
    long ok = xQueueSend(queue, &count, 1000 / portTICK_PERIOD_MS);
    if (ok)
    {
      printf("Message added to queue \n");
    }
    else
    {
      printf("Failed to add in queue \n");
    }
    //printf("hello");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void Task2(void *param)
{
  int rxInt;
  while (true)
  {
    if (xQueueReceive(queue, &rxInt, 1000 / portTICK_PERIOD_MS))
    {
      printf("Doing something with http : %d \n", rxInt);
    }
  }
}

void app_main(void)
{
  queue = xQueueCreate(3, sizeof(int));
  xTaskCreate(&listenForHTTP, "get http", 2048, NULL, 2, NULL);       //task1 call function with passing parameter
  xTaskCreate(&Task2, "do something with http", 2048, NULL, 1, NULL); //task2 call function with passing parameter
}
