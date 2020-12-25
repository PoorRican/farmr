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

struct pump_t {
  const uint8_t trigger;
  const uint8_t echo;
  const uint8_t pin;
  uint16_t duration;
  uint16_t interval;
};


struct {
  float ideal = 7.5;
  uint16_t interval = 15;
  uint8_t pin = 8;
} ph_sensor_t;

// pH Pumps/Sensors/Monitor
extern Pump_pH acid_pump;
extern Pump_pH base_pump;

extern SensorPH ph_sensor;
extern pHMonitor ph_monitor;

// Reservoir
extern SensorPing reservoir_sonar;
extern WaterPump reservoir_pump;

#endif //FARMR_SETTINGS_H