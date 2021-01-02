//
// Created by Josue Figueroa on 12/12/20.
//

#ifndef FARMR_PUMPPH_H
#define FARMR_PUMPPH_H

#include "Relay.h"
#include <TaskSchedulerDeclarations.h>

/**
 * Represents a pump that is activated for seconds at a time.
 */
class PumpPh : public Relay {
public:
  explicit PumpPh(const uint8_t &pin, uint16_t &duration);
  PumpPh(const PumpPh &) = default;
  PumpPh& operator=(const PumpPh&) = default;

  ~PumpPh() = default;

  // Setters
  /**
   * Ensures that duration is an integer less than 10 seconds
   * @return true if given duration is valid.
   */
  bool setDuration(const uint16_t&) final;

  void restart();
};


#endif //FARMR_PUMPPH_H
