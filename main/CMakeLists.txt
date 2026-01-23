idf_component_register(
    SRCS
        "main.c"
        "gps/gps.c"
        "mqtt/mqtt_client.c"
        "display/display.c"
        "system/system.c"
    INCLUDE_DIRS
        "."
        "gps"
        "mqtt"
        "display"
        "system"
)
idf_component_register(SRCS "esp32-gps-tracker.c"
                    INCLUDE_DIRS ".")
