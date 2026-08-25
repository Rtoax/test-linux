#!/bin/bash
# Syntax: `NAME[,ALIAS1,ALIAS2]: English shotcut (Chinese shotcut) @RELATE1 @RELATE2`
#
# - AB: A Ball (一个球[, RFC|IEEE])
# - ABC[,ALIAS1,ALIAS2]: A Ball Circle (一个球圈[, RFC|IEEE]) @AB
#
set -e
readonly DOC_ROOT=$(dirname $(realpath $0))
declare word check

__usage__() {
	echo -e "
Usage:
-C, --check        check instead of listing
-w, --word         match the whole word
-h, --help         show this help information
"
	exit ${1-0}
}

ARG_TEMP=$(getopt \
	--options whC \
	--long word \
	--long check \
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
	-C|--check)
		shift
		check=YES
		;;
	--)
		shift
		break
		;;
	esac
done

declare name=$1
declare -a files=( $(find ${DOC_ROOT} -name 'abbrev*.rst') )

list_all() {
	local f
	for f in ${files[@]}
	do
		# strip root prefix
		local dir=${f#${DOC_ROOT}/}
		# - Delete white lines
		# - filter '-' start lines
		# - Add filename suffix
		cat ${f} | \
			sed '/^$/d' | \
			grep '^-' | \
			sed "s|$| <${dir}>|g"
	done | sort
}

find_and_list() {
	list_all | grep -i " .*${name}.*:" ${word:+-w}
}

listing() {
	if [[ ${name} ]]; then
		find_and_list | nl
	else
		list_all | nl
	fi
}

checking() {
	local f
	for f in ${files[@]}
	do
		local not_match="$(cat ${f} | \
					grep ^- | \
					grep -v -E '^- [^:]+: [^(]+ \([^)]*\)( @[^ ]+)*$')"
		if [[ "${not_match}" ]]; then
			echo >&2 "ERROR: ${f} check failed"
			echo "${not_match}"
			exit 1
		fi
	done
}

pushd ${DOC_ROOT} 2>&1 >/dev/null
if [[ ${check} ]]; then
	checking
else
	listing
fi
popd 2>&1 >/dev/null
