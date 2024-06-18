#!/bin/bash

nr_jobs=10

[[ ! -e /usr/bin/parallel ]] && echo "WARNING: Not found parallel" && exit 0

rm -f tmp.sh
for ((i = 0; i < $nr_jobs; i++))
do
	cat >>tmp.sh<<-EOF
	echo "Hello $$"
	EOF
done

chmod +x ./tmp.sh

parallel -j $nr_jobs < ./tmp.sh
