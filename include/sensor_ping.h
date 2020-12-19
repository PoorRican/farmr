//
// Created by Josue Figueroa on 12/12/20.
//
#ifndef FARMR_SENSOR_PING_H
#define FARMR_SENSOR_PING_H

#include <NewPing.h>
#include "sensor.h"

class SensorPing: public Sensor {
public:
  SensorPing(const int&, const int&);
  SensorPing(const SensorPing&) = default;
  SensorPing& operator=(const SensorPing&) = default;
  ~SensorPing() override = default;

  SensName getType() const;

  void init() final;
  void update() final;
  void fastUpdate() final;

  uint8_t get() const;
  uint16_t getRaw();
  uint8_t getPercent() const;
  bool above_threshold() const;

  // Calibration functions
  void setMax(uint16_t = 0);
  void setMin(uint16_t = 0);
#ifdef SENSORLESS_OPERATION
  /**
   * Debug function used for simulating water level
   */
  void setLevel(uint8_t val) {
    level = val;
  }
#endif

protected:
  int pinTrigger;
  int pinEcho;

  NewPing sonar;

  uint16_t max;
  uint16_t min;
  uint16_t threshold = 25;  // "low-level" threshold percentage

  // Smoothing counter
  uint8_t samples = 0;

  uint8_t levels[sample_size];
  uint8_t level = 0;

  void smooth() final;
};


#endif //FARMR_SENSOR_PING_H
