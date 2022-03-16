//
// Created by Josue Figueroa on 12/13/20.
//

#ifndef FARMR_MONITOR_H
#define FARMR_MONITOR_H

#include <Arduino.h>
#include <TaskSchedulerDeclarations.h>

/**
 * Abstract watchdog class for monitoring a process/metric (eg: pH, filtering, Nx) and controlling pumps.
 * TODO: PID will be implemented here
 */
class Monitor {
public:
  enum ProcessType {
    None,
    Filtration,
    Nitrobacter,
    pH,
    Temperature
  };
  explicit Monitor(float &ideal, uint16_t &interval);

  virtual ProcessType getType() const = 0;
  virtual bool setIdeal(float&) = 0;
  float getIdeal() const;
  virtual bool setInterval(uint16_t&) = 0;
  uint16_t getInterval() const;

  void addTasks(Scheduler&);

  void startPolling();
  void stopPolling();
  /**
   * Main function and called by polling timer.
   * Measure area of responsibility then attempt to get to ideal.
   * Uses `read`, `increase`, and `decrease`.
   */
  virtual void poll() = 0;

protected:
  float ideal;            // Equilibrium value
  uint16_t interval;      // Polling interval

  Task *pollingTimer = nullptr;

  virtual void increase() = 0;
  virtual void decrease() = 0;
};


#endif //FARMR_MONITOR_H
