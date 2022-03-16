//
// Created by Josue Figueroa on 12/12/20.
//

#ifndef FARMR_REAGENTPUMP_H
#define FARMR_REAGENTPUMP_H

#include "relay.h"
#include <TaskSchedulerDeclarations.h>

/**
 * Represents a pump that is activated for seconds at a time.
 */
class ReagentPump : public Relay<> {
public:
  explicit ReagentPump(const uint8_t &pin, uint16_t &duration);
  ReagentPump(const ReagentPump &) = default;
  ReagentPump& operator=(const ReagentPump&) = default;

  ~ReagentPump() = default;

  // Setters
  /**
   * Ensures that duration is an integer less than 10 seconds
   * @return true if given duration is valid.
   */
  bool setDuration(const uint16_t &) final;

  void restart();
};


#endif //FARMR_REAGENTPUMP_H
