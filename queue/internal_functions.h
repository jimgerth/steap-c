#ifndef __QUEUE_INTERNAL_FUNCTIONS_H__
#define __QUEUE_INTERNAL_FUNCTIONS_H__

#include <stdbool.h>


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
queue_empty(queue_t *);

#endif
