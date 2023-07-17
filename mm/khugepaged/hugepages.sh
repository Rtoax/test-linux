#!/bin/bash

set -e

declare -a hugepage_dirs
declare -a nr_hugepages

hugepage_dirs=( $(ls /sys/kernel/mm/hugepages/) )

for p in ${hugepage_dirs[@]}
do
	nr_hugepages+=( $(cat /sys/kernel/mm/hugepages/$p/nr_hugepages) )
done

echo -e "    SIZE \tNUM"
for ((i = 0; i < ${#hugepage_dirs[@]}; i++))
do
	echo -e "    ${hugepage_dirs[$i]:10}\t${nr_hugepages[$i]}"
done

