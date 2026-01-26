#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "gps.h"
#include "mqtt_client.h"
#include "display.h"
#include "system.h"

void app_main(void)
{
    ESP_LOGI("MAIN", "System startup");

    gps_init();
    mqtt_client_init();
    display_init();
    system_init();

    xTaskCreate(gps_task, "gps_task", 4096, NULL, 5, NULL);
    xTaskCreate(mqtt_task, "mqtt_task", 4096, NULL, 5, NULL);
    xTaskCreate(display_task, "display_task", 4096, NULL, 4, NULL);
    xTaskCreate(system_task, "system_task", 4096, NULL, 3, NULL);
}
