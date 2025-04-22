#!/bin/bash

SOLUTION_DIR="./"  # Change if needed

echo "M/N, avg time depth (μs), avg time hill (μs)"

# Temporary files to store grouped values
DEPTH_FILE=$(mktemp)
HILL_FILE=$(mktemp)
FINAL_OUTPUT=$(mktemp)

# Find and sort files correctly using natural numerical sorting
find "$SOLUTION_DIR" -type f -name "M*_*.solution" | sort -V | while read -r SOLUTION_FILE; do
    FILE_NAME=$(basename "$SOLUTION_FILE")
    M_VALUE=$(echo "$FILE_NAME" | awk -F'[_]' '{print substr($1,2)}')
    X_VALUE=$(echo "$FILE_NAME" | awk -F'[_]' '{print $2}' | cut -d'.' -f1)

    INPUT_FILE="M${M_VALUE}_${X_VALUE}.txt"

    # Get depth time
    TIME_SPENT1=$(./bscp depth "$INPUT_FILE" "$SOLUTION_FILE" 2>/dev/null | grep "Time spent:" | awk '{print $3}')
    TIME_SPENT1_US=$(awk "BEGIN {printf \"%.0f\", $TIME_SPENT1 * 1000000}")

    # Get hill time (average over 5 runs)
    SUM_TIME=0.0
    ITERATIONS=5

    for ((j=1; j<=ITERATIONS; j+=1)); do
        CURRENT_TIME=$(./bscp hill "$INPUT_FILE" "$SOLUTION_FILE" 2>/dev/null | grep "Time spent:" | awk '{print $3}')
        if [[ -n "$CURRENT_TIME" ]]; then
            SUM_TIME=$(awk "BEGIN {print $SUM_TIME + $CURRENT_TIME}")
        fi
    done

    TIME_SPENT2=$(awk "BEGIN {printf \"%.6f\", $SUM_TIME / $ITERATIONS}")
    TIME_SPENT2_US=$(awk "BEGIN {printf \"%.0f\", $TIME_SPENT2 * 1000000}")

    # Store data in temp files
    echo "$M_VALUE $TIME_SPENT1_US" >> "$DEPTH_FILE"
    echo "$M_VALUE $TIME_SPENT2_US" >> "$HILL_FILE"
done

# Compute and store averages in final output
for M in $(awk '{print $1}' "$DEPTH_FILE" | sort -nu); do
    AVG_DEPTH=$(awk -v m="$M" '$1 == m {sum+=$2; count++} END {if (count > 0) printf "%.0f", sum/count}' "$DEPTH_FILE")
    AVG_HILL=$(awk -v m="$M" '$1 == m {sum+=$2; count++} END {if (count > 0) printf "%.0f", sum/count}' "$HILL_FILE")
    echo "$M, $AVG_DEPTH, $AVG_HILL" >> "$FINAL_OUTPUT"
done

# Sort the final output numerically and print
sort -n "$FINAL_OUTPUT"

# Clean up temp files
rm "$DEPTH_FILE" "$HILL_FILE" "$FINAL_OUTPUT"
