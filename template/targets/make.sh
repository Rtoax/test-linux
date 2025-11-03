#!/bin/bash
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

LOG=$1
shift
make $@ | tee ${LOG}
if [[ ${PIPESTATUS[0]} -ne 0 ]]; then
	rm -f ${LOG}
	error "make failed: make $@"
fi
