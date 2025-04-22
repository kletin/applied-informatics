#!/bin/bash

# Loop from 200 to 10, decreasing by 10 each time
for ((i=200; i>=10; i-=10)); do
    ./modify.sh bcsp_generate.c $i
    echo "Compiling bcsp_generate$i.c"
    gcc -o bcsp_generate$i bscp_generate$i.c
    echo "Generating M$i""_1.._10"".txt"
    ./bcsp_generate$i M$i 1 10

    FILE_PART1="M$i"
    for ((t=1; t<=10; t+=1)); do
        echo running hill for "$FILE_PART1""_""$t"".txt"
        ./bscp hill "$FILE_PART1""_""$t"".txt" "$FILE_PART1""_""$t"".solution"
        echo "\n"
    done
done
