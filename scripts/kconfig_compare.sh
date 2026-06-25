#!/bin/bash
# Compare linux kernel config file
#
# Copyright (C) 2025-2026 Rong Tao
#
set -e

readonly KCFGCMP_ROOT=$(dirname $(realpath $0))
readonly prog=$0
readonly NOT_DEF=-

config_file_base=
config_file_cmp=

# ym: 'y' -> 'm'
readonly DISPLAYERS=( all diff missing ym extra )
display=diff
verbose=

name_len_max=0

. ${KCFGCMP_ROOT}/liblog.sh

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
	                        diff: base and config is different
	                        ym: base=y, config=m
	                        missing: base=<y|m>, config=
				extra: base=, config=<y|m>

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
		if [[ ! -z ${config_file_cmp} ]] && \
		   [[ ${1} != ${config_file_cmp} ]]; then
			error "already set config to ${config_file_cmp}, duplicate ${1}"
		fi
		config_file_cmp=$1
		shift
		;;
	-d | --display)
		shift
		display=$1
		if ! [[ " ${DISPLAYERS[@]} " =~ " ${display} " ]]; then
			error "display only support '${DISPLAYERS[@]}'"
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
		DEBUG=YES
		;;
	--)
		shift
		break
		;;
	*)
		error "unknown $1"
		;;
	esac
done

if [[ -z ${config_file_base} ]] || [[ -z ${config_file_cmp} ]]; then
	error "must specify config file"
fi

# ${str%%=*}: get config name
# ${str##*=}: get config value
config_line_base=( $(grep ^CONFIG ${config_file_base} | grep -E "[y|m]$" | sort) )
config_line_cmp=( $(grep ^CONFIG ${config_file_cmp} | grep -E "[y|m]$" | sort) )

declare -a configs values values1

# Iterate all base configs
get_diff()
{
	local config
	for config in ${config_line_base[@]}
	do
		local name=${config%%=*}
		local val=${config##*=}

		if [[ ${verbose} ]]; then
			debug "${name}=${val}"
		fi

		local match_config=$( grep ^"${name}=" ${config_file_cmp} || : )

		if [[ ${display} == missing ]] &&
		   [[ ${match_config##*=} ]]; then
			continue
		fi

		# Not found config in config 2, set it to undefined
		if [[ -z ${match_config##*=} ]]; then
			match_config="${name}=${NOT_DEF}"
		fi

		if [[ ${display} == ym ]] &&
		   [[ ${val}${match_config##*=} != ym ]]; then
			continue
		fi

		if [[ ${display} != all ]] &&
		   [[ ${val} == ${match_config##*=} ]]; then
			continue
		fi

		if [[ ${#name} -gt ${name_len_max} ]]; then
			name_len_max=${#name}
		fi

		configs+=( ${name} )
		values+=( ${val} )
		values1+=( ${match_config##*=} )
	done
}

# In config2, but no in base config
get_extra()
{
	local config
	for config in ${config_line_cmp[@]}
	do
		local name=${config%%=*}
		local val=${config##*=}

		if [[ ${verbose} ]]; then
			debug "${name}=${val}"
		fi

		local match_config=$( grep ^"${name}=" ${config_file_base} || : )

		# Skipping matched config, because it's already handled above.
		if [[ ${match_config} ]]; then
			continue
		fi

		if [[ ${#name} -gt ${name_len_max} ]]; then
			name_len_max=${#name}
		fi

		configs+=( ${name} )
		values+=( ${NOT_DEF} )
		values1+=( ${val} )
	done
}

if [[ ${display} == extra ]]; then
	get_extra
else
	get_diff
fi

for ((i = 0; i < ${#configs[@]}; i++))
do
	color=
	reset=

	# Missing
	if [[ ${values1[$i]} == ${NOT_DEF} ]]; then
		color="\033[1;31m" # bold and red
		reset="\033[m"
	# Same
	elif [[ ${values[$i]} == ${values1[$i]} ]]; then
		color="\033[2m" # gray
		reset="\033[m"
	# Only in config2
	elif [[ ${values[$i]} == ${NOT_DEF} ]]; then
		color="\033[32m" # green
		reset="\033[m"
	fi
	printf "${color}%-4d %-*.*s %-4s %-4s${reset}\n" \
		$i ${name_len_max} ${name_len_max} \
		${configs[$i]} ${values[$i]} ${values1[$i]}
done
