#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRL 100
#define SIZE 1000

typedef struct {
	void *data;
	int type;
} cell;

typedef struct {
	cell **array;
	int size;
} array;

enum {INT, FLOAT, CHAR, STRING};
char *types[] = { "int", "float", "char", "string" };

array *init_array(void) {
	array *a;
	
	a = malloc(sizeof(array));
	a->array = malloc(sizeof(cell *) * SIZE);
	a->size = 0;
	return a;
}

void get_data(void **data, int *type) {
	char c;
	char *s, *t;
	
	t = malloc(STRL);
	printf("Type data type (int, float, char, string): ");
	scanf_s(" %s", t);
	if (!strcmp(t, "int")) {
		*data = malloc(sizeof(int));
		printf("Type an integer: ");
		if (!scanf_s(" %d", (int *) *data)) {
			printf("failed to obtain data\n");
			exit(1);
		}
		*type = INT;
	} else if (!strcmp(t, "float")) {
		*data = malloc(sizeof(float));
		printf("Type a floating-point number: ");
		if (!scanf_s(" %f", (float *) *data)) {
			printf("failed to obtain data\n");
			exit(1);
		}
		*type = FLOAT;
	} else if (!strcmp(t, "char")) {
		*data = malloc(sizeof(char));
		printf("Type a character: ");
		while (isspace(c = getchar()));
		*(char *) *data = c;
		while ((c = getchar()) != '\n');
		*type = CHAR;
	} else if (!strcmp(t, "string")) {
		*data = malloc(sizeof(char *));
		s = malloc(STRL);
		printf("Type a string: ");
		getchar();
		if (!fgets(s, STRL, stdin)) {
			printf("failed to obtain data\n");
			exit(1);
		}
		s[strlen(s)-1] = '\0';
		*(char **) *data = s;
		*type = STRING;
	} else {
		printf("invalid data type\n");
		exit(1);
	}
	free(t);
}

cell *init_cell(void) {
	int type;
	void *data;
	cell *c;
	
	get_data(&data, &type);
	c = malloc(sizeof(cell));
	c->data = data;
	c->type = type;
	return c;
}

void push_cell(array *a, cell *c) {
	if (a->size >= SIZE) {
		printf("failed to push cell: size limit exceeded\n");
		exit(1);
	}

	a->array[a->size++] = c;
}

cell *pop_cell(array *a) {
	if (a->size <= 0) {
		printf("failed to pop cell: array is empty\n");
		exit(1);
	}

	return a->array[--a->size];
}

cell *get_cell(array *a, int i) {
	if (i < 0 || i >= a->size) {
		printf("failed to get cell: out of bounds index\n");
		exit(1);
	}

	return a->array[i];
}

void insert_cell(array *a, cell *c, int i) {
	int j;

	if (i < 0 || i >= a->size) {
		printf("failed to insert cell: out of bounds index\n");
		exit(1);
	}

	if (i == a->size) {
		return push_cell(a, c);
	}

	for (j = a->size - 1; j >= i; j--) {
		a->array[j + 1] = a->array[j];
	}
	a->array[i] = c;
	a->size++;
}

cell *delete_cell(array *a, int i) {
	int j;
	cell *c;

	if (i < 0 || i >= a->size) {
		printf("failed to remove cell: out of bounds index\n");
		exit(1);
	}

	if (i == a->size) {
		return pop_cell(a);
	}

	c = get_cell(a, i);
	for (j = i; j < a->size; j++) {
		a->array[j] = a->array[j + 1];
	}
	a->size--;
	return c;
}

void print_cell(cell *c) {
	putchar('\t');
	switch (c->type) {
	case INT:
		printf("%d", *(int *) c->data);
		break;
	case FLOAT:
		printf("%f", *(float *) c->data);
		break;
	case CHAR:
		printf("%c", *(char *) c->data);
		break;
	case STRING:
		printf("%s", *(char **) c->data);
		break;
	default:
		printf("failed to print cell: invalid data type\n");
		break;
	}
	putchar('\n');
}

void print_array(array *a) {
	int i;
	
	if (a->size == 0) {
		printf("array is empty\n");
		return;
	}

	for (i = 0; i < a->size; i++) {
		print_cell(get_cell(a, i));
	}
}

void free_array(array *a) {
	int i;
	cell *c;

	for (i = 0; i < a->size; i++) {
		c = get_cell(a, i);
		if (c->type == STRING) {
			free(*(char **) c->data);
		}
		free(c->data);
		free(c);
	}
	free(a->array);
	free(a);
}

int main(void) {
	int i;
	array *a;
	cell *c;
	char input[10];
	
	a = init_array();
	while (scanf_s("%s", input)) {
		if (!strcmp(input, "push")) {
			c = init_cell();
			push_cell(a, c);
		} else if (!strcmp(input, "pop")) {
			c = pop_cell(a);
			print_cell(c);
		} else if (!strcmp(input, "insert")) {
			if (!scanf_s(" %d", &i)) {
				printf("failed to obtain index\n");
				exit(1);
			}
			c = init_cell();
			insert_cell(a, c, i);
		} else if (!strcmp(input, "delete")) {
			if (!scanf_s(" %d", &i)) {
				printf("failed to obtain index\n");
				exit(1);
			}
			c = delete_cell(a, i);
			print_cell(c);
		} else if (!strcmp(input, "get")) {
			if (!scanf_s(" %d", &i)) {
				printf("failed to obtain index\n");
				exit(1);
			}
			c = get_cell(a, i);
			print_cell(c);
		} else if (!strcmp(input, "size")) {
			printf("\t%d\n", a->size);
		} else if (!strcmp(input, "print")) {
			print_array(a);
		} else if (!strcmp(input, "help")) {
			printf(
				"array - dynamic array with heap allocation\n"
				"usage: command [args]\n\t"
				"push\t- push to array\n\t"
				"pop\t- pop  from array\n\t"
				"insert i\t- insert to array\n\t"
				"delete i\t- delete from array\n\t"
				"get i\t- get from array\n\t"
				"size\t - print array size\n\t"
				"print\t- print array\n\t"
				"help\t- display this message\n\t"
				"exit\t- exit from program\n"
			);
		} else if (!strcmp(input, "exit")) {
			break;
		} else {
			printf("invalid command: %s\n", input);
		}
	}
	free_array(a);
	return 0;
}
