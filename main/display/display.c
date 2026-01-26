#include "display.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "DISPLAY";

void display_init(void)
{
    ESP_LOGI(TAG, "DISPLAY init");
}

void display_task(void *pvParameters)
{
    while (1) {
        ESP_LOGI(TAG, "DISPLAY task running");
        vTaskDelay(pdMS_TO_TICKS(2500));
    }
}
