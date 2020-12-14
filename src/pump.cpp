//
// Created by Josue Figueroa on 12/12/20.
//

#include "pump.h"


Pump::Pump(const Pump &other) {
  pin = other.pin;
  duration = other.duration;
  interval = other.interval;
  sonar = other.sonar;
}

Pump& Pump::operator=(const Pump &other) {
  pin = other.pin;
  duration = other.duration;
  interval = other.interval;
  sonar = other.sonar;
  return *this;
}


void Pump::init() const {
  pinMode(pin, OUTPUT);
}


void Pump::startPumpOnTimer() {
  if (!pumpTimer.enabled) {
    int time = calcNextOnTime();
    pumpTimer.id = Alarm.timerOnce(time, startWatering);
    pumpTimer.enabled = true;
    startPumpOffTimer();
  }
}

void Pump::stopPumpOnTimer() {
  if (pumpTimer.enabled) {
    Alarm.free(pumpTimer.id);
    pumpTimer.enabled = false;
    stopPumpOffTimer();
  }
}

void Pump::startPumpOffTimer() {
  if (!pumpOffTimer.enabled) {
    pumpOffTimer.id = Alarm.timerOnce(duration, stopWatering);
    pumpOffTimer.enabled = true;
  }
}


void Pump::stopPumpOffTimer() {
  if (pumpOffTimer.enabled) {
    Alarm.free(pumpOffTimer.id);
    pumpOffTimer.enabled = false;
  }
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

// Pump routines
OnTick_t Pump::startWatering() {
  if (sonar->above_threshold()) {
    digitalWrite(pin, HIGH);
    pumpOn = true;
    stopPumpOnTimer();
  }
}

OnTick_t Pump::stopWatering() {
  digitalWrite(pin, LOW);
  pumpOn = false;
  stopPumpOffTimer();
  if (!oneShot) { startPumpOnTimer(); }
}


