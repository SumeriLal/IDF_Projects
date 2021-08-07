#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

xSemaphoreHandle binSemaphore; // Creating binary semaphore object

void writeToBus(char *message)
{
  printf(message);
}

void listenForHTTP(void *param)
{
  while (true)
  {
    printf("Received http message \n");
    xSemaphoreGive(binSemaphore); // Returning binary semaphore to the object
    printf("Processed http message\n");
    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}

void Task2(void *param)
{
  while (true)
  {
    printf("Doing something with http \n");
    xSemaphoreTake(binSemaphore, portMAX_DELAY); // Taking binary semaphore to the object
  }
}

void app_main(void)
{
  binSemaphore = xSemaphoreCreateBinary();
  xTaskCreate(&listenForHTTP, "get http", 2048, NULL, 2, NULL);       //task1 call function with passing parameter
  xTaskCreate(&Task2, "do something with http", 2048, NULL, 1, NULL); //task2 call function with passing parameter
}
