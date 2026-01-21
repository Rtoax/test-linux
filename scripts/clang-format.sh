#!/bin/bash
set -e

fatal() {
	echo >&2 -en "\033[31m"
	echo >&2 -e "FATAL: "${@}
	echo >&2 -en "\033[0m"
	exit 1
}

readonly GIT_TOPDIR=$(git rev-parse --show-toplevel 2>/dev/null || :)

# Check code format wich git-clang-format
readonly clang_format=$(which git-clang-format 2>/dev/null || :)

if  [[ -z ${clang_format} ]] && [[ -z ${FORCE1} ]]; then
	fatal "Not found git-clang-format, please install or FORCE1=1"
elif [[ -z ${FORCE1} ]]; then
	repository=$(basename ${GIT_TOPDIR})
	if [[ " ostools tools ulpatch " =~ " ${repository} " ]]; then
		branch=origin/master
	elif [[ " test-linux tst-linux " =~ " ${repository} " ]]; then
		branch=origin/main
	else
		fatal "Unknown repository '${repository}', please develop me!"
	fi
	patch="$( ${clang_format} --diff ${branch} --extensions c,cpp,cu,h,hpp | \
			grep -v 'no modified files to format' || :)"
	if [[ $? != 0 ]] || [[ "${patch}" ]]; then
		echo "${patch}"
		fatal "Bad code format, please modify according to the above diff or FORCE1=1"
	fi
fi

exit 0
