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

// Main function to load and validate maze, then start the game
int main(int argc, char *argv[]) {
    // Your existing file reading and validation code here
    // ...

    // Assume validation is successful, and we proceed to the game
    int playerX = 1; // Starting X position
    int playerY = 1; // Starting Y position
    int showMap = 0; // Initially not showing the full map

    // Initialize the maze (if loading from a file, this would be done differently)
    char maze[MAX_ROWS][MAX_COLS] = {
        "###########",
        "#S  #    E#",
        "# #######  ",
        "#         #",
        "###########"
    };
    int rows = 5; // Number of rows in the maze
    int cols = 10; // Number of columns in the maze

    // Print the initial maze
    printMaze(maze, rows, cols, showMap, playerX, playerY);

    // Game loop
    char input;
    int gameRunning = 1;
    while (gameRunning) {
        printf("Enter move (WASD) or 'M' to show map, 'Q' to quit: ");
        scanf(" %c", &input); // Note the space before %c to eat any leftover newline characters

        if (input == 'M' || input == 'm') {
            showMap = !showMap;
            printMaze(maze, rows, cols, showMap, playerX, playerY);
            continue;
        }

        if (input == 'Q' || input == 'q') {
            gameRunning = 0;
            continue;
        }

        int moveResult = movePlayer(maze, &playerX, &playerY, input, cols, rows);

        if (moveResult == 2) {
            printf("Congratulations! You've found the exit!\n");
            gameRunning = 0;
            continue;
        } else if (moveResult == 1) {
            printMaze(maze, rows, cols, showMap, playerX, playerY);
        }
    }

    printf("Game over.\n");
    return 0;
}
