# Requirement ↔ Test Traceability Matrix

**Project:** Irrigation Controller — Bare-Metal ARM Firmware
**Author:** Steve Fredy Meka

This matrix links each requirement to the automated Unity test that verifies it.
It applies, to a bare-metal C firmware, the same requirement-to-test traceability
principle used by DOORS (requirements) and XRAY (test management) in regulated
industries — ensuring every requirement is covered by at least one test.

---

## Traceability matrix

| Requirement | Description | Verifying test (Unity) | Status |
|---|---|---|---|
| REQ-01 | Pump inactive at initialization | `test_initial_state_pump_inactive` | ✅ Verified |
| REQ-02 | Low humidity activates pump | `test_low_humidity_activates_pump` | ✅ Verified |
| REQ-03 | High humidity deactivates pump | `test_high_humidity_deactivates_pump` | ✅ Verified |
| REQ-04 | Hysteresis (pump off between thresholds) | `test_pump_stays_off_between_thresholds` | ✅ Verified |
| REQ-05 | Sensor error forces pump off (fail-safe) | `test_sensor_error_forces_pump_off` | ✅ Verified |
| REQ-06 | Pump stops after max runtime (anti-flooding) | `test_pump_stops_after_max_runtime` | ✅ Verified |
| REQ-07 | Low threshold < high threshold (invariant) | `test_thresholds_are_correctly_ordered` | ✅ Verified |

---

## Coverage summary

- **7 requirements, 7 verifying tests — full coverage.**
- All tests pass, natively and cross-compiled for ARM Cortex-M under QEMU
  (see CI status in the README).

---

## Notes on REQ-07 (regression story)

`test_thresholds_are_correctly_ordered` was added after a commit accidentally
swapped `HUMIDITY_LOW_THRESHOLD` and `HUMIDITY_HIGH_THRESHOLD`. The existing tests
did not catch it (they only checked extreme values). This new test explicitly
verifies the design invariant `LOW < HIGH` and reliably detects the fault —
a concrete example of improving test coverage in response to a discovered bug.

> This is the same traceability principle used by DOORS + XRAY in regulated
> industries (automotive ISO 26262, railway EN 50128, aerospace DO-178C), applied
> here with lightweight open tools (Unity + Markdown).
