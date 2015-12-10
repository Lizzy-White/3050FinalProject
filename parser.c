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
	maze->labyrinth = malloc(sizeof(node_t*));
	
	char c;
	int curr_col, i;
	bool newline = false;
	curr_col = 0;
	maze->num_cols = get_num_columns(input);
	
	maze->labyrinth[0] = alloc_and_set(maze->labyrinth[0], maze->num_cols);

	while ((c = getc(input)) != EOF) {
		if (c == '\n') {
			if (curr_col + 1 < maze->num_cols) 
				for (i = curr_col + 1; i < maze->num_cols; i++)
					maze->labyrinth[maze->num_rows][i].object = ' ';
			newline = true;
			continue;
		}
		else if (newline) {
			maze->num_rows++;
			curr_col = 0;
			maze->labyrinth = realloc(maze->labyrinth, sizeof(node_t*)*(maze->num_rows + 1));
			maze->labyrinth[maze->num_rows] = alloc_and_set(maze->labyrinth[maze->num_rows], maze->num_cols);
			newline = false;
		}
		if (c == '#' || c == ' ') { 
			if (c == '#')
				maze->labyrinth[maze->num_rows][curr_col].wall = true;
			maze->labyrinth[maze->num_rows][curr_col].object = c;
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
//				printf("[%c]", c);
				quit(INVALID_CHARACTER_ENCOUNTERED, maze, input);
			}
			maze->labyrinth[maze->num_rows][curr_col].object = c;
		}
		else if (c == '\r') {
			newline = true;
			continue;
		}
		else {
//			printf("%c", c);
			quit(INVALID_CHARACTER_ENCOUNTERED, maze, input);
		}
		if (curr_col != -1) {
			maze->labyrinth[maze->num_rows][curr_col].i_pos = maze->num_rows;
			maze->labyrinth[maze->num_rows][curr_col].j_pos = curr_col;
		}
		curr_col++;
	}
	maze->num_rows++;
	return maze;
}

node_t* alloc_and_set(node_t* maze_row, int n) {
	maze_row = malloc(sizeof(node_t)*n);
	memset(maze_row, 0, sizeof(node_t)*n);
	return maze_row;
}

int get_num_columns(FILE* input) {
	char c;
	int n, max;
	n = max = 0;
	
	while ((c = getc(input)) != EOF) {
		if (c == '\n' || c == '\r') {
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
