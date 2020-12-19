//
// Created by Josue Figueroa on 12/18/20.
//

#ifndef FARMR_SETTINGS_H
#define FARMR_SETTINGS_H

#include "monitor_ph.h"
#include "pump_water.h"
#include "sensor_ping.h"
#include "SensorPH.h"

struct pump_t {
  const uint8_t trigger;
  const uint8_t echo;
  const uint8_t pin;
  uint16_t duration;
  uint16_t interval;
};

// PH Pumps/Sensor
pump_t acid_array = {25, 26, 27, 10, 5};
SensorPing acid_sonar(acid_array.trigger, acid_array.echo);
Pump_pH acid_pump(acid_array.pin, acid_array.duration, acid_array.interval, &acid_sonar);

pump_t base_array = {28, 29, 30, 10, 5};
SensorPing base_sonar(base_array.trigger, base_array.echo);
Pump_pH base_pump(base_array.pin, base_array.duration, base_array.interval, &base_sonar);

// PH Monitor
struct {
  float ideal = 7.5;
  uint16_t interval = 10;
  uint8_t pin = 8;
} ph_sensor_t;
SoftwareSerial ph_serial(68, 69);
SensorPH ph_sensor(ph_sensor_t.pin, &ph_serial);
pHMonitor ph_monitor(ph_sensor_t.ideal, ph_sensor_t.interval, ph_sensor, acid_pump, base_pump);

// Reservoir
pump_t reservoir_array = {23, 24, 10, 10, 4};
SensorPing reservoir_sonar(23, 24);
WaterPump reservoir_pump(reservoir_array.pin, reservoir_array.interval, reservoir_array.interval, &reservoir_sonar);

#endif //FARMR_SETTINGS_H