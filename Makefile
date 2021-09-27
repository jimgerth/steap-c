CC = gcc
CFLAGS = -Wall -Wextra

thread_pool: thread_pool.o task.o queue.o
	$(CC) $(CFLAGS) thread_pool.o task.o queue.o -o thread_pool

thread_pool.o: thread_pool.c task.h task/external_typedefs.h task/external_functions.h queue.h queue/external_typedefs.h queue/external_functions.h
	$(CC) $(CFLAGS) -c thread_pool.c

task.o: task/task.c task/task.h task/internal_typedefs.h task/internal_functions.h task/external_functions.h
	$(CC) $(CFLAGS) -c task/task.c

queue.o: queue/queue.c queue/queue.h queue/internal_typedefs.h queue/internal_functions.h queue/external_functions.h
	$(CC) $(CFLAGS) -c queue/queue.c
