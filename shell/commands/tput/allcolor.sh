#!/bin/bash
set -e

for i in $(seq 0 1 256)
do
	tput setaf $i
	echo "This is color of number $i."
	tput sgr0
done
