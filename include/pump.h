//
// Created by Josue Figueroa on 12/12/20.
//

#ifndef FARMR_PUMP_H
#define FARMR_PUMP_H

#include <Arduino.h>
#include "scheduler.h"
#include "sensor_ping.h"

extern Scheduler ts;

class Pump {
public:
  explicit Pump(const uint8_t &pin, uint16_t &duration, uint16_t &interval, SensorPing *sonar);
  Pump(const Pump&) = default;
  Pump& operator=(const Pump&) = default;

  ~Pump() = default;

  void init() const;

  // Timer Routines
  void startPumpOnTimer();
  void stopPumpOnTimer();
  void startPumpOffTimer();
  void stopPumpOffTimer();
  virtual int calcNextOnTime() const = 0;

  // Getters
  bool getPumpOn() const;
  uint16_t getDuration() const;
  uint16_t getInterval() const;
  uint8_t getPin() const;
  bool aboveThreshold() const;

  // Setters
  void setPumpOn(bool);
  virtual bool setDuration(const uint16_t&) = 0;
  virtual bool setInterval(const uint16_t&) = 0;

protected:
  bool pumpOn = false;
  uint8_t pin;
  uint16_t duration;   // Max duration to keep pin active
  uint16_t interval;   // Min interval in-between pin activations
  SensorPing *sonar = nullptr;

  Task *pumpTimer = nullptr;
  Task *pumpOffTimer = nullptr;
};

void startWatering();
void stopWatering();


#endif //FARMR_PUMP_H
