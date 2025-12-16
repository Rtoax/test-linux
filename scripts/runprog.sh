#!/bin/bash
# Usage: runprog.sh [options] -- EXE [ARGS]
set -e

readonly prog_name=runprog
LOG_FILE=runprog.log
declare -a ENVS
verbose=
SUDO=

error() {
	echo >&2 "ERROR: $@"
	exit 1
}

__usage__()
{
	echo -e "
-e, --env [ENV=V]      set a env (may be listed multiple times)
--maybe-sudo           running with superuser if possible

-v, --verbose          run verbose mode
-h, --help             show this help information
" | more

	exit ${1-0}
}

GETOPT_ARGS=$(getopt \
	--options l:e:vh \
	--long log: \
	--long env: \
	--long help \
	--long verbose \
	--long maybe-sudo \
	-n ${prog_name} -- "$@")

test $? != 0 && __usage__ 1

eval set -- "$GETOPT_ARGS"

while true; do
	case $1 in
	-l | --log)
		shift
		LOG_FILE=$1
		shift
		;;
	-e | --env)
		shift
		ENVS+=( ${1} )
		shift
		;;
	-v | --verbose)
		shift
		set -x
		export PS4='+${BASH_SOURCE}:${LINENO}:${FUNCNAME[0]}: '
		verbose=YES
		;;
	-h | --help)
		shift
		__usage__
		;;
	--maybe-sudo)
		shift
		if sudo --non-interactive true 2>/dev/null; then
			# Pass all ENVS to child process
			SUDO="sudo -E"
		fi
		;;
	--)
		shift
		break
		;;
	esac
done

${ENVS:+env} ${ENVS[@]} ${SUDO} ${@} | tee ${LOG_FILE}
if [[ ${PIPESTATUS[0]} -ne 0 ]]; then
	rm -f ${LOG_FILE}
	error "${@}: run failed"
fi
