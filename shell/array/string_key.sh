#!/bin/bash
set -e
declare -A scores

scores["Alice"]=95
scores["Bob"]=88
scores["Charlie"]=92
scores["Mary Ann"]=89

for name in "${!scores[@]}"; do
	echo "NAME: $name, SCORE: ${scores[$name]}"
done
