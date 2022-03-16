//
// Created by Josue Figueroa on 12/12/20.
//

#ifndef FARMR_RELAY_H
#define FARMR_RELAY_H

#define _TASK_LTS_POINTER       // Compile with support for local task storage pointer

#include <Arduino.h>
#include <TaskSchedulerDeclarations.h>

extern Scheduler ts;

/**
 * Represents a relay controlled by a relay circuit.
 * All timing tasks are handled internally. Derivative classes only need to overwrite `setDuration`.
 *
 * `T` is the variable type used to define pump duration. eg: float. Defaults to uint16_t
 */
template<class T=uint16_t>
class Relay {
public:
  enum RelayType {
    None,
    PumpWater,
    PumpPh,
    PumpNutrient,
    ThermoElectricElement,
  };
  /**
   *
   * @param pin : Output pumpPin of pump
   * @param duration : duration of pump being applied (in minutes)
   * @param interval : time between pump activations (in hours)
   */
  explicit Relay(const uint8_t &pin, T &duration, bool=true);
  Relay(const Relay&) = default;
  Relay& operator=(const Relay&) = default;

  ~Relay() = default;

  virtual RelayType getType() const;

  void init() const;
  void addTasks(Scheduler&);

  // Timer Routines
  void startRelayOnTimer();
  void stopRelayOnTimer() const;
  void startRelayOffTimer();
  void stopRelayOffTimer() const;

  // Getters
  bool getRelayOn() const;
  T getDuration() const;
  uint8_t getPin() const;
  bool getInverse() const;

  // Setters
  void setRelayOn(bool);
  virtual bool setDuration(const T&) = 0;
  void setInverse(bool);

  // Relay Routines
  void energize();
  void deenergize();

protected:
  bool relayOn = false;
  bool inverse;         // Relay is energized with logic-LOW. Defaults to true
  uint8_t pin;
  T duration;           /// Stores the raw value of time to keep pump activated

  Task *relayTimer = nullptr;
  Task *relayOffTimer = nullptr;
};

void startRelay();
void stopRelay();


#endif //FARMR_RELAY_H
