//
// Created by Josue Figueroa on 12/11/20.
//
// TODO: should night-pumping be allowed?
// TODO: ability to reset watering cycles

#ifndef FARMR_PUMP_WATER_H
#define FARMR_PUMP_WATER_H

#include <Time.h>
#include <TimeAlarms.h>
#include "pump.h"
#include "sensor_ping.h"

class WaterPump : public Pump {
public:
  // Constructors
  WaterPump(const uint8_t &pin, const uint16_t &duration, const uint16_t &interval,
            SensorPing *sonar);
  WaterPump(const WaterPump &other) = default;
  WaterPump& operator=(const WaterPump&) = default;

  ~WaterPump() = default;

  // Setters
  /**
   * Sets duration that water pump should be run in.
   * Converts minutes to seconds.
   * @var min (uint16_t) : minutes
   * @return true if min greater-than 0 and less-than or equal to 12
   */
  bool setDuration(const uint16_t&) final;
  /** Sets frequency interval of water pump cycles.
   * @var freq (uint16_t) : count of cycles to run daily
   * @return true if freq greater-than 0 and less-than or equal to 12
   */
  bool setInterval(const uint16_t&) final;

  /**
   * Calculate when next cycle will begin
   *
   * TODO: handle fractions of an hour and uneven intervals
   *
   * @var hour (const int&) : current hour
   *
   * @return (int) hours until next alarm
   */
  int calcNextOnTime() const final;
};

#endif //FARMR_PUMP_WATER_H
