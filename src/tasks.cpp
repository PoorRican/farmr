//
// Created by Josue Figueroa on 12/28/20.
//

#include "tasks.h"
#include "settings.h"
#include "UI_PhMonitor.h"
#include "UI_Reservoir.h"

void update_sensors() {
  currentPh = ph_monitor->getCurrentPh();
  reservoirLevel = reservoir_level->get();
}