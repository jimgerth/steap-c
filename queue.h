#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdbool.h>
#include <pthread.h>


/*
 * An enqueueable item with a generic data payload.
 */
typedef struct queue_item_t {
    struct queue_item_t *next;
    void *data;
} queue_item_t;

/*
 * A queue of items with a generic data payload.
 *
 * This queue serves as a "first in, first out" buffer, keeping track of
 * references to queue items, which in turn keep track of arbitrary data. New
 * items can be inserted into the queue (submitted), while items already in the
 * queue can be removed again (retrieved). Items will be retrieved in the same
 * order they were previously submitted.
 */
typedef struct queue_t {
    queue_item_t *head;
    queue_item_t *tail;
    pthread_mutex_t mutex;
    pthread_cond_t not_empty;
} queue_t;

/*
 * Create a new queue_item_t object.
 *
 * This will create and initialize a new queue_item_t and return a handle to
 * that object.
 *
 * This will return NULL if the queue_item_t could not be created.
 */
queue_item_t *
queue_item_create(void *);

/*
 * Destroy a queue_item_t object.
 *
 * This will destroy a queue_item_t object, that is not needed anymore. This
 * includes freeing up any memory associated with the queue_item_t object for
 * example.
 */
void
queue_item_destroy(queue_item_t *);

/*
 * Initialize a new queue item.
 *
 * This must be called for any newly declared queue_item_t, before calling any
 * other queue_* function with it.
 */
void
queue_item_init(queue_item_t *, void *);

/*
 * Create a new queue_t object.
 *
 * This will create and initialize a new queue_t and return a handle to that
 * object.
 *
 * This will return NULL if the queue_t could not be created.
 */
queue_t *
queue_create(void);

/*
 * Destroy a queue_t object.
 *
 * This will destroy a queue_t object, that is not needed anymore. This includes
 * freeing up any memory associated with the queue_t object for example.
 *
 * No more left over items can be retrieved from the queue after destroying it.
 */
void
queue_destroy(queue_t **);

/*
 * Initialize a new queue.
 *
 * This must be called for any newly declared queue_t instance, before calling
 * any other queue_* function with it.
 */
void
queue_init(queue_t *);

/*
 * Return whether the given queue is empty.
 */
bool
queue_empty(queue_t *);

/*
 * Add the given item to the given queue.
 *
 * This call is synchronized and thus safe to call from different threads.
 */
void
queue_submit(queue_t *, queue_item_t *);

/*
 * Remove and return the oldest item from the given queue.
 *
 * This call will return that item from the queue that has been inserted the
 * longest time ago, operating according to the "first in, first out" principle.
 *
 * This call is synchronized and thus safe to call from different threads.
 *
 * This call will block if the given queue is empty. It will only return once an
 * item could successfully be retrieved from the queue.
 */
queue_item_t *
queue_retrieve(queue_t *);

#endif /* !_QUEUE_H_ */
