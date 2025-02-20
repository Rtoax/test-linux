#!/bin/bash

# Define the C code to execute
c_code='#include <stdio.h>
int main() {
	printf("Hello, World!\n");
	return 0;
}'

# Create a temporary file for the executable
temp_executable=$(mktemp -u /tmp/temp_executable.XXXXXX)

# Compile the C code and generate the executable
echo "$c_code" | gcc -xc - -o "$temp_executable"

# Check if the compilation was successful
if [ $? -eq 0 ]; then
	# Execute the compiled program
	"$temp_executable"
else
	echo "Compilation failed."
fi

# Clean up the temporary executable
rm -f "$temp_executable"
