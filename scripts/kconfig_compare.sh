#!/bin/bash
# Wrote by Rong Tao, 2025
set -e

readonly NOT_DEF=x

config_file_base=$1
config_file_cmp=$2

if [[ -z ${config_file_base} ]] || [[ -z ${config_file_cmp} ]]; then
	echo >&2 "Usage: $0 [configbase] [configcmp]"
	exit 1
fi

# ${str%%=*}: get config name
# ${str##*=}: get config value
config_line_base=( $(grep ^CONFIG ${config_file_base} | grep -E "[y|m]$" | sort) )

declare -a configs values values1


for config in ${config_line_base[@]}
do
	name=${config%%=*}
	val=${config##*=}

	for file in ${config_file_cmp[@]}
	do
		cmp_config_line=$( grep ^"${name}=" ${file} || : )
		[[ -z ${cmp_config_line} ]] && cmp_config_line="${name}=${NOT_DEF}"

		if [[ ${val} == ${cmp_config_line##*=} ]]; then
			continue
		fi

		configs+=( ${name} )
		values+=( ${val} )
		values1+=( ${cmp_config_line##*=} )

	done
done

for ((i = 0; i < ${#configs[@]}; i++))
do
	color=
	reset=
	if [[ ${values1[$i]} == ${NOT_DEF} ]]; then
		color="\033[1;31m"
		reset="\033[m"
	fi
	printf "${color}%-4d %-64s %-4s %-4s${reset}\n" \
		$i ${configs[$i]} ${values[$i]} ${values1[$i]}
done
