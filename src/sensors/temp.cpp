//
// Created by Josue Figueroa on 12/29/20.
//

#include "sensors/temp.h"

SensorTemp::SensorTemp(const uint8_t &pin, DallasTemperature *sensor) : Sensor(pin), sensor(sensor) {
  temperature = -1;
}

Sensor::SensName SensorTemp::getType() const {
  return Sensor::Temperature;
}

void SensorTemp::init() {
#ifndef SENSORLESS_OPERATION
  sensor->begin();
  sensor->setResolution(11);
#endif
}

void SensorTemp::update() {
#ifndef SENSORLESS_OPERATION
  sensor->requestTemperatures();
  input = (celsiusMode) ? sensor->getTempCByIndex(0) : sensor->getTempFByIndex(0);
#endif
}

double SensorTemp::get() const {
  return temperature;
}

void SensorTemp::setCelsius(boolean v) {
  celsiusMode = v;
}

bool SensorTemp::getCelsius() const {
  return celsiusMode;
}
