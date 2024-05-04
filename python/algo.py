graph = dict(((0, (1, 2, 3)), (1, (0, 2)), (2, (1, 4)), (3, (0,))))

def bfs(graph, head):
    stack = list()
    visited = set()
    stack.append(head)
    visited.add(head)
    while len(stack) > 0:
        node = stack.pop()
        print(str(node) + ': ', end='')
        if node not in graph:
            print('null')
            continue
        for adj in graph.get(node):
            if adj not in visited:
                stack.append(adj)
                visited.add(adj)
                print(str(adj) + ', ', end='')
        print()

from collections import deque

def dfs(graph, head):
    queue = deque()
    visited = set()
    queue.append(head)
    visited.add(head)
    while len(queue) > 0:
        node = queue.popleft()
        print(str(node) + ': ', end='')
        if node not in graph:
            print('null')
            continue
        for adj in graph[node]:
            if adj not in visited:
                visited.add(adj)
                queue.append(adj)
                print(str(adj) + ', ', end='')
        print()

bfs(graph, 0)
dfs(graph, 0)

import random

array = list(range(100))
random.shuffle(array)

def insert(array):
    for i in range(1, len(array)):
        item = array[i]
        j = i - 1
        while j >= 0 and array[j] > item:
            array[j + 1] = array[j]
            j -= 1
        """
        Why it does not work?
        for j in reversed(range(i)):
            if array[j] <= item:
                j += 1
                break
            array[j + 1] = array[j]
        """
        array[j + 1] = item

import math

def merge(array, p, r):
    if p >= r:
        return
    q = (p + r) // 2
    merge(array, p, q)
    merge(array, q+1, r)
    combine(array, p, q, r)

def combine(array, p, q, r):
    left = array[p:q+1]
    right = array[q+1:r+1]
    left.append(math.inf)
    right.append(math.inf)
    i, j = 0, 0
    for k in range(p, r+1):
        if left[i] <= right[j]:
            array[k] = left[i]
            i += 1
        else:
            array[k] = right[j]
            j += 1

def quicksort(array, p, r):
    if p >= r:
        return
    q = partition(array, p, r)
    quicksort(array, p, q-1)
    quicksort(array, q+1, r)

def partition(array, p, r):
    q = p
    for u in range(p, r):
        if array[u] < array[r]:
            swap(array, q, u)
            q += 1
    swap(array, q, r)
    return q

def swap(array, p, r):
    temp = array[p]
    array[p] = array[r]
    array[r] = temp

array_copy = array.copy()
insert(array_copy)
print(array_copy)
array_copy = array.copy()
merge(array_copy, 0, len(array_copy)-1)
print(array_copy)
array_copy = array.copy()
quicksort(array_copy, 0, len(array_copy)-1)
print(array_copy)

"""
NOTES:
1. At Mergesort, q is included in left! (left[p:q+1])
   I do not know why exactly. I thought it should not matter.
2. At Quicksort, q is not included at recursive calls (quicksort(a, p, q-1))
   It is because partition element is already 'sorted'
3. Why cant I rewrite insertion if I wish so???
"""
