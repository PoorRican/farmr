//
// Created by Josue Figueroa on 12/29/20.
//

#include "sensors/SensorLevel.h"

SensorLevel::SensorLevel(const uint8_t &pin) : Sensor(pin) {}

Sensor::SensName SensorLevel::getType() const {
  return Sensor::Level;
}

void SensorLevel::init() {
#ifdef Arduino_h
  pinMode(pin, INPUT);
#endif
}

uint8_t SensorLevel::get() const {
  return level;
}

void SensorLevel::update() {
  // TODO: this needs to be tested
#ifndef SENSORLESS_OPERATION
  float resistance = readResistance();
  if (resistance > min || (min - max) == 0.0) {
    level = 0.0;
    return;
  }
  float scale = (min - resistance) / (min - max);
  level = scale * 100;      // get percentage as integer
#endif
}

void SensorLevel::calibrateMin() {
  min = readResistance();
}

void SensorLevel::calibrateMax() {
  max = readResistance();
}

bool SensorLevel::aboveThreshold() const {
  return level >= threshold;
}

uint8_t SensorLevel::getThreshold() const {
  return threshold;
}

bool SensorLevel::setThreshold(const uint8_t& val) {
    if (val >= 1 && val <= 100) {
      threshold = val;
      return true;
    }
  return false;
}

float SensorLevel::readResistance() const {
#ifdef Arduino_h
  auto resistance = (float)analogRead(pin);
  resistance = ((float)1023 / resistance) - (float)1;
  return LEVEL_SERIES_RESISTOR / resistance;
#endif
}