#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_sleep.h"
#include "driver/rtc_io.h"

#define BUTTON GPIO_NUM_15
#define BUTTON1 GPIO_NUM_4
RTC_DATA_ATTR int timesWokenUp = 0;

void app_main(void)
{
  rtc_gpio_deinit(BUTTON);
  rtc_gpio_deinit(BUTTON1);
  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON);

  //General GPIO functions using the pin
  rtc_gpio_pullup_dis(BUTTON);
  rtc_gpio_pulldown_en(BUTTON);
  rtc_gpio_pullup_dis(BUTTON1);
  rtc_gpio_pulldown_en(BUTTON1);

  uint64_t mask = (1ULL << BUTTON) | (1ULL << BUTTON1);
  esp_sleep_enable_ext1_wakeup(mask, ESP_EXT1_WAKEUP_ANY_HIGH);
  printf("Going to sleep. Woken Up %d\n", timesWokenUp++);
  esp_deep_sleep_start();
}
