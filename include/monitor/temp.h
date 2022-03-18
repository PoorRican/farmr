//
// Created by Josue Figueroa on 12/31/20.
//

#ifndef FARMR_MONITORTEMP_H
#define FARMR_MONITORTEMP_H

#include "monitor.h"
#include "sensors/temp.h"
#include "appliances/WaterPump.h"
#include "appliances/ThermoElectricElement.h"

class MonitorTemp : public Monitor {
public:
  MonitorTemp(float &, uint16_t &, uint16_t &, SensorTemp *, WaterPump *, ThermoElectricElement *, ThermoElectricElement *);

  ProcessType getType() const final;

  /**
   * Constrains value to 1.0 and 14.0
   * @return
   */
  bool setIdeal(float &) final;

  float getTemp();

  /**
   * Constrains value to 15 to 120 minutes.
   * Interval should not be too small.
   */
  bool setInterval(uint16_t &) final;
  bool setDuration(uint16_t&);

  void poll() final;

protected:
  /// tolerance between ideal and actual values
  constexpr static float tolerance = 1.5;

  /// change PID tuning when within this gap
  constexpr static double gap_threshold = 5.0;

  float temperature;

  SensorTemp *sensor;
  WaterPump *pump;
  ThermoElectricElement *heatingElement;
  ThermoElectricElement *coolingElement;

  void increase() final;
  void decrease() final;
};

void pollTemp();

#endif //FARMR_MONITORTEMP_H
