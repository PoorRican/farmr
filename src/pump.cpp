//
// Created by Josue Figueroa on 12/12/20.
//

#include "pump.h"

Pump::Pump(const uint8_t &pin, uint16_t &duration, uint16_t &interval, SensorPing *sonar)
: pin(pin), duration(duration), interval(interval), sonar(sonar) {};


void Pump::init() const {
  pinMode(pin, OUTPUT);
}


void Pump::startPumpOnTimer() {
  pumpTimer->enable();
}

void Pump::stopPumpOnTimer() {
  pumpTimer->disable();
}

void Pump::startPumpOffTimer() {
  pumpOffTimer->enable();
}


void Pump::stopPumpOffTimer() {
  pumpOffTimer->disable();
}


// Getters
bool Pump::getPumpOn() const {
  return pumpOn;
}

uint16_t Pump::getDuration() const {
  return duration;
}

uint16_t Pump::getInterval() const {
  return interval;
}

uint8_t Pump::getPin() const {
  return pin;
}

void Pump::setPumpOn(bool val) {
  pumpOn = val;
}

bool Pump::aboveThreshold() const {
  return sonar->above_threshold();
}

// Pump routines
void startWatering() {
  Task& t = ts.currentTask();
  Pump& p = *((Pump*) t.getLtsPointer());
  if (p.aboveThreshold()) {
    digitalWrite(p.getPin(), HIGH);
    p.setPumpOn(true);
    p.startPumpOffTimer();
  }
  else {
    p.stopPumpOffTimer();
    // TODO: give error
  }
}

void stopWatering() {
  Task& t = ts.currentTask();
  Pump& p = *((Pump*) t.getLtsPointer());
  digitalWrite(p.getPin(), LOW);
  p.setPumpOn(false);
}