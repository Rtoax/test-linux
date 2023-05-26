#!/bin/bash

features=(avx avx2)

# $1 - feature name
check_support()
{
	local feature=$1
	local support=$(lscpu | grep -o " $feature ")
	local feature=$(echo $feature | tr [:lower:] [:upper:])

	if [[ ! -z $support ]]; then
		echo "Support $feature"
	else
		echo "Unsupport $feature"
	fi
}

for f in ${features[@]}
do
	check_support $f
done
