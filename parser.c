#include "parser.h"


void read_input(char* filename, maze_t* maze, robot_t* bots) {
	FILE* input = fopen(filename, "r");
	if (!input) {
		exit(INPUT_FILE_FAILED_TO_OPEN);
	}

	parse(input, maze, bots);

	if (fclose(input) == EOF) {
		quit(INPUT_FILE_FAILED_TO_CLOSE, maze, input);
	}
}

maze_t* parse(FILE* input, maze_t* maze, robot_t* bots) {	
	maze->labyrinth = malloc(sizeof(char*));
	
	char c;
	int curr_col;
	bool newline = false;
	curr_col = 0;
	maze->num_cols = get_num_columns(input);
	
	maze->labyrinth[0] = alloc_and_set(maze->labyrinth[0], maze->num_cols);

	while ((c = getc(input)) != EOF) {
		if (c == '\n') {
			newline = true;
			continue;
		}
		else if (newline) {
			maze->num_rows++;
			curr_col = -1;
			maze->labyrinth = realloc(maze->labyrinth, sizeof(char*)*(maze->num_rows + 1));
			maze->labyrinth[maze->num_rows] = alloc_and_set(maze->labyrinth[maze->num_rows], maze->num_cols);
			newline = false;
		}
		else if (c == '#' || c == ' ') { 
			maze->labyrinth[maze->num_rows][curr_col] = c;
		}
		else if (isalpha(c)) {
			if (c == 'S') 
				set_start(&bots[0], maze->num_rows, curr_col);
			else if (c == 'E') 
				set_end(&bots[0], maze->num_rows, curr_col);
			else if (c == 'F') 
				set_start(&bots[1], maze->num_rows, curr_col);
			else if (c == 'L') 
				set_end(&bots[1], maze->num_rows, curr_col);
			else{
				quit(INVALID_CHARACTER_ENCOUNTERED, maze, input);
			}
			maze->labyrinth[maze->num_rows][curr_col] = c;
		}
		else if (c == '\r') {
			continue;
		}
		else {
			quit(INVALID_CHARACTER_ENCOUNTERED, maze, input);
		}
		curr_col++;	
	}
	maze->num_rows++;
	return maze;
}

char* alloc_and_set(char* maze_row, int n) {
	maze_row = malloc(sizeof(char)*n);
	memset(maze_row, ' ', sizeof(char)*n);
	return maze_row;
}

int get_num_columns(FILE* input) {
	char c;
	int n, max;
	n = max = 0;
	
	while ((c = getc(input)) != EOF) {
		if (c == '\n') {
			if (n > max)
				max = n;
			n = 0;
			continue;
		}
		n++;
	}
	
	fseek(input, 0, SEEK_SET);
	
	return max;
}

void quit(error e, maze_t* maze, FILE* fp) {
	fclose(fp);
	uninit_maze(maze);
	exit(e);
}
