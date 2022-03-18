//
// Created by Josue Figueroa on 12/13/20.
//

#ifndef FARMR_MONITOR_H
#define FARMR_MONITOR_H

#define _TASK_LTS_POINTER       // Compile with support for local task storage pointer

#include <Arduino.h>
#include <TaskSchedulerDeclarations.h>
#include <PID_v1.h>

/// Stores P,I,D function tuning values
struct tuning_param_t {
  double Kp;
  double Ki;
  double Kd;
};

enum pid_tuning_mode_t {
  Aggressive,
  Conservative
};

/**
 * Abstract watchdog class for monitoring a process/metric (eg: pH, filtering, Nx) and controlling pumps.
 *
 * Derived classes should define a duration, which defines a max window size. Using time proportioning control (TPC),
 * the PID output is normalized in relation to this window size.
 *
 * There is also an aggressive and conservative PID tuning that alternate depending on how close the input is to setpoint.
 * Both tunings are adjustable via Serial commands, as it is not practical for UI.
 *
 * Implementation of TPC and adaptive tunings are based on the examples included in the PID library.
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
  explicit Monitor(double &ideal, uint16_t &interval, uint16_t &duration);

  virtual ProcessType getType() const = 0;

  virtual bool setSetpoint(double&) = 0;
  double getSetpoint() const;

  virtual bool setInterval(uint16_t&) = 0;
  uint16_t getInterval() const;

  void addTasks(Scheduler&);

  void startPolling();
  void stopPolling();
  /**
   * Main function and called by polling timer.
   * Measure area of responsibility then attempt to get to setpoint.
   * Uses `read`, `increase`, and `decrease`.
   */
  virtual void poll() = 0;

  // PID Methods
  /**
   * Sets PID to normalize output, and starts the PID
   */
  void initPid();

  /**
   * Switches tune PID tuning mode
   * @param tune desired aggressiveness
   */
  void switchPidMode(pid_tuning_mode_t tune);
  /**
   * @return current PID aggressiveness mode
   */
  pid_tuning_mode_t getPidMode() const;

  /**
   * Change parameters for aggressive tune
   */
  void setAggressiveTune(double &, double &, double&);
  /**
   * Get parameters for aggressive tune
   */
  tuning_param_t getAggressiveTune() const;

  /**
   * Change parameters for conservative tune
   */
  void setConservativeTune(double &, double &, double&);
  /**
   * Get parameters for conservative tune
   */
  tuning_param_t getConservativeTune() const;

protected:
  /// Equilibrium/setpoint value
  double setpoint;

  /// Sensor data used as input for PID-function
  double input;

  /// Polling interval
  uint16_t interval;

  /// TPC output
  uint16_t duration;

  /// Defines a maximum time for PID output.
  /// Must be overwritten by derived classes
  uint16_t window_size;

  Task *pollingTimer;

  /// current PID tuning
  pid_tuning_mode_t pid_mode;

  /// aggressive tuning parameter. When far away from setpoint.
  tuning_param_t aggr = {4, 0.2, 1};
  /// conservative tuning parameter. When close to setpoint.
  tuning_param_t cons = {1, 0.05, 0.25};

  PID *pid;

  virtual void increase() = 0;
  virtual void decrease() = 0;
};


#endif //FARMR_MONITOR_H
