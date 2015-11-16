#include "maze.h"

void init_maze(maze_t* maze) {
	memset(maze, 0, sizeof(maze_t));
}

void print_maze(maze_t maze) {
	int i, j;
	for (i = 0; i < maze.num_rows; i++) {
		printf("\n");
		for (j = 0; j < maze.num_cols; j++) {
/*
 * COLOR TESTING
 * 			if (isalpha(maze.labyrinth[i][j]))
				printf(YEL "%c", maze.labyrinth[i][j]);
			else
*/				printf(NRM "%c", maze.labyrinth[i][j]);
		}
	}
	printf("\n");
}

void uninit_maze(maze_t* maze) {
	int i;
	for (i = 0; i < maze->num_rows; i++)
		free(maze->labyrinth[i]);
	free(maze->labyrinth);
}
