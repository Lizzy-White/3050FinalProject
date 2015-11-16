#include "maze.h"
#include "parser.h"
#include "robot.h"
#include "errors.h"

int main(int argc, char** argv) {
	if (argc != 2) {
		printf("\nInsufficient command line arguments"
				"\nUsage: ./a.out <input file>"
				"\nExiting...");
		exit(INSUFFICIENT_COMMAND_LINE_ARGUMENTS);
	}

	maze_t maze;
	init_maze(&maze);
	robot_t bots[2];
	init_robots(bots);
	read_input(argv[1], &maze, bots);
	print_maze(maze);
	uninit_maze(&maze);
	return 0;
}
