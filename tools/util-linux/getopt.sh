#!/bin/bash
set -e

# return: -- '1.1.1'
getopt --options n:h --long name --long help -- -- 1.1.1
# return: '1.1.1' --
getopt --long name --long help -- -- 1.1.1

option_arg() {
	declare -a positional

	# -v[V]: could not have any spaces
	# --verbose[=V]: must use '='
	local OPTS=$(getopt --options v:: --long verbose:: -n option_arg -- "${@}")
	if [[ $? -ne 0 ]]; then
		echo >%2 "ERROR: getopt failed, \"${@}\""
		exit 1
	fi

	#echo >&2 "OPTS=${OPTS}"
	eval set -- "${OPTS}"
	while true; do
		case $1 in
		-v | --verbose)
			shift
			case $1 in
			"")
				echo 1
				;;
			*)
				echo $1
				;;
			esac
			shift
			;;
		--)
			shift
			positional+=( "${@}" )
			break
			;;
		*)
			echo >&2 "ERROR: unknown $1"
			exit 1
		esac
	done
}

if [[ $(option_arg -v) != 1 ]] ||
   [[ $(option_arg -v3) != 3 ]] ||
   [[ $(option_arg -vXXX) != XXX ]] ||
   [[ $(option_arg --verbose=3) != 3 ]] ||
   [[ $(option_arg --verbose=XXX) != XXX ]]; then
	echo >&2 "ERROR: test option_arg() failed"
	exit 1
fi
