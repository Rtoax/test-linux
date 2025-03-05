#!/bin/bash
set -e

LD=${LD}
PIE=

while true; do
	case $1 in
	pie | PIE)
		shift
		PIE=YES
		;;
	*)
		break
		;;
	esac
done

[[ -z ${LD} ]] && LD=ld

temp_file=$(mktemp -u tmp-lds-XXXXXX)

${LD} --verbose ${PIE:+--pic-executable} > ${temp_file}

# Seek two "======" line numbers
start_end=( $(sed -n '/=====/=' ${temp_file}) )

# Get start and end line number, 1 for strip '========='
start=$(( ${start_end[0]} + 1 ))
end=$(( ${start_end[1]} - 1 ))

# Print
sed -n "${start}, ${end}p" ${temp_file} > default.lds

rm -f ${temp_file}
