#!/bin/bash
set -e

file="CLONE_.h"

clones=( $(grep -ow CLONE_[A-Z]* /usr/include/linux/sched.h) )

for c in ${clones[@]}
do
	printf "#ifdef %s\n" ${c} >> ${file}
	printf "DEF_CLONE(%s);\n" ${c} >> ${file}
	printf "#endif\n" >> ${file}
done
