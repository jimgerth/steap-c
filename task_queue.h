#ifndef _TASK_QUEUE_H_
#define _TASK_QUEUE_H_

#include <stdbool.h>
#include <pthread.h>


/*
 * The length of the task array of any task_queue_t instance.
 */
#define TASK_QUEUE_LENGTH 5

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

/*
 * A queue of tasks, waiting to be executed.
 *
 * This task queue serves as a "first in, first out" buffer keeping track of
 * tasks being submitted (inserted into the queue), or retrieved (removed from
 * the queue) for execution. Tasks will be retrieved in the same order they were
 * previously submitted.
 */
typedef struct {
    task_t *tasks[TASK_QUEUE_LENGTH];
    int head;
    int tail;
    pthread_mutex_t mutex;
    pthread_cond_t not_empty;
    pthread_cond_t not_full;
} task_queue_t;

/*
 * Return whether the given task queue is empty.
 */
bool
task_queue_empty(task_queue_t *);

/*
 * Return whether the given task queue is full.
 */
bool
task_queue_full(task_queue_t *);

/*
 * Initialize a new task queue.
 *
 * This must be called for any newly declared task queue before calling any other
 * task queue function with it.
 */
void
task_queue_init(task_queue_t *);

/*
 * Add the given task to the given task queue.
 *
 * This call is synchronized and thus safe to call from different threads.
 *
 * This call will block if the given task queue is full. It will only return once
 * the given task could successfully be added to the queue.
 */
void
task_queue_submit(task_queue_t *, task_t *);

/*
 * Remove and return the oldest task from the given task queue.
 *
 * This call will return that task from the task queue that has been inserted the
 * longest time ago, operating according to the "first in, first out" principle.
 *
 * This call is synchronized and thus safe to call from different threads.
 *
 * This call will block if the given task queue is empty. It will only return
 * once a task could successfully be retrieved from the queue.
 */
task_t *
task_queue_retrieve(task_queue_t *);

#endif /* !_TASK_QUEUE_H */
