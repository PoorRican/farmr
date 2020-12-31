//
// Created by Josue Figueroa on 12/12/20.
//

#include "scheduler.h"
#include "Relay.h"

Relay::Relay(const uint8_t &pin, uint16_t &duration)
: pin(pin), duration(duration) {

  pumpTimer = new Task(TASK_IMMEDIATE, TASK_ONCE, startPump);
  pumpTimer->setLtsPointer(this);
  pumpOffTimer = new Task(this->duration, TASK_ONCE, stopPump);
  pumpOffTimer->setLtsPointer(this);
};


void Relay::init() const {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);            // immediately de-energize coil upon power applied
}

void Relay::addTasks(Scheduler &scheduler) {
  scheduler.addTask(*(pumpTimer));
  scheduler.addTask(*(pumpOffTimer));
}


void Relay::startPumpOnTimer() {
#ifdef VERBOSE_OUTPUT
  Serial.println("'startPumpOnTimer' called");
#endif
  pumpTimer->enable();
}

void Relay::stopPumpOnTimer() const {
#ifdef VERBOSE_OUTPUT
  Serial.println("'stopPumpOnTimer' called");
#endif
  pumpTimer->disable();
}

void Relay::startPumpOffTimer() {
#ifdef VERBOSE_OUTPUT
  Serial.println("'startPumpOffTimer' called");
#endif
  pumpOffTimer->set(duration, TASK_ONCE, stopPump);
  setDuration(duration);
  pumpOffTimer->enableDelayed();
}

void Relay::stopPumpOffTimer() const {
#ifdef VERBOSE_OUTPUT
  Serial.println("'stopPumpOffTimer' called");
#endif
  pumpOffTimer->disable();
}


// Getters
bool Relay::getPumpOn() const {
  return pumpOn;
}

uint16_t Relay::getDuration() const {
  return duration;
}

uint8_t Relay::getPin() const {
  return pin;
}

void Relay::setPumpOn(bool val) {
  pumpOn = val;
}

// Relay routines
void startPump() {
  Task& t = ts.currentTask();
  Relay& p = *((Relay*) t.getLtsPointer());

  digitalWrite(p.getPin(), LOW);        // logic LOW energizes relay
  p.setPumpOn(true);

  p.startPumpOffTimer();

#ifdef BASIC_TESTING
  String feedback = "Relay (at pumpPin " + (String)p.getPin() + ") turned on";
  Serial.println(feedback);
#endif
}

void stopPump() {
  Task& t = ts.currentTask();
  Relay& p = *((Relay*) t.getLtsPointer());

  digitalWrite(p.getPin(), HIGH);     // logic HIGH de-energizes relay
  p.setPumpOn(false);

#ifdef BASIC_TESTING
  String feedback = "Relay (pumpPin " + (String)p.getPin() + ") turned off";
  Serial.println(feedback);
#endif
}