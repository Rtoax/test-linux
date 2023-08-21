#!/bin/bash

progress_bar()
{
	i=$1
	len=`expr ${#i} + 5 `

	echo -n "$i % ["
	for ((j = 0; j < $i; j++))
	do
		printf "#"
	done
	for ((j = $i; j < 100; j++))
	do
		printf " "
	done
	printf "]"
	sleep 0.1

	for ((j = 0; j < `expr 100 + $len`; j++))
	do
		printf "\b"
	done
}

for ((i = 0; i < 100; i++))
do
	progress_bar $i
done
