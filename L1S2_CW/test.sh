#!/bin/bash

chmod -r Data/bad_missing.txt

echo -e "~~ Bad user inputs ~~"

echo -n "Testing bad input(walls)-"
timeout 0.2s ./maze Data/good_data.txt > tmp
if grep -g "Error: Move into walls" tmp;
then
    echo "PASS"
else
    echo "FAIL".
fi

echo -n "Testing bad input(wrong key)-"
timeout 0.2s ./maze Data/good_ data.txt > tmp
if grep -q "Error: Invalid input" tmp;
then
    echo "PASS"
else
    echo "FAIL".   
fi

echo -n "Testing bad input(wrong filename)-"
timeout 0.2s ./maze Data/bad_mising.txt > tmp
if grep -q "Error: Cannot open the file" tmp;
then
    echo "PASS"
else
    echo "FAIL".   
fi

echo -e "~~ Common logic error ~~"

echo -n "Testing start point-"
timeout 0.2s ./maze Data/no_start.txt > tmp
if grep -q "Error: No starting point" tmp;
then
    echo "PASS"
else
    echo "FAIL".   
fi

echo -n "Testing end point-"
timeout 0.2s ./maze Data/end.txt > tmp
if grep -q "Error: No ending point" tmp;
then
    echo "PASS"
else
    echo "FAIL".   
fi

echo -n "Testing start point-"
timeout 0.2s ./maze Data/multi_start.txt > tmp
if grep -q "Error: Multiple starting point" tmp;
then
    echo "PASS"
else
    echo "FAIL".   
fi

echo -n "Testing end point-"
timeout 0.2s ./maze Data/multi_end.txt > tmp
if grep -q "Error: Multiple ending point" tmp;
then
    echo "PASS"
else
    echo "FAIL".   
fi

echo -e "~~ System error ~~"

echo -n "Testing no solution-"
timeout 0.2s ./maze Data/no_solution.txt > tmp
if grep -q "Error: No solution" tmp;
then
    echo "PASS"
else
    echo "FAIL".   
fi

echo -n "Testing bad data (wrong dimension)-"
timeout 0.2s ./maze Data/bad_dimension.txt > tmp
if grep -q "Error: Dimension not matches" tmp;
then
    echo "PASS"
else
    echo "FAIL".   
fi


echo -n "Testing bad data (missing parts)-"
timeout 0.2s ./maze Data/bad_missing.txt > tmp
if grep -q "Error: Maze is imcomplete" tmp;
then
    echo "PASS"
else
    echo "FAIL".   
fi


chmod +r Data/bad_missing.txt

rm -f tmp