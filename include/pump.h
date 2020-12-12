//
// Created by Josue Figueroa on 12/11/20.
//
// TODO: should night-pumping be allowed?
// TODO: ability to reset watering cycles

#ifndef FARMR_PUMP_H
#define FARMR_PUMP_H

#include "timer.h"
#include "reservoir.h"
#include <TimeAlarms.h>

/**
 * TODO: this should be repurposed to run buffer pumps
 */
class Pump {
public:
  // Constructors
  Pump(int, Reservoir*);
  Pump(const Pump&);
  const Pump& operator=(const Pump&);

  // Destructor
  ~Pump();

  // ===========================
  // Timer Routines
  // ===========================

  /**
   * Timer for initiating pumping.
   * Automatically starts timer to turn off pump.
   * @var min (int) : Turn on pump after x minutes
   */
  void startPumpOnTimer(int min = 0);

  /**
   * Cancels `startWaterTimer`.
   *
   * Automatically calls `stopPumpOffTimer`.
   *
   * This is used during `startWatering`,
   * and can be used when settings are changed or when reservoir is empty.
   *
   */
  static void stopPumpOnTimer();

  /**
   * Timer for stopping pumping.
   *
   * Automatically calls next `startPumpOnTimer` using pumpInterval.
   *
   * @var min (int) : Turn off pump after x minutes
   */
  void startPumpOffTimer(int min = 0);

  /**
   * Cancels `startWaterOffTimer`
   */
  static void stopPumpOffTimer();

  // Getters
  bool getPumpOn();

private:
  int pin;
  Reservoir* reservoir;
  boolean pumpOn = false;

  /**
   * Defines how long to run pumps (in minutes)
   */
  struct pump_interval_t {
    int flood = 5;  // duration of how long pump will be run for
    int gap = 55;   // intervals between flooding
  } pumpInterval;

  // ===========================
  // Pump Routines
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

#endif //FARMR_PUMP_H
