#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 100
#define MAX_COLS 100


int isRectangular(char maze[MAX_ROWS][MAX_COLS], int rows, int cols);
int validateMaze(char maze[MAX_ROWS][MAX_COLS], int rows, int cols);
void printMaze(char maze[MAX_ROWS][MAX_COLS], int rows, int cols, int showMap, int playerX, int playerY)
int movePlayer(char maze[MAX_ROWS][MAX_COLS], int *playerX, int *playerY, char direction)

int isRectangular(char maze[MAX_ROWS][MAX_COLS], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        if (strlen(maze[i]) != cols) {
            return 0;
        }
    }
    return 1;
}

// Function to validate the maze
int validateMaze(char maze[MAX_ROWS][MAX_COLS], int rows, int cols) {
    int startFound = 0, endFound = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (maze[i][j] == 'S') {
                if (startFound) return 0; // Multiple 'S' found
                startFound = 1;
            }
            if (maze[i][j] == 'E') {
                if (endFound) return 0; // Multiple 'E' found
                endFound = 1;
            }
            // Check for invalid characters
            if (maze[i][j] != ' ' && maze[i][j] != '#' && maze[i][j] != 'S' && maze[i][j] != 'E') {
                return 0;
            }
        }
    }
    return startFound && endFound; // Both 'S' and 'E' must be found
}

// Function to print the maze
void printMaze(char maze[MAX_ROWS][MAX_COLS], int rows, int cols, int showMap, int playerX, int playerY)

// Function to move the player
int movePlayer(char maze[MAX_ROWS][MAX_COLS], int *playerX, int *playerY, char direction) {
    switch (direction) {
        case 'W': case 'w': break;
        case 'A': case 'a': break;
        case 'S': case 's': break;
        case 'D': case 'd': break;
    }
}

int main(int argc, char *argv[]) {
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
    int rows = 0, cols = 0;
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
    }
    fclose(file);

    // Validate the maze
    if (rows < 5 || cols < 5 || rows > MAX_ROWS || cols > MAX_COLS ||
        !isRectangular(maze, rows, cols) || !validateMaze(maze, rows, cols)) {
        printf("Maze is invalid.\n");
        return 1;
    }
    // Print the valid maze
    printf("Maze is valid.\n");
}