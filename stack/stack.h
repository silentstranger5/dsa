#ifndef STACK

#define STACK

#include <assert.h>
#include <stdio.h>

#define STACKSIZE 1000

typedef struct {
	int stack[STACKSIZE];
	int top;
	int count;
} stack;

void init_stack(stack *s);
void push(stack *s, int x);
int pop(stack *s);
int empty_stack(stack *s);
void print_stack(stack *s);

#endif
