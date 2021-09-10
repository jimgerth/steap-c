#include <stdio.h>
#include <stdlib.h>

#define TASK_QUEUE_LENGTH 100

typedef void (*task_action_t)(void);

typedef struct {
    task_action_t action;
} task_t;

task_t task_queue[TASK_QUEUE_LENGTH];

int
main(void) {
    return EXIT_SUCCESS;
}
