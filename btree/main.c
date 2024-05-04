#include "btree.h"

int *populate(int len) {
	int *arr, i;

	arr = malloc(sizeof(int) * len);
	assert(arr);
	arr[0] = len;
	for (i = 1; i < len; i++) {
		arr[i] = rand() % 100 + 1;
	}
	return arr;
}

void remove_item(int *nums, int k, int len) {
	int i, j;

	for (i = 1; i < len; i++) {
		if (nums[i] == k) {
			break;
		}
	}
	for (j = i; j < len; j++) {
		nums[j] = nums[j + 1];
	}
}

int main(void) {
	int i, k, m, n;
	int len = 32;
	int *nums = populate(len);

	init_tree(2);
	for (i = 0; i < len; i++) {
		insert_btree(nums[i]);
	}
	print_btree(root, 0);
	for (i = 0; i < 5; i++) {
		k = nums[rand() % len];
		m = n = 0;
		search_btree(root, k, &m, &n);
		printf("%d:\t%d\t%d\n", k, m, n);
		delete_btree(root, k);
		remove_item(nums, k, len);
		print_btree(root, 0);
		len--;
	}
	free_btree(root);
	return 0;
}
