//
// Created by Josue Figueroa on 12/12/20.
//

#include "appliances/relay.h"

template<class T>
Relay<T>::Relay(const uint8_t &pin, T &duration, bool inverse)
    : pin(pin), duration(duration), inverse(inverse) {
  relayTimer = new Task(TASK_IMMEDIATE, TASK_ONCE, startRelay);
  relayTimer->setLtsPointer(this);
  relayOffTimer = new Task(this->duration, TASK_ONCE, stopRelay);
  relayOffTimer->setLtsPointer(this);
}

template<> typename Relay<>::RelayType Relay<>::getType() const {
  return None;
}

template<> void Relay<>::init() const {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);            // immediately de-energize coil upon power applied
}

template<> void Relay<>::addTasks(Scheduler &scheduler) {
  scheduler.addTask(*(relayTimer));
  scheduler.addTask(*(relayOffTimer));
}


template<> void Relay<>::startRelayOnTimer() {
#ifdef VERBOSE_OUTPUT
  Serial.println("'startRelayOnTimer' called");
#endif
  relayTimer->enable();
}

template<> void Relay<>::stopRelayOnTimer() const {
#ifdef VERBOSE_OUTPUT
  Serial.println("'stopRelayOnTimer' called");
#endif
  relayTimer->disable();
}

template<> void Relay<>::startRelayOffTimer() {
#ifdef VERBOSE_OUTPUT
  Serial.println("'startRelayOffTimer' called");
#endif
  relayOffTimer->set(duration, TASK_ONCE, stopRelay);
  setDuration(duration);
  relayOffTimer->enableDelayed();
}

template<> void Relay<>::stopRelayOffTimer() const {
#ifdef VERBOSE_OUTPUT
  Serial.println("'stopRelayOffTimer' called");
#endif
  relayOffTimer->disable();
}


// Getters
template<> bool Relay<>::getRelayOn() const {
  return relayOn;
}

template<class T>
T Relay<T>::getDuration() const {
  return duration;
}

template<>
uint8_t Relay<>::getPin() const {
  return pin;
}

template<> bool Relay<>::getInverse() const {
  return inverse;
}

// Setters
template<> void Relay<>::setRelayOn(bool val) {
#ifdef BASIC_TESTING
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
  Serial.println(s);
#endif
  relayOn = val;
}

template<> void Relay<>::setInverse(bool val) {
  inverse = val;
}

// Relay routines
template<> void Relay<>::energize() {
#ifdef Arduino_h
  digitalWrite(pin, (inverse) ? LOW : HIGH);
#endif
  setRelayOn(true);
}

template<> void Relay<>::deenergize() {
#ifdef Arduino_h
  digitalWrite(pin, (inverse) ? HIGH : LOW);
#endif
  setRelayOn(false);
}

template<class T>
void startRelay() {
  Task& t = ts.currentTask();
  Relay<T>& p = *((Relay<T>*) t.getLtsPointer());

  p.energize();

  p.startRelayOffTimer();

#ifdef BASIC_TESTING
  String feedback = "Relay (at pumpPin " + (String)p.getPin() + ") turned on";
  Serial.println(feedback);
#endif
}

template<class T>
void stopRelay() {
  Task& t = ts.currentTask();
  Relay<T>& p = *((Relay<T>*) t.getLtsPointer());

  p.deenergize();

#ifdef BASIC_TESTING
  String feedback = "Relay (pumpPin " + (String)p.getPin() + ") turned off";
  Serial.println(feedback);
#endif
}
