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

void
task_queue_enqueue(task_t task) {
    if ((task_queue.head + 1) % TASK_QUEUE_LENGTH == task_queue.tail) {
        fprintf(stderr, "Could not enqueue task: The task queue is full!\n");
    }

    task_queue.tasks[task_queue.head++] = task;
    task_queue.head %= TASK_QUEUE_LENGTH;
}

task_t
task_queue_dequeue(void) {
    if (task_queue.head == task_queue.tail) {
        fprintf(stderr, "Could not dequeue task: The task queue is empty!\n");
    }

    task_t task = task_queue.tasks[task_queue.tail++];
    task_queue.tail %= TASK_QUEUE_LENGTH;
    return task;
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
    task_queue_init();
    thread_pool_init();

    // TODO(Jim Gerth): Add tasks to queue.

    thread_pool_join();
    return EXIT_SUCCESS;
}
