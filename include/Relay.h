//
// Created by Josue Figueroa on 12/12/20.
//

#ifndef FARMR_RELAY_H
#define FARMR_RELAY_H

#define _TASK_LTS_POINTER       // Compile with support for local task storage pointer

#include <Arduino.h>
#include <TaskSchedulerDeclarations.h>
#include "sensors/sensor_ping.h"

extern Scheduler ts;

/**
 * Represents a relay controlled by a relay circuit, where a logic-LOW turns on the relay.
 * All timing tasks are handled internally. Derivative classes only need to overwrite `setDuration`
 */
class Relay {
public:
  /**
   *
   * @param pin : Output pumpPin of pump
   * @param duration : duration of pump being applied (in minutes)
   * @param interval : time between pump activations (in hours)
   */
  explicit Relay(const uint8_t &pin, uint16_t &duration);
  Relay(const Relay&) = default;
  Relay& operator=(const Relay&) = default;

  ~Relay() = default;

  void init() const;
  void addTasks(Scheduler&);

  // Timer Routines
  void startPumpOnTimer();
  void stopPumpOnTimer() const;
  void startPumpOffTimer();
  void stopPumpOffTimer() const;

  // Getters
  bool getPumpOn() const;
  uint16_t getDuration() const;
  uint8_t getPin() const;

  // Setters
  void setPumpOn(bool);
  virtual bool setDuration(const uint16_t&) = 0;

protected:
  bool pumpOn = false;
  uint8_t pin;
  uint16_t duration;   /// Stores the raw value of time to keep pump activated

  Task *pumpTimer = nullptr;
  Task *pumpOffTimer = nullptr;
};

void startPump();
void stopPump();


#endif //FARMR_RELAY_H
