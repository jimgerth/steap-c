#ifndef __QUEUE_EXTERNAL_FUNCTIONS_H__
#define __QUEUE_EXTERNAL_FUNCTIONS_H__


/*
 * Create a new queue_t object.
 *
 * This will create and initialize a new queue and return a handle to it. That
 * handle can be used with the various queue_*() functions to manipulate the
 * queue, by passing it in as the first argument.
 *
 * This will return NULL if the queue could not be created.
 */
queue_t *
queue_create(void);

/*
 * Destroy a queue_t object.
 *
 * This will destroy a queue_t object, that is not needed anymore. This includes
 * freeing up any memory associated with the queue_t object for example.
 *
 * No more left over data can be retrieved from the queue after destroying it.
 */
void
queue_destroy(queue_t **);

/*
 * Add the given data to the given queue.
 *
 * This call is synchronized and thus safe to call from different threads.
 */
void
queue_submit(queue_t *, void *);

/*
 * Remove and return the oldest data from the given queue.
 *
 * This call will return that data from the queue that has been inserted the
 * longest time ago, operating according to the "first in, first out" principle.
 *
 * This call is synchronized and thus safe to call from different threads.
 *
 * This call will block if the given queue is empty. It will only return once
 * data could successfully be retrieved from the queue.
 */
void *
queue_retrieve(queue_t *);


#endif
