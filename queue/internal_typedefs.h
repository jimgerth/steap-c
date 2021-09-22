#ifndef __QUEUE_INTERNAL_TYPEDEFS_H__
#define __QUEUE_INTERNAL_TYPEDEFS_H__

#include <pthread.h>


typedef struct queue_item_t {
    struct queue_item_t *next;
    void *data;
} queue_item_t;

typedef struct queue_t {
    queue_item_t *head;
    queue_item_t *tail;
    pthread_mutex_t mutex;
    pthread_cond_t not_empty;
} queue_t;


#endif
