#!/bin/bash
set -e

word=

__usage__() {
	echo -e "
Usage:

-h, --help         show this help information
"
	exit ${1-0}
}

ARG_TEMP=$(getopt \
	--options wh \
	--long word \
	--long help \
	-n ${0} -- "$@")

test $? != 0 && __usage__ 1

eval set -- "$ARG_TEMP"

while true; do
	case $1 in
	-h|--help)
		shift
		__usage__
		;;
	-w|--word)
		shift
		word=YES
		;;
	--)
		shift
		break
		;;
	esac
done

name=$1
files=( $(find -name abbreviation.md) )

list_all() {
	for f in ${files[@]}
	do
		# - Delete white lines
		# - Add filename suffix
		cat ${f} | \
			sed '/^$/d' | \
			sed "s|$| <$(dirname ${f})>|g"
	done | sort | nl
}

find_name() {
	list_all | grep -i " ${name}:" ${word:+-w}
}

if [[ ${name} ]]; then
	find_name
else
	list_all
fi
