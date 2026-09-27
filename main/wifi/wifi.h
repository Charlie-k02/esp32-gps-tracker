
#pragma once
#include <stdbool.h>

/**
 * @brief Initialise le Wi-Fi en mode STA et se connecte.
 * @return true si connecté et IP obtenue, sinon false (après timeout).
 */
bool wifi_init_sta_and_wait(void);
