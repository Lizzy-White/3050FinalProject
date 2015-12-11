#include "search.h"
#include "maze.h"
#include "parser.h"
#include "heap.h"
#include "robot.h"

int main(int argc, char** argv) {
	if (argc != 3) {
		printf("\nInsufficient number of command line arguments.  Exiting...\n");
		exit(INSUFFICIENT_COMMAND_LINE_ARGUMENTS);
	}

	int r = atoi(argv[2]);
	if (r < 0)
		exit(INVALID_COMMAND_INPUT);

	maze_t maze[2];	
	init_maze(&maze[0]);
	init_maze(&maze[1]);

	robot_t bots[2];
	init_robots(bots);

	read_input(argv[1], &maze[0], bots);
	read_input(argv[1], &maze[1], bots);

	node_t starting_node[2], target_node[2], *neighbours[4], **parents[2];
	init_start_and_target_nodes(starting_node, target_node, bots);

	if (r == 0)
		a_star(maze, starting_node, target_node, neighbours, parents);
	else {
		char**** visits = NULL;
		int x;
		int done[2];
		done[0] = done[1] = false;
		visits = init_visits(visits, maze);
		x = DFS(starting_node[0], starting_node[1], maze, r, starting_node, target_node, done, visits);
		if (x == -1) {
			printf("\nNo solution with r = %d", r);
			return 0;
		}
		print_maze(maze);
		uninit_visits(visits, maze);
	}
	uninit_maze(&maze[0]);
	uninit_maze(&maze[1]);
	return 0;
}
