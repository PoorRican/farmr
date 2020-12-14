//
// Created by Josue Figueroa on 12/13/20.
//

#ifndef FARMR_PROCESSMONITOR_H
#define FARMR_PROCESSMONITOR_H


#include <Arduino.h>
#include "timer.h"


/**
 * Abstract watchdog class for monitoring a process/metric (eg: pH, filtering, Nx) and controlling pumps.
 */
class ProcessMonitor {
public:
  enum ProcessType {
    None,
    Filtration,
    Nitrobacter,
    pH
  };
  ProcessMonitor(float &ideal, uint16_t &interval);
  virtual ProcessType getType() const = 0;
  virtual bool setIdeal(float&) = 0;
  virtual bool setInterval(uint16_t&) = 0;

  void startPolling();
  void stopPolling();
  /**
   * Main function and called by polling timer.
   * Measure area of responsibility then attempt to get to ideal.
   * Uses `read`, `increase`, and `decrease`.
   */
  virtual OnTick_t poll() = 0;

protected:
  float ideal;         // Ideal value
  uint16_t interval;      // Interval to control polling

  timer pollingTimer;

  virtual void increase() = 0;
  virtual void decrease() = 0;
};


#endif //FARMR_PROCESSMONITOR_H
