#include <stdint.h>   // pour uint8_t, int32_t, etc.
#include <stddef.h>   // pour NULL
#include <stdbool.h>  // pour bool, true, false
#include "system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "SYSTEM";

void system_init(void) {
	ESP_LOGI(TAG, "SYSTEM init");
}

void system_task(void *pvParameters) {
	while (1) {
		ESP_LOGI(TAG, "SYSTEM task running");
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}
