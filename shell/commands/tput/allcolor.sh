#!/bin/bash
set -e

colors=$(tput colors)

reset() {
	# Reset all attribute, or 'tput op'
	tput sgr0
}

for i in $(seq 0 1 $((${colors} - 1)))
do
	# set front
	tput setaf $i
	echo -n "This is front color of number $i."
	reset

	# set background
	tput setab $i
	echo -n " This is background color of number $i."
	reset

	echo
done
