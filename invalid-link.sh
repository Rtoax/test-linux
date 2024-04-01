#!/bin/bash
set -e

links=( $(find -path ".git" -a -prune -o -type l -exec echo {} +) )
for f in ${links[@]}
do
	real_f=$(realpath $f 2>/dev/null || true)
	if [[ ! -f $real_f ]] && [[ ! -d $real_f ]]; then
		echo "Invalid-link: $f"
	fi
done
