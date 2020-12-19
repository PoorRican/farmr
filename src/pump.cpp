//
// Created by Josue Figueroa on 12/12/20.
//

#include "scheduler.h"
#include "pump.h"

Pump::Pump(const uint8_t &pin, uint16_t &duration)
: pin(pin), duration(duration) {};


void Pump::init() const {
  pinMode(pin, OUTPUT);
}

void Pump::addTasks(Scheduler &scheduler) {
  scheduler.addTask(*(pumpTimer));
  scheduler.addTask(*(pumpOffTimer));
  pumpTimer->enable();
}


void Pump::startPumpOnTimer() const {
  pumpTimer->enable();
}

void Pump::stopPumpOnTimer() const {
  pumpTimer->disable();
}

void Pump::startPumpOffTimer() const {
  pumpOffTimer->enable();
}


void Pump::stopPumpOffTimer() const {
  pumpOffTimer->disable();
}


// Getters
bool Pump::getPumpOn() const {
  return pumpOn;
}

uint16_t Pump::getDuration() const {
  return duration;
}

uint8_t Pump::getPin() const {
  return pin;
}

void Pump::setPumpOn(bool val) {
  pumpOn = val;
}

// Pump routines
void startWatering() {
  Task& t = ts.currentTask();
  Pump& p = *((Pump*) t.getLtsPointer());
  if (p.aboveThreshold()) {
    digitalWrite(p.getPin(), HIGH);
    p.setPumpOn(true);
    p.startPumpOffTimer();
    p.stopPumpOnTimer();
  }
  else {
    digitalWrite(p.getPin(), LOW);
    p.stopPumpOnTimer();
    p.stopPumpOffTimer();
    // TODO: give error
  }
}

void stopWatering() {
  Task& t = ts.currentTask();
  Pump& p = *((Pump*) t.getLtsPointer());
  digitalWrite(p.getPin(), LOW);
  p.setPumpOn(false);
  p.startPumpOnTimer();
}