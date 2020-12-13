//
// Created by Josue Figueroa on 12/12/20.
//

#ifndef FARMR_PUMP_PH_H
#define FARMR_PUMP_PH_H


#include "pump.h"
#include "sensor_ping.h"


class Pump_pH : public Pump {
  Pump_pH(uint8_t &pin, uint16_t &duration, uint16_t &interval, SensorPing *sonar)
  : Pump(pin, duration, interval, sonar) {};
  Pump_pH(const Pump_pH &other) : Pump(other) {}
  Pump_pH& operator=(const Pump_pH&);

  ~Pump_pH() = default;

  // Setters
  /**
   * Ensures that duration is an integer less than 10 seconds
   * @return true if given duration is valid.
   */
  bool setDuration(uint16_t&) final;
  /**
   * Ensures that interval is in-between 10 and 120 seconds.
   * @return true if given interval is valid.
   */
  bool setInterval(uint16_t&) final;

  /**
   * Start pump immediately
   * @return 1
   */
  int calcNextOnTime() const final;
};


#endif //FARMR_PUMP_PH_H
