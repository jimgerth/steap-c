#ifndef __TASK_INTERNAL_FUNCTIONS_H__
#define __TASK_INTERNAL_FUNCTIONS_H__


/*
 * Initialize a new task.
 *
 * This must be provided with a task action function and an argument for that
 * function.
 */
void
task_init(task_t *, task_action_t, void *);


#endif
