//
// Created by Josue Figueroa on 12/31/20.
//

#ifndef FARMR_THERMOELECTRICELEMENT_H
#define FARMR_THERMOELECTRICELEMENT_H

#include "relay.h"

/**
 * Represents a heating element or peltier cooler connected to a relay
 */
class ThermoElectricElement : public Relay<> {
public:
  // Constructors
  ThermoElectricElement(const uint8_t &pin, uint16_t &duration);
  ThermoElectricElement(const ThermoElectricElement &other) = default;
  ThermoElectricElement& operator=(const ThermoElectricElement&) = default;

  ~ThermoElectricElement() = default;

  // Setters
  /**
   * Sets duration that thermoelectric element should be run for.
   * Converts minutes to seconds.
   * @var min (uint16_t) : minutes
   * @return true if greater-than 0 and less-than or equal to 20
   */
  bool setDuration(const uint16_t&) final;

  void restart();
};

#endif //FARMR_THERMOELECTRICELEMENT_H
