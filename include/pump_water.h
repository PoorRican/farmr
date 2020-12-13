//
// Created by Josue Figueroa on 12/11/20.
//
// TODO: should night-pumping be allowed?
// TODO: ability to reset watering cycles

#ifndef FARMR_PUMP_WATER_H
#define FARMR_PUMP_WATER_H

#include <Time.h>
#include <TimeAlarms.h>
#include "timer.h"
#include "reservoir.h"

/**
 * TODO: this should be repurposed to run buffer pumps
 */
class WaterPump {
public:
  // Constructors
  WaterPump(const int&, Reservoir*);
  WaterPump(const WaterPump&);
  const WaterPump& operator=(const WaterPump&);

  // Destructor
  ~WaterPump();

  // ===========================
  // Timer Routines
  // ===========================

  /**
   * Timer for initiating pumping.
   * Automatically starts timer to turn off pump.
   */
  void startPumpOnTimer();

  /**
   * Cancels `startWaterTimer`.
   *
   * Automatically calls `stopPumpOffTimer`.
   *
   * This is used during `startWatering`,
   * and can be used when settings are changed or when reservoir is empty.
   *
   */
  void stopPumpOnTimer();

  /**
   * Timer for stopping pumping.
   *
   * Automatically calls next `startPumpOnTimer` using pumpInterval.
   *
   * @var min (int) : Turn off pump after x minutes
   */
  void startPumpOffTimer();

  /**
   * Cancels `startWaterOffTimer`
   */
  void stopPumpOffTimer();

  /**
   * Calculate when next cycle will begin
   *
   * TODO: handle fractions of an hour and uneven intervals
   *
   * @var hour (const int&) : current hour
   *
   * @return (int) hours until next alarm
   */
  int calcNextCycleTime(const int& hour) const;

  // Getters
  bool getPumpOn() const;
  int getFrequency() const;
  int getFloodTime() const;
  int getPin() const;

  // Setters
  /**
   * Sets `pumpInterval.flood` time in between 1 and 12 minutes.
   * @var min (int&) : desired cycle length
   * @return
   */
  bool setFloodTime(int &min);

  /**
   * Sets frequency of cycling to no more than 12 times per day.
   * @var freq (int&) : desired cycle frequency
   * @return true if parameter is valid
   */
  bool setFrequency(int &freq);

private:
  int pin;
  Reservoir* reservoir;
  boolean pumpOn = false;

  /**
   * Timers for when pump will be turned on or off
   */
  timer pumpTimer;
  timer pumpOffTimer;

  /**
   * Defines how long to run pumps (in minutes)
   */
  struct pump_interval_t {
    int flood = 10;         // duration of how long pump will be run for
    int frequency = 4;      // how many times a day to cycle
  } pumpInterval;

  // ===========================
  // WaterPump Routines
  // ===========================
  /**
   * Callback function to turn on pump
   */
  OnTick_t startWatering();
  /**
   * Callback function to turn off pump
   */
  OnTick_t stopWatering();

};

#endif //FARMR_PUMP_WATER_H
