#ifndef H_MAZE_H
#define H_MAZE_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "heap.h"

#define YEL "\x1B[33m"
#define GRN "\x1B[32m"
#define BLU "\x1B[34m"
#define NRM "\x1B[0m"
#define PNK "\x1B[35m"
#define KRED "\x1B[31m"
#define CYN "\x1B[36m"
/*
 * MAZE:
 * 	labyrinth: 2-D array containing the visual maze
 * 	num_rows: total number of rows in the maze
 * 	num_cols: total number of columns in the maze
 */
typedef struct maze {
	node_t** labyrinth;
	int num_rows;
	int num_cols;
} maze_t;

/*
 * Sets all members of maze to NULL or 0
 */
void init_maze(maze_t* maze);

/*
 * Prints the maze.
 */
void print_maze(maze_t* maze);

/*
 * Frees all memory allocated in the maze.
 */
void uninit_maze(maze_t* maze);

#endif
