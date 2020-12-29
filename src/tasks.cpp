//
// Created by Josue Figueroa on 12/28/20.
//

#include "tasks.h"
#include "settings.h"
#include "UI_PhMonitor.h"

void update_sensors() {
  currentPh = ph_monitor->getCurrentPh();
}