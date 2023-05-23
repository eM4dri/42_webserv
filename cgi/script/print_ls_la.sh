#!/bin/bash

# Run the ls command and capture the output
output=$(ls)

# Print the output
echo "Content-Type: text/plain;"
echo ""
echo "ls -la $PWD"
echo "$output"
