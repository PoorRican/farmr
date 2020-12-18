//
// Created by Josue Figueroa on 12/13/20.
//

#ifndef FARMR_MONITOR_PH_H
#define FARMR_MONITOR_PH_H

#include <Arduino.h>
#include "ProcessMonitor.h"
#include "SensorPH.h"
#include "pump_ph.h"

class pHMonitor : public ProcessMonitor {
public:
  pHMonitor(float &, uint16_t &, SensorPH &, Pump_pH &, Pump_pH &);

  ProcessType getType() const final;

  /**
   * Constrains value to 1.0 and 14.0
   * @return
   */
  bool setIdeal(float &) final;

  /**
   * Constrains value to 5 to 120 seconds.
   * Interval should not be too small.
   */
  bool setInterval(uint16_t &) final;

  void poll() final;

private:
                                    // to prevent buffer solution from continually being used
  const float tolerance = 0.2;      // tolerance between ideal and actual values
  SensorPH &sensor;
  Pump_pH &acidPump;
  Pump_pH &basePump;

  void increase() final;

  void decrease() final;

};

void pollPH();

#endif //FARMR_MONITOR_PH_H
