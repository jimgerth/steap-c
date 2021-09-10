#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

#include "task_queue.h"


#define THREAD_POOL_SIZE 5

pthread_t thread_pool[THREAD_POOL_SIZE];

void *
thread_start_routine(void *arg) {
    while (true) {
        task_t task;
        if (task_queue_dequeue(&task) == DEQUEUE_SUCCESS) {
            task.action();
        } else {
            sleep(1);
        }
    }

    return NULL;
}

void
thread_pool_init(void) {
    for (int i = 0; i < THREAD_POOL_SIZE; i++) {
        pthread_create(&thread_pool[i], NULL, thread_start_routine, NULL);
    }
}

void
thread_pool_join(void) {
    for (int i = 0; i < THREAD_POOL_SIZE; i++) {
        pthread_join(thread_pool[i], NULL);
    }
}

int
main(void) {
    task_queue_init();
    thread_pool_init();

    // TODO(Jim Gerth): Add tasks to queue.

    thread_pool_join();
    return EXIT_SUCCESS;
}
