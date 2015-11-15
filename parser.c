#include "parser.h"

void read_input(char* filename) {
	FILE* input = fopen(filename, "r");
	if (!input) {
		exit(INPUT_FILE_FAILED_TO_OPEN);
	}


	fclose(input);
}
