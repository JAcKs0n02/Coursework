#/usr/bin/bash

# test no input
function test_no_input()
{
    output=`./maze`
    if [ "$output"!="No maze file" ]; then
        echo "failure:test_no_input"
    else
        echo "success:test_no_input"
    fi
}

# test two input
function test_multi_input()
{
    output=`./maze "./test_data/valid.txt" "./test_data/valid.txt"`
    if ["$output"="Too many input parameter!" ]; then
        echo "failure:test_multi_input"
    else
        echo "success:test_multi_input"
    fi
}

# test input file not exist
function test_input_file_no_exist()
{
    output=`./maze "a.txt"`
    if [ "$output" != "Maze file not exist" ]; then
        echo "failure:test_input_file_no_exist"
    else 
        echo "success:test_input_file_no_exist"
    fi
}

# test col is not equal
function test_col_not_equal_each_row()
{
    output=`./maze "./test_data/Rows or columns are not equal.txt"`
    if [ "$output" != "Col is not equal each row!" ]; then
        echo "failure:test_col_not_equal_each_row"
    else
        echo "success:test_col_not_equal_each_row"
    fi
}

# test multi start
function test_multi_start()
{
    output=`./maze "./test_data/Have two S.txt"`
    if [ "$output" != "Multi start point!" ]; then
        echo "failure:test_multi_start"
    else
        echo "success:test_multi_start"
    fi   
}

# test multi end
function test_multi_end()
{
    output=`./maze "./test_data/Have two E.txt"`
    if [ "$output" != "Multi end point!" ]; then
        echo "failure:test_multi_end"
    else
        echo "success:test_multi_end"
    fi   
}

# test no start
function test_no_start()
{
    output=`./maze "./test_data/No S.txt"`
    if [ "$output" != "No start point!" ]; then
        echo "failure:test_no_start"
    else
        echo "success:test_no_start"
    fi   
}

# test no end
function test_no_end()
{
    output=`./maze "./test_data/No E.txt"`
    if [ "$output" != "No end point!" ]; then
        echo "failure:test_no_end"
    else
        echo "success:test_no_end"
    fi   
}

# test illegal character
function test_illegal_maze()
{
    output=`./maze "./test_data/Illegal character exists.txt"`
    if [ "$output" != "Maze character illegal!" ]; then
        echo "failure:test_illegal_maze"
    else
        echo "success:test_illegal_maze"
    fi  
}

# test error maze size
function test_size_maze()
{
    output=`./maze "./test_data/More than 5 - 100 Range.txt"`
    if [ "$output" != "Maze size is not in [5,100]!" ]; then
        echo "failure:test_size_maze"
    else
        echo "success:test_size_maze"
    fi  
}

# all test case
test_no_input
test_multi_input
test_input_file_no_exist
test_col_not_equal_each_row
test_multi_start
test_multi_end
test_no_start
test_no_end
test_illegal_maze
test_size_maze
