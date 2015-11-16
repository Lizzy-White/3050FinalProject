#include "parser.h"

void read_input(char* filename) {
	FILE* input = fopen(filename, "r");
	if (!input) {
		exit(INPUT_FILE_FAILED_TO_OPEN);
	}

	int num_columns;
	char** maze = parse(input, &num_columns);

	if (fclose(input) == EOF) {
		quit(INPUT_FILE_FAILED_TO_CLOSE);
	}
}

char** parse(FILE* input, int* num_columns) {	
	char **maze = malloc(sizeof(char*));
	
	char c;
	int num_rows = 0, curr_col = 0;
	*num_columns = get_num_columns(input);
	
	*maze = malloc(sizeof(char)*(*num_columns));

	while ((c = getc(input)) != EOF) {
		if (c == '\n') {
			num_rows++;
			**maze = realloc(maze, sizeof(char*)*(num_rows + 1);
			maze[num_rows] = malloc(sizeof(char)*(*num_columns));
		}
		else if (c == '#' || c == ' ') 
			maze[num_rows][num_columns] = c;
		else if (isalpha(c)) {
			if (c == 'S')
				robot1_start = 
			//CHECK FOR VALID ALPHA
			//S F E L
		}
		else {
		
		}
		curr_col++;	
	}	
}

int get_num_columns(FILE* input) {
	int n = 0;
	char c;
	while ((c = getc(input)) != '\n')
		n++;
	fseek(input, 0, SEEK_SET);
	return n;
}

void quit(error e, char** maze, int n) {

}
