#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

#include "task_queue.h"


bool
task_queue_empty(task_queue_t *task_queue) {
    return task_queue->head == task_queue->tail;
}

bool
task_queue_full(task_queue_t *task_queue) {
    return (task_queue->head + 1) % TASK_QUEUE_LENGTH == task_queue->tail;
}

void
task_queue_init(task_queue_t *task_queue) {
    task_queue->head = 0;
    task_queue->tail = 0;
    pthread_mutex_init(&task_queue->mutex, NULL);
    pthread_cond_init(&task_queue->not_empty, NULL);
    pthread_cond_init(&task_queue->not_full, NULL);
}

void
task_queue_submit(task_queue_t *task_queue, task_t task) {
    pthread_mutex_lock(&task_queue->mutex);

    while (task_queue_full(task_queue)) {
        pthread_cond_wait(&task_queue->not_full, &task_queue->mutex);
    }

    task_queue->tasks[task_queue->head++] = task;
    task_queue->head %= TASK_QUEUE_LENGTH;

    pthread_cond_signal(&task_queue->not_empty);

    pthread_mutex_unlock(&task_queue->mutex);
}

task_t
task_queue_retrieve(task_queue_t *task_queue) {
    pthread_mutex_lock(&task_queue->mutex);

    while (task_queue_empty(task_queue)) {
        pthread_cond_wait(&task_queue->not_empty, &task_queue->mutex);
    }

    task_t retrieved = task_queue->tasks[task_queue->tail++];
    task_queue->tail %= TASK_QUEUE_LENGTH;

    pthread_cond_signal(&task_queue->not_full);

    pthread_mutex_unlock(&task_queue->mutex);

    return retrieved;
}
