#ifndef _TASK_H_
#define _TASK_H_


/*
 * An arbitrary action to be executed as part of a task.
 *
 * A task_action_t function accepts a generic void* argument which it can use in
 * its execution.
 */
typedef void (*task_action_t)(void *);

/*
 * An abstract encapsulation of some computative work to be done.
 *
 * A task can be thought of as an independent unit of work. This could be a
 * mathmatical computation, some file input/output, or anything else.
 *
 * The actual code to be executed for this task is in the action function. The
 * argument will be passed into the action function when it is called.
 */
typedef struct {
    task_action_t action;
    void *argument;
} task_t;

#endif /* !_TASK_H_ */
