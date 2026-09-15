#!/bin/bash
set -e

declare -A arr_key2d

for i in {1..3}
do
	for j in {1..3}
	do
		arr_key2d["${i},${j}"]="$i,$j"
	done
done

for i in {1..3}
do
	for j in {1..3}
	do
		printf "arr_key2d[%d,%d] = %s\n" $i $j ${arr_key2d["${i},${j}"]}
	done
done
