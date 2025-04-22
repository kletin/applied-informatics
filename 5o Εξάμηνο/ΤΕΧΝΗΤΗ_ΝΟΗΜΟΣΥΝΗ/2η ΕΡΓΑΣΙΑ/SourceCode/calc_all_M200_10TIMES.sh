#!/bin/bash

TIMES=10  # No spaces around '='

echo "M/N , P(solutions)"

# Loop from 10 to 200, increasing by 10 each time
for ((i=10; i<=200; i+=10)); do
    FILE_PART1="M$i"

    # Count the number of matching files
    FILE_COUNT=$(ls -al ${FILE_PART1}_*.solution 2>/dev/null | wc -l)

    M_N_RATIO=$((i / 10))  # Integer division in Bash

    PERCENTAGE=$(awk "BEGIN {printf \"%.1f\", $FILE_COUNT / $TIMES}")

    echo "${M_N_RATIO} , ${PERCENTAGE}"
done
