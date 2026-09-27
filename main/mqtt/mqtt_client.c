
#include <stdint.h>   // pour uint8_t, int32_t, etc.
#include <stddef.h>   // pour NULL
#include <stdbool.h>  // pour bool, true, false

#include "tracker_mqtt.h"
#include "gps.h"

#include "esp_log.h"
#include "mqtt_client.h"
#include "esp_event.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "MQTT_CLIENT";

static esp_mqtt_client_handle_t client = NULL;

#define MQTT_BROKER_URI "mqtt://broker.hivemq.com"

/* ================= MQTT EVENT HANDLER ================= */

static void mqtt_event_handler(void *handler_args,
                               esp_event_base_t base,
                               int32_t event_id,
                               void *event_data)
{
    esp_mqtt_event_handle_t event = event_data;

    switch ((esp_mqtt_event_id_t)event_id) {

    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(TAG, "MQTT CONNECTED");
        break;

    case MQTT_EVENT_DISCONNECTED:
        ESP_LOGW(TAG, "MQTT DISCONNECTED");
        break;

    default:
        break;
    }
}

/* ================= MQTT INIT ================= */

void mqtt_client_init(void)
{
    esp_mqtt_client_config_t cfg = {
        .broker.address.uri = MQTT_BROKER_URI,
    };

    client = esp_mqtt_client_init(&cfg);

    esp_mqtt_client_register_event(
        client,
        ESP_EVENT_ANY_ID,
        mqtt_event_handler,
        NULL
    );

    esp_mqtt_client_start(client);

    ESP_LOGI(TAG, "MQTT started");
}

/* ================= MQTT TASK ================= */

void mqtt_task(void *arg)
{
    //mqtt_app_start();

    while (1) {

        gps_fix_t fix = gps_get_last_fix();

        if (fix.valid && client) {

            char payload[128];

            snprintf(payload, sizeof(payload),
                     "{\"lat\":%.6f,\"lon\":%.6f,\"ts\":%lld}",
                     fix.lat,
                     fix.lon,
                     (long long)fix.timestamp_ms);

            esp_mqtt_client_publish(
                client,
                "esp32/gps/fix",
                payload,
                0,
                1,
                0
            );

            ESP_LOGI(TAG, "Published: %s", payload);
        }

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
