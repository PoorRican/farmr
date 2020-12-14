//
// Created by Josue Figueroa on 12/12/20.
//

#ifndef FARMR_PUMP_H
#define FARMR_PUMP_H

#include <Arduino.h>
#include "timer.h"
#include "sensor_ping.h"


class Pump {
public:
  explicit Pump(uint8_t &pin, uint16_t &duration, uint16_t &interval, SensorPing *sonar)
  : pin(pin), duration(duration), interval(interval), sonar(sonar) {};
  Pump(const Pump&);
  Pump& operator=(const Pump&);

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

  // Setters
  virtual bool setDuration(uint16_t&) = 0;
  virtual bool setInterval(uint16_t&) = 0;

protected:
  bool pumpOn = false;
  bool oneShot = false;
  uint8_t pin;
  uint16_t duration;   // Max duration to keep pump active
  uint16_t interval;   // Min interval in-between pump activations
  SensorPing *sonar = nullptr;

  timer pumpTimer;
  timer pumpOffTimer;

  // Callback functions
  OnTick_t startWatering();
  OnTick_t stopWatering();


};

#endif //FARMR_PUMP_H
