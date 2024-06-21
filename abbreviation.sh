#!/bin/bash
files=( $(find -name abbreviation.md) )

for f in ${files[@]}
do
	# - Delete white lines
	# - Add filename suffix
	cat ${f} | \
		sed '/^$/d' | \
		sed "s|$| <$(dirname ${f})>|g"
done | sort | nl
