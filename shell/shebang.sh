#!/bin/bash
set -e
shebang=$(awk 'NR==1' ${0})
if [[ "${shebang:0:2}" == "#!" ]]; then
	echo ${shebang:2}
fi
