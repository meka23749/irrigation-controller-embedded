# Requirements Specification

**Project:** Irrigation Controller — Bare-Metal ARM Firmware
**Author:** Steve Fredy Meka
**Version:** 1.0
**Date:** [enter date]

---

## 1. Purpose

This document specifies the functional and safety requirements of the irrigation
controller firmware. The controller drives a pump based on a humidity sensor, with
built-in safety behavior. The logic is hardware-independent and verified by
automated unit tests (Unity), running natively and cross-compiled for ARM Cortex-M
under QEMU.

---

## 2. Definitions

| Term | Meaning |
|---|---|
| Pump | The irrigation pump, either active (on) or inactive (off) |
| Humidity | Soil humidity in percent (0–100), from the sensor |
| Hysteresis | Two distinct thresholds (low/high) to avoid rapid pump toggling |
| Tick | One control cycle, advancing time by `elapsed_seconds` |
| Fail-safe | Safe default behavior when a fault is detected |

---

## 3. Functional requirements

| ID | Requirement | Value |
|---|---|---|
| REQ-01 | On initialization, the pump shall be inactive (safe initial state). | pump off at start |
| REQ-02 | When the pump is off and humidity is below the low threshold, the pump shall be activated. | humidity < 30 % |
| REQ-03 | When the pump is on and humidity is above the high threshold, the pump shall be deactivated. | humidity > 70 % |
| REQ-04 | Between the low and high thresholds, the pump shall keep its state (hysteresis / dead band). | 30 %–70 % |

---

## 4. Safety requirements

| ID | Requirement | Value |
|---|---|---|
| REQ-05 | On sensor error, the pump shall be forced off and its runtime reset (fail-safe). | SENSOR_ERROR → pump off |
| REQ-06 | The pump shall be stopped once its continuous runtime reaches the maximum, to prevent over-watering / flooding. | ≥ 600 s |

---

## 5. Design invariants

| ID | Requirement |
|---|---|
| REQ-07 | The low humidity threshold shall be strictly lower than the high threshold (hysteresis validity). |

---

## 6. Notes

- Thresholds and limits are defined in `src/irrigation_controller.h`
  (`HUMIDITY_LOW_THRESHOLD = 30`, `HUMIDITY_HIGH_THRESHOLD = 70`,
  `MAX_PUMP_RUNTIME_SECONDS = 600`).
- The control logic is intentionally hardware-independent (pure C), so it can be
  unit-tested on a host PC before cross-compilation to ARM Cortex-M.
- Each requirement is verified by at least one automated test — see
  [02_Traceability_Matrix.md](02_Traceability_Matrix.md).
