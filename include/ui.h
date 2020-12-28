//
// Created by Josue Figueroa on 12/25/20.
//

#ifndef FARMR_UI_H
#define FARMR_UI_H

#include <Arduino.h>
#include <Wire.h>
#include <menu.h>
#include <menuIO/liquidCrystalOut.h>
#include <menuIO/serialOut.h>
#include <menuIO/chainStream.h>
#include <AnalogButtons.h>
#include <ui.h>
#include "settings.h"

using namespace Menu;

extern navRoot nav;
extern LiquidCrystal lcd;

void pollUi();

void bDwn();
void bUp();
void bSel();
void bEsc();

// Reservoir Pump
extern bool pumpingOn;
extern unsigned int threshold;
extern uint16_t reservoirDuration;
extern uint16_t reservoirInterval;

void turnOnReservoirPump();
void turnOffReservoirPump();

result setReservoirThreshold(eventMask,navNode&, prompt&);
result setReservoirDuration(eventMask,navNode&, prompt&);
result setReservoirInterval(eventMask,navNode&, prompt&);

// pH Monitor
extern bool phMonitoring;
extern float idealPh;
extern uint16_t phPollInterval;
extern uint16_t phPumpDuration;

void turnOnPhMonitor();
void turnOffPhMonitor();

result setIdealPh(eventMask,navNode&, prompt&);
result setPhPollInterval(eventMask,navNode&, prompt&);
result setPhPumpDuration(eventMask,navNode&, prompt&);

extern AnalogButtons analogButtons;
extern Button b1;
extern Button b2;
extern Button b3;
extern Button b4;
//Button b5 = Button(640, &b5Click);        // select

extern chainStream<0> in;

#endif //FARMR_UI_H
