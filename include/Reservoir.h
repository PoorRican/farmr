//
// Created by Josue Figueroa on 12/30/20.
//

#ifndef FARMR_RESERVOIR_H
#define FARMR_RESERVOIR_H

#include "appliances/PumpWater.h"
#include "sensors/SensorLevel.h"

class Reservoir {
public:
  Reservoir(const uint16_t &, const uint8_t &, PumpWater*, SensorLevel *);
  Reservoir(const Reservoir &) = default;
  Reservoir& operator=(const Reservoir&) = default;

  ~Reservoir() = default;

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
   * Sets threshold. Should be a percent as an inteeger.
   * @return true if between 1 and 100; otherwise false
   */
  bool setThreshold(const uint8_t&);

  uint16_t getInterval() const;
  uint8_t getThreshold() const;

  void addTasks(Scheduler&);
  void runCycle();
  void startCycle();
  void stopCycle();

protected:
  SensorLevel *level;
  PumpWater *pump;
  Task *cycleTimer;

  uint16_t interval;
  uint8_t threshold;

  bool aboveThreshold() const;
};

void cycleWater();

#endif //FARMR_RESERVOIR_H
