#include <stdio.h>
#include <esp_wifi.h>
#include <esp_http_client.h>
#include <nvs_flash.h>
#include <esp_system.h>
#include <esp_event.h>

void wifi_init_sta(void){
    esp_netif_init(); //Inicializando stack de red
    //Prepara las estructuras de manejo de dirección IP, DHCP, etc
    esp_event_loop_create_default(); //bucle de eventos
    //gestiona conexión, desconexión, obtención de IP, etc
    //Sin esto el sistema WiFi no procesa ni notifica eventos
    esp_netif_create_default_wifi_sta();
    //Crea una interfaz de red preconfigurada para el modo STA(cliente)
    //Esto es necesario para que el sistema sepa que vas a usar WiFi como
    //cliente y puedas gestionar las conexiones IP
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    //Crea una estructura de configuración por defecto del driver wIfI
    //Es necesario para saber como inicializarse internamente
    esp_wifi_init(&cfg); //Inicia el driver WiFi
    //Esto equivale a encender el chip WiFi con las config listas
    wifi_config_t wifi_config = {
        .sta = {
                .ssid = "MOVISTAR_78A8",
                .password = "NS2ajtQJ7TtDt9m",
        },
    };
    esp_wifi_set_mode(WIFI_MODE_STA);
    //Sin esto el módulo no sabrá como comportarse
    esp_wifi_set_config(WIFI_IF_STA,&wifi_config);
    //Indica al driver de WiFi cual es la config para el modo STA
    esp_wifi_start();//Inicia el módulo WiFi
    esp_wifi_connect();//Intentar conectarse a la red config
}

void app_main() {
    nvs_flash_init();
    wifi_init_sta(); //Conexión red WiFi
}
