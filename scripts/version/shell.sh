#!/bin/bash
# This script only display BASH version, do not display other anything, because
# the git/hooks will use it.
#
# Usage: shell.sh [--name] [--pretty-name]
set -e

MY_SHELL=${SHELL}
if [[ -z ${MY_SHELL} ]]; then
	echo >&2 "ERROR: not found shell in anywhere"
	exit 1
fi

_name=$(basename ${MY_SHELL})

if [[ $1 == --name ]]; then
	echo ${_name} | tr '[[:lower:]]' '[[:upper:]]'
elif [[ $1 == --pretty-name ]]; then
	echo ${_name^}
else
	version=$(${MY_SHELL} --version | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true)

	source $(dirname $(realpath $0))/libversion.sh

	version_parser ${@} -- ${version}
fi
