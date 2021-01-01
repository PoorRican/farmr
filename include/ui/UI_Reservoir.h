//
// Created by Josue Figueroa on 12/27/20.
//

#ifndef FARMR_UI_RESERVOIR_H
#define FARMR_UI_RESERVOIR_H

#include <menu.h>

extern uint8_t reservoirLevel;

void turnOnReservoirCycle();
void turnOffReservoirCycle();

result setReservoirThreshold(eventMask,navNode&, prompt&);
result setReservoirDuration(eventMask,navNode&, prompt&);
result setReservoirInterval(eventMask,navNode&, prompt&);

// Calibration Routines
result calibrateReservoirMax(eventMask, navNode&, prompt &);
result calibrateReservoirMin(eventMask, navNode&, prompt &);

#endif //FARMR_UI_RESERVOIR_H
