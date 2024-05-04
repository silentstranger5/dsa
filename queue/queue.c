#include "queue.h"

void init_queue(queue *q)
{
	q->first = 0;
	q->last  = -1;
	q->count = 0;
}

void enqueue(queue *q, int x)
{
	if (q->count >= QUEUESIZE)
		printf("failed to enqueue: queue is full\n");
	else {
		q->last = (q->last + 1) % QUEUESIZE;
		q->queue[q->last] = x;
		q->count++;
	}
}

int dequeue(queue *q)
{
	int x;

	if (q->count <= 0) {
		printf("failed to dequeue: queue is empty\n");
		x = 0;
	} else {
		x = q->queue[q->first];
		q->first = (q->first + 1) % QUEUESIZE;
		q->count--;
	}
	return x;
}

int head(queue *q)
{
	return q->queue[q->first];
}

int empty_queue(queue *q)
{
	return q->count <= 0;
}

void print_queue(queue *q)
{
	int i;

	for (i = q->first; i <= q->last; i++)
		printf("%d ", q->queue[i]);
	putchar('\n');
}
