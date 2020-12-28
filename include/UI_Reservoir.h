//
// Created by Josue Figueroa on 12/27/20.
//

#ifndef FARMR_UI_RESERVOIR_H
#define FARMR_UI_RESERVOIR_H

#include <menu.h>

extern bool pumpingOn;
extern unsigned int threshold;
extern uint16_t reservoirDuration;
extern uint16_t reservoirInterval;

void turnOnReservoirPump();
void turnOffReservoirPump();

result setReservoirThreshold(eventMask,navNode&, prompt&);
result setReservoirDuration(eventMask,navNode&, prompt&);
result setReservoirInterval(eventMask,navNode&, prompt&);

// Menu Definitions


#endif //FARMR_UI_RESERVOIR_H
