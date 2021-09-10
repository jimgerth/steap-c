#include <stdio.h>
#include <stdlib.h>

#define TASK_QUEUE_LENGTH 5

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

int
main(void) {
    return EXIT_SUCCESS;
}
