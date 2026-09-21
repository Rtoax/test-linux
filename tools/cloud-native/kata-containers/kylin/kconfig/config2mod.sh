#!/bin/bash
set -e

if ! [[ $1 ]] || ! [[ $2 ]]; then
	echo >&2 "Usage: $0 [linux-code-tree-root] [config]"
	exit 1
fi

linux_root=$1
configs=( $(awk '{print $1}' $2 | grep ^CONFIG) )

config2mod() {

	pushd ${linux_root}

	for c in ${configs[@]}
	do
		obj=$(grep -w $c $(find -name Makefile) | grep .o$ | \
			grep obj- | awk '{print $NF}' || :)
		if [[ -z ${obj} ]]; then
			printf "%s\n" $c
		else
			mod=${obj%.*}
			printf "%s\t%s\n" $c $mod
		fi
	done

	popd
}

config2mod
