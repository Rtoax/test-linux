#!/bin/bash
set -e

my_array=("apple" "banana" "cherry" "date")
new_separator="|"
old_IFS=$IFS
IFS=$new_separator
# apple|banana|cherry|date
echo "${my_array[*]}"
# apple banana cherry date
echo "${my_array[@]}"
IFS=$old_IFS
