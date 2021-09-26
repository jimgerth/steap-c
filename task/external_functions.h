#ifndef __TASK_EXTERNAL_FUNCTIONS_H__
#define __TASK_EXTERNAL_FUNCTIONS_H__


/*
 * Create a new task_t object.
 *
 * This will create and initialize a new task and return a handle to it. That
 * handle can be used with the various task_*() functions to manipulate the
 * task, by passing it in as the first argument.
 *
 * This will return NULL if the task could not be created.
 */
task_t *
task_create(task_action_t, void *);

/*
 * Destroy a task_t object.
 *
 * This will destroy a task_t object, that is not needed anymore. This includes
 * freeing up any memory associated with the task_t object for example.
 */
void
task_destroy(task_t **);

/*
 * Execute the given task.
 *
 * This will hand execution over to the task's action function, passing in the
 * task's supplied argument.
 */
void
task_execute(task_t *);


#endif
