#!/bin/bash
# Wrote by Rong Tao, 2025
set -e

readonly prog=$0
readonly NOT_DEF=x

config_file_base=
config_file_cmp=

verbose=

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

	-h, --help             show help
	-v, --verbose          display verbose

EXAMPLES
	${prog} -b /boot/config-$(uname -r) -c /boot/config-$(uname -r)

SEE ALSO
	bash(1), etc.
"
	exit ${1-0}
}

TEMP_ARGS=$(getopt --options hvb:c: \
	--long base: \
	--long config: \
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
