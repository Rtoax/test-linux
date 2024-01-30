#!/bin/bash

nr_jobs=100

rm -f tmp.sh
for ((i = 0; i < $nr_jobs; i++))
do
	cat >>tmp.sh<<-EOF
	echo "Hello $$"
	EOF
done

chmod +x ./tmp.sh

parallel -j $nr_jobs < ./tmp.sh
