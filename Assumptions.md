# 📋 Assumptions Document — Task 4: Intelligent Remote Bed Elevation Control

**Project:** Intelligent Remote Bed Elevation Control
**Author:** Mosab Saifelldin Kartoun Omda
**Date:** October 21, 2026

---

## 1. Hardware Assumptions

| # | Assumption |
|---|---|
| H-1 | The servo motor used (SG90 or equivalent) operates within a 0°–90° range sufficient to simulate real hospital bed elevation. |
| H-2 | The ESP32 microcontroller has stable WiFi connectivity to the local network running the MQTT broker. |
| H-3 | The OLED display (SSD1306, 128×64) is connected via I2C on the default SDA/SCL pins of the ESP32. |
| H-4 | Power supply to the servo motor is adequate (5V, ≥500mA) to avoid voltage drops during movement. |
| H-5 | The servo motor can reach and hold any angle between 0° and 90° reliably without mechanical backlash. |
| H-6 | LED and buzzer components are correctly wired to designated GPIO pins with appropriate resistors. |

---

## 2. Software & Network Assumptions

| # | Assumption |
|---|---|
| S-1 | The MQTT broker (`test.mosquitto.org` or local Mosquitto) is running and accessible during all demonstrations. |
| S-2 | Node-RED is installed and running on `http://127.0.0.1:1880` on the same machine used for the dashboard. |
| S-3 | The `node-red-dashboard` package is installed in the Node-RED environment. |
| S-4 | All MQTT topics are uniquely named and do not conflict with other projects using the same public broker. |
| S-5 | The public MQTT broker (`test.mosquitto.org`) is used for demonstration purposes only; a production system would use a secured, authenticated broker. |
| S-6 | Internet connectivity is available for using the public MQTT broker. |

---

## 3. Design & Functional Assumptions

| # | Assumption |
|---|---|
| D-1 | A bed angle range of 0°–90° is considered sufficient to simulate all medically relevant positions (flat, semi-reclined, upright). |
| D-2 | The predefined mode angles (Sleeping: 10°, Breathing Support: 45°, Emergency: 90°) are assumed to be clinically reasonable approximations for simulation purposes. |
| D-3 | The rate-limiting constraint (maximum 10° change per step with 15ms delay) is assumed to provide smooth enough movement for patient comfort simulation. |
| D-4 | A dosage change of more than 30° in a single command is treated as a "large movement" requiring user confirmation in the dashboard. |
| D-5 | The "automatic mode" simulates patient condition changes using a predefined sequence or random variation; it does not use real patient sensor data. |
| D-6 | The system is a simulation prototype and is not intended for actual clinical use. |

---

## 4. Safety Assumptions

| # | Assumption |
|---|---|
| SA-1 | The red LED and buzzer are sufficient indicators for safety alerts in this simulation context. |
| SA-2 | Rate limiting alone is sufficient to prevent unsafe servo movements in the prototype. |
| SA-3 | No physical emergency stop hardware is implemented; the "STOP" button on the dashboard serves this function in simulation. |

---

## 5. Scope Limitations

- This project is a **simulation prototype** and not a certified medical device.
- WiFi-based control introduces latency; in a real system, redundant communication channels would be required.
- The servo motor simulates bed movement; real implementation would require motorized actuators.
- No authentication or encryption is applied to MQTT communication in this prototype.

---

_Document Version: 1.0_
_Last Updated: October 21, 2026_
