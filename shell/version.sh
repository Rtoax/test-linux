#!/bin/bash
# This script only display BASH version, do not display other anything, because
# the git/hooks will use it.
set -e
MY_SHELL=$(which bash 2>/dev/null || :)
if [[ -z ${MY_SHELL} ]]; then
	echo >&2 "ERROR: not found bash in anywhere"
	exit 1
fi
${MY_SHELL} --version | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true
