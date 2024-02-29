# Test Script

# Test loading valid maze file
echo "Testing loading of a valid maze file..."
./maze valid_maze.txt
# Expected: Maze should load without errors

# Test loading invalid maze file
echo "Testing loading of an invalid maze file..."
./maze invalid_maze.txt
# Expected: Error message for invalid file

# Test moving player into a wall
echo "Testing player movement into a wall..."
# Expected: Error message for invalid move and no change in player position

# Test moving player to exit
echo "Testing player movement to exit..."
# Expected: Win message and game termination

# Test invalid command line arguments
echo "Testing invalid command line arguments..."
./maze
# Expected: Error message for missing maze file argument

# Test memory cleanup
echo "Testing memory cleanup after game ends..."
# Expected: No memory leaks or errors reported


#!/bin/bash
chmod u-x maze_10x10.txt

maze_file = ("maze_5x5.txt", "maze_15x15.txt", "maze_10x10.txt")

echo -e "~~ Validation Tests ~~"

echo -n "Test the maze file "
./maze maze_file > tmp
if grep -q "Maze matchs the width and height" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Testing player movement into a wall"
./maze > tmp
if grep -q "Error: player move into the wall" tmp
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Test bad user input"
./maze > tmp
if grep -q "Error: Input invalid key" tmp
then
    echo "PASS"
else
    echo "FAIL"
fi


# Test loading valid maze file
echo "Testing loading of a valid maze file (maze_5x5.txt, maze_15x15.txt, maze_10x10.txt)"
if ./maze valid_maze.txt; then
    echo "PASS: Valid maze loaded successfully."
else
    echo "FAIL: Valid maze failed to load."
fi

# Test loading invalid maze file
echo "Testing loading of an invalid maze file..."
if ./maze invalid_maze.txt; then
    echo "PASS: Invalid maze file correctly identified."
else
    echo "FAIL: Invalid maze file not handled correctly."
fi

# Test moving player into the wall


# Test invalid command line arguments
echo "Testing invalid command line arguments"
if ! ./maze; then
    echo "PASS: Error message for missing maze file argument displayed."
else
    echo "FAIL: No error message for missing maze file argument."
fi

echo "Note: Memory cleanup test is not included in this script."
