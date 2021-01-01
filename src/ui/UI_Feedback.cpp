//
// Created by Josue Figueroa on 1/1/21.
//

#include "ui/UI_Feedback.h"

result idle(menuOut &o, idleEvent e) {
  // o.clear();
  switch(e) {
    case idleStart:
      o.flush();
      // idleTimeout.reset();
      break;
    case idleEnd:
      nav.reset();
      break;
    default:break;
  }
  return proceed;
}

result alertRestoreSettings(menuOut &o, idleEvent e) {
  // o.clear();
  switch(e) {
    case idleStart:
      o.println("Settings reset!");
      nav.reset();
      break;
    default:break;
  }
  return proceed;
}

result alertReservoirCalibrated(menuOut &o, idleEvent e) {
  // o.clear();
  switch(e) {
    case idleStart:
      o.println("Level calibrated!");
      break;
    default:break;
  }
  return proceed;
}

result alertPhCalibrated(menuOut &o, idleEvent e) {
  // o.clear();
  switch(e) {
    case idleStart:
      o.println("pH Calibrated!");
      break;
    default:break;
  }
  return proceed;
}

