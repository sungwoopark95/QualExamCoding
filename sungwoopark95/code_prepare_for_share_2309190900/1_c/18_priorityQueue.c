#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
typedef struct {
    int *heap_array;
    int heap_size;
    int heap_capacity;
} PriorityQueue;

PriorityQueue* initialize(int capacity) {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->heap_size = 0;
    pq->heap_capacity = capacity;
    pq->heap_array = (int*)malloc(sizeof(int) * capacity);
    return pq;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(PriorityQueue* pq, int i) {
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < pq->heap_size && pq->heap_array[left] > pq->heap_array[largest])
        largest = left;

    if (right < pq->heap_size && pq->heap_array[right] > pq->heap_array[largest])
        largest = right;

    if (largest != i) {
        swap(&pq->heap_array[i], &pq->heap_array[largest]);
        heapify(pq, largest);
    }
}

void INSERT(PriorityQueue* pq, int key) {
    if (pq->heap_size == pq->heap_capacity) {
        printf("\nOverflow: Could not insert Key\n");
        return;
    }

    pq->heap_size++;
    int i = pq->heap_size - 1;
    pq->heap_array[i] = key;

    while (i != 0 && pq->heap_array[(i - 1) / 2] < pq->heap_array[i]) {
        swap(&pq->heap_array[i], &pq->heap_array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int MAXIMUM(PriorityQueue* pq) {
    return pq->heap_array[0];
}

int EXTRACT_MAX(PriorityQueue* pq) {
    if (pq->heap_size <= 0)
        return INT_MIN;
    
    if (pq->heap_size == 1) {
        pq->heap_size--;
        return pq->heap_array[0];
    }

    int root = pq->heap_array[0];
    pq->heap_array[0] = pq->heap_array[pq->heap_size - 1];
    pq->heap_size--;
    
    heapify(pq, 0);

    return root;
}

void INCREASE_KEY(PriorityQueue* pq, int i, int new_val) {
   if(new_val < pq->heap_array[i]) {
      printf("New key is smaller than current key.");
      return;
   }
   
   pq->heap_array[i] = new_val;

   while(i > 0 && pq->heap_array[(i-1)/2] < pq->heap_array[i]) {
      swap(&pq->heap_array[i], &pq->heap_array[(i-1)/2]);
      i = (i-1)/2;
   }
}


void printHeap(PriorityQueue* pq) {
   for(int i=0; i<pq->heap_size; i++) {
      printf("%d ", pq->heap_array[i]);
   }
   printf("\n");
}

int main() {
   PriorityQueue* pq = initialize(11);
   INSERT(pq, 3);
   INSERT(pq, 2);
   INSERT(pq, 15);
   INSERT(pq, 5);
   INSERT(pq, 4);
   INSERT(pq, 45);

   printHeap(pq);

   printf("%d ", EXTRACT_MAX(pq));
   printf("%d ", MAXIMUM(pq));

   printHeap(pq);

   return 0;
}