CC = gcc
CFLAGS = -g -Wall 

all: maze_solver

maze_solver: maze.o robot.o parser.o heap.o search.o main.o
	$(CC) $(CFLAGS) -o maze_solver maze.o robot.o parser.o heap.o search.o main.o

maze.o: maze.c maze.h
	$(CC) $(CFLAGS) -c maze.c

robot.o: robot.c robot.h
	$(CC) $(CFLAGS) -c robot.c

parser.o: parser.c parser.h
	$(CC) $(CFLAGS) -c parser.c

heap.o: heap.c heap.h
	$(CC) $(CFLAGS) -c heap.c

search.o: search.c search.h
	$(CC) $(CFLAGS) -c search.c

main.o: main.c parser.h robot.h maze.h errors.h
	$(CC) $(CFLAGS) -c main.c

clean:
	$(RM) *.o maze_solver
