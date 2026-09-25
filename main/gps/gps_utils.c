
#include <stdint.h>   // pour uint8_t, int32_t, etc.
#include <stddef.h>   // pour NULL
#include <stdbool.h>  // pour bool, true, false
#include "gps_utils.h"
#include <stdlib.h>   // atof
#include <string.h>   // strncpy

double gps_nmea_to_decimal(const char *nmea, int is_lon)
{
    if (!nmea || nmea[0] == '\0') return 0.0;

    int deg_len = is_lon ? 3 : 2;

    char deg_buf[4] = {0};          // suffisant pour "ddd"
    strncpy(deg_buf, nmea, deg_len);

    double deg = atof(deg_buf);
    double minutes = atof(nmea + deg_len);

    return deg + (minutes / 60.0);
}

double gps_apply_hemisphere(double value, char hemi)
{
    if (hemi == 'S' || hemi == 'W') return -value;
    return value;
}