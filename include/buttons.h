//
// Created by Josue Figueroa on 12/27/20.
//

#ifndef FARMR_BUTTONS_H
#define FARMR_BUTTONS_H

#include <AnalogButtons.h>
#include <menu.h>
#include "settings.h"

extern navRoot nav;

extern AnalogButtons analogButtons;

// set to VMA203 LCD/Button Shield
extern Button b1;   // right
extern Button b2;   // down
extern Button b3;   // up
extern Button b4;   // left
extern Button b5;   // select

void init_buttons();

// UI Callbacks
void bDwn();
void bUp();
void bSel();
void bEsc();

/**
 * Single-use func that cancels automatic reset to default settings during startup
 * when a new version is detected.
 */
void cancelUpdate();

#endif //FARMR_BUTTONS_H
