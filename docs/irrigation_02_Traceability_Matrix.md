# Requirement ↔ Test Traceability Matrix

This matrix links each requirement to the automated Unity test that verifies it.
It applies, to a bare-metal C firmware, the same requirement-to-test traceability
principle used by DOORS (requirements) and XRAY (test management).

---

## Traceability matrix

| Requirement | Description | Verifying test (Unity) | Status |
|---|---|---|---|
| REQ-01 | Pump inactive at initialization | `test_initial_state_pump_inactive` | ✅ Verified |
| REQ-02 | Low humidity activates pump | `test_low_humidity_activates_pump` | ✅ Verified |
| REQ-03 | High humidity deactivates pump | `test_high_humidity_deactivates_pump` | ✅ Verified |
| REQ-04 | Hysteresis (pump keeps its state between thresholds) | `test_pump_stays_off_between_thresholds` | ⚠️ Partially verified: "stays off" is tested, "stays on" is not (a mutation removing the hysteresis passes all tests) |
| REQ-05 | Sensor error forces pump off (fail-safe) | `test_sensor_error_forces_pump_off` | ✅ Verified |
| REQ-06 | Pump stops after max runtime (anti-flooding) | `test_pump_stops_after_max_runtime` | ⚠️ Verified as written, but the requirement is incomplete: the pump restarts on the next tick (3,595 s on in a simulated hour of dry soil) |
| REQ-07 | Low threshold < high threshold (invariant) | `test_thresholds_are_correctly_ordered` | ✅ Verified |

---

## Coverage summary

- **7 requirements, each linked to at least one test.** All tests pass, natively.
- **5 requirements fully verified**, 2 with known gaps (REQ-04, REQ-06), see
  [Known Limitations](../README.md#known-limitations).
- The QEMU step in CI only shows that the firmware builds and boots; it does not run the
  tests on the target.

---

## Notes on REQ-07 (regression story)

`test_thresholds_are_correctly_ordered` was added after a commit accidentally
swapped `HUMIDITY_LOW_THRESHOLD` and `HUMIDITY_HIGH_THRESHOLD`. The existing tests
did not catch it (they only checked extreme values). This new test explicitly
verifies the design invariant `LOW < HIGH` and reliably detects the fault —
a concrete example of improving test coverage in response to a discovered bug.
