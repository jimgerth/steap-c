#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define TASK_QUEUE_LENGTH 5
#define THREAD_POOL_SIZE 5

typedef void (*task_action_t)(void);

typedef struct {
    task_action_t action;
} task_t;

typedef struct {
    task_t tasks[TASK_QUEUE_LENGTH];
    int head;
    int tail;
} task_queue_t;

task_queue_t task_queue;

void
task_queue_init(void) {
    task_queue.head = 0;
    task_queue.tail = 0;
}

int
task_queue_enqueue(task_t task) {
    if ((task_queue.head + 1) % TASK_QUEUE_LENGTH == task_queue.tail) {
        return 1;
    }

    task_queue.tasks[task_queue.head++] = task;
    return 0;
}

task_t
task_queue_dequeue(void) {
    if (task_queue.head != task_queue.tail) {
        return task_queue.tasks[task_queue.tail++];
    }
}

pthread_t thread_pool[THREAD_POOL_SIZE];

void *
thread_start_routine(void *arg) {
    //TODO(Jim Gerth): Implement thread loop.
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
    thread_pool_init();
    thread_pool_join();
    return EXIT_SUCCESS;
}
