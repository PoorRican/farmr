//
// Created by Josue Figueroa on 12/11/20.
//
// TODO: should night-pumping be allowed?
// TODO: ability to reset watering cycles

#ifndef FARMR_PUMP_WATER_H
#define FARMR_PUMP_WATER_H

#include "pump.h"
#include <TaskSchedulerDeclarations.h>
#include <Time.h>
#include "sensor_ping.h"

class WaterPump : public Pump {
public:
  // Constructors
  WaterPump(const uint8_t &pin, uint16_t &duration, uint16_t &interval,
            SensorPing *sonar, Scheduler*);
  WaterPump(const WaterPump &other) = default;
  WaterPump& operator=(const WaterPump&) = default;

  ~WaterPump() = default;

  // Setters
  /**
   * Sets duration that water pin should be run in.
   * Converts minutes to seconds.
   * @var min (uint16_t) : minutes
   * @return true if min greater-than 0 and less-than or equal to 12
   */
  bool setDuration(const uint16_t&) final;
  /** Sets frequency interval of water pin cycles.
   * @var freq (uint16_t) : count of cycles to run daily
   * @return true if freq greater-than 0 and less-than or equal to 12
   */
  bool setInterval(const uint16_t&);
  uint16_t getInterval() const;

  bool aboveThreshold() const final;

protected:
  SensorPing *sonar = nullptr;

  uint16_t interval;   // Min interval in-between pin activations
};

#endif //FARMR_PUMP_WATER_H
