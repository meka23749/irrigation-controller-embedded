# Changelog

## v1.0.0 - ARM cross-compilation with QEMU simulation

### Changes
- Implement irrigation controller logic with full unit test coverage (Unity)
- Add ARM Cortex-M bare-metal startup code and linker script
- Cross-compile firmware for ARM using arm-none-eabi-gcc
- Validate firmware execution in QEMU (lm3s6965evb)

### Bug fixed during development
Firmware crashed with HardFault (PC stuck at 0x00000000) when first
run in QEMU. Root cause: linker script used STM32-style FLASH origin
(0x08000000), but QEMU's lm3s6965evb machine maps code at 0x00000000.

Diagnosed using objdump symbol inspection and QEMU instruction tracing,
fixed by correcting the FLASH ORIGIN address and expanding the
interrupt vector table to the Cortex-M minimum of 16 entries.

### Tests
- 6/6 unit tests passing (native build)
- Firmware boots and runs correctly in QEMU (no crash, stable loop)