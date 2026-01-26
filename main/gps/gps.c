#include "gps.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "GPS";

void gps_init(void)
{
    ESP_LOGI(TAG, "GPS init");
}

void gps_task(void *pvParameters)
{
    while (1) {
        ESP_LOGI(TAG, "GPS task running");
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
