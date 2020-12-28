//
// Created by Josue Figueroa on 12/25/20.
//

#ifndef FARMR_UI_MAIN_H
#define FARMR_UI_MAIN_H

#include <Arduino.h>
#include <Wire.h>
#include <menu.h>
#include <menuIO/liquidCrystalOut.h>
#include <menuIO/chainStream.h>
#include "settings.h"
#include <AnalogButtons.h>

using namespace Menu;

extern navRoot nav;
extern LiquidCrystal lcd;

void pollUi();

extern AnalogButtons analogButtons;

#endif //FARMR_UI_MAIN_H
