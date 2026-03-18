#!/bin/bash
# This script only display git version, do not display other anything,
# because the git/hooks will use it.
set -e
GIT=$(which git 2>/dev/null || :)
if [[ -z ${GIT} ]]; then
	echo >&2 "ERROR: not found GIT in your system"
	exit 0
fi
${GIT} --version | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true
