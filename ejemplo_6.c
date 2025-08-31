#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

void app_main() {
    gpio_config_t io_conf = {
      .pin_bit_mask = (1ULL<<GPIO_NUM_2),
      .mode = GPIO_MODE_INPUT,
      .pull_up_en = GPIO_PULLUP_ENABLE,
      .intr_type = GPIO_INTR_DISABLE
    };

    gpio_config(&io_conf);

    while(1){
      int button_state = gpio_get_level(GPIO_NUM_2);
      if (button_state == 0){
        printf("Pulsador presionado\n");
      }
      vTaskDelay(200/portTICK_PERIOD_MS);
    }
}
