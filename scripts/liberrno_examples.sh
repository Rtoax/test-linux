#!/bin/bash
set -e

. liberrno.sh

for ((i=0;i<${NR_ERRNO};i++))
do
	echo -e "ERRNAMES[$i]=${ERRNAMES[$i]}"
done
