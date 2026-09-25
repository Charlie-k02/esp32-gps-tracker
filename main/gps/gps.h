
#pragma once
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    bool valid;
    double lat;
    double lon;
    int64_t timestamp_ms;
} gps_fix_t;

void gps_init(void);
void gps_task(void *arg);
gps_fix_t gps_get_last_fix(void);
