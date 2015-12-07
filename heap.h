#ifndef H_HEAP_H
#define H_HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define LEFT(i) 2*i+1
#define RIGHT(i) 2*i+2
#define PARENT(i) (i-1)/2
#define SIZE 8

/*
 * NODE:
 * 		g_cost - distance from starting node to current node; always 1
 * 		h_cost - distance from current node to target node
 * 		f_cost - g_cost + h_cost
 * 		i_pos - row of this node's locations
 * 		j_pos - column of this node's location
 * 		object - visual representation of the maze spot
 * 		parent - ??????????????????????????????????????????????????????
 * 		open - states whether the node is in the open list
 * 		closed - states whether the node is in the closed list
 * 		wall - states whether or not the node is a wall
 */
typedef struct node {
	int g_cost;
	int h_cost;
	int f_cost;
	int i_pos;
	int j_pos;
	char object;
	struct node* parent;
	bool open;
	bool closed;
	bool wall;
	bool on_path;
} node_t;

/*
 * HEAP:
 * 		A - array of keys
 * 		size - number of elements in the heap
 */
typedef struct heap {
	node_t* A;
	int size;
} heap_t;

/*
 * Malloc space for the array.
 * Initialize all bytes to 0.
 * Set the heap size to the number of elements in the array
 * O(1)
 */
void init_heap(heap_t* heap);

/*
 * Swaps two elements.
 * O(1)
 */
void swap(node_t* x, node_t* y);

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
void insert(heap_t* heap, node_t x);

/*
 * Returns the element at heap->A[0]
 * O(1)
 */
node_t minimum(heap_t* heap);

/*
 * Returns and removes the element at heap->A[0], restoring heap properties
 * after deletion
 * O(log(n))
 */
node_t extract_min(heap_t* heap);

/*
 * Decreases the value of element i to key
 * O(log(n))
 */
void decrease_key(heap_t* heap, int i, node_t key);

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

#endif
