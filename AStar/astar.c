//#include "astar.h"
#include "../heap.h"
#include "../robot.h"
#include "../parser.h"
#include "../errors.h"

void print_parents(node_t end, node_t start, maze_t* maze);
void get_neighbours(node_t* neighbours, maze_t maze, node_t curr, node_t target_node);
void check_edges_and_walls(node_t* neighbours, maze_t maze, node_t curr);
void add_to_open(heap_t* open, node_t* new_node);
node_t remove_from_open(heap_t* open);
void add_to_closed(node_t** closed, node_t* new_node, int *size);
bool compare_node(node_t one, node_t two);
void set_target(node_t* target, robot_t bot);
void set_starting(node_t* starting_node, robot_t bot);
void add_node(node_t** list, node_t* node, int* size);
int calc_cost(node_t curr, node_t target);
void set_f_cost(node_t* curr, node_t start, node_t end);
int calc_f_cost(node_t* curr, node_t start, node_t end); 
/*********************************
 * PARSING SHIT
 * *******************************/
int main(int argc, char** argv) {
	if (argc != 2) {
		printf("\nInsufficient number of command line arguments.  Exiting...\n");
		exit(INSUFFICIENT_COMMAND_LINE_ARGUMENTS);
	}
	heap_t open;
	int size, open_size, closed_size, new_f_cost, i;
	node_t starting_node, curr, target_node, *closed, neighbours[4];
	maze_t maze;
	robot_t bots[2];
	
	init_heap(&open);
	init_maze(&maze);
	init_robots(bots);
//delete when loop is implemented
	int bot_number = 0;
//function
/******************************
 * TODO LOOP
 * ****************************/
	closed = NULL;
	size = open_size = closed_size = 0;
	closed = malloc(sizeof(node_t));
	memset(closed, 0, sizeof(node_t));

	starting_node.f_cost = 0;

	read_input(argv[1], &maze, bots);
print_maze(maze);
	set_target(&target_node, bots[bot_number]);
	set_starting(&starting_node, bots[bot_number]);
printf("\nTARGET: (%d, %d)\nSTARTING: (%d, %d)", target_node.i_pos, target_node.j_pos, starting_node.i_pos, starting_node.j_pos);
//	set_f_cost(&starting_node, starting_node, target_node);
//printf("\nF_COST %d", starting_node.f_cost);
	add_to_open(&open, &starting_node);

print_array(open);
int j = 0;
int k;
	//check that target is reachable from starting

	while (1) {
		curr = remove_from_open(&open);
		add_to_closed(&closed, &curr, &closed_size);

		if (compare_node(target_node, curr)) {
//DO WHAT??? SAVE PATH SOMEHOW
			print_parents(target_node, starting_node, &maze);
			return 0;
		}
printf("\nRound: %d", j++);
		get_neighbours(neighbours, maze, curr, target_node);
		for (k = 0; k < 4; k++) {
			printf("\nNeighbour[%d]: (%d, %d) wall: %d", k, neighbours[k].i_pos, neighbours[k].j_pos, neighbours[k].wall);
		}
		for (i = 0; i < 4; i++) {
			if (neighbours[i].wall || neighbours[i].closed)
				continue;
		
			new_f_cost = calc_f_cost(&neighbours[i], curr, target_node); 

			if (new_f_cost < neighbours[i].f_cost || !neighbours[i].open) {
				set_f_cost(&neighbours[i], curr, target_node);
				maze.labyrinth[neighbours[i].i_pos][neighbours[i].j_pos].f_cost = new_f_cost;
//				set_f_cost(&maze.labyrinth[neighbours[i].i_pos][neighbours[i].j_pos], curr, target_node);
				neighbours[i].parent = &curr;
				maze.labyrinth[neighbours[i].i_pos][neighbours[i].j_pos].parent = &curr;
				if (!neighbours[i].open) {
					add_to_open(&open, &neighbours[i]);
					maze.labyrinth[neighbours[i].i_pos][neighbours[i].j_pos].open = true;
				}
			}
		}
		memset(neighbours, 0, sizeof(node_t)*4);
	}

	return 0;
}

void print_parents(node_t end, node_t start, maze_t* maze) {
	node_t curr = end;
	while (!compare_node(curr, start)) {
		(*maze).labyrinth[curr.i_pos][curr.j_pos].on_path = true;
//		(*maze).labyrinth[curr.i_pos][curr.j_pos].parent = &(curr.parent);
		printf("\n(%d, %d)", curr.i_pos, curr.j_pos);
		curr = *(curr.parent);
	}
}

void get_neighbours(node_t* neighbours, maze_t maze, node_t curr, node_t target_node) {
	check_edges_and_walls(neighbours, maze, curr);
/*	int i;
	for (i = 0; i < 4; i++) {
		if ((*neighbours)[i] != NULL) {
			set_f_cost((*neighbours)[i], curr, target_node); 
		}
	}
*/
}

void check_edges_and_walls(node_t* neighbours, maze_t maze, node_t curr) {
	if (curr.i_pos == 0)
		neighbours[0].wall = true;
	else {
//		maze.labyrinth[curr.i_pos - 1][curr.j_pos].parent = curr;
		neighbours[0] = maze.labyrinth[curr.i_pos - 1][curr.j_pos];
	}
	
	if (curr.i_pos == maze.num_rows - 1)
		neighbours[2].wall = true;
	else {
//		maze.labyrinth[curr.i_pos + 1][curr.j_pos].parent = curr;
		neighbours[2] = maze.labyrinth[curr.i_pos + 1][curr.j_pos];
	}

	if (curr.j_pos == 0)
		neighbours[3].wall = true;
	else {
//		maze.labyrinth[curr.i_pos][curr.j_pos - 1].parent = curr;
		neighbours[3] = maze.labyrinth[curr.i_pos][curr.j_pos - 1];
	}

	if (curr.j_pos == maze.num_cols - 1)
		neighbours[1].wall = true;
	else {
//		maze.labyrinth[curr.i_pos][curr.j_pos + 1].parent = curr;
		neighbours[1] = maze.labyrinth[curr.i_pos][curr.j_pos + 1];	
	}
}












void add_to_open(heap_t* open, node_t* new_node) {
	new_node->open = true;
	insert(open, *new_node);
}

node_t remove_from_open(heap_t* open) {
	node_t node = extract_min(open);
	node.open = false;
	return node;
}

void add_to_closed(node_t** closed, node_t* new_node, int *size) {
	*closed = realloc(*closed, sizeof(node_t*)*(*size + 1));
	new_node->closed = true;
	*closed[*size] = *new_node;
	(*size)++;
}

bool compare_node(node_t one, node_t two) {
	if (one.i_pos == two.i_pos && one.j_pos == two.j_pos)
		return true;
	return false;
}

void set_target(node_t* target_node, robot_t bot) {
	target_node->i_pos = bot.end_row;
	target_node->j_pos = bot.end_col;
}

void set_starting(node_t* starting_node, robot_t bot) {
	starting_node->i_pos = bot.start_row;
	starting_node->j_pos = bot.start_col;
}

void add_node(node_t** list, node_t* node, int* size) {
	if (*size > 0)
		*list = realloc(*list, sizeof(node_t)*(*size+1));
	list[*size++] = node;
}

int calc_cost(node_t curr, node_t target) {
	return abs(curr.i_pos - target.i_pos) + abs(curr.j_pos - target.j_pos);
}

void set_f_cost(node_t* curr, node_t start, node_t end) {
	(*curr).g_cost = calc_cost((*curr), start);
	(*curr).h_cost = calc_cost((*curr), end);
	(*curr).f_cost = (*curr).g_cost + (*curr).h_cost;
}

int calc_f_cost(node_t* curr, node_t start, node_t end) {
	int g_cost, h_cost, f_cost;
	g_cost = calc_cost((*curr), start);
	h_cost = calc_cost((*curr), end);
	f_cost = (*curr).g_cost + (*curr).h_cost;
	return f_cost;
}
