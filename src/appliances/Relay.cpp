//
// Created by Josue Figueroa on 12/12/20.
//

#include "logger.h"
#include "appliances/Relay.h"

Relay::Relay(const uint8_t &pin, uint16_t &duration, bool inverse)
    : pin(pin), duration(duration), inverse(inverse) {
  relayTimer = new Task(TASK_IMMEDIATE, TASK_ONCE, startRelay);
  relayTimer->setLtsPointer(this);
  relayOffTimer = new Task(this->duration, TASK_ONCE, stopRelay);
  relayOffTimer->setLtsPointer(this);
}

typename Relay::RelayType Relay::getType() const {
  return None;
}

void Relay::init() {
  pinMode(pin, OUTPUT);
  deenergize();
}

void Relay::addTasks(Scheduler &scheduler) {
  scheduler.addTask(*(relayTimer));
  scheduler.addTask(*(relayOffTimer));
}

void Relay::startRelayOnTimer() {

#ifdef VERBOSE_OUTPUT
  logger.verbose("'startRelayOnTimer' called");
#endif

  relayTimer->enable();
}

void Relay::stopRelayOnTimer() const {

#ifdef VERBOSE_OUTPUT
  logger.verbose("'stopRelayOnTimer' called");
#endif

  relayTimer->disable();
}

void Relay::startRelayOffTimer() {

#ifdef VERBOSE_OUTPUT
  logger.verbose("'startRelayOffTimer' called");
#endif

  relayOffTimer->set(duration, TASK_ONCE, stopRelay);
  setDuration(duration);
  relayOffTimer->enableDelayed();
}

void Relay::stopRelayOffTimer() const {

#ifdef VERBOSE_OUTPUT
  logger.verbose("'stopRelayOffTimer' called");
#endif

  relayOffTimer->disable();
}


// Getters
bool Relay::getRelayOn() const {
  return relayOn;
}

uint16_t Relay::getDuration() const {
  return duration;
}

uint8_t Relay::getPin() const {
  return pin;
}

bool Relay::getInverse() const {
  return inverse;
}

// Setters
void Relay::setRelayOn(bool val) {

#ifdef VERBOSE_OUTPUT
  String s = "";
  switch (getType()) {
    case PumpWater: {
      s += "Water Pump";
      break;
    }
    case PumpPh: {
      s += "pH Pump";
      break;
    }
    case PumpNutrient: {
      s += "Nutrient Pump";
      break;
    }
    case ThermoElectricElement: {
      s += "ThermoElectric Element";
    }
    default: {
      s += "Unknown relay type";
      break;
    }
  }
  s += " turned ";
  s += ((val) ? "on" : "off");
  logger.verbose((char*)&s);
#endif

  relayOn = val;
}

void Relay::setInverse(bool val) {
  inverse = val;
}

// Relay routines
void Relay::energize() {

#ifdef Arduino_h
  digitalWrite(pin, (inverse) ? LOW : HIGH);
#endif

  setRelayOn(true);
}

void Relay::deenergize() {

#ifdef Arduino_h
  digitalWrite(pin, (inverse) ? HIGH : LOW);
#endif

  setRelayOn(false);
}


void startRelay() {
  Task& t = ts.currentTask();
  Relay& p = *((Relay*) t.getLtsPointer());

  p.energize();

  p.startRelayOffTimer();

#ifdef BASIC_TESTING
  String feedback = "Relay (at pumpPin " + (String)p.getPin() + ") turned on";
  logger.debug((char*)&feedback);
#endif
}

void stopRelay() {
  Task& t = ts.currentTask();
  Relay& p = *((Relay*) t.getLtsPointer());

  p.deenergize();

#ifdef BASIC_TESTING
  String feedback = "Relay (pumpPin " + (String)p.getPin() + ") turned off";
  logger.debug((char*)&feedback);
#endif
}
