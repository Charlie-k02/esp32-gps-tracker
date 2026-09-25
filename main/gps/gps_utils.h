
#pragma once

/**
 * @brief Convertit un champ NMEA ddmm.mmmm (lat) ou dddmm.mmmm (lon) en degrés décimaux.
 * @param nmea string NMEA (ex: "4807.038")
 * @param is_lon 0 pour latitude, 1 pour longitude
 * @return degrés décimaux (positif, sans signe hémisphère)
 */
double gps_nmea_to_decimal(const char *nmea, int is_lon);

/**
 * @brief Applique le signe selon l'hémisphère.
 * @param value valeur positive en degrés décimaux
 * @param hemi 'N','S','E','W'
 * @return valeur signée
 */
double gps_apply_hemisphere(double value, char hemi);
