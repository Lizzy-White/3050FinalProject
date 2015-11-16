#ifndef H_ROBOT_H
#define H_ROBOT_H

#include <string.h>

/*
 * ROBOT:
 * 	holds starting and ending rows and columns of each robot
 */
typedef struct robot {
	int start_row;
	int start_col;
	int end_row;
	int end_col;
} robot_t;

/*
 * Sets all member of bots to NULL or 0.
 */
void init_robots(robot_t* bots);

/*
 * Sets starting index of specific bot once found in file
 */
void set_start(robot_t* bot, int row, int col);

/*
 * Sets ending index of specific bot once found in file
 */
void set_end(robot_t* bot, int row, int col);

#endif
