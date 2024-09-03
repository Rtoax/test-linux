#!/bin/bash

func_2nd()
{
	local i=0
	for p; do
		i=$(($i + 1))
		echo $i : $p
	done

	echo "func_2nd: $@"
	echo "func_2nd: $*"
}

for_each_args()
{
	local i=0
	for p; do
		i=$(($i + 1))
		echo $i : $p
	done
	func_2nd "$@"
}

for_each_args 1 2 3 a b c

for_each_args "1 2" "3 4" 5 6
