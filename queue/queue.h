#ifndef QUEUE

#define QUEUE

#include <assert.h>
#include <stdio.h>

#define QUEUESIZE 1000

typedef struct {
	int queue[QUEUESIZE];
	int first;
	int last;
	int count;
} queue;

void init_queue(queue *q);
void enqueue(queue *q, int x);
int dequeue(queue *q);
int head(queue *q);
int empty_queue(queue *q);
void print_queue(queue *q);

#endif QUEUE
