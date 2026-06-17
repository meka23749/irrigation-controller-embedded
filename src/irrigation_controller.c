#include "irrigation_controller.h"

void irrigation_init(irrigation_state_t* state) {
    state->humidity_percent = 50;
    state->sensor_status = SENSOR_OK;
    state->pump_active = false;
    state->pump_runtime_seconds = 0;
}

void irrigation_set_humidity(irrigation_state_t* state, uint8_t humidity) {
    state->humidity_percent = humidity;
}

void irrigation_set_sensor_status(irrigation_state_t* state, sensor_status_t status) {
    state->sensor_status = status;
}

void irrigation_tick(irrigation_state_t* state, uint32_t elapsed_seconds) {

    if (state->sensor_status == SENSOR_ERROR) {
        state->pump_active = false;
        state->pump_runtime_seconds = 0;
        return;
    }

    if (state->pump_active) {
        state->pump_runtime_seconds += elapsed_seconds;
    }

    if (state->pump_runtime_seconds >= MAX_PUMP_RUNTIME_SECONDS) {
        state->pump_active = false;
        state->pump_runtime_seconds = 0;
        return;
    }

    if (!state->pump_active && state->humidity_percent < HUMIDITY_LOW_THRESHOLD) {
        state->pump_active = true;
        state->pump_runtime_seconds = 0;
    }

    if (state->pump_active && state->humidity_percent > HUMIDITY_HIGH_THRESHOLD) {
        state->pump_active = false;
        state->pump_runtime_seconds = 0;
    }
}

bool irrigation_is_pump_active(const irrigation_state_t* state) {
    return state->pump_active;
}
