#!/bin/bash
# Running a program, this script be called in template.
#
# Copyright (C) 2025-2026 Rong Tao
#
# Usage: runprog.sh [options] -- EXEC [EXEC ARGS...]
#
set -e

readonly WHERE_AM_I=$(dirname $(realpath $0))
readonly TEST_LINUX_ROOT=$(realpath ${WHERE_AM_I}/../)
readonly LOG_CMD_FILE=${TEST_LINUX_ROOT}/runprog.cmd.log
readonly prog_name=runprog
LOG_FILE=runprog.log
declare -a ENVS
verbose=
SUDO=
TMOUT=

. ${WHERE_AM_I}/liblog.sh

__usage__()
{
	echo -e "
-e, --env [ENV=<VAL>]  set a env (may be listed multiple times)
-T, --timeout [SEC]    set timeout seconds
--maybe-sudo           running with superuser if possible

-l, --log [FILE]       set log file name

-v, --verbose          run verbose mode
-h, --help             show this help information
" | more

	exit ${1-0}
}

GETOPT_ARGS=$(getopt \
	--options l:e:T:vh \
	--long log: \
	--long timeout: \
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
	-T | --timeout)
		shift
		TMOUT=$1
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

LEFT_ARGS=( "${@}" )
EXEC=${LEFT_ARGS[0]}

# If not found EXEC in system env, and it's exist file under current directory,
# add './' prefix.
if [[ -f ${EXEC} ]] && [[ "${EXEC:0:1}" != "/" ]] && \
   [[ "${EXEC:0:2}" != "./" ]] && [[ "${EXEC:0:3}" != "../" ]] && \
   [[ ! $(which ${EXEC} 2>/dev/null) ]]; then
	LEFT_ARGS[0]="./${EXEC}"
fi

readonly CMD="${ENVS:+env} ${ENVS[@]} ${SUDO} ${TMOUT:+timeout ${TMOUT}} ${LEFT_ARGS[@]}"

eval "${CMD}" | tee ${LOG_FILE}
if [[ ${PIPESTATUS[0]} -ne 0 ]]; then
	rm -f ${LOG_FILE}
	echo -e "Failed: '\033[31m${CMD}\033[m', in ${PWD}" >> ${LOG_CMD_FILE}
	error "${@}: run failed"
else
	echo -e "Succes: '\033[32m${CMD}\033[m', in ${PWD}" >> ${LOG_CMD_FILE}
fi
