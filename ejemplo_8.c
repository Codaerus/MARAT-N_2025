#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

void app_main() {
    gpio_set_direction(GPIO_NUM_2,GPIO_MODE_INPUT);
    gpio_pullup_en(GPIO_NUM_2);
    gpio_set_direction(GPIO_NUM_4,GPIO_MODE_OUTPUT);
    while(1){
      int button_state = gpio_get_level(GPIO_NUM_2);
      if (button_state == 0){
        printf("Pulsador presionado\n");
        gpio_set_level(GPIO_NUM_4,1);
      }
      else{
        gpio_set_level(GPIO_NUM_4,0);
      }
      vTaskDelay(200/portTICK_PERIOD_MS);
    }
}
