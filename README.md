# ESP32 GPS Tracker

Embedded GPS tracker based on ESP32 using ESP-IDF and FreeRTOS.

## Project status

Work in progress — a learning project focused on ESP-IDF, FreeRTOS and MQTT.

- Builds successfully with ESP-IDF v5.5.2 for the ESP32-S3.
- GPS functionality was tested previously; it has not yet been revalidated with the current firmware.
- Wi-Fi, MQTT and other application modules are preliminary drafts adapted from online examples. They still require review, understanding and hardware testing.
- End-to-end GPS tracking over MQTT has not yet been validated.

## Next steps

- Review and understand each module.
- Validate GPS, Wi-Fi and MQTT behaviour on hardware.
- Document the architecture, wiring and build instructions.
