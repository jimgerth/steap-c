#ifndef TASK_QUEUE_H
#define TASK_QUEUE_H

#include <stdbool.h>
#include <pthread.h>


#define TASK_QUEUE_LENGTH 5

typedef void (*task_action_t)(void);

typedef struct {
    task_action_t action;
} task_t;

typedef struct {
    task_t tasks[TASK_QUEUE_LENGTH];
    int head;
    int tail;
    pthread_mutex_t mutex;
    pthread_cond_t not_empty;
    pthread_cond_t not_full;
} task_queue_t;

bool
task_queue_empty(task_queue_t *task_queue);

bool
task_queue_full(task_queue_t *task_queue);

void
task_queue_init(task_queue_t *task_queue);

void
task_queue_submit(task_queue_t *task_queue, task_t task);

task_t
task_queue_retrieve(task_queue_t *task_queue);

#endif
