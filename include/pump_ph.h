//
// Created by Josue Figueroa on 12/12/20.
//

#ifndef FARMR_PUMP_PH_H
#define FARMR_PUMP_PH_H

#include "pump.h"
#include <TaskSchedulerDeclarations.h>
#include "sensor_ping.h"

class Pump_pH : public Pump {
public:
  explicit Pump_pH(const uint8_t &pin, uint16_t &duration, Scheduler*);
  Pump_pH(const Pump_pH &) = default;
  Pump_pH& operator=(const Pump_pH&) = default;

  ~Pump_pH() = default;

  // Setters
  /**
   * Ensures that duration is an integer less than 10 seconds
   * @return true if given duration is valid.
   */
  bool setDuration(const uint16_t&) final;

  bool aboveThreshold() const final;

  void restart();

protected:
  bool oneShot = true;
};


#endif //FARMR_PUMP_PH_H
