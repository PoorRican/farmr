//
// Created by Josue Figueroa on 12/12/20.
//

#include "sensor.h"

// Constructors
Sensor::Sensor(const int &pin) : _pin(pin) {}
Sensor::Sensor(const Sensor &other) {
  _pin = other._pin;
}

const Sensor& Sensor::operator=(const Sensor &other) {
  _pin = other._pin;
  return *this;
}

// Destructor
Sensor::~Sensor() = default;

Sensor::SensName Sensor::getType() const {
  return Sensor::None;
}