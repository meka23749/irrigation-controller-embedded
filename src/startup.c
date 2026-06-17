#include <stdint.h>

extern int main(void);
extern uint32_t _estack;

void Reset_Handler(void) {
    main();
    while (1) {
    }
}

void Default_Handler(void) {
    while (1) {
    }
}

__attribute__((section(".isr_vector")))
void (* const isr_vector[16])(void) = {
    (void (*)(void))(&_estack),
    Reset_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    0,
    0,
    0,
    0,
    Default_Handler,
    Default_Handler,
    0,
    Default_Handler,
    Default_Handler,
};