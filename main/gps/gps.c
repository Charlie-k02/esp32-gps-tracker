/**
 * @file gps.c
 * @brief Driver applicatif GPS (NEO-6M) via UART + parsing NMEA minimal.
 *
 * Responsabilités :
 *  - Initialiser l'UART utilisé par le module GPS
 *  - Lire le flux NMEA en tâche FreeRTOS
 *  - Extraire des champs utiles (ex: $GPRMC)
 *
 * Notes :
 *  - Les coordonnées NMEA sont en format ddmm.mmmm (lat) / dddmm.mmmm (lon)
 *  - Même immobile, la position varie légèrement (jitter GPS)
 */


#include <stdint.h>   // pour uint8_t, int32_t, etc.
#include <stddef.h>   // pour NULL
#include <stdbool.h>  // pour bool, true, false
#include <string.h>

#include "driver/uart.h"
#include "esp_log.h"
#include "esp_timer.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "gps.h"
#include "gps_utils.h"




#define GPS_UART_NUM      UART_NUM_1
#define GPS_TX_PIN        43 // GPIO ESP32 -> RX du GPS
#define GPS_RX_PIN        44 // GPIO ESP32 <- TX du GPS
#define GPS_BAUDRATE      9600 // Parfois 38400 en fonction du GPS
#define GPS_BUF_SIZE      1024

static gps_fix_t s_last_fix = {0};
static SemaphoreHandle_t s_fix_mutex = NULL;

static const char *TAG = "GPS";

//Prototype interne : parsing d'une phrase $GPRMC (fonction privée du module).
static void parse_gprmc(const char *sentence);

void gps_init(void) {

	// Configuration UART classique pour NEO-6M: 9600 bauds, 8N1, pas de flow control
	uart_config_t uart_config = { .baud_rate = GPS_BAUDRATE, .data_bits =
			UART_DATA_8_BITS, .parity = UART_PARITY_DISABLE, .stop_bits =
			UART_STOP_BITS_1, .flow_ctrl = UART_HW_FLOWCTRL_DISABLE };

	// Installation de driver UART et alloue un buffer RX.
	// Pas de configuration d'events, lecture simple via uart_read_bytes().
	uart_driver_install(GPS_UART_NUM, GPS_BUF_SIZE * 2, 0, 0, NULL, 0);
	// Application de la configuration UART
	uart_param_config(GPS_UART_NUM, &uart_config);
	// Association des GPIO de l'ESP32-S3 aux signaux UART (TX, RX).
	uart_set_pin(GPS_UART_NUM, GPS_TX_PIN, GPS_RX_PIN, UART_PIN_NO_CHANGE,
			UART_PIN_NO_CHANGE);

	ESP_LOGI(TAG, "GPS UART initialized");
	s_fix_mutex = xSemaphoreCreateMutex();

}

/**
 * @brief Tâche FreeRTOS : lit le flux NMEA et déclenche le parsing sur certaines trames.
 *
 * @param pvParameters Non utilisé.
 */

void gps_task(void *pvParameters)
{
    static char line[128];
    int idx = 0;

    uint8_t c;

    while (1) {
    	// Lecture jusqu'à GPS_BUF_SIZE-1 bytes (timeout 1s).
        int len = uart_read_bytes(GPS_UART_NUM, &c, 1, pdMS_TO_TICKS(100));

        if (len > 0) {


        	// TODO: découper par lignes \n pour éviter de parser des trames tronquées.
        	if (c == '\n') {

        		line[idx] = '\0';

                // Log brut utile au debug (à réduire plus tard)

                ESP_LOGI("GPS_RAWbrut", "%s", line);

                if (strstr(line, "$GPRMC")) {

                	ESP_LOGI("GPS_RAW", "%s", line);
                    parse_gprmc(line);
                }

                idx = 0; // reset pour prochaine ligne
            }
            else if (idx < sizeof(line) - 1) {
                line[idx++] = c;
            }
        }
    }
}


/**
 * @brief Parse minimal d'une trame $GPRMC.
 *
 * Pour l'instant on récupère uniquement lat/lon bruts.
 * TODO: convertir ddmm.mmmm vers degrés décimaux et appliquer un filtre.
 */

static void parse_gprmc(const char *line)
{
	// Copie locale modifiable car strtok() altère la chaîne
    char buf[128];
    strncpy(buf, line, sizeof(buf)-1);
    buf[sizeof(buf)-1] = '\0';

    char *fields[12];
    int i = 0;

    char *token = strtok(buf, ",");

    while (token && i < 12) {
        fields[i++] = token;
        token = strtok(NULL, ",");
    }

    // On doit avoir au moins 7 champs
    if (i < 7) {
        ESP_LOGW("GPS","Trame incomplète");
        return;
    }
     // Champs $GPRMC :
     // 1: UTC time
     // 2: Status (A=valid, V=void)
     // 3: Latitude (ddmm.mmmm)
     // 4: N/S
     // 5: Longitude (dddmm.mmmm)
     // 6: E/W
    char *status = fields[2];  // A ou V
    char *lat    = fields[3];
    char *ns     = fields[4];
    char *lon    = fields[5];
    char *ew     = fields[6];

    ESP_LOGI("GPS","Status=%s", status);

    if (status[0] == 'A') {

        ESP_LOGI("GPS","FIX OK -> Lat:%s %s Lon:%s %s",lat, ns, lon, ew);
    }
    else {
        ESP_LOGW("GPS","Pas de fix GPS (status=%s)", status);
    }
}
