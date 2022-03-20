//
// Created by Josue Figueroa on 12/27/20.
//

#include "logger.h"
#include "buttons.h"

AnalogButtons analogButtons(A0, INPUT, 2, 25);

Button b1 = Button(0, &bSel);               // right
Button b2 = Button(256, &bUp);              // down
Button b3 = Button(98, &bDwn);              // up
Button b4 = Button(410, &bEsc);             // left
Button b5 = Button(640, &cancelUpdate);     // select

void init_buttons() {
  analogButtons.add(b1);
  analogButtons.add(b2);
  analogButtons.add(b3);
  analogButtons.add(b4);
  analogButtons.add(b5);
}

void bSel(){
#ifdef BASIC_TESTING
  logger.debug("Sel pressed");
#endif
  nav.doNav(enterCmd);
}

void bDwn(){
#ifdef BASIC_TESTING
  logger.debug("Dwn pressed");
#endif
  nav.doNav(downCmd);
}

void bUp(){
#ifdef BASIC_TESTING
  logger.debug("Up pressed");
#endif
  nav.doNav(upCmd);
}

void bEsc(){
#ifdef BASIC_TESTING
  logger.debug("Esc pressed");
#endif
  nav.doNav(escCmd);
}

void cancelUpdate() {
#ifdef VERBOSE_OUTPUT
  logger.debug("Sel button pressed...");
#endif
  updateEEPROM = true;
}