//
// Created by Josue Figueroa on 12/13/20.
//

#ifndef FARMR_MONITORPH_H
#define FARMR_MONITORPH_H

#include <Arduino.h>
#include "ProcessMonitor.h"
#include "sensors/SensorPH.h"
#include "appliances/PumpPh.h"

class MonitorPh : public ProcessMonitor {
public:
  MonitorPh(float &, uint16_t &, SensorPH &, PumpPh &, PumpPh &);

  ProcessType getType() const final;

  /**
   * Constrains value to 1.0 and 14.0
   * @return
   */
  bool setIdeal(float &) final;

  float getCurrentPh() const;

  /**
   * Constrains value to 5 to 120 seconds.
   * Interval should not be too small.
   */
  bool setInterval(uint16_t &) final;
  bool setDuration(uint16_t&);

  void poll() final;

private:
                                    // to prevent buffer solution from continually being used
  const float tolerance = 0.2;      // tolerance between ideal and actual values
  SensorPH &sensor;
  PumpPh &acidPump;
  PumpPh &basePump;

  void increase() final;

  void decrease() final;

};

void pollPH();

#endif //FARMR_MONITORPH_H
