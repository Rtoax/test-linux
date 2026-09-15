#!/bin/bash
set -e

max=1
get_next() {
	((max++))
}

__id_file=$(mktemp -u)
next_id() {
	local num=1
	if [[ -f ${__id_file} ]]; then
		num=$(cat ${__id_file})
	fi
	echo "id.${num}"
	echo $((++num)) > ${__id_file}
}

for i in {1..5}
do
	get_next
	echo $max
	echo $(next_id)
done

rm ${__id_file}
