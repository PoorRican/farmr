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
  Pump(uint8_t pin, uint16_t duration, uint16_t interval, SensorPing &sonar)
  : pin(pin), duration(duration), interval(interval), sonar(sonar) {};
  Pump(const Pump&);
  const Pump& operator=(const Pump&);

  ~Pump() = default;

  // Timer Routines
  void startPumpOnTimer();
  void stopPumpOnTimer();
  void startPumpOffTimer();
  void stopPumpOffTimer();
  virtual int calcNextOnTime() = 0;

  // Getters
  bool getPumpOn() const;
  uint16_t getDuration() const;
  uint16_t getFloodTime() const;
  uint8_t getPin() const;

  // Setters
  virtual bool setDuration(uint16_t&) = 0;
  virtual bool setInterval(uint16_t&) = 0;

protected:
  SensorPing &sonar;
  bool pumpOn = false;
  uint8_t pin;
  uint16_t duration;   // Max duration to keep pump active
  uint16_t interval;   // Min interval in-between pump activations

  timer pumpTimer;
  timer pumpOffTimer;

  // Callback functions
  OnTick_t startWatering();
  OnTick_t stopWatering();


};

#endif //FARMR_PUMP_H
