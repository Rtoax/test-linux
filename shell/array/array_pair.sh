#!/bin/bash

pairs=(
util-linux	https://github.com/util-linux/util-linux.git
linux		https://github.com/torvalds/linux.git
)

for ((i = 0; i < ${#pairs[@]}; i+=2))
do
	printf "%-20s %s\n" ${pairs[$i]} ${pairs[$(expr $i + 1)]}
done

