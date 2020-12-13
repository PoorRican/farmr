//
// Created by Josue Figueroa on 12/11/20.
//

#include "pump_water.h"


// Constructors
WaterPump::WaterPump(const int &pin, Reservoir *reservoir) : pin(pin), reservoir(reservoir) {}
WaterPump::WaterPump(const WaterPump &other) {
  pin = other.pin;
  reservoir = other.reservoir;
}
const WaterPump& WaterPump::operator=(const WaterPump& other) {
  pin = other.pin;
  reservoir = other.reservoir;
  return *this;
}

// Destructor
WaterPump::~WaterPump() = default;


// Timer Routines
void WaterPump::startPumpOnTimer() {
  if (!pumpTimer.enabled) {
    int min = calcNextCycleTime(hour()) * 60;
    pumpTimer.id = Alarm.timerOnce(min, startWatering);
    pumpTimer.enabled = true;
    startPumpOffTimer();
  }
}

void WaterPump::stopPumpOnTimer() {
  if (pumpTimer.enabled) {
    Alarm.free(pumpTimer.id);
    pumpTimer.enabled = false;
    stopPumpOffTimer();
  }
}

void WaterPump::startPumpOffTimer() {
  if (!pumpOffTimer.enabled) {
    int flood = pumpInterval.flood * 60;
    pumpOffTimer.id = Alarm.timerOnce(flood, stopWatering);
    pumpOffTimer.enabled = true;
    startPumpOnTimer();
  }
}


void WaterPump::stopPumpOffTimer() {
  if (pumpOffTimer.enabled) {
    Alarm.free(pumpOffTimer.id);
    pumpOffTimer.enabled = false;
  }
}

int WaterPump::calcNextCycleTime(const int &hour) const {
  const int cycle_len = 24 / pumpInterval.frequency;  // cycle length (in hours)
  const int until_next = (24 - hour) % cycle_len;     // hours until next cycle
  int _return = until_next ? until_next : cycle_len;  // calculate next cycle time
  return _return % 24;                                // normalize
}

// Pump routines
OnTick_t WaterPump::startWatering() {
  if (reservoir->above_threshold()) {
    digitalWrite(pin, HIGH);
    pumpOn = true;
    stopPumpOnTimer();
  }
}

OnTick_t WaterPump::stopWatering() {
  digitalWrite(pin, LOW);
  pumpOn = false;
  stopPumpOffTimer();
}


// Getters

bool WaterPump::getPumpOn() const {
  return pumpOn;
}

int WaterPump::getPin() const {
  return pin;
}

int WaterPump::getFrequency() const {
  return pumpInterval.frequency;
}

int WaterPump::getFloodTime() const {
  return pumpInterval.flood;
}


// Setters

bool WaterPump::setFloodTime(int &min) {
  if (min > 0 && min <= 12) {
    pumpInterval.flood = min;
    return true;
  }
}

bool WaterPump::setFrequency(int &freq) {
  if (freq > 0 && freq <= 12) {
    pumpInterval.frequency = freq;
    return true;
  }
  return false;
}