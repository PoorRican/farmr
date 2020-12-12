//
// Created by Josue Figueroa on 12/11/20.
//

#include "pump.h"


// Costructors
Pump::Pump(int pin, Reservoir *reservoir) : pin(pin), reservoir(reservoir) {}
Pump::Pump(const Pump &other) {
  pin = other.pin;
  reservoir = other.reservoir;
}
const Pump& Pump::operator=(const Pump& other) {
  pin = other.pin;
  reservoir = other.reservoir;
  return *this;
}

// Destructor
Pump::~Pump() = default;


// Timer Routines
void Pump::startPumpOnTimer(int min) {
  int _min = min * 60;
  if (!pumpTimer.enabled) {
    if (min) {
      pumpTimer.id = Alarm.timerOnce(_min, startWatering);
      pumpTimer.enabled = true;
    }
    else {
      startWatering();
    }
    startPumpOffTimer(pumpInterval.flood);
  }
}

void Pump::stopPumpOnTimer() {
  if (pumpTimer.enabled) {
    Alarm.free(pumpTimer.id);
    pumpTimer.enabled = false;
    stopPumpOffTimer();
  }
}

void Pump::startPumpOffTimer(int min) {
  if (!pumpOffTimer.enabled) {
    int _min = min * 60;
    int _gap = _min + pumpInterval.gap * 60;
    if (_min) {
      pumpOffTimer.id = Alarm.timerOnce(_min, stopWatering);
      pumpOffTimer.enabled = true;
    }
    else {
      stopWatering();
    }
    startPumpOnTimer(_gap);
  }
}


void Pump::stopPumpOffTimer() {
  if (pumpOffTimer.enabled) {
    Alarm.free(pumpOffTimer.id);
    pumpOffTimer.enabled = false;
  }
}

// Pump routines
OnTick_t Pump::startWatering() {
  if (reservoir->above_threshold()) {
    digitalWrite(pin, HIGH);
    pumpOn = true;
    stopPumpOnTimer();
  }
}


OnTick_t Pump::stopWatering() {
  digitalWrite(pin, LOW);
  pumpOn = false;
  stopPumpOffTimer();
}

bool Pump::getPumpOn() {
  return pumpOn;
}