cc = gcc
CFLAGS = -g -Wall

all: maze_solver

maze_solver: maze.o robot.o parser.o main.o
	$(CC) $(CFLAGS) -o maze_solver maze.o robot.o parser.o main.o

maze.o: maze.c maze.h
	$(CC) $(CFLAGS) -c maze.c

robot.o: robot.c robot.h
	$(CC) $(CFLAGS) -c robot.c

parser.o: parser.c parser.h
	$(CC) $(CFLAGS) -c parser.c

main.o: main.c parser.h robot.h maze.h
	$(CC) $(CFLAGS) -c main.c

clean:
	$(RM) *.o maze_solver
