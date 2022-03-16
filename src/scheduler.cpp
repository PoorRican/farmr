//
// Created by Josue Figueroa on 12/24/20.
//

#include "scheduler.h"

void init_tasks() {
  // TODO: convert this to a for-loop

  // Relay tasks
  acid_pump->addTasks(ts);
  base_pump->addTasks(ts);
  reservoir_pump->addTasks(ts);

  reservoir->addTasks(ts);

  // Monitor Tasks
  ph_monitor->addTasks(ts);
}