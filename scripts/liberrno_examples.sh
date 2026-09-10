#!/bin/bash
set -e

. liberrno.sh

for ((i=0;i<${NR_ERRNO};i++))
do
	echo -e "${ERRNO[$i]}=$i"
done
