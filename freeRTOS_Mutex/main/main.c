#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

xSemaphoreHandle mutexBus; // Creating mutexBus for the semaphore

void writeToBus(char *message)
{
  printf(message);
}

void Task1(void *param)
{
  while (true)
  {
    printf("Reading Temparature\n");
    if (xSemaphoreTake(mutexBus, 1000 / portTICK_PERIOD_MS)) // Taking semaphore to mutex
    {
      writeToBus("temperature is 25c\n");
      xSemaphoreGive(mutexBus); // Returning semaphore to mutex
    }
    else
    {
      printf("Writing Temparature timed out \n");
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void Task2(void *param)
{
  while (true)
  {
    printf("Reading Humidity\n");
    if (xSemaphoreTake(mutexBus, 1000 / portTICK_PERIOD_MS))
    {
      writeToBus("humidity is 80\n");
      xSemaphoreGive(mutexBus);
    }
    else
    {
      printf("Writing humidity timed out \n");
    }
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

void app_main(void)
{
  mutexBus = xSemaphoreCreateMutex();
  xTaskCreate(&Task1, "temperature", 2048, NULL, 2, NULL); //task1 call function with passing parameter
  xTaskCreate(&Task2, "humidity", 2048, NULL, 2, NULL);    //task2 call function with passing parameter
}
