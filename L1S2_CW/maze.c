// Skeleton Code
/*
// Struct to represent the Maze
typedef struct {
    char** grid; // 2D array to store maze characters
    int rows;
    int cols;
    int playerX
    int playerY
} Maze;

// Function prototypes
void loadMazeFromFile(const char* filename, Maze* maze);
void displayMaze(const Maze* maze);
void movePlayer(Maze* maze, char direction);
void startGame(Maze* maze);
bool isMoveValid(const Maze* maze, int newX, int newY);
void cleanUpMaze(Maze* maze);

// Main function outline
int main(int argc, char* argv[]) {
    // Check if command line argument is provided
    // Initialize the maze struct
    // Load maze from the file
    // Start game loop
    // Clean up resources
    // Return with appropriate exit code

    if (argc != 2) {
        printf("Usage: %s <maze_file.txt>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char maze[MAX_ROWS][MAX_COLS];
    int rows = 0, cols = 0, playerX = 1, playerY = 1;
    char line[MAX_COLS + 1];

    // Read the maze from file and find 'S' start position
    while (fgets(line, sizeof(line), file)) {
        // Remove newline character
        size_t len = strlen(line);
        if (line[len - 1] == '\n') {
            line[len - 1] = '\0';
            len--;
        }
        
        if (cols == 0) {
            cols = len;
        } else if (len != cols) { // Check if the maze is rectangular
            printf("Maze is not rectangular.\n");
            fclose(file);
            return 1;
        }
        
        strcpy(maze[rows], line);
        if (playerX == -1 && playerY == -1) { // Look for the 'S' start position
            char *startPos = strchr(line, 'S');
            if (startPos != NULL) {
                playerX = (int)(startPos - line);
                playerY = rows;
            }
        }
        rows++;
    }
    fclose(file);

    // Validate the maze
    if (rows < 5 || cols < 5 || rows > MAX_ROWS || cols > MAX_COLS ||
        !isRectangular(maze, rows, cols) || !validateMaze(maze, rows, cols)) {
        printf("Maze is invalid.\n");
        return 1;
    }
    // Load the maze from a file or initialize it here
    // Print the valid maze
    printf("Maze is valid.\n");
    
}

// Function to check if the maze is rectangular
int isRectangular(char maze[MAX_ROWS][MAX_COLS], int rows, int cols);
// Function to validate the maze
int validateMaze(char maze[MAX_ROWS][MAX_COLS], int rows, int cols);
// Function to print the maze
void printMaze(char maze[MAX_ROWS][MAX_COLS], int rows, int cols, int showMap, int playerX, int playerY)
// Function to move the player
int movePlayer(char maze[MAX_ROWS][MAX_COLS], int *playerX, int *playerY, char direction)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 100
#define MAX_COLS 100

typedef struct {
    char grid[MAX_ROWS][MAX_COLS]; // 2D array to store maze characters
    int rows;
    int cols;
} Maze;

// Function prototypes
int isRectangular(const Maze* maze);
int validateMazeStructure(const Maze* maze);
int loadMazeFromFile (const char* filename, Maze* maze);
void movePlayer(Maze* maze, char direction);
void startGame(Maze* maze);
void isMoveValid(const Maze* maze, int newX, int newY);
void cleanUpMaze(Maze* maze);


// Function to check if the maze is rectangular
int isRectangular(const Maze* maze) {
    for (int i = 0; i < maze->rows; i++) {
        if (strlen(maze->grid[i]) != maze->cols) {
            return 0;
        }
    }
    return 1;
}

// Function to validate the maze structure
int validateMazeStructure(const Maze* maze) {
    for (int i = 0; i < maze->rows; i++) {
        for (int j = 0; j < maze->cols; j++) {
            // Check for invalid characters, assuming valid characters are ' ', '#', 'S', 'E'
            if (maze->grid[i][j] != ' ' && maze->grid[i][j] != '#') {
                return 0;
            }
        }
    }
    return 1;
}

// Function to load maze from file
int loadMazeFromFile(const char* filename, Maze* maze) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char line[MAX_COLS + 1];
    maze->rows = 0;
    int cols = 0;

    while (fgets(line, sizeof(line), file)) {
        // Remove newline character
        size_t len = strlen(line);
        if (line[len - 1] == '\n') {
            line[len - 1] = '\0';
            len--;
        }

        // Set the number of columns if it's the first row
        if (cols == 0) {
            cols = len;
        } else if (len != cols) { // Check if the maze is rectangular
            printf("Maze is not rectangular.\n");
            fclose(file);
            return 1;
        }

        strcpy(maze->grid[maze->rows], line);
        maze->rows++;
    }
    maze->cols = cols; // Update maze cols after file read
    fclose(file);
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <maze_file.txt>\n", argv[0]);
        return 1;
    }

    Maze maze;

    if (loadMazeFromFile(argv[1], &maze)) {
        return 1; // Error loading maze
    }

    // Validate the maze's structure
    if (maze.rows < 5 || maze.cols < 5 || maze.rows > MAX_ROWS || maze.cols > MAX_COLS ||
        !isRectangular(&maze) || !validateMazeStructure(&maze)) {
        printf("Maze structure is invalid.\n");
        return 1;
    }

    // Maze structure is valid
    printf("Maze structure is valid.\n");
    return 0;
}
