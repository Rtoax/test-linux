#!/bin/bash
files=( $(find -name abbreviation.md) )

for f in ${files[@]}
do
	# - Delete white lines
	# - Add filename suffix
	cat ${f} | \
		sed '/^$/d' | \
		sed "s|$| <${f}>|g"
done | sort | nl
