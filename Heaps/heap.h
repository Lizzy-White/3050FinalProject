#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define LEFT(i) 2*i+1
#define RIGHT(i) 2*i+2
#define PARENT(i) (i-1)/2
#define SIZE 8

/*
 * HEAP:
 * 		A - array of keys
 * 		size - number of elements in the heap
 */
typedef struct heap {
	int* A;
	int size;
} heap_t;

/*
 * Malloc space for the array.
 * Initialize all bytes to 0.
 * Set the heap size to the number of elements in the array
 * O(1)
 */
void init_heap(heap_t* heap, int n);

/*
 * Swaps two elements.
 * O(1)
 */
void swap(int* x, int* y);

/* Traverse the heap, making the subtree with root heap->A[i] a heap if 
 * and only if the subtrees rooted at both heap->A[LEFT(i)] and 
 * heap->A[RIGHT(i)] are heaps
 * O(log(n))
 */
void min_heapify(heap_t* heap, int i, int n);

/*
 * Makes the nearly complete binary tree stored in heap->A[0...n-1] a heap.
 * O(n)
 */
void build_min_heap(heap_t* heap, int n); 

/*
 * Takes in an array and builds a min heap from it.
 * Swap the root (the minimum element) with the last element in the array.
 * Now, the minimum is in the correct place.
 * Call min_heapify to fix the heap.
 * Repeat.
 * O(nlog(n))
 */
void heapsort(heap_t* heap, int n);

/*
 * Finds the kth-smallest element of the heap.
 * O(nlog(k))
 */
int kth_smallest(heap_t* heap, int k, int n); 

/*
 * Inserts the key x into the heap.
 * O(log(n))
 */
void insert(heap_t* heap, int x);

/*
 * Returns the element at heap->A[0]
 * O(1)
 */
int minimum(heap_t* heap);

/*
 * Returns and removes the element at heap->A[0], restoring heap properties
 * after deletion
 * O(log(n))
 */
int extract_min(heap_t* heap);

/*
 * Decreases the value of element i to key
 * O(log(n))
 */
void decrease_key(heap_t* heap, int i, int key);

/*
 * Prints the heap in index order
 * O(n)
 */
void print_array(heap_t heap);

/*
 * Frees all space associated with the heap.
 * O(1)
 */
void uninit_heap(heap_t* heap);
