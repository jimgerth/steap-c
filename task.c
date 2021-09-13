#include "task.h"


void
task_init(task_t *task, task_action_t action, void *argument) {
    task->action = action;
    task->argument = argument;
}
