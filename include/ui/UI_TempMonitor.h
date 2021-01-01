//
// Created by Josue Figueroa on 12/31/20.
//

#ifndef FARMR_UI_TEMPMONITOR_H
#define FARMR_UI_TEMPMONITOR_H

#include <menu.h>

extern float currentTemp;

void turnOnTempMonitor();
void turnOffTempMonitor();

result setIdealTemp(eventMask,navNode&, prompt&);
result setTempInterval(eventMask,navNode&, prompt&);
result setTempDuration(eventMask,navNode&, prompt&);

#endif //FARMR_UI_TEMPMONITOR_H
