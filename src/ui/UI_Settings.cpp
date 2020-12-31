//
// Created by Josue Figueroa on 12/28/20.
//

#include "ui/UI_Settings.h"
#include "settings.h"

result restoreDefaults(eventMask e, navNode& _nav, prompt &item) {
  settings.writeDefaults();
  return proceed;
}