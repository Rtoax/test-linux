#!/bin/bash

declare -a arr

# This pipeline while will open new shell
echo -e "a\nb\nc\nd\n" | while read v
do
	echo $v
	arr+=( "$v" )
done

while read v
do
	echo $v
	arr+=( "$v" )
done <<< $(echo -e "a\nb\nc\nd\n")

while read v
do
	echo $v
	arr+=( "$v" )
done <<< "a b c d"

for i in $(seq 1 1 4)
do
	echo $i
	arr+=( "$i" )
done

echo ${arr[@]}
