#!/bin/bash

dir=""
declare -a indent_arg

set_dir() {
	local d=$1
	[[ ! -d ${d} ]] && echo "ERROR: $d is not directory" && exit 1
	dir=$d
}
__usage__()
{
	echo -e "
code_formatter [options]

-d, --dir  [DIR]       specify directory to check

--indent-arg           add argument to indent command for C/C++
                       (may be listed multiple times)
                       for example: --indent-arg -st

-h, --help             show this information
-v, --verbose          verbose
"
	exit ${1-0}
}

TEMP=$(getopt \
	--options d:vh \
	--long dir: \
	--long indent-arg: \
	--long verbose \
	--long help \
	-n code_formatter -- "$@")

test $? != 0 && __usage__ 1

eval set -- "$TEMP"

while true; do
	case $1 in
	-d|--dir)
		shift
		set_dir $1
		shift
		;;
	--indent-arg)
		shift
		indent_arg+=( $1 )
		shift
		;;
	-h|--help)
		shift
		__usage__
		;;
	-v|--verbose)
		shift
		export PS4='+${BASH_SOURCE}:${LINENO}:${FUNCNAME[0]}: '
		set -x
		;;
	--)
		shift
		break
		;;
	esac
done

if [[ -z ${dir} ]]; then
	echo "WARNING: Must specify directory, use current $PWD"
	dir=$PWD
fi

indent_arg+=( --linux-style )


# C/C++
find ${dir} -name '*.[ch]' -type f -exec indent ${indent_arg[@]} {} \;
find ${dir} -regextype posix-extended -regex ".*\.(cc|cxx|cpp|hpp)" -type f -exec indent ${indent_arg[@]} {} \;

# Python
find ${dir} -name '*.py' -type f -exec black {} \;
