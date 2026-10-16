#!/bin/bash
set -e

readonly CDATs=( $(sudo find /sys/ -name CDAT || true) )

for cdat in ${CDATs[@]}
do
	echo -e "\033[1;32m${cdat}\033[m"
	sudo ./cdat ${cdat}
done
