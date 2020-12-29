//
// Created by Josue Figueroa on 12/27/20.
//

#ifndef FARMR_UI_PHMONITOR_H
#define FARMR_UI_PHMONITOR_H

#include <menu.h>

extern float currentPh;

void turnOnPhMonitor();
void turnOffPhMonitor();

result setIdealPh(eventMask,navNode&, prompt&);
result setPhPollInterval(eventMask,navNode&, prompt&);
result setPhPumpDuration(eventMask,navNode&, prompt&);

#endif //FARMR_UI_PHMONITOR_H
