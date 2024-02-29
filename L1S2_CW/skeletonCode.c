#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 100
#define MAX_COLS 100

// Define a struct for the Maze
typedef struct {
    char grid[MAX_ROWS][MAX_COLS];
    int rows, cols;
} Maze;

// Define a struct for the Player
typedef struct {
    int x, y; // Player's position
    char direction; // Last movement direction
} Player;

// Function prototypes
int isRectangular(Maze *maze);
int validateMaze(Maze *maze);
void printMaze(Maze *maze, Player *player, int showMap);
int movePlayer(Maze *maze, Player *player, char direction);
