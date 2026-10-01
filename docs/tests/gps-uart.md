# TC-GPS-001 — Raw UART reception

Status: Not executed

## Objective
Verify that the ESP32 receives readable NMEA sentences from the GPS.

## Configuration
- ESP32-S3 UART1: 9600 baud, 8 data bits, no parity, 1 stop bit.
- ESP32 TX: GPIO17; ESP32 RX: GPIO18.
- GPS antenna unavailable.
- Wi-Fi, MQTT, display and NMEA parsing disabled for this test.

## Procedure
Run the test firmware and observe serial logs for 30 seconds.

## Acceptance criteria
Repeated readable lines starting with "$" are received.
The application does not crash or restart during observation.

A valid position is not required. This test does not validate
NMEA checksums, parsing or positioning accuracy.

## Results
Firmware commit and local changes: pending.
Observed behaviour: pending.
Evidence: pending.
Verdict: pending.