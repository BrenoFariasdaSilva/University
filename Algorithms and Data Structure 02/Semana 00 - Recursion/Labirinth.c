#include <stdio.h>
#include <stdbool.h>

#define SIZE 10
#define PATH 2
#define START_I 0
#define START_J 0
#define END_I 9
#define END_J 9
#define DEAD_END 5
#define DOWN 1
#define RIGHT 2
#define UP 3
#define LEFT 4

typedef struct Movements
{
	int attemps;
	int position;
	int Memoization[SIZE * SIZE];
} Movements;

bool explorar (int Maze[SIZE][SIZE], int i, int j, Movements lastMovements);
bool isPathValid (int Maze[SIZE][SIZE], int i, int j);
int findPath (int Maze[SIZE][SIZE], int i, int j);
bool isEndPath (int i, int j);
void printVector (int Vector[SIZE][SIZE]);

int main ()
{
	int Vector[SIZE][SIZE] = {
	{0, 1, 1, 1, 0, 0, 1, 1, 1, 0},
	{0, 0, 1, 1, 1, 0, 1, 0, 1, 1},
	{0, 0, 1, 0, 0, 0, 1, 1, 1, 0},
	{0, 0, 0, 0, 1, 1, 0, 1, 0, 0},
	{0, 1, 0, 1, 0, 1, 1, 1, 0, 0},
	{0, 0, 0, 1, 0, 1, 0, 1, 0, 0},
	{0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
	{1, 1, 0, 0, 1, 0, 1, 0, 1, 0},
	{0, 1, 0, 0, 0, 0, 1, 0, 1, 0},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 0}};

	Movements lastMovements = {75, 0};

	if (explorar (Vector, START_I, START_J, lastMovements))
	{
		printf("Maze is complete! \n");
		printVector (Vector);
	}

	else
	{
		printf("This Maze has no solution");
	}

	return 0;
}

bool explorar (int Maze[SIZE][SIZE], int i, int j, Movements lastMovements)
{
	lastMovements.attemps--;

	if (isEndPath(i, j))
	{
		Maze[i][j] = PATH;
		return true;
	}

	if (lastMovements.attemps == 0)
		return false;

	int movement;
	// Backtracking of last movements, stored inside struct lastMovements.
	while ((movement = findPath (Maze, i, j)) == DEAD_END)
	{
		int previousMovement = lastMovements.Memoization[lastMovements.position--];
		Maze[i][j] = DEAD_END;

		if (previousMovement == DOWN)
			return (explorar (Maze, i - 1, j, lastMovements));

		if (previousMovement == RIGHT)
			return (explorar (Maze, i, j - 1, lastMovements));

		if (previousMovement == UP)
			return (explorar (Maze, i + 1, j, lastMovements));

		if (previousMovement == LEFT)
			return (explorar (Maze, i, j + 1, lastMovements));
	}

	int nextI = i, nextJ = j;
	lastMovements.Memoization[lastMovements.position++] = movement;
	if (movement == DOWN)
		nextI = i + 1;

	else if (movement == RIGHT)
		nextJ = j + 1;

	else if (movement == UP)
		nextI = i - 1;
		
	else if (movement == LEFT)
		nextJ = j - 1;

	Maze[i][j] = PATH;
	return (explorar (Maze, nextI, nextJ, lastMovements));
}

bool isPathValid (int Maze[SIZE][SIZE], int i, int j)
{
	return ((i >= 0 && j >= 0 && i <= END_I && j <= END_J) && Maze[i][j] == 0);
}

int findPath (int Maze[SIZE][SIZE], int i, int j)
{
	if (isPathValid (Maze, i + 1, j))
		return DOWN;

	if (isPathValid (Maze, i, j + 1))
		return RIGHT;

	if (isPathValid (Maze, i - 1, j))
		return UP;

	if (isPathValid (Maze, i, j - 1))
		return LEFT;
		
	return DEAD_END;
}

bool isEndPath (int i, int j)
{
	return (i == END_I && j == END_J);
}

void printVector (int Vector[SIZE][SIZE])
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (Vector[i][j] == DEAD_END)
			{
				printf("0 ");
			}
			else
			{
				printf("%d ", Vector[i][j]);
			}
		}
		printf("\n");
	}
	printf("\n");
}