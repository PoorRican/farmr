//
// Created by Josue Figueroa on 12/14/20.
//

#ifndef FARMR_SENSORTEMP_H
#define FARMR_SENSORTEMP_H

#include "sensor.h"
#include <DallasTemperature.h>

class SensorTemp: Sensor {
public:
  SensorTemp(const uint8_t &, DallasTemperature*);
  SensorTemp(const SensorTemp&) = default;
  SensorTemp& operator=(const SensorTemp&) = default;
  ~SensorTemp() override = default;

  SensName getType()  const final;

  void init() final;
  void update() final;
  void fastUpdate() final {};
  float get() const;
  void setCelsius(boolean);
  bool getCelsius() const;

#ifdef SENSORLESS_OPERATION
  /**
   * Debug flag used for manually setting `pH`
   */
  void setTemp(float val) {
    temperature = val;
  }
#endif

protected:
  DallasTemperature *sensor;

  boolean celsiusMode = true;
  uint8_t sample_counter = 0;
  float readings[sample_size];
  float temperature;

  void smooth() final {}
};


#endif //FARMR_SENSORTEMP_H
