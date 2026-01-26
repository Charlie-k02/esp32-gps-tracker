#include "mqtt_client.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "MQTT_CLIENT";

void mqtt_client_init(void)
{
    ESP_LOGI(TAG, "MQTT_CLIENT init");
}

void mqtt_client_task(void *pvParameters)
{
    while (1) {
        ESP_LOGI(TAG, "MQTT_CLIENT task running");
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
