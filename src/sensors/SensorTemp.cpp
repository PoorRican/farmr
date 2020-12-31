//
// Created by Josue Figueroa on 12/14/20.
//

#include "sensors/SensorTemp.h"

DallasTemperature temperatureSensor(&oneWire);

SensorTemp::SensorTemp(const uint8_t &pin, DallasTemperature *sensor) : Sensor(pin), sensor(sensor) {
}

Sensor::SensName SensorTemp::getType() const {
  return Sensor::Temperature;
}

void SensorTemp::init() {
  sensor->begin();
  sensor->setResolution(11);
}

void SensorTemp::update() {
#ifndef SENSORLESS_OPERATION
  sensor->requestTemperatures();
  temperature = (celsiusMode) ? sensor->getTempCByIndex(0) : sensor->getTempFByIndex(0);
#endif
}

float SensorTemp::get() const {
  return temperature;
}

void SensorTemp::setCelsius(boolean v) {
  celsiusMode = v;
}