#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#include "queue.h"


queue_item_t *
queue_item_create(void *data) {
    queue_item_t *item;
    if ((item = malloc(sizeof (queue_item_t))) == NULL) {
        return NULL;
    }

    queue_item_init(item, data);
    return item;
}

void
queue_item_destroy(queue_item_t **item) {
    if (item == NULL) {
        return;
    }

    free(*item);
    *item = NULL;
}

void
queue_item_init(queue_item_t *item, void *data) {
    if (item == NULL) {
        return;
    }

    item->next = NULL;
    item->data = data;
}

queue_t *
queue_create(void) {
    queue_t *queue;
    if ((queue = malloc(sizeof (queue_t))) == NULL) {
        return NULL;
    }

    queue_init(queue);
    return queue;
}

void
queue_destroy(queue_t **queue) {
    if (queue == NULL) {
        return;
    }

    while (!queue_empty(*queue)) {
        queue_item_destroy(queue_retrieve(*queue));
    }

    free(*queue);
    *queue = NULL;
}

void
queue_init(queue_t *queue) {
    if (queue == NULL) {
        return;
    }

    queue->head = NULL;
    queue->tail = NULL;
    pthread_mutex_init(&queue->mutex, NULL);
    pthread_cond_init(&queue->not_empty, NULL);
}

bool
queue_empty(queue_t *queue) {
    if (queue == NULL) {
        return true;
    }

    return queue->head == NULL;
}

void
queue_submit(queue_t *queue, queue_item_t *item) {
    if (queue == NULL) {
        return;
    }

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
    if (queue == NULL) {
        return NULL;
    }

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
