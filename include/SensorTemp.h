//
// Created by Josue Figueroa on 12/14/20.
//

#ifndef FARMR_SENSORTEMP_H
#define FARMR_SENSORTEMP_H

#include "sensor.h"
#include <DallasTemperature.h>

extern DallasTemperature temperature;

class SensorTemp: Sensor {
public:
  SensorTemp(const int &pin);
  SensorTemp(const SensorTemp&) = default;
  SensorTemp& operator=(const SensorTemp&) = default;
  ~SensorTemp() = default;

  SensName getType() const;

  void init();
  void update();
  void fastUpdate();
  float get() const;
  float getRaw() const;
  void setCelsius(boolean);

protected:
  boolean celsiusMode = true;
  uint8_t sample_counter = 0;
  float readings[sample_size];
  float temp;

  void smooth();
};


#endif //FARMR_SENSORTEMP_H
