#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

#include "task_queue.h"


#define THREAD_POOL_SIZE 5

task_queue_t task_queue;
pthread_t thread_pool[THREAD_POOL_SIZE];

void *
thread_start_routine(void *arg) {
    while (true) {
        task_queue_retrieve(&task_queue).action();
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
    task_queue_init(&task_queue);
    thread_pool_init();

    // TODO(Jim Gerth): Add tasks to queue.

    thread_pool_join();
    return EXIT_SUCCESS;
}
