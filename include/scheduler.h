//
// Created by Josue Figueroa on 12/17/20.
//

#ifndef FARMR_SCHEDULER_H
#define FARMR_SCHEDULER_H

#define _TASK_LTS_POINTER       // Compile with support for local task storage pointer

#include <TaskSchedulerDeclarations.h>
#include "settings.h"

extern Scheduler ts;

/**
 * Adds individual tasks for pumps and sensor operations to scheduler.
 */
void init_tasks();

#endif //FARMR_SCHEDULER_H
