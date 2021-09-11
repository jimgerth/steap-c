#include <stdio.h>
#include <pthread.h>

#include "task_queue.h"


void
task_queue_init(void) {
    task_queue.head = 0;
    task_queue.tail = 0;
    pthread_mutex_init(&task_queue.mutex, NULL);
    pthread_cond_init(&task_queue.not_empty, NULL);
}

void
task_queue_enqueue(task_t task) {
    pthread_mutex_lock(&task_queue.mutex);

    if ((task_queue.head + 1) % TASK_QUEUE_LENGTH == task_queue.tail) {
        fprintf(stderr, "Could not enqueue task: The task queue is full!\n");
        return;
    }

    task_queue.tasks[task_queue.head++] = task;
    task_queue.head %= TASK_QUEUE_LENGTH;

    pthread_cond_signal(&task_queue.not_empty);

    pthread_mutex_unlock(&task_queue.mutex);
}

task_queue_dequeue_status
task_queue_dequeue(task_t *task) {
    pthread_mutex_lock(&task_queue.mutex);

    while (task_queue.head == task_queue.tail) {
        pthread_cond_wait(&task_queue.not_empty, &task_queue.mutex);
    }

    task_t dequeued = task_queue.tasks[task_queue.tail++];
    task_queue.tail %= TASK_QUEUE_LENGTH;

    pthread_mutex_unlock(&task_queue.mutex);

    *task = dequeued;
    return DEQUEUE_SUCCESS;
}
