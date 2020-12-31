//
// Created by Josue Figueroa on 12/12/20.
//

#ifndef FARMR_PUMP_H
#define FARMR_PUMP_H

#define _TASK_LTS_POINTER       // Compile with support for local task storage pointer

#include <Arduino.h>
#include <TaskSchedulerDeclarations.h>
#include "sensor_ping.h"

extern Scheduler ts;

class Pump {
public:
  /**
   *
   * @param pin : Output pumpPin of pump
   * @param duration : duration of pump being applied (in minutes)
   * @param interval : time between pump activations (in hours)
   */
  explicit Pump(const uint8_t &pin, uint16_t &duration);
  Pump(const Pump&) = default;
  Pump& operator=(const Pump&) = default;

  ~Pump() = default;

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
  virtual bool aboveThreshold() const = 0;

  // Setters
  void setPumpOn(bool);
  virtual bool setDuration(const uint16_t&) = 0;

protected:
  bool pumpOn = false;
  uint8_t pin;
  unsigned long duration;   // Max duration to keep pumpPin active

  Task *pumpTimer = nullptr;
  Task *pumpOffTimer = nullptr;
};

void startPump();
void stopPump();


#endif //FARMR_PUMP_H
