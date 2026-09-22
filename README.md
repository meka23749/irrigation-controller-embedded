# Irrigation Controller: Embedded C, ARM Cross-Compilation, CI-CD

Bare-metal C firmware for automated irrigation control, built with a full
embedded DevOps pipeline: ARM cross-compilation, unit testing, QEMU
hardware simulation, and CI/CD automation.

## What it does

The firmware reads a simulated soil humidity sensor and controls a water
pump according to simple safety rules:

- Humidity below 30% -> activate pump
- Humidity above 70% -> deactivate pump
- Sensor error -> force pump off (fail-safe)
- Maximum continuous runtime: 10 minutes (safety timer)

## Architecture

```text
src/
├── irrigation_controller.c    # Business logic (pure C, hardware-independent)
├── main.c                     # Application entry point
├── startup.c                  # Cortex-M startup code, interrupt vector table
└── linker.ld                  # Memory layout for QEMU lm3s6965evb target

tests/
└── test_irrigation_controller.c
    # Unity unit tests
```

## Build and Test (Native, Fast Feedback Loop)

```bash
gcc -I src -I tests/unity \
    tests/test_irrigation_controller.c \
    src/irrigation_controller.c \
    tests/unity/unity.c \
    -o test_native

./test_native
```

## Cross-Compile for ARM Cortex-M

```bash
arm-none-eabi-gcc \
    -mcpu=cortex-m4 \
    -mthumb \
    -nostdlib \
    -T src/linker.ld \
    src/startup.c \
    src/main.c \
    src/irrigation_controller.c \
    -o firmware.elf
```

## Run in QEMU 

```bash
qemu-system-arm \
    -M lm3s6965evb \
    -nographic \
    -kernel firmware.elf
```
## CI/CD pipeline

Every push triggers two GitHub Actions jobs:

1. **Native unit tests** - fast feedback, runs on every commit
2. **ARM cross-compile + QEMU validation** - builds the real target firmware
   and verifies it boots without crashing

## Notes

Two real issues were found and fixed during development - documented in
[CHANGELOG.md](CHANGELOG.md) and visible in the commit history:

- A **HardFault crash** caused by an incorrect FLASH origin address in the
  linker script, diagnosed using \objdump\ and QEMU instruction tracing.
- A **logic bug** where humidity thresholds were accidentally swapped.
  The existing test suite did not catch it; a new sanity-check test
  (\	est_thresholds_are_correctly_ordered\) was added specifically to
  catch this class of configuration error, which then revealed and
  confirmed the bug for the fix.

## Requirements & Traceability

The firmware is developed with an explicit engineering approach: each behavior is
specified as a numbered requirement, and every requirement is verified by at least
one automated test.

- [Requirements Specification](docs/01_Requirements.md) — functional & safety requirements
- [Traceability Matrix](docs/02_Traceability_Matrix.md) — requirement ↔ test mapping (7/7 covered)

This mirrors the requirement-management and traceability practices (DOORS / XRAY)
used in regulated industries (ISO 26262, EN 50128, DO-178C).

## Tech stack

- C (bare-metal, no OS)
- ARM GNU Toolchain (\arm-none-eabi-gcc\)
- Unity test framework
- QEMU (ARM Cortex-M emulation)
- GitHub Actions CI/CD

## Author

Steve Meka
