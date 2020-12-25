//
// Created by Josue Figueroa on 12/12/20.
//

#include "scheduler.h"
#include "pump.h"

Pump::Pump(const uint8_t &pin, uint16_t &duration)
: pin(pin), duration(duration) {};


void Pump::init() const {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);            // immediately de-energize coil upon power applied
}

void Pump::addTasks(Scheduler &scheduler) {
  scheduler.addTask(*(pumpTimer));
  scheduler.addTask(*(pumpOffTimer));
}


void Pump::startPumpOnTimer() const {
#ifdef VERBOSE_OUTPUT
  Serial.println("'startPumpOnTimer' called");
#endif
  pumpTimer->enable();
}

void Pump::stopPumpOnTimer() const {
#ifdef VERBOSE_OUTPUT
  Serial.println("'stopPumpOnTimer' called");
#endif
  pumpTimer->disable();
}

void Pump::startPumpOffTimer() const {
#ifdef VERBOSE_OUTPUT
  Serial.println("'startPumpOffTimer' called");
#endif
  pumpOffTimer->enableDelayed();
}

void Pump::stopPumpOffTimer() const {
#ifdef VERBOSE_OUTPUT
  Serial.println("'stopPumpOffTimer' called");
#endif
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
void startPump() {
  Task& t = ts.currentTask();
  Pump& p = *((Pump*) t.getLtsPointer());

  if (p.aboveThreshold()) {
    digitalWrite(p.getPin(), LOW);        // logic LOW energizes relay
    p.setPumpOn(true);

    p.startPumpOffTimer();

#ifdef BASIC_TESTING
    String feedback = "Pump (at pin " + (String)p.getPin() + ") turned on";
    Serial.println(feedback);
#endif
  }
  else {
    digitalWrite(p.getPin(), HIGH);     // logic HIGH de-energizes relay
    p.setPumpOn(false);
    p.stopPumpOnTimer();
    p.stopPumpOffTimer();

#ifdef BASIC_TESTING
    String feedback = "Error turning pump on (pin " + (String)p.getPin() + ")";
    Serial.println(feedback);
#endif
  }
}

void stopPump() {
  Task& t = ts.currentTask();
  Pump& p = *((Pump*) t.getLtsPointer());

  digitalWrite(p.getPin(), HIGH);     // logic HIGH de-energizes relay
  p.setPumpOn(false);

#ifdef BASIC_TESTING
  String feedback = "Pump (pin " + (String)p.getPin() + ") turned off";
  Serial.println(feedback);
#endif
}