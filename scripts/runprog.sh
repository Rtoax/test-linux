#!/bin/bash
# Usage: run_prog.sh [-v|--verbose] [--maybe-sudo] LOG_FILE EXE [ARGS]

set -e

verbose=
SUDO=

error() {
	echo >&2 "ERROR: $@"
	exit 1
}

while true;
do
	case $1 in
	-v | --verbose)
		shift 1
		set -x
		verbose=YES
		;;
	--maybe-sudo)
		shift 1
		if sudo --non-interactive true 2>/dev/null; then
			SUDO=sudo
		fi
		;;
	*)
		break
		;;
	esac
done

readonly LOG_FILE=$1
shift
readonly EXE=$1
shift

${SUDO} ${EXE} $@ | tee ${LOG_FILE}
if [[ ${PIPESTATUS[0]} -ne 0 ]]; then
	rm -f ${LOG_FILE}
	error "${EXE} $@: run failed"
fi
