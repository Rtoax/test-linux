#!/bin/bash
set -e

declare -a ALL_X_ELFs

get_all_elf() {
	while read f
	do
		read -r -N 8 bin < $f
		if [[ ${bin} == $'\x7f'ELF* ]]; then
			ALL_X_ELFs+=( $f )
		fi
	done <<< $(find . -maxdepth 1 -type f -perm -u=x)
}


[[ ${FAKECUDA_DEBUG} ]] && set -x

printf "\033[2m"
readonly FAKECUDA_ROOT=$(realpath $(dirname $(readlink $0)))
make -C ${FAKECUDA_ROOT} --no-print-directory --silent 1>/dev/null

printf "\033[m"
set +x

exec_one() {
	local PREFIX
	[[ -f $1 ]] && [[ -x $1 ]] && PREFIX=./
	LD_LIBRARY_PATH=${FAKECUDA_ROOT} "${PREFIX}$@"
}

if [[ "$1" == "ALL" ]]; then
	get_all_elf

	# skip $1, pass args to exec_one()
	shift

	for f in ${ALL_X_ELFs[@]}
	do
		exec_one $f $@
	done

	echo -e "\033[32mTEST: ${ALL_X_ELFs[@]}\033[m"
elif [[ $1 ]]; then
	exec_one $@
else
	echo >&2 "USAGE: $0 [ELF FILE] [<args>]"
	echo >&2 "USAGE: $0 ALL [<args>]"
fi
