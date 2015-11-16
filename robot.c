#include "robot.h"

void init_robots(robot_t* bots) {
	memset(bots, 0, sizeof(robot_t));
}

void set_start(robot_t* bot, int row, int col) {
	bot->start_row = row;
	bot->start_col = col;
}

void set_end(robot_t* bot, int row, int col) {
	bot->end_row = row;
	bot->end_col = col;
}
