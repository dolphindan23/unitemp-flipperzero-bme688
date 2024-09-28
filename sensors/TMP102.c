/*
    Unitemp - TMP102 Temperature Sensor Reader
    Copyright (C) 2022-2023 Victor Nikitchuk (https://github.com/quen0n)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License.
*/

#include "TMP102.h"
#include "../interfaces/I2CSensor.h"

const SensorType TMP102 = {
    .typename = "TMP102",
    .interface = &I2C,
    .datatype = UT_TEMPERATURE,
    .pollingInterval = 1000,
    .allocator = unitemp_TMP102_I2C_alloc,
    .mem_releaser = unitemp_TMP102_I2C_free,
    .initializer = unitemp_TMP102_init,
    .deinitializer = unitemp_TMP102_I2C_deinit,
    .updater = unitemp_TMP102_I2C_update
};

bool unitemp_TMP102_I2C_alloc(Sensor* sensor, char* args) {
    I2CSensor* i2c_sensor = (I2CSensor*)sensor->instance;
    i2c_sensor->minI2CAdr = 0x48 << 1; // TMP102 default I2C address (0x48)
    i2c_sensor->maxI2CAdr = 0x49 << 1; // Supports 0x48 to 0x49
    return true;
}

bool unitemp_TMP102_I2C_free(Sensor* sensor) {
    UNUSED(sensor);
    return true;
}

bool unitemp_TMP102_init(Sensor* sensor) {
    // Initialization code if needed
    return true;
}

bool unitemp_TMP102_I2C_deinit(Sensor* sensor) {
    UNUSED(sensor);
    return true;
}

UnitempStatus unitemp_TMP102_I2C_update(Sensor* sensor) {
    I2CSensor* i2c_sensor = (I2CSensor*)sensor->instance;
    uint8_t data[2];

    // Read temperature data from TMP102
    if (!unitemp_i2c_readArray(i2c_sensor, 2, data)) {
        return UT_SENSORSTATUS_TIMEOUT;
    }

    // Combine the two bytes into one temperature value
    int16_t temp_raw = (data[0] << 4) | (data[1] >> 4); // Only use the top 12 bits
    sensor->temp = temp_raw * 0.0625; // Convert to Celsius (0.0625°C per LSB)

    // Display temperature on Flipper Zero screen
    char display_buffer[64];
    snprintf(display_buffer, sizeof(display_buffer), "Temperature: %.2f °C", sensor->temp);
    flipper_display_string(display_buffer); // Function to display string on Flipper Zero

    return UT_SENSORSTATUS_OK;
}
