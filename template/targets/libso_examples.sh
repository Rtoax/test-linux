#!/bin/bash
set -e

touch liba.so.1.1.1
./libso.sh multi-version liba.so.1.1.1
if [[ $(readlink liba.so) != liba.so.1 ]]; then
	echo >&2 "ERROR: wrong multi-version"
	exit 1
fi


libs=( $(./libso.sh multi-version-pure-name-list liba.so.1 libb.so.2 libc.so) )

if [[ "${libs[@]}" != "liba.so libb.so" ]]; then
	echo >&2 "ERROR: wrong multi-version-pure-name-list"
	exit 1
fi
