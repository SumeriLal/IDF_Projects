#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <string.h>

void callingFunk()
{
  char buffer[30];
  memset(buffer, 'x', sizeof(buffer));
  buffer[29] = 0;
  printf("Buffer is: %s\n", buffer);
  for (int i = 0; i < 30; i++)
  {
    int num1 = (rand() % 5) + 1;
    int known = 100;
    printf("Random Number: %d\n", known / num1);
  }
}

void task1(void *param)
{
  callingFunk();
  vTaskDelete(NULL);
}

void app_main(void)
{
  xTaskCreate(&task1, "Task 1", 2048, NULL, 1, NULL); //task2 call function with passing parameter
}
