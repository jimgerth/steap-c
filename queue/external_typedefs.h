#ifndef __QUEUE_EXTERNAL_TYPEDEFS_H__
#define __QUEUE_EXTERNAL_TYPEDEFS_H__


/*
 * A queue of items with a generic data payload.
 *
 * This queue serves as a "first in, first out" buffer, keeping track of
 * references to queue items, which in turn keep track of arbitrary data. New
 * items can be inserted into the queue (submitted), while items already in the
 * queue can be removed again (retrieved). Items will be retrieved in the same
 * order they were previously submitted.
 */
typedef void queue_t;


#endif
