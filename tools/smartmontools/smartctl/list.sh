#!/bin/bash
set -e

SSDs=( $(ls /dev/ | grep -E '[v|s]d[a-z]+') )
NVMes=( $(ls /dev/ | grep -Eo 'nvme[0-9]+' | sort -u) )

for name in ${SSDs[@]} ${NVMes[@]}
do
	sudo smartctl --all /dev/${name}
done
