# 🏥 Task 4: Intelligent Remote Bed Elevation Control

**Student Name:** Mosab Saifelldin Kartoun Omda  
**Internship Program:** ElevanceSkills IoT Internship  
**Submission Date:** October 21, 2026  
**Primary Wokwi Simulation:** [https://wokwi.com/projects/478424473823858689](https://wokwi.com/projects/478424473823858689)

---

## 📌 Project Overview

This project implements an **Intelligent Remote Bed Elevation Control System** as part of an IoT-based Smart Hospital simulation suite. It enables remote adjustment of a hospital bed's angle (0°–90°) using a Node-RED dashboard slider connected to a servo motor via an ESP32 microcontroller over HiveMQ MQTT. The system ensures patient safety through smooth transitions, predefined clinical modes (Sleeping, Breathing Support, Emergency), and automatic adjustments based on simulated patient condition.

---

## 🌐 Wokwi Projects Portfolio (All 4 Internship Tasks)

All tasks developed during the ElevanceSkills IoT Internship are publicly accessible on Wokwi:

| Task | Title | Wokwi Simulation Link |
|---|---|---|
| **Task 1** | Multi-Sensor Expansion Using FreeRTOS | [https://wokwi.com/projects/472146856163278849](https://wokwi.com/projects/472146856163278849) |
| **Task 2** | Dual-Role IoT Monitoring System | [https://wokwi.com/projects/470079753951045633](https://wokwi.com/projects/470079753951045633) |
| **Task 3** | Smart Medication Dosage Adjustment System | [https://wokwi.com/projects/478395139061374977](https://wokwi.com/projects/478395139061374977) |
| **Task 4** | Intelligent Remote Bed Elevation Control | [https://wokwi.com/projects/478424473823858689](https://wokwi.com/projects/478424473823858689) |

---

## 🎯 Objectives

- Enable remote bed angle control (0°–90°) via a dashboard slider
- Implement smooth servo motor transitions for patient comfort (non-blocking `millis()`)
- Apply safety constraints to prevent sudden large movements
- Provide predefined clinical modes:
  - 🌙 **Sleeping** (10°)
  - 🫁 **Breathing Support** (45°)
  - 🚨 **Emergency** (90° - Fast response mode)
- Support automatic angle adjustment cycling for demonstration
- Integrate real-time feedback via HiveMQ MQTT and Node-RED Dashboard

---

## 🏗️ System Architecture

```
[Node-RED Dashboard (http://localhost:1880/ui)]
        │
    (MQTT Broker - broker.hivemq.com:1883)
        │
    [ESP32 DevKit-C v4 (Wokwi)]
        │
    [SG90 Servo Motor (GPIO 18 PWM)]
```

---

## 📡 MQTT Topics

| Topic | Direction | Payload | Description |
|---|---|---|---|
| `mosab/bed/command` | Dashboard → ESP32 | `SLEEP`, `BREATHING`, `EMERGENCY`, `AUTO`, `STOP`, `0-90` | Bed control commands |
| `mosab/bed/angle` | ESP32 → Dashboard | Integer (0–90) | Real-time current servo angle (every 500ms) |
| `mosab/bed/status` | ESP32 → Dashboard | `SLEEP`, `BREATHING`, `EMERGENCY`, `AUTO`, `STOP`, `MANUAL` | System operational status |

---

## 📁 Repository Structure

```
task4-bed-elevation-control/
├── README.md
├── docs/
│   ├── TechnicalReport.pdf   <-- Full PDF report (with Wokwi links & diagrams)
│   ├── TechnicalReport.md
│   ├── BugLog.md
│   ├── Assumptions.md
│   └── Self-Attestation-Checklist.md
├── src/
│   ├── esp32_firmware/
│   │   ├── smart_bed.ino
│   │   └── diagram.json
│   └── nodered_flow/
│       └── flows_smart_bed.json
└── screenshots/
    ├── dashboard_overview.png
    ├── slider_control.png
    ├── predefined_modes.png
    ├── medication_dashboard.png
    ├── medication_confirm.png
    ├── medication_critical.png
    └── medication_oled.png
```

---

## 🚀 How to Run

### 1. Run ESP32 Simulation on Wokwi
Open [https://wokwi.com/projects/478424473823858689](https://wokwi.com/projects/478424473823858689) and press the green **Play** button.

### 2. Import Node-RED Flow
1. Open Node-RED: `http://127.0.0.1:1880`
2. Menu (top-right) → Import → Select `src/nodered_flow/flows_smart_bed.json`
3. Click **Deploy**

### 3. Open Dashboard
Navigate to `http://127.0.0.1:1880/ui` to interact with the bed controls.

---

## 👨‍💻 Author

- **Student:** Mosab Saifelldin Kartoun Omda
- **Internship Program:** ElevanceSkills IoT Internship
- **Contact:** training@elevanceskills.com

