#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void task1(void *param)
{
  while (true)
  {
    printf("Reading temperature: %s \n", (char *)param); //Use of the pased parameter
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void task2(void *param)
{
  while (true)
  {
    printf("Reading humidity: %s \n", (char *)param);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}
void app_main(void)
{
  // xTaskCreate(&task1, "Temperature Reading", 2048, NULL, 2, NULL);               //task1 call function with passing null parameter
  // xTaskCreate(&task2, "Humidity Reading", 2048, NULL, 2, NULL);                  //task2 call function with passing null parameter
  xTaskCreate(&task1, "Temperature Reading", 2048, "Task 1", 2, NULL);             //task1 call function with passing parameter
  xTaskCreate(&task2, "Humidity Reading", 2048, "Task 2", 2, NULL);                //task2 call function with passing parameter
  xTaskCreatePinnedToCore(&task2, "Humidity reading", 2048, "Task 2", 2, NULL, 1); //task2 call function with passing parameter and selection of core in microcontroller
}

//Note: Always void vtask return null and xTask return output.
