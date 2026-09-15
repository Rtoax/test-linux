#!/bin/bash

declare -a orig del result after

orig=( a b c d e f g )
del=( b d f )

echo "ORIG: ${orig[@]}"
echo "DEL:  ${del[@]}"

result=("${orig[@]}")

for ele in "${del[@]}"; do
	result=(${result[@]/*${ele}*/})
done
after=( ${result[@]} )

echo "RSLT: ${after[@]}"

