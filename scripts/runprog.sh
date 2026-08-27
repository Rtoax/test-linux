#!/bin/bash
# Running a program, this script be called in template.
#
# Copyright (C) 2025-2026 Rong Tao. All rights reserved.
#
# Usage: runprog.sh [options] -- execution [args...]
#
set -e

readonly WHERE_AM_I=$(dirname $(realpath $0))
readonly TEST_LINUX_ROOT=$(realpath ${WHERE_AM_I}/../)
readonly prog_name=runprog
declare RECORD_FILE=${TEST_LINUX_ROOT}/runprog.cmd.log
declare LOG_FILE=runprog.log
declare -a ENVS
declare verbose=
declare SUDO=
declare TMOUT=
declare REAL_RET=0 EXPECT_RET=0

. ${WHERE_AM_I}/liblog.sh

__usage__()
{
	echo -e "
runprog [OPTIONS]

OPTIONS:

-e, --env [ENV=<VAL>]  set a env (may be listed multiple times)
-T, --timeout [SEC]    set timeout seconds
--maybe-sudo           running with superuser if possible
--expect-return [RET]  expect return value, default 0

-l, --log [FILE]       set log file name
    --nolog            skipping log
    --nocmdlog         skipping cmd log file

-v, --verbose          run verbose mode
-h, --help             show this help information
" | more

	exit ${1-0}
}

GETOPT_ARGS=$(getopt \
	--options l:e:T:vh \
	--long log: \
	--long nolog \
	--long nocmdlog \
	--long timeout: \
	--long env: \
	--long help \
	--long verbose \
	--long maybe-sudo \
	--long expect-return: \
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
	--nolog)
		shift
		LOG_FILE=
		;;
	--nocmdlog)
		shift
		RECORD_FILE=
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
		__usage__ 0
		;;
	--maybe-sudo)
		shift
		if sudo --non-interactive true 2>/dev/null; then
			# Pass all ENVS to child process
			SUDO="sudo -E"
		fi
		;;
	--expect-return)
		shift
		EXPECT_RET=${1}
		if ! [[ ${EXPECT_RET} =~ ^-?[0-9]+$ ]]; then
			error "--expect-return must pass digist, got '${EXPECT_RET}'"
		fi
		shift
		;;
	--)
		shift
		break
		;;
	esac
done

SPAWN=( "${@}" )
EXEC=${SPAWN[0]}

if [[ -z ${EXEC} ]]; then
	error "Need pass execution"
fi

# If it's exist file under current directory, then, add './' prefix.
if [[ -f ${EXEC} ]] &&
   [[ "${EXEC:0:1}" != "/" ]] &&
   [[ "${EXEC:0:2}" != "./" ]] &&
   [[ "${EXEC:0:3}" != "../" ]]; then
	# If file has x permission, just add './'
	if test -x ${EXEC}; then
		SPAWN[0]="./${EXEC}"
	fi
# Otherwise, found EXEC in system env.
elif [[ $(which ${EXEC} 2>/dev/null) ]]; then
	SPAWN[0]=$(which ${EXEC})
else
	error "Not found program '${EXEC}'"
fi

First2char=$(head -c 2 ${SPAWN[0]} 2>/dev/null || true)
if [[ "${First2char}" == "#!" ]]; then
	Firstline=$(head -n 1 ${SPAWN[0]} 2>/dev/null || true)
	SHEBANG=${Firstline:2}
else
	SHEBANG=""
fi

WHOLE_CMD=""
WHOLE_CMD+="${ENVS:+env ${ENVS[@]} }"
WHOLE_CMD+="${SUDO:+${SUDO} }"
WHOLE_CMD+="${TMOUT:+timeout ${TMOUT} }"
WHOLE_CMD+="${SHEBANG:+${SHEBANG} }"
WHOLE_CMD+="${SPAWN[@]}"

if [[ ${LOG_FILE} ]]; then
	ERR_LOG_FILE=${LOG_FILE}.stderr
	if [[ ${LOG_FILE##*.} == log ]]; then
		ERR_LOG_FILE=${LOG_FILE%.*}.stderr.log
	fi
	# Store stderr and stdout logs separately
	eval "${WHOLE_CMD}" > >(tee --append ${LOG_FILE}) \
			   2> >(tee --append ${ERR_LOG_FILE} >&2) || {
		REAL_RET=$?
		true
	}
else
	eval "${WHOLE_CMD}" || {
		REAL_RET=$?
		true
	}
fi

if [[ ${REAL_RET} -ne ${EXPECT_RET} ]]; then
	[[ ${LOG_FILE} ]] && rm -f ${LOG_FILE}
	if [[ ${RECORD_FILE} ]]; then
		echo -e "Run '\033[31m${WHOLE_CMD}\033[m' failed in ${PWD}" >> ${RECORD_FILE}
	fi
	error "${@}: run failed, exit with ${REAL_RET} (expect ${EXPECT_RET})"
else
	if [[ ${RECORD_FILE} ]]; then
		echo -e "Run '\033[32m${WHOLE_CMD}\033[m' success in ${PWD}" >> ${RECORD_FILE}
	fi
fi

# If you run with sudo, then we need to reset the owner of the log file.
if [[ ${SUDO_USER} ]] && [[ ${RECORD_FILE} ]]; then
	${SUDO} chown ${SUDO_USER}:${SUDO_USER} ${RECORD_FILE}
fi
