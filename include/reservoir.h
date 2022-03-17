//
// Created by Josue Figueroa on 12/30/20.
//

#ifndef FARMR_RESERVOIR_H
#define FARMR_RESERVOIR_H

#include <Arduino.h>
#include <TaskSchedulerDeclarations.h>
#include "appliances/WaterPump.h"
#include "sensors/distance.h"

/**
 * This class serves as a water cycle timer and monitor for reservoir levels.
 * Water cycle functionality does not serve a purpose in a DWC / NFT style system,
 * therefore it should be disabled.
 */
class Reservoir {
public:
  Reservoir(const uint16_t &, const uint8_t &, WaterPump*, SensorDistance *);
  Reservoir(const Reservoir &) = default;
  Reservoir& operator=(const Reservoir&) = default;

  ~Reservoir() = default;

  enum PumpMode {
    Off,
    Cycle,
    Continuous
  };

  /**
   * Duration of water cycle.
   * @var min (uint16_t) : minutes
   * @return true if min greater-than 0 and less-than or equal to 12
   */
  bool setDuration(const uint16_t&);
  uint16_t getDuration() const;
  /** Sets frequency interval of water cycles.
   * @var freq (uint16_t) : amount of time in between cycles
   * @return true if freq greater-than 0 and less-than or equal to 12
   */
  bool setInterval(const uint16_t&);
  /**
   * Sets threshold. Should be a percent as an integer.
   * @return true if between 1 and 100; otherwise false
   */
  bool setThreshold(const uint8_t&);

  uint16_t getInterval() const;
  uint8_t getThreshold() const;

  uint8_t getCurrentLevel() const;

  void addTasks(Scheduler&);

  // ===============================
  // Pump Control

  PumpMode getPumpMode() const;

  /**
   * Immediately restarts cycle
   */
  void runCycleNow();

  /**
   * Immediately turns on pumps. Disables cycle.
   * This is meant to be used for DWC systems.
   */
  void enableContinuous();

  /**
   * Begins timer scheduling.
   * Meant for NFT systems or any other system that requires a cycle.
   */
  void enableCycle();
  /**
   * Stops timer scheduling, turns off pump
   */
  void disableCycle();

protected:
  PumpMode mode;
  uint16_t interval;
  uint8_t threshold;

  WaterPump *pump;
  SensorDistance *level;
  Task *cycleTimer;

  bool aboveThreshold() const;
};

void cycleWater();

#endif //FARMR_RESERVOIR_H
