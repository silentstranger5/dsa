#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100
#define STR  32

enum { INT, FLOAT, CHAR, STRING };

typedef struct {
	union {
		int i;
		float f;
		char c;
		char *s;
	} value;
	int type;
} field;

typedef struct {
	field fields[SIZE];
	int last;
} array;

void print_field(field *f) {
	int t;

	t = f->type;
	switch (t) {
	case INT:
		printf("\t%d\tint\n", f->value.i);
		break;
	case FLOAT:
		printf("\t%f\tfloat\n", f->value.f);
		break;
	case CHAR:
		printf("\t%c\tchar\n", f->value.c);
		break;
	case STRING:
		printf("\t%s\tstr\n", f->value.s);
		break;
	default:
		break;
	}
}

void set_field(char *s, field *fp) {
	int i;
	float f;
	char c, *sc;

	if (f = atof(s)) {
		if (ceil(f) == f) {
			i = (int) f;
			fp->value.i = i;
			fp->type = INT;
		} else {
			fp->value.f = f;
			fp->type = FLOAT;
		}
	} else if (strlen(s) == 1) {
		c = s[0];
		fp->value.c = c;
		fp->type = CHAR;
	} else {
		if (s[0] == '\'') {
			s++;
		}
		sc = strdup(s);
		fp->value.s = sc;
		fp->type = STRING;
	}

}

void insert_array(char *s, array *a, int idx) {
	int i;
	field *fp;

	if (idx < 0 || idx > a->last) {
		printf("failed to insert: invalid index\n");
		return;
	}

	if (!(s && strlen(s))) {
		printf("failed to insert: invalid value\n");
		return;
	}

	if (a->last == SIZE) {
		printf("failed to push: array is full\n");
		return;
	}

	for (i = a->last; i > idx; i--) {
		a->fields[i] = a->fields[i - 1];
	}

	fp = &(a->fields[idx]);
	set_field(s, fp);
	print_field(fp);
	a->last++;
}

void delete_array(array *a, int idx) {
	int i;

	if (idx < 0 || idx >= a->last) {
		printf("failed to delete: invalid index\n");
		return;
	}

	print_field(&(a->fields[idx]));
	for (i = idx; i < a->last; i++) {
		a->fields[i] = a->fields[i + 1];
	}
	a->last--;
}

void push_array(char *s, array *a) {
	insert_array(s, a, a->last);
}

void pop_array(array *a) {
	delete_array(a, a->last - 1);
}

void get_array(array *a, int i) {
	if (i < 0 || i >= a->last) {
		printf("failed to get: invalid index\n");
		return;
	}

	print_field(&(a->fields[i]));
}

void set_array(char *s, array *a, int i) {
	if (i < 0 || i >= a->last) {
		printf("failed to set: invalid index\n");
		return;
	}

	set_field(s, &(a->fields[i]));
	print_field(&(a->fields[i]));
}

void print_array(array *a) {
	int i, t;

	if (!a->last) {
		printf("array is empty\n");
		return;
	}

	for (i = 0; i < a->last; i++) {
		print_field(&(a->fields[i]));
	}
}

void print_size(array *a) {
	printf("\t%d\n", a->last);
}

void free_array(array *a) {
	int i;
	field *f;

	for (i = 0; i < a->last; i++) {
		f = &(a->fields[i]);
		if (f->type == STRING) {
			free(f->value.s);
		}
	}
}

int main(void) {
	array a;
	char s[STR], t[STR];
	char *arg, *c;
	int i;

	a.last = 0;

	while (scanf("%s", s)) {
		if (!strcmp(s, "push")) {
			fgets(t, STR, stdin);
			t[strcspn(t, "\n")] = 0;
			push_array(t+1, &a);
		} else if (!strcmp(s, "pop")) {
			pop_array(&a);
		} else if (!strcmp(s, "insert")) {
			if (!scanf("%d", &i)) {
				printf("failed to insert: invalid index\n");
			} else {
				fgets(t, STR, stdin);
				t[strcspn(t, "\n")] = 0;
				insert_array(t+1, &a, i);
			}
		} else if (!strcmp(s, "delete")) {
			if (!scanf("%d", &i)) {
				printf("failed to delete: invalid index\n");
			} else {
				delete_array(&a, i);
			}
		} else if (!strcmp(s, "get")) {
			if (!scanf("%d", &i)) {
				printf("failed to get: invalid index\n");
			} else {
				get_array(&a, i);
			}
		} else if (!strcmp(s, "set")) {
			if (!scanf("%d", &i)) {
				printf("failed to set: invalid index\n");
			} else {
				fgets(t, STR, stdin);
				t[strcspn(t, "\n")] = 0;
				set_array(t+1, &a, i);
			}
		} else if (!strcmp(s, "print")) {
			print_array(&a);
		} else if (!strcmp(s, "size")) {
			print_size(&a);
		} else if (!strcmp(s, "help")) {
			printf(
				"dynamic - dynamic array with unions and type inference\n"
				"usage:\tcommand [args]\n\t"
				"push <value> - push value to the array\n\t"
				"pop - pop value from the array\n\t"
				"insert <index> - insert value to the array\n\t"
				"delete <index> - delete value from the array\n\t"
				"get <index> - get value from the array\n\t"
				"set <index> <value> - set value at the index\n\t"
				"print - print array\n\t"
				"size - array size\n\t"
				"help - show this message\n\t"
				"exit - close this program\n"
			);
		} else if (!strcmp(s, "exit")) {
			break;
		} else {
			printf("unknown command: %s\n", s);
		}
	}
	free_array(&a);
}
