//
// Created by Josue Figueroa on 12/18/20.
//

#ifndef FARMR_SETTINGS_H
#define FARMR_SETTINGS_H

#include <Arduino.h>
#include "pump_water.h"
#include "sensor_ping.h"
#include "pump_ph.h"
#include "monitor_ph.h"

// pH Pumps/Sensors/Monitor
extern Pump_pH acid_pump;
extern Pump_pH base_pump;

extern SensorPH ph_sensor;
extern pHMonitor ph_monitor;

// Reservoir
extern SensorPing reservoir_sonar;
extern WaterPump reservoir_pump;

#endif //FARMR_SETTINGS_H