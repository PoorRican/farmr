//
// Created by Josue Figueroa on 12/12/20.
//

#include "scheduler.h"
#include "appliances/Relay.h"

template<class T>
Relay<T>::Relay(const uint8_t &pin, T &duration, bool inverse)
: pin(pin), duration(duration), inverse(inverse) {

  relayTimer = new Task(TASK_IMMEDIATE, TASK_ONCE, startRelay);
  relayTimer->setLtsPointer(this);
  relayOffTimer = new Task(this->duration, TASK_ONCE, stopRelay);
  relayOffTimer->setLtsPointer(this);
};

template<class T>
typename Relay<T>::RelayType Relay<T>::getType() const {
  return None;
}

template<class T>
void Relay<T>::init() const {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);            // immediately de-energize coil upon power applied
}

template<class T>
void Relay<T>::addTasks(Scheduler &scheduler) {
  scheduler.addTask(*(relayTimer));
  scheduler.addTask(*(relayOffTimer));
}


template<class T>
void Relay<T>::startRelayOnTimer() {
#ifdef VERBOSE_OUTPUT
  Serial.println("'startRelayOnTimer' called");
#endif
  relayTimer->enable();
}

template<class T>
void Relay<T>::stopRelayOnTimer() const {
#ifdef VERBOSE_OUTPUT
  Serial.println("'stopRelayOnTimer' called");
#endif
  relayTimer->disable();
}

template<class T>
void Relay<T>::startRelayOffTimer() {
#ifdef VERBOSE_OUTPUT
  Serial.println("'startRelayOffTimer' called");
#endif
  relayOffTimer->set(duration, TASK_ONCE, stopRelay);
  setDuration(duration);
  relayOffTimer->enableDelayed();
}

template<class T>
void Relay<T>::stopRelayOffTimer() const {
#ifdef VERBOSE_OUTPUT
  Serial.println("'stopRelayOffTimer' called");
#endif
  relayOffTimer->disable();
}


// Getters
template<class T>
bool Relay<T>::getRelayOn() const {
  return relayOn;
}

template<class T>
T Relay<T>::getDuration() const {
  return duration;
}

template<class T>
uint8_t Relay<T>::getPin() const {
  return pin;
}

template<class T>
bool Relay<T>::getInverse() const {
  return inverse;
}

// Setters
template<class T>
void Relay<T>::setRelayOn(bool val) {
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

template<class T>
void Relay<T>::setInverse(bool val) {
  inverse = val;
}

// Relay routines
template<class T>
void Relay<T>::energize() {
#ifdef Arduino_h
  digitalWrite(pin, (inverse) ? LOW : HIGH);
#endif
  setRelayOn(true);
}

template<class T>
void Relay<T>::deenergize() {
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