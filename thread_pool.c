#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

#include "task.h"
#include "queue.h"


#define THREAD_POOL_SIZE 5

queue_t queue;
pthread_t thread_pool[THREAD_POOL_SIZE];

void *
thread_start_routine(void *arg) {
    while (true) {
        task_execute((task_t *)queue_retrieve(&queue));
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
    queue_init(&queue);
    thread_pool_init();

    // TODO(Jim Gerth): Add tasks to queue.

    thread_pool_join();
    return EXIT_SUCCESS;
}
