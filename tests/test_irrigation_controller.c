#include "unity.h"
#include "irrigation_controller.h"

static irrigation_state_t state;

void setUp(void) {
    irrigation_init(&state);
}

void tearDown(void) {
}

void test_initial_state_pump_inactive(void) {
    TEST_ASSERT_FALSE(irrigation_is_pump_active(&state));
}

void test_low_humidity_activates_pump(void) {
    irrigation_set_humidity(&state, 20);
    irrigation_tick(&state, 1);
    TEST_ASSERT_TRUE(irrigation_is_pump_active(&state));
}

void test_high_humidity_deactivates_pump(void) {
    irrigation_set_humidity(&state, 20);
    irrigation_tick(&state, 1);
    TEST_ASSERT_TRUE(irrigation_is_pump_active(&state));

    irrigation_set_humidity(&state, 80);
    irrigation_tick(&state, 1);
    TEST_ASSERT_FALSE(irrigation_is_pump_active(&state));
}

void test_sensor_error_forces_pump_off(void) {
    irrigation_set_humidity(&state, 20);
    irrigation_tick(&state, 1);
    TEST_ASSERT_TRUE(irrigation_is_pump_active(&state));

    irrigation_set_sensor_status(&state, SENSOR_ERROR);
    irrigation_tick(&state, 1);
    TEST_ASSERT_FALSE(irrigation_is_pump_active(&state));
}

void test_pump_stops_after_max_runtime(void) {
    irrigation_set_humidity(&state, 20);
    irrigation_tick(&state, 1);
    TEST_ASSERT_TRUE(irrigation_is_pump_active(&state));

    irrigation_tick(&state, 700);
    TEST_ASSERT_FALSE(irrigation_is_pump_active(&state));
}

void test_pump_stays_off_between_thresholds(void) {
    irrigation_set_humidity(&state, 50);
    irrigation_tick(&state, 1);
    TEST_ASSERT_FALSE(irrigation_is_pump_active(&state));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_initial_state_pump_inactive);
    RUN_TEST(test_low_humidity_activates_pump);
    RUN_TEST(test_high_humidity_deactivates_pump);
    RUN_TEST(test_sensor_error_forces_pump_off);
    RUN_TEST(test_pump_stops_after_max_runtime);
    RUN_TEST(test_pump_stays_off_between_thresholds);
    return UNITY_END();
}
