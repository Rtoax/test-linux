#!/bin/bash
# TODO

source $(dirname $(realpath $0))/libversion.sh

CMD=

version_cmd_usage()
{
	echo -e "
-C, --cmd [CMD]
" | more
	exit ${1-0}
}

TEMP=$(getopt \
	--options C: \
	--long cmd: \
	-n version-cmd -- "$@")

test $? != 0 && version_cmd_usage 1

eval set -- "$TEMP"

while true; do
	case $1 in
	-C | --cmd)
		shift
		CMD=$1
		shift
		;;
	--)
		shift
		break
		;;
	*)
		echo >&2 "ERROR: unknown ${1}"
		exit 1
		;;
	esac
done


if [[ -z ${CMD} ]]; then
	echo >&2 "ERROR: not set --cmd"
	exit 0
fi
version=$(${CMD} --version 2>&1 | \
		grep -Eo -e '[0-9]+\.[0-9]+\.[0-9]+' \
			 -e '[0-9]+\.[0-9]+' 2>/dev/null || true | \
		head -1)

version_parser ${@} -- ${version}
