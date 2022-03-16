//
// Created by Josue Figueroa on 12/29/20.
//

#include "sensors/distance.h"

SensorDistance::SensorDistance(const uint8_t &pin) : Sensor(pin) {}

Sensor::SensName SensorDistance::getType() const {
  return Sensor::Level;
}

void SensorDistance::init() {
#ifdef Arduino_h
  pinMode(pin, INPUT);
#endif
}

uint8_t SensorDistance::get() const {
  return level;
}

void SensorDistance::update() {
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

void SensorDistance::calibrateMin() {
  min = readResistance();
}

void SensorDistance::calibrateMax() {
  max = readResistance();
}

bool SensorDistance::aboveThreshold() const {
  return level >= threshold;
}

uint8_t SensorDistance::getThreshold() const {
  return threshold;
}

bool SensorDistance::setThreshold(const uint8_t& val) {
    if (val >= 1 && val <= 100) {
      threshold = val;
      return true;
    }
  return false;
}

float SensorDistance::readResistance() const {
#ifdef Arduino_h
  auto resistance = (float)analogRead(pin);
  resistance = ((float)1023 / resistance) - (float)1;
  return LEVEL_SERIES_RESISTOR / resistance;
#endif
}