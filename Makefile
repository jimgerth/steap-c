CC = gcc
CFLAGS = -Wall -Wextra

thread_pool: thread_pool.c
	$(CC) $(CFLAGS) thread_pool.c -o thread_pool
