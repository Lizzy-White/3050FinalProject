#include "search.h"

void a_star(maze_t* maze, node_t* starting_node, node_t* target_node, node_t** neighbours, node_t*** parents) {
	heap_t open[2];
	int size, parent_size[2], open_size, closed_size[2], new_f_cost, i, index, robot_num;
	node_t *curr_ref[2], *closed_ref[2], *curr, *closed;
	bool cont_flag[2];

	for (robot_num = 0; robot_num < 2; robot_num++) {
		init_heap(&open[robot_num]);
		closed_ref[robot_num] = curr_ref[robot_num] = NULL;
		size = open_size = closed_size[0] = closed_size[1] = 0;
		closed_ref[robot_num] = malloc(sizeof(node_t));
		memset(closed_ref[robot_num], 0, sizeof(node_t));
		add_to_open(&open[robot_num], &starting_node[robot_num]);
		maze[robot_num].labyrinth[starting_node[robot_num].i_pos][starting_node[robot_num].j_pos].open = true;
		cont_flag[robot_num] = true;
	}

	while (1) {
		for (robot_num = 0; robot_num < 2; robot_num++) {
			if (!cont_flag[0] && !cont_flag[1]) {
				parents[0] = store_parents(target_node[0], starting_node[0], &maze[0], BLUE, &parent_size[0]);
				printf("\nROBOT 1:\nFinal path in DARK BLUE\n");
				print_maze(maze);
				parents[1] = store_parents(target_node[1], starting_node[1], &maze[1], RED, &parent_size[1]);
				printf("\nROBOT 2:\nFinal path in RED\n");
				print_maze(maze);
				print_parents(parents, parent_size);
				return;
			}

			if (!cont_flag[robot_num])
				continue;

			closed = closed_ref[robot_num];
			curr_ref[robot_num] = remove_from_open(&open[robot_num], &maze[robot_num]);
			curr = curr_ref[robot_num];
			closed = add_to_closed(closed, curr, &closed_size[robot_num]);
			closed_ref[robot_num] = closed;

			maze[robot_num].labyrinth[curr->i_pos][curr->j_pos].open = false;
			maze[robot_num].labyrinth[curr->i_pos][curr->j_pos].closed = true;

			if (robot_num == 0)
				maze[robot_num].labyrinth[curr->i_pos][curr->j_pos].visit = CYAN;
			else
				maze[robot_num].labyrinth[curr->i_pos][curr->j_pos].visit = PINK;

			if (compare_node(target_node[robot_num], *curr)) {
				cont_flag[robot_num] = false;
				continue;
			}

			get_neighbours(neighbours, maze[robot_num], *curr);

			for (i = 0; i < 4; i++) {
				if (neighbours[i]->wall || neighbours[i]->closed)
					continue;

				if (robot_num == 0){
					if (maze[robot_num].labyrinth[neighbours[i]->i_pos][neighbours[i]->j_pos].visit != CYAN)
						maze[robot_num].labyrinth[neighbours[i]->i_pos][neighbours[i]->j_pos].visit = YELLOW;
				}
				else
					if (maze[robot_num].labyrinth[neighbours[i]->i_pos][neighbours[i]->j_pos].visit != PINK)
						maze[robot_num].labyrinth[neighbours[i]->i_pos][neighbours[i]->j_pos].visit = GREEN;

				new_f_cost = calc_f_cost(neighbours[i], *curr, target_node[robot_num]); 

				if (new_f_cost < neighbours[i]->f_cost || !neighbours[i]->open) {
					set_f_cost(neighbours[i], *curr, target_node[robot_num]);
					neighbours[i]->parent = curr;
					if (!neighbours[i]->open) {
						add_to_open(&open[robot_num], neighbours[i]);
						maze[robot_num].labyrinth[neighbours[i]->i_pos][neighbours[i]->j_pos].open = true;
					}
					else {
						index = find_index((*neighbours)[i], open[robot_num]);
						decrease_key(&open[robot_num], index, (*neighbours)[i]);
					}
				}
			}
			usleep(45000);
			print_maze(maze);
		}

	}
}


int DFS(node_t R1, node_t R2, maze_t* maze, int r, node_t* start, node_t* target, int* done, char**** visits) {
	if (compare_node(R1, target[0])) 
		done[0] = true;
	if (compare_node(R2, target[1]))
		done[1] = true;
	if (done[0] && done[1])
		return 1;

	node_t* curr[2];

	curr[0] = &(maze[0].labyrinth[R1.i_pos][R1.j_pos]);
	curr[1] = &(maze[1].labyrinth[R2.i_pos][R2.j_pos]);

	curr[0]->visit = BLUE;
	curr[1]->visit = RED;
	//	print_maze(maze);

	node_t* neighbours[2][4];
	get_neighbours(neighbours[0], maze[0], *curr[0]);
	get_neighbours(neighbours[1], maze[1], *curr[1]);

	int k, m, x = 0;
	for (m = 0; m < 2; m++) {
		for (k = 0; k < 4; k++) {	
			set_f_cost(neighbours[m][k], start[m], target[m]);
			neighbours[m][k]->parent = curr[m]; 
		}
	}

	insertion_sort(neighbours[0]);
	insertion_sort(neighbours[1]);
	int i = 0;
	int a, b, c, d;
	for (m = 0; m < 2; m++) {
		for (i = 0; i < 4; i++) {
			if (m == 0){
				a = neighbours[m][i]->i_pos;
				b = neighbours[m][i]->j_pos;
				c = curr[1]->i_pos;
				d = curr[1]->j_pos;
			}
			else {
				a = curr[0]->i_pos;
				b = curr[0]->j_pos;
				c = neighbours[m][i]->i_pos;
				d = neighbours[m][i]->j_pos;
			}
			if (visits[a][b][c][d] != '1' && !neighbours[m][i]->wall && distance_check(r, *(neighbours[m][i]), *(curr[(m + 1)%2])) && !done[m]) {

				visits[a][b][c][d] = '1';
				if (m == 0) {
					neighbours[m][i]->visit = BLUE;
					x = DFS(*(neighbours[m][i]), R2, maze, r, start, target, done, visits);
				}
				else{
					neighbours[m][i]->visit = RED;
					x = DFS(R1, *(neighbours[m][i]), maze, r, start, target, done, visits);
				}

			}
			if (x == 1) 
				return 1;
		}	
	}

	curr[0]->visit = CYAN;
	curr[1]->visit = PINK;
	return -1;
}

void print_parents(node_t*** parents, int* size) {
	int i, j;
	for (i = 0; i < 2; i++) {
		printf("\nROBOT %d's PATH:   ", i+1);
		for	(j = 0; j < size[i]; j++)   
			printf("(%d, %d) -> ", parents[i][j]->i_pos, parents[i][j]->j_pos);
	}
}

char**** init_visits(char**** visits, maze_t* maze) {
	visits = malloc(sizeof(char***)*maze[0].num_rows);
	int a, b, c;
	for (a = 0; a < maze[0].num_rows; a++) {
		visits[a] = malloc(sizeof(char**)*maze[0].num_cols);
		for (b = 0; b < maze[0].num_cols; b++) {
			visits[a][b] = malloc(sizeof(char*)*maze[0].num_rows);
			for (c = 0; c < maze[0].num_rows; c++){
				visits[a][b][c] = malloc(sizeof(char)*maze[0].num_cols);
				memset(visits[a][b][c], 0, sizeof(char)*maze[0].num_cols);
			}
		}
	}
	return visits;
}

void init_start_and_target_nodes(node_t* starting_node, node_t* target_node, robot_t* bots){
	int robot_num;
	for (robot_num = 0; robot_num < 2; robot_num++) {
		set_target(&target_node[robot_num], bots[robot_num]);
		set_starting(&starting_node[robot_num], bots[robot_num]);
	}
}
void insertion_sort(node_t** a){
	int i, j;
	node_t* key;
	for (j = 1; j < 4; j++) {
		key = a[j];
		i = j - 1;
		while (i >= 0 && a[i]->f_cost >= key->f_cost) {
			if (a[i]->f_cost == key->f_cost && a[i]->h_cost <= key->h_cost) { 
				i--;
				continue;
			}
			a[i+1] = a[i];
			a[i--] = key;
		}
	}
}

int distance_check(int r, node_t R1, node_t R2)
{
	int distance1;
	int distance2;
	int distance;

	if(R1.i_pos == R2.i_pos)
	{
		if(R1.j_pos > R2.j_pos)
		{
			distance = R1.j_pos - R2.j_pos;
			if(distance > r)
			{
				return 1;
			}

			else 
			{
				return 0;
			}
		}

		else if(R2.j_pos > R1.j_pos)
		{
			distance = R2.j_pos - R1.j_pos;
			if(distance > r)
			{
				return 1;
			}

			else
			{
				return 0;
			}
		}

		else 
		{
			return 0;
		}

	}

	if(R1.i_pos > R2.i_pos)
	{
		distance1 = R1.i_pos - R2.i_pos;
		if(distance1 <= r)
		{
			if(R1.j_pos > R2.j_pos)
			{
				distance2 = R1.j_pos - R2.j_pos;
				if(distance2 > r)
				{
					return 1;
				}

				else
				{
					return 0;
				}

			}

			else if(R2.j_pos > R1.j_pos)
			{
				distance2 = R2.j_pos - R1.j_pos;
				if(distance2 > r)
				{
					return 1;
				}

				else
				{
					return 0;
				}
			}

			else
			{
				return 0;
			}
		}

		else
		{
			return 1;
		}       
	}

	if(R1.i_pos < R2.i_pos)
	{
		distance1 = R2.i_pos - R1.i_pos;
		if(distance1 <= r)
		{
			if(R1.j_pos > R2.j_pos)
			{
				distance2 = R1.j_pos - R2.j_pos;
				if(distance2 > r)
				{
					return 1;
				}

				else 
				{
					return 0;
				}
			}

			else if(R2.j_pos > R1.j_pos)
			{
				distance2 = R2.j_pos - R1.j_pos;
				if(distance2 > r)
				{
					return 1;
				}

				else 
				{
					return 0;
				}
			}

			else
			{
				return 0;
			}
		}
		else
		{
			return 1;
		}
	}

	return 0;

}

int find_index(node_t neighbour, heap_t open) {
	int m;
	for (m = 0; m < open.size; m++) {
		if (compare_node(open.A[m], neighbour))
			return m;
	}
	return m;
}

node_t** store_parents(node_t end, node_t start, maze_t* maze, visit_colors_t COLOR, int *size) {
	int i = 0;
	node_t* curr = &(maze->labyrinth[end.i_pos][end.j_pos]);
	while (!compare_node(*curr, start)) {
		i++;
		curr = curr->parent;
	}	
	curr = &(maze->labyrinth[end.i_pos][end.j_pos]);
	node_t** parents = malloc(sizeof(node_t*)*i);
	parents[0] = &(maze->labyrinth[end.i_pos][end.j_pos]);
	*size = i;
	while (!compare_node(*curr, start)) {
		maze->labyrinth[curr->i_pos][curr->j_pos].on_path = true;
		maze->labyrinth[curr->i_pos][curr->j_pos].visit = COLOR;
		parents[--i] = curr;
		curr = curr->parent;
	}
	return parents;
}

void get_neighbours(node_t** neighbours, maze_t maze, node_t curr) {
	if (curr.i_pos == 0)
		maze.labyrinth[curr.i_pos - 1][curr.j_pos].wall = true;
	neighbours[0] = &(maze.labyrinth[curr.i_pos - 1][curr.j_pos]);

	if (curr.i_pos == (maze.num_rows - 2))
		maze.labyrinth[curr.i_pos + 1][curr.j_pos].wall = true;
	neighbours[2] = &(maze.labyrinth[curr.i_pos + 1][curr.j_pos]);

	if (curr.j_pos == 0)
		maze.labyrinth[curr.i_pos][curr.j_pos - 1].wall = true;
	neighbours[3] = &(maze.labyrinth[curr.i_pos][curr.j_pos - 1]);

	if (curr.j_pos == (maze.num_cols - 2))
		maze.labyrinth[curr.i_pos][curr.j_pos + 1].wall = true;
	neighbours[1] = &(maze.labyrinth[curr.i_pos][curr.j_pos + 1]);	
}

void add_to_open(heap_t* open, node_t* new_node) {
	new_node->open = true;
	insert(open, *new_node);
}

node_t* remove_from_open(heap_t* open, maze_t* maze) {
	node_t node = extract_min(open);
	maze->labyrinth[node.i_pos][node.j_pos].open = false;
	return &(maze->labyrinth[node.i_pos][node.j_pos]);
}

node_t* add_to_closed(node_t* closed, node_t* new_node, int *size) {
	closed = realloc(closed, sizeof(node_t)*(*size + 1));
	new_node->closed = true;
	closed[*size] = *new_node;
	(*size)++;
	return closed;
}

bool compare_node(node_t one, node_t two) {
	if (one.i_pos == two.i_pos && one.j_pos == two.j_pos)
		return true;
	return false;
}

void set_target(node_t* target_node, robot_t bot) {
	memset(target_node, 0, sizeof(node_t));
	target_node->i_pos = bot.end_row;
	target_node->j_pos = bot.end_col;
}

void set_starting(node_t* starting_node, robot_t bot) {
	memset(starting_node, 0, sizeof(node_t));
	starting_node->i_pos = bot.start_row;
	starting_node->j_pos = bot.start_col;
}

int calc_cost(node_t curr, node_t target) {
	return abs(curr.i_pos - target.i_pos) + abs(curr.j_pos - target.j_pos);
}

void set_f_cost(node_t* curr, node_t start, node_t end) {
	curr->g_cost = calc_cost((*curr), start);
	curr->h_cost = calc_cost((*curr), end);
	curr->f_cost = curr->g_cost + curr->h_cost;
}

int calc_f_cost(node_t* curr, node_t start, node_t end) {
	int g_cost, h_cost, f_cost;
	g_cost = calc_cost((*curr), start);
	h_cost = calc_cost((*curr), end);
	f_cost = g_cost + h_cost;
	return f_cost;
}
