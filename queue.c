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
    queue->head = 0;
    queue->tail = 0;
    pthread_mutex_init(&queue->mutex, NULL);
    pthread_cond_init(&queue->not_empty, NULL);
}

bool
queue_empty(queue_t *queue) {
    return queue->head == queue->tail;
}

void
queue_submit(queue_t *queue, void *item) {
    pthread_mutex_lock(&queue->mutex);

    queue->items[queue->head++] = item;
    queue->head %= QUEUE_LENGTH;

    pthread_cond_signal(&queue->not_empty);

    pthread_mutex_unlock(&queue->mutex);
}

void *
queue_retrieve(queue_t *queue) {
    pthread_mutex_lock(&queue->mutex);

    while (queue_empty(queue)) {
        pthread_cond_wait(&queue->not_empty, &queue->mutex);
    }

    void *item = queue->items[queue->tail++];
    queue->tail %= QUEUE_LENGTH;

    pthread_mutex_unlock(&queue->mutex);

    return item;
}
