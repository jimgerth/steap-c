#include "task.h"


void
task_init(task_t *task, task_action_t action, void *argument) {
    task->action = action;
    task->argument = argument;
}

void
task_execute(task_t *task) {
    task->action(task->argument);
}
