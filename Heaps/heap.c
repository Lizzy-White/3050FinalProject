#include "heap.h"
#include "errors.h"

void init_heap(heap_t* heap, int n) {
	heap->A = malloc(sizeof(int)*n);
	memset(heap->A, 0, sizeof(int)*n);
	heap->size = n;
}

void swap(int* x, int* y) {
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

void min_heapify(heap_t* heap, int i, int n) {
	int l, r, min;
	l = LEFT(i);
	r = RIGHT(i);
	if (l < n && heap->A[l] < heap->A[i])
		min = l;
	else
		min = i;
	if (r < n && heap->A[r] < heap->A[min])
		min = r;
	if (min != i) {
		swap(&heap->A[i], &heap->A[min]);
		min_heapify(heap, min, n);
	}
}

void build_min_heap(heap_t* heap, int n) {
	int i;
	for (i = n/2; i >= 0; i--)
		min_heapify(heap, i, n);
}

void heapsort(heap_t* heap, int n) {
	build_min_heap(heap, n);
	int i;
	for (i = n-1; i > 0; i--) {
		swap(&heap->A[0], &heap->A[i]);
		min_heapify(heap, 0, i-1);
	}
}

int kth_smallest(heap_t* heap, int k, int n) {
	if (k >= n)
		return -1;
	int i;
	heap_t temp_heap;
	init_heap(&temp_heap, k);
	for (i = 0; i < k; i++) 
		temp_heap.A[i] = heap->A[i];
	build_min_heap(&temp_heap, k);
	for (i = k; i < n; i++) {
		if (heap->A[i] < temp_heap.A[0]) {
			temp_heap.A[0] = heap->A[i];
			min_heapify(&temp_heap, 0, k);
		}
	}
	int smallest = temp_heap.A[0];
	uninit_heap(&temp_heap);
	return smallest;
}

void insert(heap_t* heap, int x) {
	heap->A = realloc(heap->A, sizeof(int)*(heap->size + 1));
	heap->A[heap->size] = INT_MAX;
	decrease_key(heap, heap->size++, x);
}

int minimum(heap_t* heap) {
	return heap->A[0];
}

int extract_min(heap_t* heap) {
	if (heap->size < 1) {
		fprintf(stderr, "\nError.  Heap underflow.\n");
		exit(HEAP_UNDERFLOW_EXTRACT_MIN);
	}
	int min = heap->A[0];
	heap->A[0] = heap->A[heap->size - 1];
	heap->size--;
	min_heapify(heap, 0, heap->size);
	return min;
}

void decrease_key(heap_t* heap, int i, int key) {
	if (key > heap->A[i]) {
		fprintf(stderr, "\nError.  New key is larger than current key.\n");
		return;
	}
	
	heap->A[i] = key;
	
	while (i > 0 && heap->A[PARENT(i)] > heap->A[i]) {
		swap(&heap->A[i], &heap->A[PARENT(i)]);
		i = PARENT(i);
	}	
}

void print_array(heap_t heap) {
	int i;
	printf("\n\n");
	for (i = 0; i < heap.size; i++) 
		printf("%3d", heap.A[i]);
}

void uninit_heap(heap_t* heap) {
	free(heap->A);
	heap->size = 0;
}
