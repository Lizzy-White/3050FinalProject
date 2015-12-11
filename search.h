#ifndef H_SEARCH_H
#define H_SEARCH_H

#include "heap.h"
#include "maze.h"
#include "robot.h"
#include "errors.h"
#include "unistd.h"

/*
 * Prints the path of the starting node to the ending node.
 */
void print_parents(node_t*** parents, int* size);

/*
 * A* Algorithm for shortest path
 * Essentially a BFS utilizing a min-heap.
 * Grabs the neighbours and adds the viable ones to the open heap,
 * sorting on f_cost.
 * Determines the next appropriate neighbour to traverse to based on this f_cost.
 * Used only for the R = 0 case to get close to the shortest path.
 */
void a_star(maze_t* maze, node_t* starting_node, node_t* target_node, node_t** neighbours, node_t*** parents);

/*
 * Mallocs space and memsets to 0 a 4D array.  
 * Used to store the states of the DFS search on the maze.
 */
char**** init_visits(char**** visits, maze_t* maze);
void uninit_visits(char**** visits, maze_t* maze);
/*
 * Sets starting and target nodes to the appropriate positions of the maze
 * that contain the robots.
 */
void init_start_and_target_nodes(node_t* starting_node, node_t* target_node, robot_t* bots);

/*
 * Insertion sort on the neighbours in order of f_cost then h_cost
 */
void insertion_sort(node_t** a);

/*
 * Verifies that R1 and R2 are within a vertical + horizontal distance of r
 * apart.  Returns 0 if not, 1 if true.
 */
int distance_check(int r, node_t R1, node_t R2);

/*
 * Starts with the ending node, and traverses through the parents of each node,
 * storing them into the parents array to be printed later.
 */
node_t** store_parents(node_t end, node_t start, maze_t* maze, visit_colors_t COLOR, int* size);

/*
 * Determines the neighbours of node curr.  Goes clockwise, starting from 
 * the node directly above curr.  Marks the neighbour as a wall if unable
 * to be visited.
 */
void get_neighbours(node_t** neighbours, maze_t maze, node_t curr);

/*
 * Adds new_node to the open heap, setting new_node->open to true.
 */
void add_to_open(heap_t* open, node_t* new_node);

/*
 * Extracts and returns the min from the open heap, setting its open member
 * to false.
 */
node_t* remove_from_open(heap_t* open, maze_t* maze);

/*
 * Adds new_node to the closed heap, incrementing the size of the heap.  
 * Sets new_node->closed to true.
 */
node_t* add_to_closed(node_t* closed, node_t* new_node, int *size);

/*
 * Returns true if nodes one and two are at the same i, j position of
 * the maze.  Returns false if not.
 */
bool compare_node(node_t one, node_t two);

/*
 * Sets the target_node to the appropriate maze positions based on the
 * location of bot.
 */
void set_target(node_t* target, robot_t bot);

/*
 * Sets the starting_node to the appropriate maze positions based on the
 * location of bot.
 */
void set_starting(node_t* starting_node, robot_t bot);

/*
 * Calculates the sum of the horizontal and vertical distance
 * between curr and target.
 */
int calc_cost(node_t curr, node_t target);

/*
 * Calculates and sets the g_cost, h_cost, and f_cost of curr.
 * g_cost is the cost from curr to the starting node.
 * h_cost is the cost from curr to the target node.
 * f_cost is the sume of g_cost and h_cost.
 */
void set_f_cost(node_t* curr, node_t start, node_t end);

/*
 * Calculates the f_cost to determine if it needs to be changed.
 */
int calc_f_cost(node_t* curr, node_t start, node_t end); 

/*
 * Finds the index that neighbour is located at in the heap.
 */
int find_index(node_t neighbour, heap_t); 

/*
 * Modified DFS on the maze graph.
 * Grabs the neighbours of each robot.
 * Sorts the neighbours on f_cost then h_cost.  
 * Goes through each neighbour to determine if the robot can move there,
 * checking that the parameter R is not violated.
 * If yes, recursively call DFS, using this neighbour as the robot's next position.
 * Continue until both robots have reached their target locations.
 */
int DFS(node_t R1, node_t R2, maze_t* maze, int r, node_t* start, node_t* target, int* done, char**** visits);

#endif
