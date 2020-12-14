//
// Created by Josue Figueroa on 12/12/20.
//

#include "sensor.h"

// Constructors
Sensor::Sensor(const int &pin) : _pin(pin) {}

// Destructor
Sensor::~Sensor() = default;

Sensor::SensName Sensor::getType() const {
  return Sensor::None;
}