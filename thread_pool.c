#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

#include "task.h"
#include "queue.h"


#define THREAD_POOL_SIZE 5

queue_t *queue;
pthread_t thread_pool[THREAD_POOL_SIZE];

void *
thread_start_routine(void *arg) {
    while (true) {
        task_execute((task_t *)queue_retrieve(queue));
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

void func(void *arg) {
    printf("%d\n", (int)arg);
}

int
main(void) {
    if ((queue = queue_create()) == NULL) {
        fprintf(stderr, "Task queue could not be created.");
        return EXIT_FAILURE;
    }

    thread_pool_init();

    task_t *task1;
    if ((task1 = task_create(func, (void *)1)) == NULL) {
        fprintf(stderr, "Task 1 could not be created.\n");
    }

    task_t *task2;
    if ((task2 = task_create(func, (void *)2)) == NULL) {
        fprintf(stderr, "Task 2 could not be created.\n");
    }

    queue_submit(queue, task1);
    sleep(2);
    queue_submit(queue, task2);

    thread_pool_join();

    queue_destroy(&queue);

    return EXIT_SUCCESS;
}
