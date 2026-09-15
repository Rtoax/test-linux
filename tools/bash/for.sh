#!/bin/bash
set -e

for1() {
	for a; do
		echo $a
	done
}

for1 a b c

echo {1..3}

for ((i = 0, j = 0; i < 10; i++))
do
	if [[ $((i % 2)) -eq 1 ]]; then
		j=$(expr $j + 1)
	fi
	echo "i,j = ${i},${j}"
done
