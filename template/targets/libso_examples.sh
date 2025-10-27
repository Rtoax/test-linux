#!/bin/bash
set -e

touch liba.so.1.1.1
./libso.sh multi-version liba.so.1.1.1
if [[ $(readlink liba.so) != liba.so.1 ]]; then
	echo >&2 "ERROR: wrong multi-version"
	exit 1
fi

if [[ $(./libso.sh purename liba.so.1.1.1) != liba.so ]]; then
	echo >&2 "ERROR: wrong purename"
	exit 1
fi
if [[ $(./libso.sh purename liba.so) ]]; then
	echo >&2 "ERROR: wrong purename"
	exit 1
fi

if [[ "$(./libso.sh symlinks-names liba.so.1.1.1)" != "liba.so liba.so.1 liba.so.1.1" ]]; then
	echo >&2 "ERROR: wrong symlinks-names"
	exit 1
fi
