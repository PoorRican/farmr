//
// Created by Josue Figueroa on 12/11/20.
//
// TODO: should night-pumping be allowed?
// TODO: ability to reset watering cycles

#ifndef FARMR_PUMPWATER_H
#define FARMR_PUMPWATER_H

#include "Relay.h"
#include <TaskSchedulerDeclarations.h>
#include <Time.h>
#include "sensors/SensorLevel.h"

/**
 * Represents a pump that is activated for minutes at a time.
 */
class PumpWater : public Relay<> {
public:
  // Constructors
  PumpWater(const uint8_t &pin, uint16_t &duration);
  PumpWater(const PumpWater &other) = default;
  PumpWater& operator=(const PumpWater&) = default;

  ~PumpWater() = default;

  // Setters
  /**
   * Sets duration that water pumpPin should be run in.
   * Converts minutes to seconds.
   * @var min (uint16_t) : minutes
   * @return true if min greater-than 0 and less-than or equal to 12
   */
  bool setDuration(const uint16_t&) final;

  void restart();
};

#endif //FARMR_PUMPWATER_H
