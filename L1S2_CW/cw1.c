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
void printMaze(char maze[MAX_ROWS][MAX_COLS], int rows, int cols, int showMap, int playerX, int playerY) {
    system("clear"); // Clears the screen. Use system("cls"); on Windows.

    for (int y = 0; y < cols; y++) {
        for (int x = 0; x < rows; x++) {
            if (showMap && x == playerX && y == playerY) {
                printf("X");
            } else {
                printf("%c", maze[y][x]);
            }
        }
        printf("\n");
    }
}

// Function to move the player
int movePlayer(char maze[MAX_ROWS][MAX_COLS], int *playerX, int *playerY, char direction) {
    int newX = *playerX;
    int newY = *playerY;

    switch (direction) {
        case 'W': case 'w': newY--; break;
        case 'A': case 'a': newX--; break;
        case 'S': case 's': newY++; break;
        case 'D': case 'd': newX++; break;
    }

    // Check if new position is valid
    if (newX < 0 || newY < 0 || maze[newY][newX] == '#' || maze[newY][newX] == '\0') {
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
    
    for (int i = 0; i < rows; i++) {
        printf("%s\n", maze[i]);
    }



    // Game loop here...
    char input;
    int gameRunning = 1;
    int showMap = 0;

    printMaze(maze, rows, cols, showMap, playerX, playerY);


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

        int moveResult = movePlayer(maze, &playerX, &playerY, input);

        if (moveResult == 2) {
            printf("Congratulations! You've found the exit!\n");
            break;
        }

        printMaze(maze, rows, cols, showMap, playerX, playerY);
    }

    printf("Game over.\n");

    return 0;
}


/*
    // Print the valid maze
    printMaze(maze, rows, cols, playerX, playerY);

    // Game loop here...
    // The game loop logic remains the same as provided
    char maze[MAX_ROWS][MAX_COLS];
    int rows = 0, cols = 0, playerX = 0, playerY = 0;

    // Load the maze from a file or initialize it here
    // Print the valid maze
    for (int i = 0; i < rows; i++) {
        printf("%s\n", maze[i]);
    }

    int rows = 10;
    int cols = 5;
    int playerX = 1; // Assuming the starting point 'S' is at (1, 1)
    int playerY = 1;

    // Copying the static maze into our maze variable
    for (int y = 0; y < cols; y++) {
        for (int x = 0; x < rows; x++) {
            maze[y][x] = tempMaze[y][x];
        }
    }

    char input;
    int gameRunning = 1;
    int showMap = 0;

    printMaze(maze, rows, cols, showMap, playerX, playerY);


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

        int moveResult = movePlayer(maze, &playerX, &playerY, input);

        if (moveResult == 2) {
            printf("Congratulations! You've found the exit!\n");
            break;
        }

        printMaze(maze, rows, cols, showMap, playerX, playerY);
    }

    printf("Game over.\n");

    return 0;
}

// Definitions of other functions (isRectangular, validateMaze, printMaze, movePlayer) remain unchanged


int checkMaze(int argc, char *argv[]) {
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
    while (fgets(maze[rows], MAX_ROWS, file) && rows < MAX_ROWS) {
        maze[rows][strcspn(maze[rows], "\n")] = 0; // Remove newline character
        if (rows == 0) {
            cols = strlen(maze[0]);
        }
        rows++;
    }
    fclose(file);

    if (rows < 5 || cols < 5 || rows > MAX_ROWS || cols > MAX_COLS) {
        printf("Maze dimensions are invalid.\n");
        return 1;
    }

    if (!isRectangular(maze, rows, cols)) {
        printf("Maze is not rectangular.\n");
        return 1;
    }

    if (!validateMaze(maze, rows, cols)) {
        printf("Maze validation failed.\n");
        return 1;
    }

    printf("Maze is valid.\n");
    return 0;

}

int main() {
    char maze[MAX_ROWS][MAX_COLS];
    int rows = 0, cols = 0, playerX = 0, playerY = 0;

    // Load the maze from a file or initialize it here
    // Print the valid maze
    for (int i = 0; i < rows; i++) {
        printf("%s\n", maze[i]);
    }

    int rows = 10;
    int cols = 5;
    int playerX = 1; // Assuming the starting point 'S' is at (1, 1)
    int playerY = 1;

    // Copying the static maze into our maze variable
    for (int y = 0; y < cols; y++) {
        for (int x = 0; x < rows; x++) {
            maze[y][x] = tempMaze[y][x];
        }
    }

    char input;
    int gameRunning = 1;
    int showMap = 0;

    printMaze(maze, rows, cols, showMap, playerX, playerY);


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

        int moveResult = movePlayer(maze, &playerX, &playerY, input);

        if (moveResult == 2) {
            printf("Congratulations! You've found the exit!\n");
            break;
        }

        printMaze(maze, rows, cols, showMap, playerX, playerY);
    }

    printf("Game over.\n");
    return 0;
}
*/