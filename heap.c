#include "heap.h"
#include "errors.h"

void init_heap(heap_t* heap) {
	memset(heap, 0, sizeof(heap_t));
}

void swap(node_t* x, node_t* y) {
	node_t* temp;
	temp = x;
	x = y;
	y = temp;
}

void min_heapify(heap_t* heap, int i, int n) {
	int l, r, min;
	node_t temp;
	l = LEFT(i);
	r = RIGHT(i);
	if (l < n && heap->A[l].f_cost <= heap->A[i].f_cost)
		min = l;
	else
		min = i;
	if (r < n && heap->A[r].f_cost < heap->A[min].f_cost)
		min = r;
	if (min != i) {
		temp = heap->A[i];
		heap->A[i] = heap->A[min];
		heap->A[min] = temp;
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

void insert(heap_t* heap, node_t x) {
	heap->A = realloc(heap->A, sizeof(node_t)*(heap->size + 1));
	heap->A[heap->size].f_cost = INT_MAX;
	decrease_key(heap, heap->size++, x);
}

node_t minimum(heap_t* heap) {
	return heap->A[0];
}

node_t extract_min(heap_t* heap) {
	if (heap->size < 1) {
		fprintf(stderr, "\nError.  Robot is unable to reach the end of the maze.\n");
		exit(ROBOT_UNABLE_TO_REACH_END_OF_MAZE);
	}
	node_t min = heap->A[0];
	heap->A[0] = heap->A[heap->size - 1];
	heap->size--;
	min_heapify(heap, 0, heap->size);
	return min;
}

void decrease_key(heap_t* heap, int i, node_t key) {
	if (key.f_cost > heap->A[i].f_cost) {
		fprintf(stderr, "\nError.  New key is larger than current key.\n");
		return;
	}

	node_t temp;	
	heap->A[i] = key;
	
	while (i > 0 && heap->A[PARENT(i)].f_cost > heap->A[i].f_cost) {
		temp = heap->A[i];
		heap->A[i] = heap->A[PARENT(i)];
		heap->A[PARENT(i)] = temp;		
		i = PARENT(i);
	}	
}

void print_array(heap_t heap) {
	int i;
	printf("\n\n");
	for (i = 0; i < heap.size; i++) 
		printf("%3d", heap.A[i].f_cost);
}

void uninit_heap(heap_t* heap) {
	free(heap->A);
	heap->size = 0;
}
