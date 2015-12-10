#include "maze.h"

void init_maze(maze_t* maze) {
	memset(maze, 0, sizeof(maze_t));
}

void print_maze(maze_t* maze) {
	int i, j;
	for (i = 0; i < maze[0].num_rows; i++) {
		printf("\n");
		for (j = 0; j < maze[0].num_cols; j++) {
			if (maze[0].labyrinth[i][j].object == 'S' || maze[0].labyrinth[i][j].object == 'E')
				printf(BLU "%c", maze[0].labyrinth[i][j].object);
			else if (maze[0].labyrinth[i][j].object == 'L' || maze[0].labyrinth[i][j].object == 'F')
				printf(KRED "%c", maze[0].labyrinth[i][j].object);

			else if (maze[0].labyrinth[i][j].object == '*' && maze[1].labyrinth[i][j].object == '*')
			   printf("*");	
			else if (maze[1].labyrinth[i][j].visit == RED)
				printf(KRED "*");
			else if (maze[0].labyrinth[i][j].visit == BLUE)
				printf(BLU "*");
			else if (maze[1].labyrinth[i][j].visit == GREEN)
				printf(GRN "*");
			else if (maze[0].labyrinth[i][j].visit == YELLOW)
				printf(YEL "*");
			else if (maze[1].labyrinth[i][j].visit == PINK)
				printf(PNK "*");
			else if (maze[0].labyrinth[i][j].visit == CYAN)
				printf(CYN "*");
			else
				printf(NRM "%c", maze[0].labyrinth[i][j].object);
		}
	}

	printf("\n\n");
}

void uninit_maze(maze_t* maze) {
	int i;
	for (i = 0; i < maze->num_rows; i++)
		free(maze->labyrinth[i]);
	free(maze->labyrinth);
}
