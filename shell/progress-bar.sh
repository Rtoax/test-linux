#!/bin/bash

max_length=50

progress_bar()
{
	local i=$1
	local len=`expr ${#i} + 5 `

	echo -n "$i % ["
	for ((j = 0; j < $i; j++))
	do
		printf "#"
	done
	for ((j = $i; j < ${max_length}; j++))
	do
		printf " "
	done
	printf "]"
	sleep 0.1

	for ((j = 0; j < `expr ${max_length} + $len`; j++))
	do
		printf "\b"
	done
}

for ((i = 0; i < ${max_length}; i++))
do
	progress_bar $i
done
