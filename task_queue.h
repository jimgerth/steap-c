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

task_queue_t task_queue;

bool
task_queue_empty(void);

bool
task_queue_full(void);

void
task_queue_init(void);

void
task_queue_enqueue(task_t task);

typedef enum {
    DEQUEUE_SUCCESS,
    DEQUEUE_FAILURE,
} task_queue_dequeue_status;

task_queue_dequeue_status
task_queue_dequeue(task_t *task);

#endif
