//
// Created by Josue Figueroa on 12/27/20.
//

#ifndef FARMR_BUTTONS_H
#define FARMR_BUTTONS_H

#include <AnalogButtons.h>
#include <menu.h>

extern navRoot nav;

extern AnalogButtons analogButtons;

// set to VMA203 LCD/Button Shield
extern Button b1;   // right
extern Button b2;   // down
extern Button b3;   // up
extern Button b4;   // left
//Button b5 = Button(640, &b5Click);        // select

void init_buttons();

// UI Callbacks
void bDwn();
void bUp();
void bSel();
void bEsc();

#endif //FARMR_BUTTONS_H
