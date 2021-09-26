#ifndef __QUEUE_EXTERNAL_TYPEDEFS_H__
#define __QUEUE_EXTERNAL_TYPEDEFS_H__


/*
 * A queue of generic data.
 *
 * This queue serves as a "first in, first out" buffer, keeping track of generic
 * data. New data can be inserted into the queue (submitted), while data already
 * in the queue can be removed again (retrieved). Data will be retrieved in the
 * same order it was previously submitted.
 */
typedef void queue_t;


#endif
