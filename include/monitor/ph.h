//
// Created by Josue Figueroa on 12/13/20.
//

#ifndef FARMR_MONITORPH_H
#define FARMR_MONITORPH_H

#include "monitor.h"

#include "sensors/ph.h"
#include "appliances/ReagentPump.h"

class MonitorPh : public Monitor {
public:
  MonitorPh(double &, uint16_t &, uint16_t &, SensorPH *, ReagentPump *, ReagentPump *);

  ProcessType getType() const final;

  /**
   * Constrains value to 1.0 and 14.0
   * @return
   */
  bool setIdeal(double &) final;

  double getPh();

  /**
   * Constrains value to 5 to 120 seconds.
   * Interval should not be too small.
   */
  bool setInterval(uint16_t &) final;
  bool setDuration(uint16_t&);

  void poll() final;

protected:
  /// tolerance between ideal and actual values
  /// to prevent buffer solution from continually being used
  constexpr static double tolerance = 0.1;

  /// change PID tuning when within this gap
  constexpr static double gap_threshold = 0.9;

  double ph{};

  SensorPH *sensor;
  ReagentPump *acidPump;
  ReagentPump *basePump;

  void increase() final;
  void decrease() final;

};

void pollPH();

#endif //FARMR_MONITORPH_H
