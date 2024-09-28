#ifndef TMP102_H
#define TMP102_H

#include <stdint.h>
#include <stdbool.h>
#include "Sensor.h"

extern const SensorType TMP102;

bool unitemp_TMP102_I2C_alloc(Sensor* sensor, char* args);
bool unitemp_TMP102_I2C_free(Sensor* sensor);
bool unitemp_TMP102_init(Sensor* sensor);
bool unitemp_TMP102_I2C_deinit(Sensor* sensor);
UnitempStatus unitemp_TMP102_I2C_update(Sensor* sensor);

#endif // TMP102_H
