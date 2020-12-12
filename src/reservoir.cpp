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
void Reservoir::calibrateEmpty(unsigned int val) {
  emptyDepth = val ? val : sensor->read(CM);
}

void Reservoir::calibrateFull(unsigned int val) {
  fullDepth = val ? val : sensor->read(CM);
}

// Getter Functions
unsigned int Reservoir::getEmpty() const {
  return emptyDepth;
}

unsigned int Reservoir::getFull() const {
  return fullDepth;
}

double Reservoir::getThreshold() const {
  return reservoir_thresh;
}


bool Reservoir::above_threshold(unsigned int depth) {
  return measure_volume(depth) > reservoir_thresh;
}

double Reservoir::measure_volume(unsigned int depth) const {
  if (!depth) {
    depth = sensor->read(CM);
  }
  return depth / (double)(emptyDepth - fullDepth);
}