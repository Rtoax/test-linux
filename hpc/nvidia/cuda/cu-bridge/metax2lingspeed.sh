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
	sed -i 's/maca/luca/g' "$f"

	sed -i 's/mc_/lc_/g' "$f"

	sed -i 's/mxSml/lsSml/g' "$f"
	sed -i 's/mxsml/lssml/g' "$f"

	sed -i 's/mcrand/lcrand/g' "$f"
	sed -i 's/mcrtc/lcrtc/g' "$f"
	sed -i 's/mcruntime/lcruntime/g' "$f"
done
