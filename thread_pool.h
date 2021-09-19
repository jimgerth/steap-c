#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

#include "task.h"
#include "queue.h"


#define THREAD_POOL_SIZE 5

typedef struct thread_pool_t {
    pthread_t threads[THREAD_POOL_SIZE];
    queue_t task_queue;
}

static void *
thread_start_routine(void *arg) {
    thread_pool_t thread_pool = (thread_pool_t *)arg;

    while (true) {
        task_execute((task_t *)queue_retrieve(&thread_pool->task_queue));
    }

    return NULL;
}

void
thread_pool_init(thread_pool_t *thread_pool) {
    for (int i = 0; i < THREAD_POOL_SIZE; i++) {
        pthread_create(
            &thread_pool->threads[i],
            NULL,
            thread_start_routine,
            (void *)thread_pool
        );
    }

    task_queue_init(&thread_pool->task_queue);
}

void
thread_pool_join(thread_pool_t *thread_pool) {
    for (int i = 0; i < THREAD_POOL_SIZE; i++) {
        pthread_join(thread_pool->task_queue[i], NULL);
    }
}

#endif
