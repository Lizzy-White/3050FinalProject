# 3050FinalProject
Maze Solver

## Team Members
Andrea McGovern
Lizzy White
Alex Wilhelm

## Building
Type 'make' to build to project.
Run the following command, where <input_file> is the name of the file containing the maze and <r> is an integer.
./maze_solver <input_file> <r>

## Expected Output
For the R = 0 Case:
	The maze will print at every iteration of the algorithm, creating some animation.  If this gets annoying or doesn't look right on your computer, you can comment out search.c:85 to stop this. At the end of the algorithm, two mazes are printed.  The first shows the first robot's path.  Dark blue corresponds to the final path chosen, light blue are other traversed nodes, and yellow are other nodes considered for traversal.  The second maze shows the second robot's path.  Similarly, this maze will be colored red for the final path, pink for other traversed nodes, and green for other considered nodes.  Finally, the vertices of the nodes on the path are printed for each robot.

For the R > 0 Case:
	No animation is printed for this, as it can take a long time for R > 2.  If you would like to turn this on, simply uncomment search.c:107.  Otherwise, this will print the ending maze, with the first robot's path in blue and the second in red. 

## Ideas
A* Algorithm for finding the shortest path. This is only implemented for the R = 0 case.
DFS exhaustive search to find a path to the end, taking into account the parameter R as an additional requirement for the recursive step.
