#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

void blink_led1(void *p){
  gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
  while(1){
    gpio_set_level(GPIO_NUM_2,1);
    vTaskDelay(1000/portTICK_PERIOD_MS);
    gpio_set_level(GPIO_NUM_2,0);
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}
void saludo(void *p){
  int x = 0;
  while(1){
    printf("Hola Mundo %d\n",x);
    vTaskDelay(2000/portTICK_PERIOD_MS);
    x++;
  }
}
void app_main() {
  xTaskCreate(&blink_led1,"blink_led",2048,NULL,1,NULL);
  xTaskCreate(&saludo,"saludo",2048,NULL,1,NULL);
}
