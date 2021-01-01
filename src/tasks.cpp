//
// Created by Josue Figueroa on 12/28/20.
//

#include "tasks.h"
#include "settings.h"
#include "ui/UI_PhMonitor.h"
#include "ui/UI_TempMonitor.h"
#include "ui/UI_Reservoir.h"

void update_sensors() {
  currentPh = ph_monitor->getCurrentPh();
  currentTemp = monitor_temp->getCurrentTemp();
  reservoirLevel = reservoir_level->get();
}