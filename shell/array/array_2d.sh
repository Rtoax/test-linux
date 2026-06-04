#!/bin/bash
set -e

# skills[NAME]=( skill1 skill2 )
declare -A skills

# WARNING: not support
skills["Rong Tao"]+="basketball"
skills["Rong Tao"]+=" eat"
skills["Rong Tao"]+=" coding"

skills["Xue Yuehua"]+="learn"
skills["Xue Yuehua"]+=" eat"

echo "${!skills[@]}"
echo "${skills[@]}"

for name in "${!skills[@]}"
do
	printf "%-16s" "$name"
	for skill in ${skills[$name]}
	do
		printf " <%s>" ${skill}
	done
	echo
done
