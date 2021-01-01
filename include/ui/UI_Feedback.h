//
// Created by Josue Figueroa on 1/1/21.
//

#ifndef FARMR_UI_FEEDBACK_H
#define FARMR_UI_FEEDBACK_H

#include "ui/UI_Main.h"

/**
 * Resets navigation to root menu upon entering an idle state
 */
result idle(menuOut &o, idleEvent e);

/**
 * Alerts that settings have been restored
 */
result alertRestoreSettings(menuOut &o, idleEvent e);
/**
 * Alerts that pH has been calibrated
 */
result alertPhCalibrated(menuOut &o, idleEvent e);
/**
 * Alerts that water level sensor has been calibrated
 */
result alertLevelCalibrated(menuOut &o, idleEvent e);

#endif //FARMR_UI_FEEDBACK_H
