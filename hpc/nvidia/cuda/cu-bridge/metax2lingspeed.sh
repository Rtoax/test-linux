#!/bin/bash
# Replace all api from MetaX to LUCA
# source code in https://gitee.com/metax-maca/cu-bridge
set -e

for f in $(find -type f)
do
	if [[ ! -e $f ]] || [[ ! -f $f ]] || [[ -d ${f} ]]; then
		echo "skip ${f}"
		continue
	fi
	if [[ "$(echo $f | grep -wo docs)" ]]; then
		echo "skip doc file ${f}"
		continue
	fi
	sed -i 's/MACA/LUCA/g' "$f"
done
