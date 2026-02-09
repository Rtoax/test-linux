#!/bin/bash

declare -a langs files counts

c_file=$(mktemp --dry-run tmp-c-XXXXXX)
cpp_file=$(mktemp --dry-run tmp-cpp-XXXXXX)
go_file=$(mktemp --dry-run tmp-go-XXXXXX)
java_file=$(mktemp --dry-run tmp-java-XXXXXX)
python_file=$(mktemp --dry-run tmp-python-XXXXXX)
shell_file=$(mktemp --dry-run tmp-sh-XXXXXX)

langs=( C C++ Golang Java Python Shell )
files=( $c_file $cpp_file $go_file $java_file $python_file $shell_file )

dir=""

set_dir() {
	local d=$1
	[[ ! -d ${d} ]] && echo "ERROR: $d is not directory" && exit 1
	dir=$d
}
__usage__()
{
	echo -e "
code_count [options]

-d, --dir  [DIR]       specify directory to check

-h, --help             show this information
-v, --verbose          verbose
"
	exit ${1-0}
}

TEMP=$(getopt \
	--options d:vh \
	--long dir: \
	--long verbose \
	--long help \
	-n code_count -- "$@")

test $? != 0 && __usage__ 1

eval set -- "$TEMP"

while true; do
	case $1 in
	-d|--dir)
		shift
		set_dir $1
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


find ${dir} -name '*.[ch]' -type f -exec wc -l {} + > $c_file
# or: find ${dir} -regex ".*\.cc\|.*\.cpp" -type f -exec wc -l {} + > $cpp_file
find ${dir} -regextype posix-extended -regex ".*\.(cc|cxx|cpp|hpp)" -type f -exec wc -l {} + > $cpp_file
find ${dir} -name '*.go' -type f -exec wc -l {} + > $go_file
find ${dir} -name '*.java' -type f -exec wc -l {} + > $java_file
find ${dir} -name '*.py' -type f -exec wc -l {} + > $python_file
find ${dir} -regextype posix-extended -regex ".*\.(sh|bash|zsh)" -type f -exec wc -l {} + > $shell_file

print_count() {
	local f=$1
	local count=( $((grep total$ ${f} 2>/dev/null || true) | awk '{print $1}' 2>/dev/null) )

	if [[ "$count" ]]; then
		local sum=0
		for c in ${count[@]}
		do
			sum=$( expr $sum + $c )
		done
		echo $sum
	else
		echo 0
	fi
}

orig() {
	printf "%-8s %-16s\n"	C	$(print_count $c_file)
	printf "%-8s %-16s\n"	C++	$(print_count $cpp_file)
	printf "%-8s %-16s\n"	Java	$(print_count $java_file)
	printf "%-8s %-16s\n"	Golang	$(print_count $go_file)
	printf "%-8s %-16s\n"	Python	$(print_count $python_file)
}

for f in ${files[@]}
do
	counts+=( $(print_count $f) )
done

sum=
for c in ${counts[@]}
do
	sum=$(expr $sum + $c)
done

for ((i = 0; i < ${#langs[@]}; i++))
do
	printf "%-8s %-16s\n" ${langs[$i]} ${counts[$i]}
done
printf "%-8s %-16s\n" Total $sum

rm -f ${files[@]}
