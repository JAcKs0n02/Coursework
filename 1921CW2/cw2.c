#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 100
#define MAX_COLS 100


// Function to check if the maze is rectangular
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
void printMaze(char maze[MAX_ROWS][MAX_COLS], int rows, int cols, int showMap, int playerX, int playerY) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (showMap && i == playerY && j == playerX) {
                printf("X");
            } else {
                printf("%c", maze[i][j]);
            }
        }
        printf("\n");
    }
}

// Function to move the player
int movePlayer(char maze[MAX_ROWS][MAX_COLS], int *playerX, int *playerY, char direction, int cols, int rows) {
    int newX = *playerX;
    int newY = *playerY;

    switch (direction) {
        case 'W': case 'w': newY--; break;
        case 'A': case 'a': newX--; break;
        case 'S': case 's': newY++; break;
        case 'D': case 'd': newX++; break;
    }

    // Check if new position is valid
    if (newX < 0 || newY < 0 || newX >= cols || newY >= rows || maze[newY][newX] == '#') {
        printf("Cannot move there!\n");
        return 0;
    }

    // Check if the player has reached the exit
    if (maze[newY][newX] == 'E') {
        return 2;
    }

    *playerX = newX;
    *playerY = newY;
    return 1;
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <maze_file.txt>\n", argv[0]);
        return 1;
    }

    char maze[MAX_ROWS][MAX_COLS] = {0};
    int rows = 0, cols = 0, playerX = -1, playerY = -1;
    char line[MAX_COLS + 1];


    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    while (fgets(line, sizeof(line), file)) {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[--len] = '\0';
        }
        if (rows == 0) {
            cols = len;
        } else if (len != cols) {
            printf("Maze is not rectangular.\n");
            fclose(file);
            return 1;
        }

        strcpy(maze[rows], line);
        if (playerX == -1 && playerY == -1) { // Find the start position
            char *startPos = strchr(line, 'S');
            if (startPos != NULL) {
                playerY = rows;
                playerX = startPos - line;
            }
        }
        rows++;
        if (rows >= MAX_ROWS) {
            printf("Exceeded maximum number of rows.\n");
            fclose(file);
            return 1;
        }
    }
    fclose(file);

    if (!isRectangular(maze, rows, cols) || !validateMaze(maze, rows, cols)) {
        return 1;
    }
    
    int showMap = 0;
    printMaze(maze, rows, cols, showMap, playerX, playerY);

    char input;
    int gameRunning = 1;
    while (gameRunning) {
        printf("Enter move (WASD) or 'Q' to quit: ");
        scanf(" %c", &input); // Note the space before %c to eat any leftover newline characters

        if (input == 'Q' || input == 'q') {
            gameRunning = 0;
            continue;
        }

        int moveResult = movePlayer(maze, &playerX, &playerY, input, cols, rows);

        if (moveResult == 2) {
            printf("Congratulations! You've found the exit!\n");
            gameRunning = 0;
        }

        printMaze(maze, rows, cols, showMap, playerX, playerY);
    }

    printf("Game over.\n");
    return 0;
}