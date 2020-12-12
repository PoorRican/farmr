//
// Created by Josue Figueroa on 12/11/20.
//

#include "math.h"
#include <reservoir.h>

// Constructors
Reservoir::Reservoir(Ultrasonic *sensor) : sensor(sensor) {}

Reservoir::Reservoir(const Reservoir &other) {
  sensor = other.sensor;
  fullDepth = other.fullDepth;
  emptyDepth = other.emptyDepth;
}

const Reservoir& Reservoir::operator=(const Reservoir& other) {
  sensor = other.sensor;
  fullDepth = other.fullDepth;
  emptyDepth = other.emptyDepth;
  return *this;
}

// Destructor
Reservoir::~Reservoir() = default;

// Calibration Functions
void Reservoir::calibrateEmpty() {
  emptyDepth = sensor->read(CM);
}

void Reservoir::calibrateFull() {
  fullDepth = sensor->read(CM);
}

// TODO: this needs to be tested
bool Reservoir::check_reservoir() {
  double actual_thresh = (float)(emptyDepth - fullDepth) * (1 - reservoir_thresh);
  return sensor->read(CM) < floor(actual_thresh);
}