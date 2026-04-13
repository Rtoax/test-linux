#!/bin/bash
set -e

declare -A arr2d

for i in {1..3}
do
	for j in {1..3}
	do
		arr2d["${i},${j}"]="$i,$j"
	done
done

for i in {1..3}
do
	for j in {1..3}
	do
		printf "arr2d[%d,%d] = %s\n" $i $j ${arr2d["${i},${j}"]}
	done
done
