//
// Created by Josue Figueroa on 12/19/20.
//

#include "settings.h"

// PH Pumps/Sensor
pump_t acid_array = {25, 26, 27, 10};
Pump_pH acid_pump(acid_array.pin, acid_array.duration, &ts);

pump_t base_array = {28, 29, 30, 10};
Pump_pH base_pump(base_array.pin, base_array.duration, &ts);

// PH Monitor
SensorPH ph_sensor(ph_sensor_t.pin);
pHMonitor ph_monitor(ph_sensor_t.ideal, ph_sensor_t.interval, ph_sensor, acid_pump, base_pump, &ts);

// Reservoir
pump_t reservoir_array = {23, 24, 13, 4, 12};
SensorPing reservoir_sonar(23, 24);
WaterPump reservoir_pump(reservoir_array.pin, reservoir_array.duration, reservoir_array.interval, &reservoir_sonar, &ts);