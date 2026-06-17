#ifndef IRRIGATION_CONTROLLER_H
#define IRRIGATION_CONTROLLER_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    SENSOR_OK = 0,
    SENSOR_ERROR = 1
} sensor_status_t;

typedef struct {
    uint8_t  humidity_percent;
    sensor_status_t sensor_status;
    bool     pump_active;
    uint32_t pump_runtime_seconds;
} irrigation_state_t;

#define HUMIDITY_LOW_THRESHOLD   70
#define HUMIDITY_HIGH_THRESHOLD  30
#define MAX_PUMP_RUNTIME_SECONDS 600

void irrigation_init(irrigation_state_t* state);
void irrigation_set_humidity(irrigation_state_t* state, uint8_t humidity);
void irrigation_set_sensor_status(irrigation_state_t* state, sensor_status_t status);
void irrigation_tick(irrigation_state_t* state, uint32_t elapsed_seconds);
bool irrigation_is_pump_active(const irrigation_state_t* state);

#endif

