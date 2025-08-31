#include <stdio.h>
#include <esp_intr_alloc.h>
#include <driver/adc.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>


void app_main(void)
{
    adc1_config_width(ADC_WIDTH_BIT_12);//Configura el ancho del ADC a 12 bits
    adc1_config_channel_atten(ADC1_CHANNEL_6,ADC_ATTEN_DB_11);
    adc1_config_channel_atten(ADC1_CHANNEL_4,ADC_ATTEN_DB_11);
    while(1){
        uint16_t pot1 = adc1_get_raw(ADC1_CHANNEL_6);
        uint16_t pot2 = adc1_get_raw(ADC1_CHANNEL_4);
        printf("Valor ADC: %u %u\n",pot1, pot2);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}
