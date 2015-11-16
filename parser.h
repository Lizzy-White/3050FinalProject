#ifndef H_PARSER_H
#define H_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "errors.h"
#include "maze.h"
#include "robot.h"

/*
 * Reads in the input file, invoking parse() to parse the data accordingly.
 */
void read_input(char* filename, maze_t* maze, robot_t* bots);

/*
 * Parses the input file.
 * Stores number of rows and columns in the grid into maze.
 * Stores the starting and ending points of each robot into bots.
 * Returns the loaded maze at the end.
 */
maze_t* parse(FILE* input, maze_t* maze, robot_t* bots);

/*
 * Allocates memory for a row.
 * Sets all elements to a whitespace.
 */
char* alloc_and_set(char* maze_row, int n);

/*
 * Traverses through each line of the file, finding the longest one.
 * Uses this number to malloc the rectangular matrix.
 */
int get_num_columns(FILE* input);

/*
 * In case of some error, closes the file and frees all memory before exiting.
 */
void quit(error e, maze_t* maze, FILE* fp);

#endif
