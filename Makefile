CC = gcc
CFLAGS = -Wall -Wextra

thread_pool: thread_pool.o task_queue.o
	$(CC) $(CFLAGS) thread_pool.o task_queue.o -o thread_pool

thread_pool.o: thread_pool.c task_queue.h
	$(CC) $(CFLAGS) -c thread_pool.c

task_queue.o: task_queue.c task_queue.h
	$(CC) $(CFLAGS) -c task_queue.c
