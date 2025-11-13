#!/bin/bash
# Usage: run_prog.sh [-v|--verbose] LOG_FILE EXE [EXE ARGS]

set -e

verbose=

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
	*)
		break
		;;
	esac
done

readonly LOG_FILE=$1
shift
readonly EXE=$1
shift

${EXE} $@ | tee ${LOG_FILE}
if [[ ${PIPESTATUS[0]} -ne 0 ]]; then
	rm -f ${LOG_FILE}
	error "${EXE} $@: run failed"
fi
