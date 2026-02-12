#!/bin/bash
set -e

for i in $(seq 0 1 255)
do
	# set front
	tput setaf $i
	echo -n "This is front color of number $i."
	# Reset all attribute
	tput sgr0

	# set background
	tput setab $i
	echo -n " This is background color of number $i."
	# Reset all attribute
	tput sgr0

	echo
done
