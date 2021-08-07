#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_sleep.h"
#include "driver/rtc_io.h"

#define BUTTON GPIO_NUM_15
RTC_DATA_ATTR int timesWokenUp = 0;

void app_main(void)
{
  rtc_gpio_deinit(BUTTON);

  //General GPIO functions using the pin
  rtc_gpio_pullup_en(BUTTON);
  rtc_gpio_pulldown_dis(BUTTON);
  esp_sleep_enable_ext0_wakeup(BUTTON, 0);
  printf("Going to sleep. Woken Up %d\n", timesWokenUp++);
  esp_deep_sleep_start();
}
