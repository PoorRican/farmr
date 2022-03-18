//
// Created by Josue Figueroa on 12/29/20.
//

#ifndef FARMR_SENSORTEMP_H
#define FARMR_SENSORTEMP_H

#include "sensor.h"
#include <DallasTemperature.h>

class SensorTemp : private Sensor {
public:
  SensorTemp(const uint8_t &, DallasTemperature*);
  SensorTemp(const SensorTemp&) = default;
  SensorTemp& operator=(const SensorTemp&) = default;
  ~SensorTemp() override = default;

  SensName getType()  const final;

  void init() final;
  void update() final;
  double get() const;
  void setCelsius(boolean);
  bool getCelsius() const;

#ifdef SENSORLESS_OPERATION
  /**
   * Debug flag used for manually setting `pH`
   */
  void setTemp(double val) {
    temperature = val;
  }
#endif

protected:
  DallasTemperature *sensor;

  boolean celsiusMode = true;
  double temperature;
};

#endif //FARMR_SENSORTEMP_H
