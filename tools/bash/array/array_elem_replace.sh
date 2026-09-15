#!/bin/bash

arr=( a b b1 c)
echo ${arr[@]}

replace_from=( a b c )
replace_to=( A B C )

if [[ ${#replace_from[@]} != ${#replace_to[@]} ]]; then
	echo "ERROR: Number of From != To"
	exit 1
fi

for ((i = 0; i < ${#arr[@]}; i++ ))
do
	for ((j = 0; j < ${#replace_from[@]}; j++))
	do
		if [[ ${arr[$i]} == ${replace_from[$j]} ]]; then
			arr[$i]=${replace_to[$j]}
		fi
	done
done

echo ${arr[@]}
