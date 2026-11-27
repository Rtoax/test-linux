#!/bin/bash
set -e

run_examples_tmux() {
	local prog=./examples-tmux.sh
	echo -e "\033[1;32m$ ${prog} ${@}\033[m"
	${prog} ${@}
}

vertical_args=( SKIP --vertical-plotting )
data_formats=( SKIP line-separator-newline line-separator-semicolon )

for ver in "${vertical_args[@]}"
do
	all_args=()
	if [[ ${ver} != SKIP ]]; then
		all_args+=( ${ver} )
	fi

	for dfmt in ${data_formats[@]}
	do
		if [[ ${dfmt} != SKIP ]]; then
			all_args+=( --stdin-data-format ${dfmt} )
		fi
		run_examples_tmux ${all_args[@]}
	done
done
