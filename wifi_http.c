#include <esp_wifi.h>        //Proporciona funciones para configurar WiFi
#include <nvs_flash.h>       //Proporciona funciones de gestion en la memoria
#include <esp_system.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_event.h"
#include "esp_http_client.h"
#include <stdio.h>

#define WIFI_SSID "MOVISTAR_78A8"
#define WIFI_PASS "NS2ajtQJ7TtDt9m"

// Evento HTTP para manejar la respuesta
esp_err_t clientEvent(esp_http_client_event_t *evento) {
    switch (evento->event_id) {
        case HTTP_EVENT_ON_DATA:
            if (!esp_http_client_is_chunked_response(evento->client)) {
                printf("%.*s\n", evento->data_len, (char*)evento->data);
            }
            break;
        default:
            break;
    }
    return ESP_OK;
}

void wifi_init_sta(void){
    esp_netif_init(); //Inicializa la interfaz de red del ESP32
    esp_event_loop_create_default(); //Crea el bucle de eventos para manejar conexión wifi, desconexión, etc
    esp_netif_create_default_wifi_sta(); //Configura la interfaz como "station mode"
    
    wifi_init_config_t  cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg); //Inicializa el módulo WiFi con una configuración propocionada

    wifi_config_t wifi_config = {
        .sta = {
                    .ssid = WIFI_SSID,
                    .password = WIFI_PASS,
        },
    };

    esp_wifi_set_mode(WIFI_MODE_STA); //Configura el modo WiFi como estación (STA)
    esp_wifi_set_config(WIFI_IF_STA,&wifi_config); //Asocia la configuración de red con la interfaz WiFi
    esp_wifi_start(); //Inicia el módulo WiFi

    esp_wifi_connect(); //Intenta conectarse a la red configurada
}

void http_app_start() {
    esp_http_client_config_t clientConfig = {
        .url = "http://api.openweathermap.org/data/2.5/air_pollution?lat=-12.059314&lon=-77.033434&appid=4fff2a4791fdcdae45af625848bae3ad",
        .event_handler = clientEvent
    };

    esp_http_client_handle_t client = esp_http_client_init(&clientConfig);
    esp_err_t err = esp_http_client_perform(client);
    if (err == ESP_OK) {
        printf("HTTP request successful, status = %d\n", esp_http_client_get_status_code(client));
    } else {
        printf("HTTP request failed: %s\n", esp_err_to_name(err));
    }
    esp_http_client_cleanup(client);
}

void app_main() {
    esp_err_t ret = nvs_flash_init();
    if (ret != ESP_OK) {
        return;
    }
    wifi_init_sta(); //Llama a la función para configurar e iniciar la conexión WiFi

    // Espera simple para dar tiempo a conectar el WiFi antes de hacer la petición HTTP
    vTaskDelay(10000 / portTICK_PERIOD_MS);

    http_app_start();
}
