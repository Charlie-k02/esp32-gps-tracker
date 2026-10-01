# Hardware Description

Status: Draft — identification in progress
Evidence: photographs of the available hardware.

## Hardware inventory

| ID | Item | Observed identification |
|----|------|-------------------------|
| HW-01 | Microcontroller module | ESP32-S3-WROOM-1, N16R8 marking |
| HW-02 | Development board | Exact manufacturer and revision to be confirmed |
| HW-03 | Terminal breakout board | Freenove ESP32/ESP32-S3 breakout board, v1.2 |
| HW-04 | GPS receiver board | Module marked NEO-6M-0-000; carrier board unidentified |
| HW-05 | Display | 1.28-inch IPS, 240 × 240, GC9A01, 4-wire SPI |

## Power supply

The prototype is intended to operate from USB power.
Peripheral supply voltages and wiring have not yet been verified.

## Open verification items

- Identify GPS header pin labels and carrier-board supply requirements.
- Confirm GPS antenna availability and connection.
- Identify display header pin labels and supply requirements.
- Record the actual wiring and selected ESP32-S3 GPIOs.
- Verify the development-board pinout against its documentation.

## Wiring status

No verified wiring diagram has been established yet.

## LIM-001 — GPS antenna unavailable

No external GPS antenna is currently available.

Real-position acquisition remains unverified. UART communication
and no-fix handling can be tested independently.

Any simulated coordinates used for MQTT or web-interface testing
must be explicitly labelled as test data. These tests do not
validate satellite reception or positioning accuracy.

## Display wiring

Status: assembled; functional verification pending.

| Display pin | ESP32-S3 connection | Function |
|-------------|--------------------|----------|
| GND | GND | Common ground |
| VCC | 3V3 | Display power |
| SCL | GPIO12 | SPI clock |
| SDA | GPIO11 | SPI MOSI |
| RES | Not connected | Use the module's onboard reset circuit |
| DC | GPIO9 | Command/data selection |
| CS | GPIO10 | Chip select |
| BLK | 3V3 | Backlight permanently enabled |

The GPS carrier board is also powered from 3V3.
Its wiring has been checked by the developer; UART communication
has not yet been verified during this development session.