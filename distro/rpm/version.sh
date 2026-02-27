#!/bin/bash
# This script only display rpm version, do not display other anything,
# and don't execute failed, because the git/hooks will use it.
set -e
RPM=$(which rpm 2>/dev/null || :)
if [[ -z ${RPM} ]]; then
	echo >&2 "ERROR: not found RPM in your system"
	exit 0
fi
${RPM} --version | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true
