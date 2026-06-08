#!/bin/bash
# display the process number
set -e

while sleep 1; do
	num=( $(ps -e | wc -l)
	      $(ps -eo state | grep ^S | wc -l)
	      $(ps -eo state | grep ^R | wc -l)
	      $(ps -eo state | grep ^I | wc -l) )
	echo ${num[@]}
done | ../plotcake ${args[@]} --title 'Process Number' --xlabel 'Time' --ylabel 'Number' \
		-l All -l Sleep -l Run -l Idle ${@}
