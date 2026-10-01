# Software Requirements

Status: Draft
Scope: First prototype
Verification status: Not verified

| ID | Requirement | Planned verification |
|----|-------------|----------------------|
| SWR-001 | At startup, the system shall report NO_FIX until it receives a valid GPS position. | Startup test |
| SWR-002 | A GPS position shall be accepted only from a complete RMC sentence with a valid checksum, status A, and valid coordinate and hemisphere fields. Latitude shall be within [-90, 90] degrees and longitude within [-180, 180] degrees. | Parser tests with valid and invalid sentences |
| SWR-003 | On acceptance, the system shall store the coordinates and their reception time using a monotonic clock. | Data update test |
| SWR-004 | The position shall become STALE when its age exceeds 5 seconds or a checksum-valid RMC sentence reports status V. If no valid position has ever been received, the state shall remain NO_FIX. | Timeout and fix-loss tests |
| SWR-005 | Reception of a new valid position shall set the state to VALID. | Fix recovery test |
| SWR-006 | GPS acquisition shall continue while Wi-Fi or MQTT is disconnected. | Network disconnection test |
| SWR-007 | While MQTT is connected, the application shall attempt to publish its latest state every 2 seconds. | Publication timing test |
| SWR-008 | The system shall retain only the latest position during a network outage. After MQTT reconnection, it shall publish the latest state at the next scheduled publication, without replaying position history. | Reconnection test |
| SWR-009 | Published data shall distinguish NO_FIX, VALID and STALE. When a stored position exists, the message shall include its coordinates and age. | Payload inspection |
| SWR-010 | User interfaces shall distinguish a current position from a stale position and shall not display a position before one is available. | Display and web-interface tests |
| SWR-011 | Simulated position data shall be explicitly identified as test data in messages and user interfaces. | Simulation test |

## Timing interpretation

The 2-second publication interval is an application scheduling target,
not a guarantee of network delivery.

Reception time is measured since device startup; it is not UTC time.

## Open items

- Define measurable scheduling tolerances before timing verification.
- Define how the web interface detects a lost message stream.
- Specify the MQTT payload and connection retry policy.
- Specify accepted NMEA variants and malformed-input handling.

## Change control

Changes to these requirements shall be reviewed together with their
impact on design, implementation and tests, and recorded in Git.