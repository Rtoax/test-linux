#!/bin/bash

strs=(
	1234
	abcd
	12cd
)

for s in ${strs[@]}
do
	if [[ $s =~ ^-?[0-9]+$ ]]; then
		echo "$s is num"
	fi
done
