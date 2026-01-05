#!/bin/bash
# This script only display vim version, do not display other anything,
# because the git/hooks will use it.
set -e
VIM=$(which vim 2>/dev/null || :)
if [[ -z ${VIM} ]]; then
	echo >&2 "ERROR: not found VIM in your system"
	exit 0
fi
${VIM} --version | grep -Eo '[0-9]+\.[0-9]+' 2>/dev/null || true
