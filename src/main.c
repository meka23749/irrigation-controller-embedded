#include "irrigation_controller.h"

static irrigation_state_t state;

int main(void) {
    irrigation_init(&state);

    irrigation_set_humidity(&state, 20);

    for (volatile int i = 0; i < 5; i++) {
        irrigation_tick(&state, 1);
    }

    while (1) {
        if (irrigation_is_pump_active(&state)) {
        }
    }

    return 0;
}
