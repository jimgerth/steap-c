#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

#include "queue.h"


void
queue_item_init(queue_item_t *item, void *data) {
    item->next = NULL;
    item->data = data;
}

void
queue_init(queue_t *queue) {
    queue->head = NULL;
    queue->tail = NULL;
    pthread_mutex_init(&queue->mutex, NULL);
    pthread_cond_init(&queue->not_empty, NULL);
}

bool
queue_empty(queue_t *queue) {
    return queue->head == NULL;
}

void
queue_submit(queue_t *queue, queue_item_t *item) {
    pthread_mutex_lock(&queue->mutex);

    if (queue_empty(queue)) {
        queue->head = item;
    } else {
        queue->tail->next = item;
    }

    queue->tail = item;

    pthread_cond_signal(&queue->not_empty);

    pthread_mutex_unlock(&queue->mutex);
}

queue_item_t *
queue_retrieve(queue_t *queue) {
    pthread_mutex_lock(&queue->mutex);

    while (queue_empty(queue)) {
        pthread_cond_wait(&queue->not_empty, &queue->mutex);
    }

    queue_item_t *item = queue->head;

    queue->head = queue->head->next;

    if (queue->head == NULL) {
        queue->tail = NULL;
    }

    item->next = NULL;

    pthread_mutex_unlock(&queue->mutex);

    return item;
}
