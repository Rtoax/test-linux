#!/bin/bash
# This script only display BASH version, do not display other anything, because
# the git/hooks will use it.
set -e

MY_SHELL=${SHELL}
if [[ -z ${MY_SHELL} ]]; then
	echo >&2 "ERROR: not found shell in anywhere"
	exit 1
fi

if [[ $1 == --name ]]; then
	echo $(basename ${MY_SHELL}) | tr '[[:lower:]]' '[[:upper:]]'
else
	${MY_SHELL} --version | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true
fi
