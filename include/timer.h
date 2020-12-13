//
// Created by Josue Figueroa on 12/11/20.
//

#ifndef FARMR_TIMER_H
#define FARMR_TIMER_H

#include <TimeAlarms.h>

struct timer {
  AlarmID_t id;
  boolean enabled = false;
};

#endif //FARMR_TIMER_H
