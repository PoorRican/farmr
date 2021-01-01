//
// Created by Josue Figueroa on 12/27/20.
//

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
  Serial.println("Sel pressed");
  nav.doNav(enterCmd);
}

void bDwn(){
  Serial.println("Dwn pressed");
  nav.doNav(downCmd);
}

void bUp(){
  Serial.println("Up pressed");
  nav.doNav(upCmd);
}

void bEsc(){
  Serial.println("Esc pressed");
  nav.doNav(escCmd);
}

void cancelUpdate() {
#ifdef VERBOSE_OUTPUT
  Serial.println("Sel button pressed...");
#endif
  updateEEPROM = true;
}