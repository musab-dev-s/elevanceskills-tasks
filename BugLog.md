# 🐛 Bug Log — Task 4: Intelligent Remote Bed Elevation Control

**Project:** Intelligent Remote Bed Elevation Control
**Author:** Mosab Saifelldin Kartoun Omda
**Date Range:** [Start Date] – October 21, 2026

---

## Bug Tracking Table

| Bug ID | Date | Severity | Component | Description | Root Cause | Fix Applied | Status |
|--------|------|----------|-----------|-------------|------------|-------------|--------|
| BUG-001 | [Date] | Medium | Node-RED Flow | Dashboard widgets (slider, buttons, gauge) appeared 3 times instead of once | Flow was imported twice, creating 3 duplicate tabs all pointing to the same `grp_doc` and `grp_pump` dashboard groups | Deleted the 2 duplicate "Medication Dosage" tabs (IDs: `6ebfe92c049bcb9c` and `d895c5df7490e6d0`) from Node-RED editor and redeployed | ✅ Resolved |
| BUG-002 | [Date] | High | ESP32 Firmware | Servo motor jerks abruptly when large angle change is sent | No rate-limiting logic implemented; target angle applied instantly | Added step-by-step movement loop with 15ms delay per degree to smooth transitions | ✅ Resolved |
| BUG-003 | [Date] | Low | MQTT | MQTT connection drops intermittently after ~10 minutes | Client ID conflict when multiple devices connect with same ID | Added unique client ID using ESP32 MAC address suffix | ✅ Resolved |
| BUG-004 | [Date] | Medium | Node-RED | Slider sends continuous MQTT messages while dragging, causing servo jitter | Node-RED slider triggers `msg` on every pixel of drag movement | Added `delay` node (300ms) and `rbe` (Report by Exception) node to throttle messages | ✅ Resolved |
| BUG-005 | [Date] | Low | Dashboard | OLED display shows stale angle value after WiFi reconnect | OLED not refreshed on MQTT reconnect event | Added reconnect callback to re-publish current angle to OLED topic | ✅ Resolved |
| BUG-006 | [Date] | Medium | ESP32 Firmware | Auto mode conflicts with manual slider control | Both manual and auto tasks updating servo simultaneously | Implemented mutex flag `isAutoMode`; manual control disabled when auto mode is active | ✅ Resolved |
| BUG-007 | [Date] | Low | Node-RED | Predefined mode buttons not reflecting current angle on gauge | Gauge subscribes to `hospital/bed/angle/current` but predefined modes publish to `hospital/bed/mode` | Added function node to translate mode to angle value and publish to current angle topic | ✅ Resolved |

---

## Bug Severity Scale

| Level | Description |
|-------|-------------|
| 🔴 Critical | System crash or data loss |
| 🟠 High | Major feature broken |
| 🟡 Medium | Feature partially broken, workaround exists |
| 🟢 Low | Minor visual or UX issue |

---

## Summary

| Total Bugs Found | Resolved | Open |
|---|---|---|
| 7 | 7 | 0 |

---

_Last Updated: October 21, 2026_
