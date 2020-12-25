//
// Created by Josue Figueroa on 12/19/20.
//

#include "settings.h"
#include "pins.h"

// PH Pumps/Sensor
uint16_t ph_pump_duration = 2;
uint16_t ph_pump_interval = 10;
float ideal_ph = 7.5;
Pump_pH acid_pump(ph_monitor_t.acidPin, ph_pump_duration, &ts);
Pump_pH base_pump(ph_monitor_t.basePin, ph_pump_duration, &ts);

// PH Monitor
SensorPH ph_sensor(ph_monitor_t.sensorPin);
pHMonitor ph_monitor(ideal_ph, ph_pump_interval, ph_sensor, acid_pump, base_pump, &ts);

// Reservoir
uint16_t reservoir_duration = 4;
uint16_t reservoir_interval = 12;
SensorPing reservoir_sonar(reservoir_t.trigger, reservoir_t.echo);
WaterPump reservoir_pump(reservoir_t.pin, reservoir_duration, reservoir_interval, &reservoir_sonar, &ts);