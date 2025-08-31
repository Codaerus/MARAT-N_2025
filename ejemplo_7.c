#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

void app_main() {
    gpio_config_t io_conf = {
      .pin_bit_mask = (1ULL<<GPIO_NUM_2),
      .mode = GPIO_MODE_INPUT,
      .pull_down_en = GPIO_PULLUP_ENABLE
    };

    gpio_config(&io_conf);

    while(1){
      if(gpio_get_level(GPIO_NUM_2) == 1)
        {
          printf("Se presiono el pulsador\n");
          vTaskDelay(200/portTICK_PERIOD_MS);
        }
    }
}
