#!/bin/bash

# Check if the correct number of arguments is provided
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <INPUT_FILE> <NEW_M_VALUE>"
    exit 1
fi

# Assign command-line arguments to variables
INPUT_FILE="$1"
NEW_M_VALUE="$2"

OUTPUT_FILE="bscp_generate$NEW_M_VALUE.c"

# Check if the input file exists
if [ ! -f "$INPUT_FILE" ]; then
    echo "Error: Input file '$INPUT_FILE' not found!"
    exit 1
fi

# Use sed to find and replace the value of M dynamically
sed -E "s/(#define M )[0-9]+/\1$NEW_M_VALUE/" "$INPUT_FILE" > "$OUTPUT_FILE"

# Print success message
echo "Modified file saved as '$OUTPUT_FILE' with M = $NEW_M_VALUE"
