# Project Scope — GPS Tracker

Status: draft
Date: 2026-10-01

## Objective
Develop an educational prototype for tracking an object’s location,
featuring GPS data acquisition, MQTT transmission over Wi-Fi, and viewing
on a web map accessible from a smartphone.

## Intended Use
USB-powered laboratory prototype, within range of a Wi-Fi network.
GPS reception may require placing the antenna outdoors
or near a window.

Not intended for medical, emergency, or personal safety use.

## Hardware
- ESP32-S3-WROOM-1: development board part number to be specified.
- NEO-6M GPS: adapter board part number to be specified.
- SPI display: controller and specifications to be identified.
- USB power supply.

## Scope of the Initial Demonstration
- Acquire and interpret GPS data.
- Determine the validity and recency of the position.
- Transmit data via MQTT over Wi-Fi.
- Display the latest position on a web map.
- Report an unavailable or outdated position.

The local display is an extension to be added after this workflow has been validated.

## Proposed Success Criteria
- A valid GPS position is received under appropriate reception conditions.
- The coordinates received via MQTT match the acquired coordinates.
- The web page displays these coordinates.
- A loss of GPS data does not result in an old position
  being displayed as the current one.
- Tests are documented with observed results and anomalies.



Timeframes and tolerances will be specified in the requirements.

## Out of Scope
Battery, cellular network, trip history, and medical use.

## Documentation Approach
Educational project inspired by practices associated with ISO 13485
and IEC 62304, with no claim of compliance or certification.
The complete normative texts are not available for this project.

## Initial Status
The firmware was compiled using ESP-IDF v5.5.2 for ESP32-S3.
GPS tests were conducted previously.
The full functionality of the current version has yet to be verified.

