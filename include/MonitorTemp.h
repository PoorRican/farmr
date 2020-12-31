//
// Created by Josue Figueroa on 12/31/20.
//

#ifndef FARMR_MONITORTEMP_H
#define FARMR_MONITORTEMP_H

#include "ProcessMonitor.h"
#include "sensors/SensorTemp.h"
#include "appliances/PumpWater.h"
#include "appliances/ThermoElectricElement.h"

class MonitorTemp : public ProcessMonitor {
public:
  MonitorTemp(float &, uint16_t &, uint16_t &, SensorTemp &, PumpWater &, ThermoElectricElement&, ThermoElectricElement&);

  ProcessType getType() const final;

  /**
   * Constrains value to 1.0 and 14.0
   * @return
   */
  bool setIdeal(float &) final;

  float getCurrentTemp() const;

  /**
   * Constrains value to 15 to 120 minutes.
   * Interval should not be too small.
   */
  bool setInterval(uint16_t &) final;
  bool setDuration(uint16_t&);

  void poll() final;

private:
  const float tolerance = 5.0;      // tolerance between ideal and actual values
  uint16_t duration;

  SensorTemp &sensor;
  PumpWater &pump;
  ThermoElectricElement &heatingElement;
  ThermoElectricElement &coolingElement;

  void increase() final;

  void decrease() final;
};

void pollTemp();

#endif //FARMR_MONITORTEMP_H
