//
// Created by Josue Figueroa on 12/18/20.
//

#ifndef FARMR_SETTINGS_H
#define FARMR_SETTINGS_H

#include "debug.h"
#include "monitor_ph.h"
#include "pump_water.h"
#include "sensor_ping.h"
#include "SensorPH.h"

// PH Pumps/Sensor
struct phPump_t {
  const uint8_t trigger;
  const uint8_t echo;
  const uint8_t pump;
  uint16_t duration;
  uint16_t interval;
};
phPump_t acid_array = {25, 26, 27, 10, 5};
phPump_t base_array = {28, 29, 30, 10, 5};

SensorPing acid_sonar(acid_array.trigger, acid_array.echo);
Pump_pH acid_pump(acid_array.pump, acid_array.duration, acid_array.interval, &acid_sonar);

SensorPing base_sonar(base_array.trigger, base_array.echo);
Pump_pH base_pump(base_array.pump, base_array.duration, base_array.interval, &base_sonar);

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
const uint8_t waterPumpPin = 10;
SensorPing reservoir_sonar(23, 24);
WaterPump reservoir_pump(waterPumpPin, 10, 4, &reservoir_sonar);

#endif //FARMR_SETTINGS_H