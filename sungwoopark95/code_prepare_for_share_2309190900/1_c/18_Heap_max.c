#include <stdio.h> //printf, scanf
#include <stdlib.h> //malloc
#include <stdbool.h> //bool

#define LEFT(i) (2 * (i) + 1)
#define RIGHT(i) (2 * (i) + 2)
#define PARENT(i) (i > 0 ? (((i) - 1) / 2) : 0)
// Implementation of a priority queue using a max-heap.
typedef struct {
    int *arr;
    int capacity; // number of memory allocated for elements
    int size; // number of elements
} Max_heap;

void heapify(Max_heap *heap, int i) {
    int l = LEFT(i);
    int r = RIGHT(i);
    int max_i = i;

    if (l < heap->size && heap->arr[l] > heap->arr[max_i]) {
        max_i = l;
    }
    if (r < heap->size && heap->arr[r] > heap->arr[max_i]) {
        max_i = r;
    }

    if (max_i != i) {
        int temp = heap->arr[max_i];
        heap->arr[max_i] = heap->arr[i];
        heap->arr[i] = temp;

        heapify(heap, max_i);
    }
}

void build_heap(Max_heap *heap) {
    for (int i = PARENT(heap->size - 1); i >= 0; --i) {
        heapify(heap, i);
    }
}

int insert(Max_heap *heap, int elem) {
    if (heap->size == heap->capacity) {
        return 1;
    }

    heap->arr[heap->size] = elem;
    heap->size++;

    int i = heap->size - 1;

    while (i > 0) {
        i = PARENT(i);
        heapify(heap, i);
    }

    return 0;
}

int extract_max(Max_heap *heap, int *result) {
    if (heap->size == 0) {
        return 1;
    }

    *result = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;
    heapify(heap, 0);

    return 0;
}

int max_heap_init(Max_heap *heap, int capacity, int *inits, int n) {
    heap->arr = malloc(capacity * sizeof(int));

    if (heap->arr == NULL) {
        return 1;
    }

    heap->size = 0;
    heap->capacity = capacity;

    if (n > 0) {
        int i = 0;
        for (; i < n && i < capacity; ++i) {
            heap->arr[i] = inits[i];
        }
        heap->size = i;

        build_heap(heap);
    }

    return 0;
}

int max_heap_destroy(Max_heap *heap) {
    if (heap->arr == NULL) {
        return 1;
    }

    free(heap->arr);

    return 0;
}

long long max_heap_sum(Max_heap *heap) {
    long long result = 0;

    for (int i = 0; i < heap->size; ++i) {
        result += heap->arr[i];
    }

    return result;
}
