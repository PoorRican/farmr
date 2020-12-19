//
// Created by Josue Figueroa on 12/14/20.
//

#include "SensorTemp.h"

SensorTemp::SensorTemp(const int &pin) : Sensor(pin) {
  for (uint8_t i = 0; i < sample_size; i++) {
    readings[i] = 0;
  }
}

Sensor::SensName SensorTemp::getType() const {
  return Sensor::Temperature;
}

void SensorTemp::init() {
  temperature.begin();
  temperature.setResolution(11);
}

void SensorTemp::update() {
  readings[sample_counter++] = getRaw();
  sample_counter = sample_counter % sample_size;
  smooth();
}

void SensorTemp::fastUpdate() {
  float t = getRaw();
  for (uint8_t i = 0; i < sample_counter; i++) {
    readings[i] = t;
  }
  temp = t;
}

float SensorTemp::get() const {
  return temp;
}

float SensorTemp::getRaw() const {
  temperature.requestTemperatures();
  return (celsiusMode) ? temperature.getTempCByIndex(0) : temperature.getTempFByIndex(0);
}

void SensorTemp::setCelsius(boolean v) {
  celsiusMode = v;
}

void SensorTemp::smooth() {
  float res = 0;
  for (uint8_t i = 0; i < sample_counter; i++) {
    res += readings[i];
  }
  temp = res / (float)sample_counter;
}