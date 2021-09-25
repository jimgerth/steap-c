#ifndef __QUEUE_INTERNAL_FUNCTIONS_H__
#define __QUEUE_INTERNAL_FUNCTIONS_H__

#include <stdbool.h>


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
 * Initialize a new queue item.
 *
 * This must be called for any newly declared queue_item_t, before calling any
 * other queue_* function with it.
 */
void
queue_item_init(queue_item_t *, void *);

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
queue_is_empty(queue_t *);

#endif
