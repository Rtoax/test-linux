#!/bin/bash
# Copyright (c) 2025 Rong Tao
set -e

readonly prog=$0
readonly NOT_DEF=x

config_file_base=
config_file_cmp=

# ym: 'y' -> 'm'
readonly DISPLAYERS=( all diff missing ym )
display=diff
verbose=

name_len_max=0

__usage__()
{
	echo -e "
NAME
	${prog} - Compare linux kernel configs

SYNOPSIS
	${prog} -b=<base config> -c=<compared config>

DESCRIPTION
	-b, --base [CONFIG]    specify base config
	-c, --config [CONFIG]  specify compared config

	-d, --display [ITEM]   specify what to display, default: ${display}
	                       support: ${DISPLAYERS[@]}

	-h, --help             show help
	-v, --verbose          display verbose

EXAMPLES
	${prog} -b /boot/config-$(uname -r) -c /boot/config-$(uname -r) --display missing

SEE ALSO
	bash(1), etc.
"
	exit ${1-0}
}

TEMP_ARGS=$(getopt --options hvb:c:d: \
	--long base: \
	--long config: \
	--long display: \
	--long verbose \
	--long help \
	--name ${prog} -- "$@")
test $? != 0 && __usage__ 1

eval set -- "$TEMP_ARGS"

while true; do
	case $1 in
	-b | --base)
		shift
		config_file_base=$1
		shift
		;;
	-c | --config)
		shift
		config_file_cmp=$1
		shift
		;;
	-d | --display)
		shift
		display=$1
		if ! [[ " ${DISPLAYERS[@]} " =~ " ${display} " ]]; then
			echo >&2 "ERROR: display only support '${DISPLAYERS[@]}'"
			exit 1
		fi
		shift
		;;
	-h | --help)
		shift
		__usage__
		;;
	-v | --verbose)
		shift
		verbose=YES
		;;
	--)
		shift
		break
		;;
	*)
		echo >&2 "ERROR: unknown $1"
		exit 1
		;;
	esac
done

if [[ -z ${config_file_base} ]] || [[ -z ${config_file_cmp} ]]; then
	echo >&2 "ERROR: must specify config file"
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

	if [[ ${verbose} ]]; then
		echo >&2 "${name}=${val}"
	fi

	for file in ${config_file_cmp[@]}
	do
		cmp_config_line=$( grep ^"${name}=" ${file} || : )

		if [[ ${display} == missing ]] && [[ ${cmp_config_line##*=} ]]; then
			continue
		fi

		if [[ -z ${cmp_config_line##*=} ]]; then
			cmp_config_line="${name}=${NOT_DEF}"
		fi

		if [[ ${display} == ym ]] && [[ ${val}${cmp_config_line##*=} != ym ]]; then
			continue
		fi

		if [[ ${display} != all ]] && [[ ${val} == ${cmp_config_line##*=} ]]; then
			continue
		fi

		if [[ ${#name} -gt ${name_len_max} ]]; then
			name_len_max=${#name}
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
		color="\033[1;31m" # red
		reset="\033[m"
	elif [[ ${values[$i]} == ${values1[$i]} ]]; then
		color="\033[2m" # gray
		reset="\033[m"
	fi
	printf "${color}%-4d %-*.*s %-4s %-4s${reset}\n" \
		$i ${name_len_max} ${name_len_max} \
		${configs[$i]} ${values[$i]} ${values1[$i]}
done
