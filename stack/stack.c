#include "stack.h"

void init_stack(stack *s)
{
	s->top = -1;
	s->count = 0;
}

void push(stack *s, int x)
{
	if (s->count >= STACKSIZE)
		printf("failed to push: stack is full\n");
	else {
		s->top++;
		s->stack[s->top] = x;
		s->count++;
	}
}

int pop(stack *s)
{
	int x;

	if (s->count <= 0) {
		printf("failed to pop: stack is empty\n");
		x = 0;
	} else {
		x = s->stack[s->top];
		s->top--;
		s->count--;
	}
	return x;
}

int empty_stack(stack *s)
{
	return s->count <= 0;
}

void print_stack(stack *s)
{
	int i;

	for (i = 0; i < s->count; i++)
		printf("%d ", s->stack[i]);
	putchar('\n');
}
